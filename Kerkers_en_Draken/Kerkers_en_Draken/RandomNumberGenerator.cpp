#include "RandomNumberGenerator.h"

RandomNumberGenerator* RandomNumberGenerator::random = nullptr;

RandomNumberGenerator::RandomNumberGenerator()
{
	generator.seed(time(NULL));
}

RandomNumberGenerator::~RandomNumberGenerator()
{
}

RandomNumberGenerator* RandomNumberGenerator::getRandom()
{
	if (random == nullptr)
		random = new RandomNumberGenerator();

	return random;
}

void RandomNumberGenerator::removeRandom()
{
	if (random != nullptr)
		delete random;
}

int RandomNumberGenerator::getNumber(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

int RandomNumberGenerator::getDifferentNumber(int min, int max, int number)
{
	int random = getNumber(min, max);
	while (random == number)
		random = getNumber(min, max);
	return random;
}

bool RandomNumberGenerator::getBool(int percentage)
{
	std::uniform_int_distribution<int> distribution(1, 100);
	if (distribution(generator) <= percentage)
		return true;
	else
		return false;
}
