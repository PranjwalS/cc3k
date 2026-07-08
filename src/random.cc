export module random;

import <algorithm>;
import <chrono>;
import <random>; 

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
// std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

// export int random(int seed = seed) {
//     std::default_random_engine rng(seed);
//     for (int i = 0; i < 1000; i++) std::shuffle( v.begin(), v.end(), rng);
//     return v[0];
// };

// export int random(int lo, int hi) {
//     std::default_random_engine rng(seed);
//     return lo + (rng() % (hi - lo + 1));
// } // idek chap

export int random(const int min, const int max) {
    std::random_device seed;
    std::mt19937 gen(seed()); // Mersenne Twister
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}
