/*
 * bRandom.cpp
 *
 *  Created on: 19/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */

#include <base/Random.h>

#include <base/Log.h>

#include <random>

namespace cb {
	namespace base {

		typedef std::mersenne_twister_engine< uint32_t, 32, 351, 175, 19, 0xccab8ee7, 11, 0xffffffff, 7, 0x31b6ab00, 15, 0xffe50000, 17, 1812433253 > mt11213b;

		seed::seed() {
		}

		seed::seed(const seed &iseed) {
			_seed = iseed._seed;
		}

		seed::seed(unsigned int iseed) {
			_seed.clear();
			_seed.push_back(iseed);
		}
		seed::seed(unsigned int ivseed[], size_t in) {
			_seed.clear();
			_seed.insert(_seed.begin(), ivseed, ivseed+in);
		}
		seed::seed(unsigned int iseed1, unsigned int iseed2) {
			_seed.clear();
			_seed.push_back(iseed1);
			_seed.push_back(iseed2);
		}
		seed::seed(unsigned int iseed1, unsigned int iseed2, unsigned int iseed3) {
			_seed.clear();
			_seed.push_back(iseed1);
			_seed.push_back(iseed2);
			_seed.push_back(iseed3);
		}
		seed::seed(unsigned int iseed1, unsigned int iseed2, unsigned int iseed3, unsigned int iseed4) {
			_seed.clear();
			_seed.push_back(iseed1);
			_seed.push_back(iseed2);
			_seed.push_back(iseed3);
			_seed.push_back(iseed4);
		}

		seed::seed(string iseed) {
			_seed.clear();
			_seed.push_back(hash(iseed));
		}
		seed::seed(string ivseed[], size_t in) {
			_seed.clear();
			for(unsigned int i=0 ; i<in ; i++) {
				_seed.push_back(hash(ivseed[i]));
			}
		}
		seed::seed(string iseed1, string iseed2) {
			_seed.clear();
			_seed.push_back(hash(iseed1));
			_seed.push_back(hash(iseed2));
		}
		seed::seed(string iseed1, string iseed2, string iseed3) {
			_seed.clear();
			_seed.push_back(hash(iseed1));
			_seed.push_back(hash(iseed2));
			_seed.push_back(hash(iseed3));
		}
		seed::seed(string iseed1, string iseed2, string iseed3, string iseed4) {
			_seed.clear();
			_seed.push_back(hash(iseed1));
			_seed.push_back(hash(iseed2));
			_seed.push_back(hash(iseed3));
			_seed.push_back(hash(iseed4));
		}

		seed::~seed() {
		}

		seed_seq seed::seq() {
			return seed_seq(_seed.begin(), _seed.end());
		}

		unsigned int &seed::operator[](size_t in) {
			return _seed[in];
		}

		const unsigned int &seed::operator[](size_t in) const {
			return _seed[in];
		}

		void seed::add(unsigned int iseed) {
			_seed.push_back(iseed);
		}

		void seed::add(string iseed) {
			_seed.push_back(hash(iseed));
		}

		void seed::rem(size_t in) {
			_seed.erase(_seed.begin()+in);
		}

		size_t seed::size() const {
			return _seed.size();
		}

		void seed::resize(size_t in) {
			_seed.resize(in);
		}

		void seed::clear() {
			_seed.clear();
		}
	}  // namespace base
}  // namespace cb
