module game;

import constants;
import random;
import character;
import <iostream>;

Game::Game() {
    
}

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

bool Game::playerAttack(constants::Direction d) {
    if (!player->isValidMove(floor, d)) {
        return false;
    }

    auto [dx, dy] = constants::dirToPair(d);

    int tx = player->x + dx;
    int ty = player->y + dy;

    int idx = floor.enemiesIndex[ty][tx];

    if (idx != -1) {
        Enemy* e = enemies[idx];
        if (e->missChance()) return true;
        // elf double attack unless drow
        int attacks = (e->race == constants::Enemy::Elf && 
                        player->race != constants::Player::Drow) ? 2 : 1;
        for (int i = 0; i < attacks; i++) {
            int dmg = calcDamage(e->atk, player->def);
            player->takeDamage(dmg);
        }
        // player hits back
        int dmg = calcDamage(player->atk, e->def);
        // orc bonus vs goblin
        if (e->race == constants::Enemy::Dwarf && 
            player->race == constants::Player::Goblin) dmg = (int)(dmg * 1.5);
        e->takeDamage(dmg);
        player->onHit(e->race);
        if (!e->isAlive()) {
            floor.removeEnemy(tx, ty);
            e->onDeath(player->gold);
            player->onKill(e->race);
        }
        return true;
    }

    return false;
}

void Game::enemyTurns() {
    if (frozen) return;
    for (Enemy* e : enemies) {
        if (!e->isAlive()) continue;
        bool inRadius = std::abs(e->x - player->x) <= 1 && 
                        std::abs(e->y - player->y) <= 1;
        if (inRadius && (e->hostile || e->race != constants::Enemy::Merchant)) {
            if (randomChance(constants::probability::ENEMY_MISS)) {
                int dmg = calcDamage(e->atk, player->def);
                player->takeDamage(dmg);
            }
        } else {
            e->move(floor);
        }
    }
    player->endTurn();
}

int Game::calcDamage(int atkVal, int defVal) {
    return (int)std::ceil((100.0 / (100.0 + defVal)) * atkVal);
}

bool Game::isOver() { return player->isAlive() || floorNum > 5; }


// TODO 
void Game::spawnEnemies() {
}

void Game::spawnPotions() {
}

void Game::spawnGold() {
}
