/*
 * bTimer.h
 *
 *  Created on: 13/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */
#pragma once

#include <base/base.h>

namespace cb {
	namespace base {
		KinLock(TimerTimePoint);

		/**
		 * Classe para ser usada na medição do tempo. Ela marca a diferença de tempo
		 * entre as duas últimas atualizações e também pode paralizar a thread.
		 */
		class CbAPI Timer {
		private:
			///Momento em que o timer foi atualizado pela última vez.
			kin::TimerTimePoint _before;
			///Diferença de tempo entre as duas últimas atualizações do timer.
			float _delta;

		public:
			///Inicializa o objeto e atualiza o timer.
			Timer();
			///Finaliza o objeto.
			~Timer();

			/**
			 * Paraliza a thread pela quantidade de tempo passada por parametro.
			 * @param iseconds Quantidade de segundos da paralização.
			 */
			static void sleep(float iseconds);

			/**
			 * Obtém a diferença de tempo entre as duas últimas atualizações.
			 * @return Diferença de tempo entre as duas últimas atualizações.
			 */
			inline float delta() {return _delta;}

			///Atualiza o timer.
			void update();
		};
	}  // namespace base
}  // namespace cb
