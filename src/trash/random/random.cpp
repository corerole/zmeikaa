#include "random.hpp"

float get_random() {
	static std::default_random_engine e;
	static std::uniform_real_distribution<float> dis(0, 1); // range [0, 1)
	return dis(e);
}