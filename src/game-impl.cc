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
        // halfling miss chance — takes priority
        if (e->missChance()) return true;

        // player hits
        int dmg = calcDamage(player->atk, e->def);
        if (e->race == constants::Enemy::Orc && player->race == constants::Player::Goblin) dmg = (int)(dmg * 1.5);         // orc bonus vs goblin

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


//  basically handles both enemy moves and enemy attacks internally at once, since enemy can only do one or the other per turn!
void Game::enemyTurns() {
    if (frozen) return;
    for (Enemy* e : enemies) {
        if (!e->isAlive()) continue;
        bool inRadius = std::abs(e->x - player->x) <= 1 && std::abs(e->y - player->y) <= 1;
        if (e->race == constants::Enemy::Dragon) { // dragon stuff, if player near hoard then ATTACK
            Dragon* d = static_cast<Dragon*>(e);
            bool nearHoard = std::abs(d->hoardX - player->x) <= 1 && std::abs(d->hoardY - player->y) <= 1;
            inRadius = inRadius || nearHoard;
        }

        if (inRadius && (e->hostile || e->race != constants::Enemy::Merchant)) {    
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
    int attacks = (e.race == constants::Enemy::Elf && player->race != constants::Player::Drow) ? 2 : 1;

    for (int i = 0; i < attacks; i++) {
        if (randomChance(constants::probability::ENEMY_MISS)) {
            int dmg = calcDamage(e.atk, player->def);
            player->takeDamage(dmg);
        }
    }
}

int Game::calcDamage(int atkVal, int defVal) {
    return (int)std::ceil((100.0 / (100.0 + defVal)) * atkVal);
}

bool Game::isOver() { return !player->isAlive() || floorNum > 5; }



// Game::playerMove -> handles the full player movement action including gold pickup, potion detection, stair check, then calls Character::move



// TODO 
void Game::spawnEnemies() {
}

void Game::spawnPotions() {
}

void Game::spawnGold() {
}
