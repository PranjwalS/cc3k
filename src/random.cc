export module random;
import <span>;

// Random number generator from min to max inclusive
export int randomNum(const int min, const int max);
export double randomNum(const double min, const double max);

// Return random bool given probability that true is chosen
export bool randomChance(double probability = 0.5);

// Return random index of an array where probabilities[i] is the probability index i is chosen
// If normalize enabled, normalize probabilities to standard uniform distribution
export int randomWeightedIndex(const std::span<const double> probabilities, 
                               const bool normalize = false);
