/*
 * bRandom.cpp
 *
 *  Created on: 19/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */

#include <base/bRandom.h>

#include <base/bLog.h>

#include <random>

namespace cb {
	namespace base {

		//<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>
		//<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>

		typedef std::mersenne_twister_engine< uint32_t, 32, 351, 175, 19, 0xccab8ee7, 11, 0xffffffff, 7, 0x31b6ab00, 15, 0xffe50000, 17, 1812433253 > mt11213b;

		KinKey(RandomGenerator, mt11213b);

		KinKey(RandomDistUniformInt, std::uniform_int_distribution<int>);
		KinKey(RandomDistUniformFloat, std::uniform_real_distribution<float>);

		Random::Seed::Seed() {
		}

		Random::Seed::Seed(const Seed &iseed) {
			_seed = iseed._seed;
		}

		Random::Seed::Seed(unsigned int iseed) {
			_seed.clear();
			_seed.push_back(iseed);
		}
		Random::Seed::Seed(unsigned int ivseed[], size_t in) {
			_seed.clear();
			_seed.insert(_seed.begin(), ivseed, ivseed+in);
		}
		Random::Seed::Seed(unsigned int iseed1, unsigned int iseed2) {
			_seed.clear();
			_seed.push_back(iseed1);
			_seed.push_back(iseed2);
		}
		Random::Seed::Seed(unsigned int iseed1, unsigned int iseed2, unsigned int iseed3) {
			_seed.clear();
			_seed.push_back(iseed1);
			_seed.push_back(iseed2);
			_seed.push_back(iseed3);
		}
		Random::Seed::Seed(unsigned int iseed1, unsigned int iseed2, unsigned int iseed3, unsigned int iseed4) {
			_seed.clear();
			_seed.push_back(iseed1);
			_seed.push_back(iseed2);
			_seed.push_back(iseed3);
			_seed.push_back(iseed4);
		}

		Random::Seed::Seed(string iseed) {
			_seed.clear();
			_seed.push_back(hash(iseed));
		}
		Random::Seed::Seed(string ivseed[], size_t in) {
			_seed.clear();
			for(unsigned int i=0 ; i<in ; i++) {
				_seed.push_back(hash(ivseed[i]));
			}
		}
		Random::Seed::Seed(string iseed1, string iseed2) {
			_seed.clear();
			_seed.push_back(hash(iseed1));
			_seed.push_back(hash(iseed2));
		}
		Random::Seed::Seed(string iseed1, string iseed2, string iseed3) {
			_seed.clear();
			_seed.push_back(hash(iseed1));
			_seed.push_back(hash(iseed2));
			_seed.push_back(hash(iseed3));
		}
		Random::Seed::Seed(string iseed1, string iseed2, string iseed3, string iseed4) {
			_seed.clear();
			_seed.push_back(hash(iseed1));
			_seed.push_back(hash(iseed2));
			_seed.push_back(hash(iseed3));
			_seed.push_back(hash(iseed4));
		}

		Random::Seed::~Seed() {
		}

		unsigned int &Random::Seed::operator[](size_t in) {
			return _seed[in];
		}

		const unsigned int &Random::Seed::operator[](size_t in) const {
			return _seed[in];
		}

		void Random::Seed::add(unsigned int iseed) {
			_seed.push_back(iseed);
		}

		void Random::Seed::add(string iseed) {
			_seed.push_back(hash(iseed));
		}

		void Random::Seed::rem(size_t in) {
			_seed.erase(_seed.begin()+in);
		}

		size_t Random::Seed::size() const {
			return _seed.size();
		}

		void Random::Seed::resize(size_t in) {
			_seed.resize(in);
		}

		void Random::Seed::clear() {
			_seed.clear();
		}

		Random::UniformInt::UniformInt(int imin, int imax) {
			_distribution << new std::uniform_int_distribution<int>(imin, imax);
		}

		Random::UniformInt::UniformInt(const UniformInt &isrc) {
			_distribution << new std::uniform_int_distribution<int>(*kin::pt(isrc._distribution));
		}

		Random::UniformInt::~UniformInt() {
			kin::erase(_distribution);
		}

		int Random::UniformInt::operator()(Random &igenerator) {
			return (*_distribution)(*igenerator._generator);
		}

		void Random::UniformInt::operator()(Random &igenerator, int *ivet, size_t in) {
			for(size_t i=0 ; i<in ; i++) {
				ivet[i] = (*_distribution)(*igenerator._generator);
			}
		}

		Random::UniformFloat::UniformFloat(float imin, float imax) {
			_distribution << new std::uniform_real_distribution<float>(imin, imax);
		}

		Random::UniformFloat::UniformFloat(const UniformFloat &isrc) {
			_distribution << new std::uniform_real_distribution<float>(*kin::pt(isrc._distribution));
		}

		Random::UniformFloat::~UniformFloat() {
			kin::erase(_distribution);
		}

		float Random::UniformFloat::operator()(Random &igenerator) {
			return (*_distribution)(*igenerator._generator);
		}

		void Random::UniformFloat::operator()(Random &igenerator, float *ivet, size_t in) {
			for(size_t i=0 ; i<in ; i++) {
				ivet[i] = (*_distribution)(*igenerator._generator);
			}
		}

		Random::Random() {
			_generator << new mt11213b;
		}

		Random::Random(const Random &isrc) {
			_generator << new mt11213b(*kin::pt(isrc._generator));
		}

		Random::~Random() {
			kin::erase(_generator);
		}

		Random::Random(Seed &iseed) {
			std::seed_seq seedseq(iseed._seed.begin(), iseed._seed.end());
			_generator << new mt11213b(seedseq);
		}

		void Random::seed(Seed &iseed) {
			std::seed_seq seedseq(iseed._seed.begin(), iseed._seed.end());
			(*_generator).seed(seedseq);
		}

		string Random::str(string iformat) {
			string result;
			str(&result, 1, iformat);
			return result;
		}

		void Random::str(string *ovet, size_t in, string iformat) {
			string vall = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
			string vdigit = "0123456789";

			string vletter = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
			string vlletter = "abcdefghijklmnopqrstuvwxyz";
			string vuletter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

			string vvowel = "aeiouAEIOU";
			string vlvowel = "aeiou";
			string vuvowel = "AEIOU";

			string vconsonant = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
			string vlconsonant = "bcdfghjklmnpqrstvwxyz";
			string vuconsonant = "BCDFGHJKLMNPQRSTVWXYZ";

			std::uniform_int_distribution<int> dall(0, vall.size()-1);
			std::uniform_int_distribution<int> ddigit(0, vdigit.size()-1);

			std::uniform_int_distribution<int> dletter(0, vletter.size()-1);
			std::uniform_int_distribution<int> dlletter(0, vlletter.size()-1);
			std::uniform_int_distribution<int> duletter(0, vuletter.size()-1);

			std::uniform_int_distribution<int> dvowel(0, vvowel.size()-1);
			std::uniform_int_distribution<int> dlvowel(0, vlvowel.size()-1);
			std::uniform_int_distribution<int> duvowel(0, vuvowel.size()-1);

			std::uniform_int_distribution<int> dconsonant(0, vconsonant.size()-1);
			std::uniform_int_distribution<int> dlconsonant(0, vlconsonant.size()-1);
			std::uniform_int_distribution<int> duconsonant(0, vuconsonant.size()-1);

			for(size_t i=0 ; i<in ; i++) {
				string &result = ovet[i];
				for(size_t i=0 ; i<iformat.size() ; i++) {
					char c = iformat[i];

					switch(c) {
					case '*':
						c = vall[dall(*_generator)];
						break;
					case 'd':
						c = vdigit[ddigit(*_generator)];
						break;

					case 'x':
						c = vletter[dletter(*_generator)];
						break;
					case 'l':
						c = vlletter[dlletter(*_generator)];
						break;
					case 'L':
						c = vuletter[duletter(*_generator)];
						break;

					case 'a':
						c = vvowel[dvowel(*_generator)];
						break;
					case 'v':
						c = vlvowel[dlvowel(*_generator)];
						break;
					case 'V':
						c = vuvowel[duvowel(*_generator)];
						break;

					case 'b':
						c = vconsonant[dconsonant(*_generator)];
						break;
					case 'c':
						c = vlconsonant[dlconsonant(*_generator)];
						break;
					case 'C':
						c = vuconsonant[duconsonant(*_generator)];
						break;
					}

					result.push_back(c);
				}
			}
		}
	}  // namespace base
}  // namespace cb
