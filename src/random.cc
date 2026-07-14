export module random;

export int randomNum(const int min, const int max);
export bool randomChance(double probability);

// Return random index of an array where probabilities[i] is the probability index i is chosen
export int randomWeightedIndex(const double probabilities[], const int size);
