#include "RNG.h"

std::default_random_engine RNG::engine_{ std::random_device()() };

RNG::RNG()
{
}


RNG::~RNG()
{
}

int RNG::getInt(int lowerBound, int upperBound)
{
	std::uniform_int_distribution<int> dist(lowerBound, upperBound-1);
	return dist(engine_);
}

double RNG::getDouble(double lowerBound, double upperBound)
{
	std::uniform_real_distribution<double> dist(lowerBound, upperBound);
	return dist(engine_);
}

bool RNG::getBool(double chanceSuccess)
{
	std::uniform_real_distribution<double> dist(0, 1);
	return dist(engine_) < chanceSuccess;
}


