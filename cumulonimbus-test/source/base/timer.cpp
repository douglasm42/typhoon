/*
 * - Cumulonimbus - ☁
 * File: base/test.cpp
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
#include <UnitTest.h>

#include <cb/base/Timer.hpp>
#include <cb/base/String.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace cb;

namespace cumulonimbustest
{
	TEST_CLASS(timer) {
	public:
		TEST_METHOD(BaseTimerConstructor) {
			base::Timer t;
			Assert::AreEqual(t.delta(), 0.0f, L"Valor errado para delta.", LINE_INFO());
		}

		TEST_METHOD(BaseTimerSleepAndTick) {
			const float seconds = 2.0f;
			base::Timer t;
			base::Timer::sleep(seconds);
			t.tick();
			Assert::IsTrue(t.delta() > seconds, L"Delta depois do sleep esté menor que o tempo de sleep.", LINE_INFO());
		}
	};
}
