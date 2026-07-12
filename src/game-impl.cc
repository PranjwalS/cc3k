module game;

import constants;
import random;
import character;
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
            player{player}, chambers(numChambers), numFloors{numFloors} {}

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
        // halfling miss chance — takes priority
        if (e->missChance()) return true;

        // player hits
        int dmg = calcDamage(player->getAtk(), e->getDef());
        if (e->getRace() == constants::Enemy::Orc && player->getRace() == constants::Player::Goblin) dmg = (int)(dmg * 1.5); // orc bonus vs goblin

        e->takeDamage(dmg);
        player->onHit(e->getRace());

        if (!e->isAlive()) {
            floor.removeEnemy(tx, ty);
            // e->onDeath(player->getGold());        NEED TO FIX Enemy::onDeath
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
            bool nearHoard = std::abs(d->hoardX - player->getX()) <= 1 && std::abs(d->hoardY - player->getY()) <= 1;
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

// TODO 
void Game::spawnEnemies() {
}

void Game::spawnPotions() {
}

void Game::spawnGold() {
}
