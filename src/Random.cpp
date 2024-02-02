#include "Random.h"

int Random::RandomInt(int rangeMin, int rangeMax) {
	clock_t time = clock();
	std::mt19937 randNumb((unsigned int)time);
	std::uniform_int_distribution<int> dist(rangeMin, rangeMax);
	return dist(randNumb);
}