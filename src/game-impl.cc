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

std::vector<const Enemy*> Game::getEnemies() const {
    std::vector<const Enemy*> result;
    result.reserve(enemies.size());
    
    for (const auto& enemy : enemies) {
        result.push_back(enemy.get());
    }
    return result;
}

std::vector<const Gold*> Game::getGold() const {
    std::vector<const Gold*> result;
    result.reserve(gold.size());
    
    for (const auto& curGold : gold) {
        result.push_back(curGold.get());
    }
    return result;
}

std::vector<const Potion*> Game::getPotions() const {
    std::vector<const Potion*> result;
    result.reserve(potions.size());
    
    for (const auto& potion : potions) {
        result.push_back(potion.get());
    }
    return result;
}

void Game::nextFloor() {
    if (floorNum > numFloors) return;
    int numChambers = floor.numChambers;
    ++floorNum;
    floor = Floor(numChambers);
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
        if (e->getRace() == constants::Enemy::Orc && player->getRace() == constants::Player::Goblin) dmg = (int)(dmg * 1.5); // orc bonus vs goblin

        e->takeDamage(dmg);
        player->onHit(e->getRace());
        std::string enemySymbol(1, enemyToSymbol(e->getRace()));
        currentAction = "PC deals " + std::to_string(dmg) + " damage to " + enemySymbol + " (" + std::to_string(e->getHp()) + " HP).";

        if (e->getRace() == constants::Enemy::Merchant) {
            merchantsHostile = true;
            for (auto& ptr : enemies) {
                if (ptr->getRace() == constants::Enemy::Merchant) {
                    static_cast<Merchant*>(ptr.get())->becomeHostile();
                }
            }
        }

        if (!e->isAlive()) {
            floor.removeEnemy(tx, ty);
            e->onDeath(*player);
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
        if (e->getRace() == constants::Enemy::Dragon) { // dragon stuff, if player near hoard then ATTACK
            Dragon* d = static_cast<Dragon*>(e);
            bool nearHoard = std::abs(d->getHoardX() - player->getX()) <= 1 && std::abs(d->getHoardY() - player->getY()) <= 1;
            inRadius = inRadius || nearHoard;
        }

        if (inRadius && (e->isHostile() || e->getRace() != constants::Enemy::Merchant)) {    
            enemyAttack(*e);
        } else {
            e->move(floor);
        }
    }
    player->endTurn();
}

// called by enemyTurns
void Game::enemyAttack(Enemy& e) {      
    // elf double attack unless drow
    int attacks = (e.getRace() == constants::Enemy::Elf && player->getRace() != constants::Player::Drow) ? 2 : 1;
    std::string enemySymbol(1, enemyToSymbol(e.getRace()));

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
    if (!player->move(floor, dir)) return false;
    floor.movePlayer(px, py, player->getX(), player->getY());
    currentAction = "PC moves " + dirToStr(dir) + ".";
    return true;
}



void Game::usePotion(constants::Direction dir) {
    auto [dx, dy] = dirToPair(dir);
    int tx = player->getX() + dx;
    int ty = player->getY() + dy;
    if (tx < 0 || tx >= constants::board::WIDTH || ty < 0 || ty >= constants::board::HEIGHT) return; // out of bounds
    int idx = floor.potionsIndex[ty][tx];
    if (idx == -1) return; // no found :(
    Potion* p = potions[idx].get();
    p->becomeKnown();  // so cant be reused, check p->known == false when calling in game loop ig
    player->applyPotion(p->getHpMod(), p->getAtkMod(), p->getDefMod());
    std::string potionName = p->isKnown() ? potionTypeToStr(p->getType()) : "unknown potion";
    currentAction = "PC uses " + potionName + ".";
    floor.removePotion(tx, ty); // need to figure whether potion dissapears if used, or just becomes unusable
}

void Game::spawnPlayer() {
    Chamber& c = floor.chooseChamber();
    auto [x, y] = *c.randomEmptyCell();
    player->setPosition(x, y);
    floor.grid[y][x] = '@';
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
        constants::Enemy race = randomEnemy();

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
            
            enemies.emplace_back(newEnemy(constants::Enemy::Dragon, floor));
            int enemyIdx = enemies.size() - 1;
            floor.addEnemy(dx, dy, enemyIdx, constants::Enemy::Dragon);
            enemies[enemyIdx]->setPosition(dx, dy);
            chamber.removeEmpty(dx, dy);
        } else {
            auto cell = chamber.randomEmptyCell();
            if (!cell) continue; // No available cells
            x = cell->first; y = cell->second;
        }

        // Spawn
        gold.emplace_back(std::make_unique<Gold>(amount));
        int goldIdx = gold.size() - 1;
        floor.addGold(x, y, goldIdx);
        chamber.removeEmpty(x, y);

        ++i;
    }
}

void Game::spawnAll() {
    spawnPlayer();  
    spawnEnemies();
    spawnPotions();
    spawnGold();
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
    std::string playerRaceStr = playerToStr(player->getRace()).value();
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
    os << "Score: " << score;
}

void Game::display(std::ostream& os) const {
    os << floor;
    displayInfo(os);
}
