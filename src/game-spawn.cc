module game;

void Game::addGold(int amount, bool isHoard, int x, int y, Chamber *chamber=nullptr) {
    gold.emplace_back(std::make_unique<Gold>(amount, isHoard));
    int goldIdx = gold.size() - 1;
    floor.addGold(x, y, goldIdx);
    if (chamber) chamber->removeEmpty(x, y);
}

void Game::addEnemy(constants::EnemyRace race, int x, int y, 
                    int hx=0, int hy=0, Chamber *chamber=nullptr) {
    enemies.emplace_back(newEnemy(race, floor, hx, hy));
    int enemyIdx = enemies.size() - 1;
    floor.addEnemy(x, y, enemyIdx, race);
    if (chamber) chamber->removeEmpty(x, y);

    enemies[enemyIdx]->setPosition(x, y);
}

void Game::addPotion(constants::PotionType type, int x, int y, Chamber *chamber=nullptr) {
    potions.emplace_back(std::make_unique<Potion>(type));
    int potionIdx = potions.size() - 1;
    floor.addPotion(x, y, potionIdx);
    if (chamber) chamber->removeEmpty(x, y);
}

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
        addEnemy(race, x, y, 0, 0, &chamber);
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
        addPotion(type, x, y, &chamber);
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

            addEnemy(constants::EnemyRace::Dragon, dx, dy, x, y, &chamber);
        } else {
            auto cell = chamber.randomEmptyCell();
            if (!cell) continue; // No available cells
            x = cell->first; y = cell->second;
        }

        // Spawn
        addGold(amount, isHoard, x, y, &chamber);
        ++i;
    }
}

void Game::spawnAll() {
    Chamber& playerChamber = spawnPlayer();
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

std::optional<std::pair<int, int>> hoardFromDragonPos(std::string& map, int x, int y) {
    for (int d = 0; d < constants::NUM_DIRECTIONS; d++) {
        auto dir = static_cast<constants::Direction>(d);
        auto [px, py] = std::make_pair(x, y) + dir;
        int idx = py * constants::board::WIDTH + px;

        if (constants::board::isInBounds(px, py) && map[idx] == '9') {
            return std::make_pair(px, py);
        }
    }

    return std::nullopt;
}

void Game::useNextMap() {
    std::string& map = maps[floorNum - 1];

    for (int y = 0; y < constants::board::HEIGHT; y++) {
        for (int x = 0; x < constants::board::WIDTH; x++) {
            int idx = y * constants::board::WIDTH + x;
            char ch = map[idx];

            bool isEnemy = isEnemySymbol(ch);

            if (ch == static_cast<char>(constants::EnemyRace::Dragon)) {
                auto opt = hoardFromDragonPos(map, x, y);
                if (!opt) {
                    std::cerr << "Cannot find hoard from dragon position." << std::endl;
                    return;
                }
                auto [hx, hy] = *opt;
                addEnemy(constants::EnemyRace::Dragon, x, y, hx, hy);
                addGold(constants::goldPile::DRAGON_HOARD, true, hx, hy);
            } else if (isEnemy) { // non dragon enemies
                auto race = static_cast<constants::EnemyRace>(ch);
                addEnemy(race, x, y);
            } else if ('0' <= ch && ch <= '5') { // potion
                auto type = static_cast<constants::PotionType>(ch - '0');
                addPotion(type, x, y);
            } else if ('6' <= ch && ch <= '8') { // non dragon hoard gold 
                int goldArr[] = {
                    constants::goldPile::SMALL,
                    constants::goldPile::NORMAL,
                    constants::goldPile::MERCHANT_HOARD
                };
                int amount = goldArr[ch - '6'];
                addGold(amount, false, x, y);
            } else if (ch == constants::symbol::PLAYER) {
                player->setPosition(x, y);
                floor.setGrid(x, y, constants::symbol::PLAYER);
            } else if (ch == constants::symbol::STAIRS) {
                floor.setGrid(x, y, constants::symbol::STAIRS);
            } // '9' (dragon hoard) is handled by dragon case.
        }
    }
}
