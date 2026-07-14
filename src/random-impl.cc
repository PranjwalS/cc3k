module random;

import <random>;

// Seed Mersenne Twister algorithm to generate gen
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

int randomWeightedIndex(const double probabilities[], const int size, const bool normalize) {
    double total = 1.0;
    // Normalize probabilities 
    if (normalize) {
        total = 0.0;
        for (int i = 0; i < size; ++i) {
            total += probabilities[i];
        }
    }
    std::uniform_real_distribution<double> dist(0.0, total);
    double r = dist(gen);

    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += probabilities[i];
        if (r < sum) return i;
    }

    return size - 1;
}
