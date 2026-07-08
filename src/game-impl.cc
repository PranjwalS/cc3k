module game;

import <iostream>;

void Game::init(char race) {
    if (race == 's') player = new Shade{floor};
    else if (race == 'd') player = new Drow{floor};
    else if (race == 'v') player = new Vampire{floor};
    else if (race == 't') player = new Troll{floor};
    else if (race == 'g') player = new Goblin{floor};
    spawnEnemies();     // todo these 3
    spawnPotions();
    spawnGold();
}

void Game::playerAttack(std::string dir) {
    auto [dx, dy] = toDir(dir);
    int tx = player->x + dx;
    int ty = player->y + dy;
    for (Enemy* e : enemies) {
        if (e->x == tx && e->y == ty && e->isAlive()) {
            if (e->missChance()) return;
            // elf double attack unless drow
            int attacks = (e->symbol == 'E' && player->type != 'D') ? 2 : 1;
            for (int i = 0; i < attacks; i++) {
                int dmg = calcDamage(e->atk, player->def);
                player->takeDamage(dmg);
            }
            // player hits back
            int dmg = calcDamage(player->atk, e->def);
            // orc bonus vs goblin
            if (e->symbol == 'O' && player->type == 'G') dmg = (int)(dmg * 1.5);
            e->takeDamage(dmg);
            player->onHit(e->symbol);
            if (!e->isAlive()) {
                e->onDeath(player->gold);
                player->onKill(e->symbol);
            }
            return;
        }
    }
}

void Game::enemyTurns() {
    if (frozen) return;
    for (Enemy* e : enemies) {
        if (!e->isAlive()) continue;
        bool inRadius = std::abs(e->x - player->x) <= 1 && 
                        std::abs(e->y - player->y) <= 1;
        if (inRadius && (e->hostile || e->symbol != 'M')) {
            if (random(0, 1)) {
                int dmg = calcDamage(e->atk, player->def);
                player->takeDamage(dmg);
            }
        } else {
            e->move(floor);
        }
    }
    player->endTurn();
}




// TODO 
void Game::spawnEnemies() {
}

void Game::spawnPotions() {
}

void Game::spawnGold() {
}

