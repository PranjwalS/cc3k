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
        enemies.emplace_back(newEnemy(race, floor));
        int enemyIdx = enemies.size() - 1;
        floor.addEnemy(x, y, enemyIdx, race);
        enemies[enemyIdx]->setPosition(x, y);
        chamber.removeEmpty(x, y);

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
        potions.emplace_back(std::make_unique<Potion>(type));
        int potionIdx = potions.size() - 1;
        floor.addPotion(x, y, potionIdx);
        chamber.removeEmpty(x, y);

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

        if (amount == constants::goldPile::DRAGON_HOARD) {
            auto pair = chamber.randomHoard();
            if (!pair) continue; // no pairs of cells to spawn hoard
            auto [p, d] = *pair;
            x = p.first; y = p.second;
            auto [dx, dy] = p + d; // dragon x and y
            
            enemies.emplace_back(newEnemy(constants::EnemyRace::Dragon, floor, x, y));
            int enemyIdx = enemies.size() - 1;
            floor.addEnemy(dx, dy, enemyIdx, constants::EnemyRace::Dragon);
            enemies[enemyIdx]->setPosition(dx, dy);
            chamber.removeEmpty(dx, dy);
            gold.emplace_back(std::make_unique<Gold>(amount, true));
        } else {
            auto cell = chamber.randomEmptyCell();
            if (!cell) continue; // No available cells
            x = cell->first; y = cell->second;
            gold.emplace_back(std::make_unique<Gold>(amount));
        }

        // Spawn
        int goldIdx = gold.size() - 1;
        floor.addGold(x, y, goldIdx);
        chamber.removeEmpty(x, y);

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