/* 
 * - Cumulonimbus - ☁
 * File: Timer.h
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

#include <base/base.h>

#include <chrono>
#include <thread>

namespace cb {
	namespace base {
		/**
		 * Classe para ser usada na medição do tempo. Ela marca a diferença de tempo
		 * entre as duas últimas atualizações e também pode paralizar a thread.
		 */
		class CbAPI Timer {
		private:
			typedef std::chrono::steady_clock::time_point time_point;

			///Momento em que o timer foi atualizado pela última vez.
			time_point _before;
			///Diferença de tempo entre as duas últimas atualizações do timer.
			float _delta;

		public:
			///Inicializa o objeto e atualiza o timer.
			Timer() {tick(); _delta = 0.0f;}
			///Finaliza o objeto.
			~Timer() {}

			/**
			 * Paraliza a thread pela quantidade de tempo passada por parametro.
			 * @param iseconds Quantidade de segundos da paralização.
			 */
			inline static void sleep(float iseconds) {
				std::this_thread::sleep_for(std::chrono::microseconds((int)(iseconds*1000000)));
			}

			/**
			 * Obtém a diferença de tempo entre as duas últimas atualizações.
			 * @return Diferença de tempo entre as duas últimas atualizações.
			 */
			inline float delta() {return _delta;}

			///Atualiza o timer.
			inline void tick() {
				time_point now = std::chrono::steady_clock::now();
				std::chrono::duration<float> sec = now - _before;

				_delta = sec.count();
				_before = now;
			}
		};
	}  // namespace base
}  // namespace cb
