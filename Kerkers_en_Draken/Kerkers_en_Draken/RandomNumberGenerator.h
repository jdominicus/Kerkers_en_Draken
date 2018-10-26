#pragma once

#include <random>
#include <ctime>

class RandomNumberGenerator
{
	public:
		~RandomNumberGenerator();

	private:
		static RandomNumberGenerator* random;
		std::default_random_engine generator;

	public:
		static RandomNumberGenerator* getRandom();
		static void removeRandom();

		int getNumber(int min, int max);
		int getDifferentNumber(int min, int max, int number);
		bool getBool(int percentage);

	private:
		RandomNumberGenerator();
};

