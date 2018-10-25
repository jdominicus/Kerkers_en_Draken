#pragma once

#include <random>
#include <ctime>

class RandomNumberGenerator
{
	public:
		RandomNumberGenerator();
		~RandomNumberGenerator();

	private:
		std::default_random_engine generator;

	public:
		int getNumber(int min, int max);
		int getDifferentNumber(int min, int max, int number);
		bool getBool(int percentage);
};

