/* 
 * - Cumulonimbus - ☁
 * File: Mouse.h
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

#include <input/input.h>

#include <win32/video/Windows.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace cb {
	namespace input {
		class CbAPI DirectInput {
		private:
			static LPDIRECTINPUT8 _direct_input;
			static size_t _device_count;

		public:
			static void reg();
			static void unreg();
			static LPDIRECTINPUT8 directinput() {return _direct_input;}
		};

		/**
			* Classe responsavel por tentar simplificar esse monstro que a Microsoft chama de DirectInput.
			*
			* @author Douglas M. Freitas
			*/
		class CbAPI DIDevice {
		private:
			///Ponteiro para a instância do dispositivo de entrada DirectInput.
			LPDIRECTINPUTDEVICE8 _device;

			///Tamanho do buffer de eventos do dispositivo.
			DWORD _buffer_size;

		public:
			/**
				* Inicializa o dispositivo de acordo com os parametros passados.
				* O nivel cooperativo de todos os dispositivos criados sempre será DISCL_NONEXCLUSIVE | DISCL_FOREGROUND.
				*
				* @param[in] iwindow Handler da janela pela qual o dispositivo deverá enviar a entrada.
				* @param[in] idirectinput Instância do DirectInput a ser utilizada para a criação do dispositivo.
				* @param[in] iguid Tipo do dispositivo a ser usado na criação.
				* @param[in] idataformat Formato da entrada do dispositivo.
				*/
			DIDevice(HWND iwindow, REFGUID iguid, LPCDIDATAFORMAT idataformat);

			///Finaliza o dispositivo.
			~DIDevice();

			/**
				* Modifica o tamanho do buffer de eventos.
				*
				* @param[in] isize Novo tamanho do buffer de eventos.
				*/
			void bufferSize(DWORD isize);

			/**
				* Obtém o tamanho do buffer de eventos.
				*
				* @return Tamanho do buffer de eventos.
				*/
			DWORD bufferSize() const {return _buffer_size;}

			/**
				* Obtém e esvazia o buffer de eventos do dispositivo.
				*
				* @param[out] odata Endereço de um ponteiro para DIDEVICEOBJECTDATA.
				* @return Retorna a quantidade de eventos e em odata um vetor contendo os eventos.
				*/
			DWORD data(DIDEVICEOBJECTDATA **odata);

			/**
				* Modifica uma propriedade do tipo DWORD do dispositivo.
				*
				* @param[in] iprop Propriedade a ser alterada.
				* @param[in] iobj Objeto a ser alterado.
				* @param[in] ihow Escopo da propriedade.
				* @param[in] idata Novo valor da propriedade.
				*/
			void property(REFGUID iprop, DWORD iobj, DWORD ihow, DWORD idata);

			/**
				* Obtém o valor de uma propriedade do dispositivo.
				*
				* @param[in] iprop Propriedade a ser obtida.
				* @param[in] iobj Objeto relacionado a propriedade.
				* @param[in] ihow Escopo da propriedade.
				* @return Valor da propriedade.
				*/
			UINT_PTR property(REFGUID iprop, DWORD iobj, DWORD ihow) const;
		};
	}  // namespace input
}  // namespace cb
