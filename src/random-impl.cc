module random;

import <random>;

static std::random_device seed;
static std::mt19937 gen(seed());

int randomNum(const int min, const int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

bool randomChance(double probability) {
    std::bernoulli_distribution dist(probability);
    return dist(gen) == 1;
}
