#include "MyRandom.h"

float getRandomFloat(float x, float y) {
	static std::default_random_engine e1(time(nullptr));
	static std::uniform_real_distribution<> dis1(x, y);
	return dis1(e1);
}

int getRandomInt(int x, int y) {
	static std::default_random_engine e(time(nullptr));
	static std::uniform_int_distribution<> dis(x, y);
	return dis(e);
}