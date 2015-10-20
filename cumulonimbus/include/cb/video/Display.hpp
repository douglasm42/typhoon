/* 
 * - Cumulonimbus - ☁
 * File: Display.h
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
#pragma once

#include <cb/video/video.hpp>

#include <cb/math/math.hpp>

#include <vector>

namespace cb {
	namespace video {
		class Display {
		public:
			/**
				* Classe responsavel por simplificar a obtenção das resoluções do monitor e alterar a resolução dele.
				* Para utiliza-la não é necessário instanciar um objeto.
				*/
			class Mode {
			private:
				uint32 _width;
				uint32 _height;

			public:
				Mode():_width(0), _height(0) {}
				Mode(uint32 iwidth, uint32 iheight):_width(iwidth), _height(iheight) {}
				Mode(const Mode &dm):_width(dm._width), _height(dm._height) {}

				uint32 width() const {return this->_width;}
				uint32 height() const {return this->_height;}

				Mode &operator=(const Mode &b) {
					this->_width = b._width;
					this->_height = b._height;
					return *this;
				}

				bool operator<(const Mode &b) const {return (_width > b._width) || (_width == b._width && _height > b._height);}
			};

			/**
				* Muda a resolução da tela de acordo com o modo passado por parametro.
				*
				* @param[in] idisplay_mode Resolução escolhida.
				*/
			static void activate(Mode idisplay_mode);

			/**
				* Restaura a resolução padrão da area de trabalho.
				*/
			static void reset();

			/**
				* Obtém a resolução atual da tela.
				* @return Resolução atual da tela.
				*/
			static Mode getActiveMode();

			/**
				* Obtém a resolução padrão da area de trabalho.
				* @return Resolução padrão da area de trabalho.
				*/
			static Mode getDefaultMode();

			/**
				* Obtém um vetor com todas as resoluções disponiveis.
				* @param[out] odisplay_modes_array Referência de um vetor que deve ser preenchido com as resoluções.
				*/
			static void getModes(std::vector<Mode> &odisplay_modes_array);
		};
	}  // namespace video
}  // namespace cb
