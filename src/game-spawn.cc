module game;

Chamber& Game::spawnPlayer() {
    Chamber& c = floor.chooseChamber();
    auto [x, y] = *c.randomEmptyCell();
    player->setPosition(x, y);
    floor.setGrid(x, y, constants::symbol::PLAYER);
    c.removeEmpty(x, y);
    currentAction = "Player character has spawned.";
    return c;
}

void Game::addGold(int amount, bool isHoard, Chamber &chamber, int x, int y) {
    gold.emplace_back(std::make_unique<Gold>(amount, isHoard));
    int goldIdx = gold.size() - 1;
    floor.addGold(x, y, goldIdx);
    chamber.removeEmpty(x, y);
}

void Game::addEnemy(constants::EnemyRace race, Chamber &chamber, int x, int y) {
    enemies.emplace_back(newEnemy(race, floor));
    int enemyIdx = enemies.size() - 1;
    floor.addEnemy(x, y, enemyIdx, race);
    chamber.removeEmpty(x, y);

    enemies[enemyIdx]->setPosition(x, y);
}

void Game::addPotion(constants::PotionType type, Chamber &chamber, int x, int y) {
    potions.emplace_back(std::make_unique<Potion>(type));
    int potionIdx = potions.size() - 1;
    floor.addPotion(x, y, potionIdx);
    chamber.removeEmpty(x, y);
}

void Game::spawnStairs(const Chamber& playerChamber) {
    Chamber* c = nullptr;
    do {
        c = &floor.chooseChamber();
    } while (c == &playerChamber);
    auto [x, y] = *c->randomEmptyCell();
    floor.setGrid(x, y, constants::symbol::STAIRS);
    c->removeEmpty(x, y);
}

void Game::spawnEnemies() {
    for (int i = 0; i < constants::NUM_ENEMIES; ) {
        if (floor.spawnCapacityReached()) break; // Chambers are full
        // Pick cell
        Chamber& chamber = floor.chooseChamber();
        auto cell = chamber.randomEmptyCell();
        if (!cell) continue; // chamber is full
        auto [x, y] = *cell;

        // Pick race
        constants::EnemyRace race = randomEnemy();

        // Spawn
        addEnemy(race, chamber, x, y);
        ++i;
    }
}

void Game::spawnPotions() {
    for (int i = 0; i < constants::NUM_POTIONS; ) {
        if (floor.spawnCapacityReached()) break; // Chambers are full
        // Pick cell
        Chamber& chamber = floor.chooseChamber();
        auto cell = chamber.randomEmptyCell();
        if (!cell) continue; // chamber is full
        auto [x, y] = *cell;

        // Pick type
        constants::PotionType type = randomPotion();

        // Spawn
        addPotion(type, chamber, x, y);
        ++i;
    }
}

void Game::spawnGold() {
    for (int i = 0; i < constants::NUM_GOLD; ) {
        if (floor.spawnCapacityReached()) break; // Chambers are full
        // Determine amount of gold
        int amount = randomGold();
        Chamber& chamber = floor.chooseChamber();
        int x, y;
        bool isHoard = amount == constants::goldPile::DRAGON_HOARD;

        if (isHoard) {
            auto pair = chamber.randomHoard();
            if (!pair) continue; // no pairs of cells to spawn hoard
            auto [p, d] = *pair;
            auto [dx, dy] = p + d; // dragon x and y
            x = p.first; y = p.second; // potion x and y

            addEnemy(constants::EnemyRace::Dragon, chamber, dx, dy);
        } else {
            auto cell = chamber.randomEmptyCell();
            if (!cell) continue; // No available cells
            x = cell->first; y = cell->second;
        }

        // Spawn
        addGold(amount, isHoard, chamber, x, y);
        ++i;
    }
}

void Game::spawnAll() {
    Chamber playerChamber = spawnPlayer();
    spawnStairs(playerChamber);
    spawnPotions();
    spawnGold();
    spawnEnemies();
}

void Game::removeAll() {
    enemies.clear();
    potions.clear();
    gold.clear();
}