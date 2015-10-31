#ifndef RNG_H
#define RNG_H

#include <random>

class RNG
{
public:
	RNG();
	~RNG();

	static int getInt(int lowerBound, int upperBound);
	static double getDouble(double lowerBound, double upperBound);
	static bool getBool(double chanceSuccess);
private:
	static std::default_random_engine engine_;
};

#endif //RNG_H

