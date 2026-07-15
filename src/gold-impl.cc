module gold;
import random;
import constants;
import <array>;

int randomGold() {
    using namespace constants::probability::spawn;
    std::array<double, NUM_WEIGHTED_GOLD> probabilities;
    for (int i = 0; i < NUM_WEIGHTED_GOLD; ++i) {
        probabilities[i] = GOLD[i].probability;
    }
    int idx = randomWeightedIndex(probabilities);
    return GOLD[idx].goldPile;
}
