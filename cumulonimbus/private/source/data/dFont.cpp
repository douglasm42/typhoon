/* 
 * - Cumulonimbus - ☁
 * File: dFont.cpp
 * 
 * Licence:
 * ============================================================================
 * Copyright (C) Staff 42 Entertainment LTDA ME - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * 
 * Written by Douglas Machado de Freitas <douglas@staff42.com>, May 2014
 * ============================================================================
 */
#include <data/Font.h>

#include <base/Log.h>
#include <base/Exception.h>

#include <thread>
#include <mutex>

#include <sstream>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

#include <map>

namespace cb {
	namespace data {
		KinKey(kin::FontFace, FT_FaceRec_);

		std::mutex _ftError_guard;
		const char *ftError(FT_Error ierror_id) {
			std::lock_guard<std::mutex> lock(_ftError_guard);

			std::map<FT_Error, base::string> error_strings;
			if(error_strings.empty()) {
#				undef __FTERRORS_H__
#				define FT_ERRORDEF( e, v, s )  error_strings[v] = s;
#				define FT_ERROR_START_LIST
#				define FT_ERROR_END_LIST

#				include FT_ERRORS_H
			}

			std::map<FT_Error, base::string>::iterator it = error_strings.find(ierror_id);
			if(it != error_strings.end()) {
				return it->second.c_str();
			} else {
				return "Unknown";
			}
		}

		std::map<std::thread::id, FT_Library> _libraries;

		void freeLibraries() {
			std::map<std::thread::id, FT_Library>::iterator it;
			for(it=_libraries.begin() ; it!=_libraries.end() ; it++) {
				FT_Done_FreeType(it->second);
			}
			_libraries.clear();
		}

		std::mutex _getLibrary_guard;
		FT_Library ftLibrary() {
			std::lock_guard<std::mutex> lock(_getLibrary_guard);

			std::thread::id thread_id = std::this_thread::get_id();

			std::map<std::thread::id, FT_Library>::iterator it = _libraries.find(thread_id);

			if(it == _libraries.end()) {
				FT_Library library;
				FT_Error error;
				error = FT_Init_FreeType(&library);
				if(error) {
					if(_libraries.empty()) {
						atexit(freeLibraries);
					}

					std::ostringstream oss;
					oss << thread_id;
					base::string thread_id_string = oss.str();

					ThrowDet(tokurei::InitError, "Error: %s on thread: %s", ftError(error), thread_id_string.c_str());
				}

				_libraries[thread_id] = library;
				return library;
			} else {
				return it->second;
			}
		}

		Font::Font()
		:_border(0), _size(0), _border_inner(false), _border_outer(false){
		}

		Font::Font(const base::string &ifilename)
		:_border(0), _size(0), _border_inner(false), _border_outer(false){
			open(ifilename);
		}

		Font::Font(istream &ifile)
		:_border(0), _size(0), _border_inner(false), _border_outer(false){
			open(ifile);
		}

		Font::Font(MFile &ifile)
		:_border(0), _size(0), _border_inner(false), _border_outer(false){
			open(ifile);
		}

		Font::~Font() {
			close();
		}

		int Font::fontUnitsToPixelsX(int ifux) {
			Assert(isOpen(), tokurei::EmptyObject);
			FT_Face face = &_face;
			return int(ifux * (face->size->metrics.x_ppem / float(face->units_per_EM)));
		}

		int Font::fontUnitsToPixelsY(int ifuy) {
			Assert(isOpen(), tokurei::EmptyObject);
			FT_Face face = &_face;
			return int(ifuy * (face->size->metrics.y_ppem / float(face->units_per_EM)));
		}

		int Font::pixelsToFontUnitsX(int ipxx) {
			Assert(isOpen(), tokurei::EmptyObject);
			FT_Face face = &_face;
			return int(ipxx * (float(face->units_per_EM) / face->size->metrics.x_ppem));
		}

		int Font::pixelsToFontUnitsY(int ipxy) {
			Assert(isOpen(), tokurei::EmptyObject);
			FT_Face face = &_face;
			return int(ipxy * (float(face->units_per_EM) / face->size->metrics.y_ppem));
		}

		int Font::height() {
			Assert(isOpen(), tokurei::EmptyObject);
			return (*_face).size->metrics.height >> 6;
		}
		int Font::underlineY() {
			Assert(isOpen(), tokurei::EmptyObject);
			if(FT_IS_SCALABLE((&_face))) {
				return fontUnitsToPixelsY((*_face).underline_position);
			} else {
				return -2;
			}
		}
		int Font::underlineThickness() {
			Assert(isOpen(), tokurei::EmptyObject);
			if(FT_IS_SCALABLE((&_face))) {
				int thickness = fontUnitsToPixelsY((*_face).underline_thickness);
				return thickness>0?thickness:1;
			} else {
				return 1;
			}
		}

		void Font::size(float isize) {
			Assert(isOpen(), tokurei::EmptyObject);
			_size = isize;
			FT_Error error = FT_Set_Char_Size(&_face, 0, FT_F26Dot6(_size * 64), 96, 96);
			if(error) {
				ThrowDet(tokurei::SetFailed, "Error: %s", ftError(error));
			}
		}

		size_t Font::glyphId(size_t ichar) {
			Assert(isOpen(), tokurei::EmptyObject);
			return FT_Get_Char_Index(&_face, (FT_ULong)ichar);
		}

		void Font::glyph(Glyph &oglyph, size_t iid) {
			Assert(isOpen(), tokurei::EmptyObject);
			FT_Error error;
			error = FT_Load_Glyph(&_face, (FT_UInt)iid, FT_LOAD_DEFAULT);
			if(error) {
				ThrowDet(tokurei::GetFailed, "Error: %s", ftError(error));
			}

			FT_Bitmap *bitmap;
			FT_Glyph glyph;

			if(_border_outer || _border_inner) {
				FT_Vector origin = {0, 0};

				FT_Stroker stroker;
				error = FT_Stroker_New(ftLibrary(), &stroker);
				if(error) {
					ThrowDet(tokurei::GetFailed, "Error: %s", ftError(error));
				}

				FT_Stroker_Set(stroker, FT_Fixed(_border) * 64, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);

				error = FT_Get_Glyph((&_face)->glyph, &glyph);
				if(error) {
					ThrowDet(tokurei::GetFailed, "Error: %s", ftError(error));
				}

				if(_border_inner) {
					error = FT_Glyph_StrokeBorder(&glyph, stroker, _border_outer?0:1, 1);
					if(error) {
						ThrowDet(tokurei::GetFailed, "Error: %s", ftError(error));
					}
				} else {
					error = FT_Glyph_Stroke(&glyph, stroker, 1);
					if(error) {
						ThrowDet(tokurei::GetFailed, "Error: %s", ftError(error));
					}
				}

				error = FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, &origin, 1);
				if(error) {
					ThrowDet(tokurei::GetFailed, "Error: %s", ftError(error));
				}

				bitmap = &((FT_BitmapGlyph)glyph)->bitmap;

				FT_Stroker_Done(stroker);
			} else {
				error = FT_Render_Glyph((&_face)->glyph, FT_RENDER_MODE_NORMAL);
				if(error) {
					ThrowDet(tokurei::GetFailed, "Error: %s", ftError(error));
				}

				bitmap = &(&_face)->glyph->bitmap;
			}

			oglyph._id = iid;

			if(FT_HAS_HORIZONTAL((&_face))) {
				oglyph._h_offset_x = (&_face)->glyph->metrics.horiBearingX >> 6;
				oglyph._h_offset_y = (&_face)->glyph->metrics.horiBearingY >> 6;
				oglyph._h_advance = (&_face)->glyph->metrics.horiAdvance >> 6;
			}

			if(FT_HAS_VERTICAL((&_face))) {
				oglyph._v_offset_x = (&_face)->glyph->metrics.vertBearingX >> 6;
				oglyph._v_offset_y = (&_face)->glyph->metrics.vertBearingY >> 6;
				oglyph._v_advance = (&_face)->glyph->metrics.vertAdvance >> 6;
			}

			if(bitmap->width * bitmap->rows) {
				oglyph._bitmap.load(bitmap->width, bitmap->rows);
				size_t height = oglyph._bitmap.height();

				for(int r=0 ; r<bitmap->rows ; r++) {
					math::uint8 *scanline = oglyph._bitmap.row(r);

					for(int i=0 ; i<bitmap->width ; i++) {
						scanline[i] = bitmap->buffer[(height - r - 1)*bitmap->pitch + i];
					}
				}
			}

			if(_border_outer || _border_inner) {
				FT_Done_Glyph(glyph);
			}
		}

		void Font::glyphs(Glyph *oglyphs, size_t *iids, size_t in) {
			Assert(isOpen(), tokurei::EmptyObject);
			for(size_t i=0 ; i<in ; i++) {
				glyph(oglyphs[i], iids[i]);
			}
		}

		void Font::open(const base::string &ifilename) {
			iFile file(ifilename);
			if(file.isOpen()) {
				open(file);
			} else {
				ThrowDet(tokurei::OpenError, "Filename: %s", ifilename.c_str());
			}
		}

		void Font::open(istream &ifile) {
			ifile.seekg(0, std::ios::end);
			std::streamoff s = ifile.tellg();

			ifile.seekg(0, std::ios::beg);

			char *d = new char[(size_t)s];
			ifile.read(d, (size_t)s);

			close();

			FT_Library library = ftLibrary();
			FT_Face face;

			FT_Error error = FT_New_Memory_Face(library, (const unsigned char *)d, (FT_Long)s, 0, &face);

			delete [] d;

			if(error) {
				ThrowDet(tokurei::OpenError, "Error: %s", ftError(error));
			}
			_face << face;

			error = FT_Select_Charmap(&_face, FT_ENCODING_UNICODE);
			if(error) {
				close();
				ThrowDet(tokurei::OpenError, "Error: %s", ftError(error));
			}

			size(_size);
		}

		void Font::open(MFile &ifile) {
			close();

			FT_Library library = ftLibrary();
			FT_Face face;

			FT_Error error = FT_New_Memory_Face(library, (const unsigned char *)ifile.data(), (FT_Long)ifile.size(), 0, &face);
			if(error) {
				close();
				ThrowDet(tokurei::OpenError, "Error: %s", ftError(error));
			}
			_face << face;

			error = FT_Select_Charmap(&_face, FT_ENCODING_UNICODE);
			if(error) {
				ThrowDet(tokurei::OpenError, "Error: %s", ftError(error));
			}

			size(_size);
		}

		void Font::close() {
			if(isOpen()) {
				FT_Done_Face(&_face);
				_face << NULL;
			}
		}

		bool Font::isOpen() {
			return !_face.empty();
		}
	}  // namespace data
}  // namespace cb
