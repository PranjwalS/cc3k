module game;

import constants;
import random;
import chamber;
import character;
import enemy;
import potion;
import gold;
import <iostream>;
import <cmath>;
import <memory>;
import <iomanip>;


void Game::nextFloor() {
    if (floorNum > numFloors) return;
    int numChambers = floor.numChambers;
    ++floorNum;
    floor = Floor(numChambers);
    removeAll();
    player->changeFloor(floor);
    spawnAll();
}

bool Game::playerAttack(constants::Direction d) {
    auto [dx, dy] = dirToPair(d);

    int tx = player->getX() + dx;
    int ty = player->getY() + dy;

    int idx = floor.enemiesIndex[ty][tx];  // checks if enemy even exists

    if (idx != -1) {
        Enemy* e = enemies[idx].get();
        // halfling chance of evasion — takes priority
        if (e->evasionChance()) return true;

        // player hits
        int dmg = calcDamage(player->getAtk(), e->getDef());
        if (e->getRace() == constants::EnemyRace::Orc && 
            player->getRace() == constants::PlayerRace::Goblin) {
            // orc bonus vs goblin
            dmg = static_cast<int>(dmg * constants::multiplier::ORC_ATTACK_GOBLIN);
        }

        e->takeDamage(dmg);
        player->onHit(e->getRace());
        std::string enemySymbol(1, enemyRaceToSymbol(e->getRace()));
        currentAction = "PC deals " + std::to_string(dmg) + " damage to " + enemySymbol + " (" + std::to_string(e->getHp()) + " HP).";

        if (e->getRace() == constants::EnemyRace::Merchant) {
            merchantsHostile = true;
            for (auto& ptr : enemies) {
                if (ptr->getRace() == constants::EnemyRace::Merchant) {
                    static_cast<Merchant*>(ptr.get())->becomeHostile();
                }
            }
        }

        if (!e->isAlive()) {
            floor.removeEnemy(tx, ty);
            if (e->getRace() == constants::EnemyRace::Dragon) {
                int nx = static_cast<Dragon*>(e)->getHoardX();
                int ny = static_cast<Dragon*>(e)->getHoardY();
                int gld_idx = floor.goldIndex[ny][nx];
                Gold* gld = gold[gld_idx].get();
                gld->toggleDragonGuarded();
            } else { e->onDeath(*player); }
            player->onKill(e->getRace());
        }
        return true;
    }
    return false;
}


//  basically handles both enemy moves and enemy attacks internally at once, since enemy can only do one or the other per turn!
void Game::enemyTurns() {
    if (frozen) return;
    for (auto& ptr : enemies) {
        Enemy* e = ptr.get(); // unique ptr to raw ptr
        if (!e->isAlive()) continue;
        bool inRadius = std::abs(e->getX() - player->getX()) <= 1 && std::abs(e->getY() - player->getY()) <= 1;
        if (e->getRace() == constants::EnemyRace::Dragon) { // dragon stuff, if player near hoard then ATTACK
            Dragon* d = static_cast<Dragon*>(e);
            bool nearHoard = std::abs(d->getHoardX() - player->getX()) <= 1 && std::abs(d->getHoardY() - player->getY()) <= 1;
            inRadius = inRadius || nearHoard;
        }

        if (inRadius && (e->isHostile() || e->getRace() != constants::EnemyRace::Merchant)) {    
            enemyAttack(*e);
        } else {
            e->move();
        }
    }
    if (player->isAlive()) player->endTurn();
}

// called by enemyTurns
void Game::enemyAttack(Enemy& e) {      
    // elf double attack unless drow
    int attacks = (e.getRace() == constants::EnemyRace::Elf && player->getRace() != constants::PlayerRace::Drow) ? 2 : 1;
    std::string enemySymbol(1, enemyRaceToSymbol(e.getRace()));

    for (int i = 0; i < attacks; i++) {
        if (randomChance(constants::probability::ENEMY_MISS)) {
            int dmg = calcDamage(e.getAtk(), player->getDef());
            player->takeDamage(dmg);
            currentAction += " " + enemySymbol + " deals " + std::to_string(dmg) + " damage to PC (" + std::to_string(player->getHp()) + " HP).";
        }
    }
}

int Game::calcDamage(int atkVal, int defVal) const {
    return (int)std::ceil((100.0 / (100.0 + defVal)) * atkVal);
}

void Game::quitGame() { forceQuit = true; }

bool Game::isOver() const { return !player->isAlive() || isWon() || forceQuit; }

bool Game::isWon() const { return floorNum > numFloors; }


bool Game::playerMove(constants::Direction dir) {
    int px = player->getX();
    int py = player->getY();
    if (!player->move(dir)) return false;
    int nx = player->getX();
    int ny = player->getY();
    currentAction = "PC moves " + dirToStr(dir) + ".";

    int gIdx = floor.goldIndex[ny][nx];
    if (gIdx != -1) {
        Gold* g = gold[gIdx].get();
        if (!g->isDragonGuarded()) {
            player->gainGold(g->getValue());
            floor.removeGold(nx, ny); // grid[ny][nx] is now '.'
            currentAction += " PC picks up " + std::to_string(g->getValue()) + " gold.";
        } else {
            currentAction += " Gold is guarded.";
        }
    }

    if (floor.grid[ny][nx] == constants::symbol::STAIRS) {
        // uhh idk if we need this stuff
        // player->applyPotion(0, -tempAtk, -tempDef); 
        // tempAtk = 0;
        // tempDef = 0;
        nextFloor();
        currentAction = " PC descends to floor " + std::to_string(floorNum) + ".";
        return true;
    }

    // add sees potion logic here!

    floor.movePlayer(px, py, nx, ny);
    return true;
}


void Game::usePotion(constants::Direction dir) {
    auto [dx, dy] = dirToPair(dir);
    int tx = player->getX() + dx;
    int ty = player->getY() + dy;
    if (tx < 0 || tx >= constants::board::WIDTH || ty < 0 || ty >= constants::board::HEIGHT) return;
    int idx = floor.potionsIndex[ty][tx];
    if (idx == -1) return;
    Potion* p = potions[idx].get();
    if (!p->isPermanent()) {
        tempAtk += p->getAtkMod();
        tempDef += p->getDefMod();
    }

    player->applyPotion(p->getHpMod(), p->getAtkMod(), p->getDefMod());
    std::string potionName = knownPotions.count(p->getType()) ? potionTypeToStr(p->getType()) : "unknown potion";
    knownPotions.insert(p->getType());
    floor.removePotion(tx, ty);
    playerMove(dir);
    currentAction = " PC uses " + potionName + ".";
}

void Game::spawnPlayer() {
    Chamber& c = floor.chooseChamber();
    auto [x, y] = *c.randomEmptyCell();
    player->setPosition(x, y);
    floor.grid[y][x] = constants::symbol::PLAYER;
    c.removeEmpty(x, y);
    currentAction = "Player character has spawned.";
}

void Game::spawnStairs() {
    Chamber& c = floor.chooseChamber();
    auto [x, y] = *c.randomEmptyCell();
    floor.grid[y][x] = constants::symbol::STAIRS;
    c.removeEmpty(x, y);
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
    spawnPlayer();
    spawnStairs();
    spawnPotions();
    spawnGold();
    spawnEnemies();
}

void Game::removeAll() {
    enemies.clear();
    potions.clear();
    gold.clear();
}

void Game::displayAction(std::ostream& os) const {
    os << "Action: " << currentAction << "\n";
}


void Game::displayInfo(std::ostream& os) const {
    int lineWidth = constants::board::WIDTH - constants::board::OFFSET;

    // Outputting the first line of info output
    std::string playerRaceStr = playerRaceToStr(player->getRace()).value();
    std::string leftSide = "Race " + playerRaceStr + " ";
    leftSide += "Gold: " + std::to_string(player->getGold());

    std::string rightSide = "Floor " + std::to_string(floorNum);
    
    int remainingPadding = lineWidth - leftSide.length();
    if (remainingPadding < 0) remainingPadding = 0;
    
    os << leftSide
       << std::right << std::setw(remainingPadding) << rightSide << "\n";

    // Displaying rest of info
    os << "HP: " << player->getHp() << "\n";
    os << "Atk: " << player->getAtk() << "\n";
    os << "Def: " << player->getDef() << "\n";
    displayAction(os);
}
void Game::displayScore(std::ostream& os) const {
    int score = player->getScore();
    if (player->getRace() == constants::PlayerRace::Shade) {
        score = static_cast<int>(score * constants::multiplier::SHADE_SCORE);
    }
    os << "Score: " << score;
}

void Game::display(std::ostream& os) const {
    os << floor;
    displayInfo(os);
}
