/*
 * dFont.cpp
 *
 *  Created on: 10/01/2014
 *      Author: Douglas
 *
 *   Copyright: Staff 42 © 2013
 */

#include <data/dFont.h>

#include <base/bLog.h>

#include <thread>
#include <mutex>

#include <sstream>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

#include <map>

namespace cb {
	namespace data {
		KinKey(FontFace, FT_FaceRec_);

		std::mutex _ftError_guard;
		string ftError(FT_Error ierror_id) {
			std::lock_guard<std::mutex> lock(_ftError_guard);

			std::map<FT_Error, string> error_strings;
			if(error_strings.empty()) {
#				undef __FTERRORS_H__
#				define FT_ERRORDEF( e, v, s )  error_strings[v] = s;
#				define FT_ERROR_START_LIST
#				define FT_ERROR_END_LIST

#				include FT_ERRORS_H
			}

			std::map<FT_Error, string>::iterator it = error_strings.find(ierror_id);
			if(it != error_strings.end()) {
				return it->second;
			} else {
				return "unknown";
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
					string thread_id_string = oss.str();

					throw DataException(base::print("data::Font::getLibrary() : Não foi possivel inicializar a biblioteca FreeType para a thread %s. Erro: '%s'.", thread_id_string.c_str(), ftError(error).c_str()));
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

		Font::Font(string ifilename)
		:_border(0), _size(0), _border_inner(false), _border_outer(false){
			open(ifilename);
		}

		Font::~Font() {
			if(isOpen()) {
				close();
			}
		}

		int Font::fontUnitsToPixelsX(int ifux) {
			FT_Face face = &_face;
			return ifux * (face->size->metrics.x_ppem / float(face->units_per_EM));
		}

		int Font::fontUnitsToPixelsY(int ifuy) {
			FT_Face face = &_face;
			return ifuy * (face->size->metrics.y_ppem / float(face->units_per_EM));
		}

		int Font::pixelsToFontUnitsX(int ipxx) {
			FT_Face face = &_face;
			return ipxx * (float(face->units_per_EM) / face->size->metrics.x_ppem);
		}

		int Font::pixelsToFontUnitsY(int ipxy) {
			FT_Face face = &_face;
			return ipxy * (float(face->units_per_EM) / face->size->metrics.y_ppem);
		}

		int Font::height() {
			return (*_face).size->metrics.height >> 6;
		}
		int Font::underlineY() {
			if(FT_IS_SCALABLE((&_face))) {
				return fontUnitsToPixelsY((*_face).underline_position);
			} else {
				return -2;
			}
		}
		int Font::underlineThickness() {
			if(FT_IS_SCALABLE((&_face))) {
				int thickness = fontUnitsToPixelsY((*_face).underline_thickness);
				return thickness>0?thickness:1;
			} else {
				return 1;
			}
		}

		void Font::size(float isize) {
			_size = isize;
			FT_Error error = FT_Set_Char_Size(&_face, 0, _size*64, 96, 96);
			if(error) {
				ThrowDataException(print("Não foi possivel mudar o tamanho da fonte. Erro: '%s'.", ftError(error).c_str()).c_str());
			}
		}

		size_t Font::glyphId(size_t ichar) {
			return FT_Get_Char_Index(&_face, ichar);
		}

		void Font::glyph(Glyph &oglyph, size_t iid) {
			FT_Error error;
			error = FT_Load_Glyph(&_face, iid, FT_LOAD_DEFAULT);
			if(error) {
				ThrowDataException(print("Não foi possivel carregar o Glyph. Erro: '%s'.", ftError(error).c_str()).c_str());
			}

			FT_Bitmap *bitmap;
			FT_Glyph glyph;

			if(_border_outer || _border_inner) {
				FT_Vector origin = {0, 0};

				FT_Stroker stroker;
				error = FT_Stroker_New(ftLibrary(), &stroker);
				if(error) {
					ThrowDataException(print("Não foi possivel criar um stroker. Erro: '%s'.", ftError(error).c_str()).c_str());
				}

				FT_Stroker_Set(stroker, _border * 64, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);

				error = FT_Get_Glyph((&_face)->glyph, &glyph);
				if(error) {
					ThrowDataException(print("Não foi possivel carregar o Glyph. Erro: '%s'.", ftError(error).c_str()).c_str());
				}

				if(_border_inner) {
					error = FT_Glyph_StrokeBorder(&glyph, stroker, _border_outer?0:1, 1);
					if(error) {
						ThrowDataException(print("Não foi possivel carregar o Glyph. Erro: '%s'.", ftError(error).c_str()).c_str());
					}
				} else {
					error = FT_Glyph_Stroke(&glyph, stroker, 1);
					if(error) {
						ThrowDataException(print("Não foi possivel carregar o Glyph. Erro: '%s'.", ftError(error).c_str()).c_str());
					}
				}

				error = FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, &origin, 1);
				if(error) {
					ThrowDataException(print("Não foi possivel carregar o Glyph. Erro: '%s'.", ftError(error).c_str()).c_str());
				}

				bitmap = &((FT_BitmapGlyph)glyph)->bitmap;

				FT_Stroker_Done(stroker);
			} else {
				error = FT_Render_Glyph((&_face)->glyph, FT_RENDER_MODE_NORMAL);
				if(error) {
					ThrowDataException(print("Não foi possivel desenhar o Glyph. Erro: '%s'.", ftError(error).c_str()).c_str());
				}

				bitmap = &(&_face)->glyph->bitmap;
			}

			oglyph.clear();

			oglyph._id = iid;

			oglyph._width = bitmap->width;
			oglyph._height = bitmap->rows;

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

			if(oglyph._width * oglyph._height) {
				oglyph._data = new math::uint8[oglyph._width * oglyph._height];
				for(size_t r=0 ; r<oglyph._height ; r++) {
					for(size_t i=0 ; i<oglyph._width ; i++) {
						oglyph._data[r*oglyph._width + i] = bitmap->buffer[(oglyph._height - r - 1)*bitmap->pitch + i];
					}
				}
			}

			if(_border_outer || _border_inner) {
				FT_Done_Glyph(glyph);
			}
		}

		void Font::glyphs(Glyph *oglyphs, size_t *iids, size_t in) {
			for(size_t i=0 ; i<in ; i++) {
				glyph(oglyphs[i], iids[i]);
			}
		}

		void Font::open(string ifilename) {
			close();

			FT_Library library = ftLibrary();
			FT_Face face;

			FT_Error error = FT_New_Face(library, ifilename.c_str(), 0, &face);
			if(error) {
				ThrowDataException(print("Não foi possivel abrir o arquivo de fonte: '%s'. Erro: '%s'.", ifilename.c_str(), ftError(error).c_str()).c_str());
			}
			_face << face;

			error = FT_Select_Charmap(&_face, FT_ENCODING_UNICODE);
			if(error) {
				ThrowDataException(print("Não foi possivel selecionar a codificação Unicode para a fonte. Erro: '%s'.", ftError(error).c_str()).c_str());
			}

			size(_size);
		}

		void Font::close() {
			FT_Done_Face(&_face);
			_face << NULL;
		}

		bool Font::isOpen() {
			return !_face.empty();
		}
	}  // namespace data
}  // namespace cb
