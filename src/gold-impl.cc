module gold;
import random;
import constants;

int randomGold() {
    using namespace constants::probability::spawn;
    double probabilities[NUM_WEIGHTED_GOLD];
    for (int i = 0; i < NUM_WEIGHTED_GOLD; ++i) {
        probabilities[i] = GOLD[i].probability;
    }
    int idx = randomWeightedIndex(probabilities, NUM_WEIGHTED_GOLD);
    return GOLD[idx].goldPile;
}
