module game;

import constants;
import random;
import chamber;
import character;
import enemy;
import potion;
import gold;
import <iostream>;

const std::vector<const Enemy*> Game::getEnemies() const {
    return std::vector<const Enemy*>(enemies.begin(), enemies.end());
}
const std::vector<const Gold*> Game::getGold() const {
    return std::vector<const Gold*>(gold.begin(), gold.end());
}
const std::vector<const Potion*> Game::getPotions() const {
    return std::vector<const Potion*>(potions.begin(), potions.end());
}

Game::Game(Player* player, const int numFloors, const int numChambers) : 
            player{player}, 
            numChambers{numChambers}, chambers(numChambers), 
            numFloors{numFloors} {}

Game::~Game() {
    delete player;
    for (Enemy* e : enemies) delete e;
    for (Gold* g : gold) delete g;
    for (Potion* p : potions) delete p;
}

void Game::init(constants::Player race) {
    if (race == constants::Player::Shade) player = new Shade{floor};
    else if (race == constants::Player::Drow) player = new Drow{floor};
    else if (race == constants::Player::Vampire) player = new Vampire{floor};
    else if (race == constants::Player::Troll) player = new Troll{floor};
    else if (race == constants::Player::Goblin) player = new Goblin{floor};
    spawnEnemies();     // todo these 3
    spawnPotions();
    spawnGold();
}

void Game::nextFloor() {
    if (floorNum > numFloors) return;
    ++floorNum;
    
    for (Enemy* e : enemies) delete e;
    for (Gold* g : gold) delete g;
    for (Potion* p : potions) delete p;
    enemies.clear();
    gold.clear();
    potions.clear();

    floor = Floor();
}

bool Game::playerAttack(constants::Direction d) {
    if (!player->isValidMove(floor, d)) {
        return false;
    }

    auto [dx, dy] = constants::dirToPair(d);

    int tx = player->getX() + dx;
    int ty = player->getY() + dy;

    int idx = floor.enemiesIndex[ty][tx];

    if (idx != -1) {
        Enemy* e = enemies[idx];
        // halfling chance of evasion — takes priority
        if (e->evasionChance()) return true;

        // player hits
        int dmg = calcDamage(player->getAtk(), e->getDef());
        if (e->getRace() == constants::Enemy::Orc && player->getRace() == constants::Player::Goblin) dmg = (int)(dmg * 1.5); // orc bonus vs goblin

        e->takeDamage(dmg);
        player->onHit(e->getRace());

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
    for (Enemy* e : enemies) {
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

    for (int i = 0; i < attacks; i++) {
        if (randomChance(constants::probability::ENEMY_MISS)) {
            int dmg = calcDamage(e.getAtk(), player->getDef());
            player->takeDamage(dmg);
        }
    }
}

int Game::calcDamage(int atkVal, int defVal) const {
    return (int)std::ceil((100.0 / (100.0 + defVal)) * atkVal);
}

void Game::quitGame() { forceQuit = true; }

bool Game::isOver() const { return !player->isAlive() || isWon() || forceQuit; }

bool Game::isWon() const { return floorNum > numFloors; }

bool Game::playerMove(constants::Direction dir) { return player->move(floor, dir); }


void Game::usePotion(constants::Direction dir) {
    auto [dx, dy] = constants::dirToPair(dir);
    int tx = player->getX() + dx;
    int ty = player->getY() + dy;
    if (tx < 0 || tx >= constants::board::WIDTH || ty < 0 || ty >= constants::board::HEIGHT) return; // out of bounds
    int idx = floor.potionsIndex[ty][tx];
    if (idx == -1) return; // no found :(
    Potion* p = potions[idx];
    p->becomeKnown();  // so cant be reused, check p->known == false when calling in game loop ig
    player->applyPotion(p->getHpMod(), p->getAtkMod(), p->getDefMod());
    floor.removePotion(tx, ty); // need to figure whether potion dissapears if used, or just becomes unusable
}

void Game::spawnEnemies() {
    for (int i = 0; i < constants::NUM_ENEMIES; ++i) {
        // Pick cell
        Chamber chamber = chambers.at(chooseChamber());
        auto cell = chamber.randomEmptyCell();
        if (!cell) continue; // No available cells
        auto [x, y] = *cell;

        // Pick race
        constants::Enemy race = randomEnemy();

        // Spawn
        Enemy* enemy = newEnemy(race, floor);
        enemies.emplace_back(enemy);
        int enemyIdx = enemies.size() - 1;
        floor.addEnemy(x, y, enemyIdx, race);
    }
}

void Game::spawnPotions() {
    for (int i = 0; i < constants::NUM_POTIONS; ++i) {
        // Pick cell
        Chamber chamber = chambers.at(chooseChamber());
        auto cell = chamber.randomEmptyCell();
        if (!cell) continue; // No available cells
        auto [x, y] = *cell;

        // Pick type
        constants::PotionType type = randomPotion();

        // Spawn
        Potion* potion = new Potion{type};
        potions.emplace_back(potion);
        int potionIdx = potions.size() - 1;
        floor.addPotion(x, y, potionIdx);
    }
}

void Game::spawnGold() {
    for (int i = 0; i < constants::NUM_GOLD; ++i) {
        // Pick cell
        Chamber chamber = chambers.at(chooseChamber());
        auto cell = chamber.randomEmptyCell();
        if (!cell) continue; // No available cells
        auto [x, y] = *cell;

        // Determine amount of gold
        int amount = randomGold();

        // Spawn
        Gold* newGold = new Gold{amount};
        gold.emplace_back(newGold);
        int goldIdx = gold.size() - 1;
        floor.addGold(x, y, goldIdx);
    }
}
