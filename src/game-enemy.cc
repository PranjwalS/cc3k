module game;

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
    if (player->getRace() == constants::PlayerRace::Troll) {
        int gainableHp = player->getMaxHp() - player->getHp();
        int hpGain = std::min(constants::TROLL_REGEN, gainableHp);
        if (hpGain > 0) currentAction += " PC regenerates " + std::to_string(hpGain) + " HP.";
    }
    if (player->isAlive()) player->endTurn();
}

// called by enemyTurns
void Game::enemyAttack(Enemy& e) {      
    // elf double attack unless drow
    int attacks = (e.getRace() == constants::EnemyRace::Elf && 
                                  player->getRace() != constants::PlayerRace::Drow) ? 2 : 1;
    std::string enemySymbol(1, enemyRaceToSymbol(e.getRace()));

    for (int i = 0; i < attacks; i++) {
        if (randomChance(constants::probability::ENEMY_MISS)) {
            int dmg = calcDamage(e.getAtk(), player->getDef());
            player->takeDamage(dmg);
            currentAction += " " + enemySymbol + " deals " 
                             + std::to_string(dmg) + " damage to PC.";
        }
    }
}
