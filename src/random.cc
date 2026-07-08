export module random;

import <algorithm>;
import <chrono>;
import <random>; 

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

export int random(const int min, const int max) {
    std::random_device seed;
    std::mt19937 gen(seed()); // Mersenne Twister
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}
