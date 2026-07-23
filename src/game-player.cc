module game;

bool Game::playerAttack(constants::Direction d) {
    auto [dx, dy] = dirToPair(d);

    int tx = player->getX() + dx;
    int ty = player->getY() + dy;
    if (!constants::board::isInBounds(tx, ty)) return false;

    int idx = floor.getEnemiesIndex()[ty][tx];

    if (idx != -1) {
        Enemy* e = enemies[idx].get();
        std::string enemySymbol(1, enemyRaceToSymbol(e->getRace()));
        // halfling chance of evasion — takes priority
        if (e->evasionChance()) {
            currentAction = enemySymbol + " evades PC's attack.";
            return true;
        }

        // player hits
        int dmg = calcDamage(player->getAtk(), e->getDef());
        if (e->getRace() == constants::EnemyRace::Orc && 
            player->getRace() == constants::PlayerRace::Goblin) {
            // orc bonus vs goblin
            dmg = static_cast<int>(dmg * constants::multiplier::ORC_ATTACK_GOBLIN);
        }

        e->takeDamage(dmg);
        player->onHit(e->getRace());
        currentAction = "PC deals " + std::to_string(dmg) + " damage to " + enemySymbol
                        + " (" + std::to_string(e->getHp()) + " HP)";

        if (player->getRace() == constants::PlayerRace::Vampire) {
            if (e->getRace() == constants::EnemyRace::Dwarf) {
                currentAction += ". PC has an allergic reaction and loses " 
                              + std::to_string(constants::VAMPIRE_ALLERGY_HP_LOSS) + " HP";
            } else {
                currentAction += " and PC gains " 
                              + std::to_string(constants::VAMPIRE_LIFESTEAL) + " HP";
            }
        }

        currentAction += ".";
        
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
                int gld_idx = floor.getGoldIndex()[ny][nx];
                Gold* gld = gold[gld_idx].get();
                gld->toggleDragonGuarded();
            } else { e->onDeath(*player); }
            player->onKill(e->getRace());

            currentAction += " " + enemySymbol + " is slain";
            if (player->getRace() == constants::PlayerRace::Goblin) {
                currentAction += " and PC steals " 
                                 + std::to_string(constants::GOBLIN_STEAL) + " Gold";
            }
            currentAction += ".";
        }
        return true;
    }
    return false;
}

bool Game::playerMove(constants::Direction dir) {
    int px = player->getX();
    int py = player->getY();
    if (!player->move(dir)) return false;
    int nx = player->getX();
    int ny = player->getY();
    currentAction = "PC moves " + std::string(dirToStr(dir)) + ".";

    std::string seenPotions = "";
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            int cx = nx + dx;
            int cy = ny + dy;
            if (!constants::board::isInBounds(cx, cy)) continue;
            int potionIdx = floor.getPotionsIndex()[cy][cx];
            if (potionIdx == -1) continue;
            std::string name;
            if (knownPotions.count(potions[potionIdx]->getType())) {
                name = std::string(potionTypeToStr(potions[potionIdx]->getType()));
            } else {
                name = "an unknown potion";
            }
            seenPotions += (seenPotions.empty() ? "" : ", ") + name;
        }
    }
    if (!seenPotions.empty()) currentAction += " PC sees " + seenPotions + ".";

    int gIdx = floor.getGoldIndex()[ny][nx];
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

    if (floor.getGrid()[ny][nx] == constants::symbol::STAIRS) {
        player->applyPotion(0, -tempAtk, -tempDef); 
        tempAtk = 0;
        tempDef = 0;
        nextFloor();
        currentAction = "PC descends to floor " + std::to_string(floorNum) + ".";
        return true;
    }

    floor.movePlayer(px, py, nx, ny);
    return true;
}

void Game::usePotion(constants::Direction dir) {
    auto [dx, dy] = dirToPair(dir);
    int tx = player->getX() + dx;
    int ty = player->getY() + dy;
    if (!constants::board::isInBounds(tx, ty)) return;
    int idx = floor.getPotionsIndex()[ty][tx];
    if (idx == -1) return;
    Potion* p = potions[idx].get();
    if (!p->isPermanent()) {
        tempAtk += p->getAtkMod();
        tempDef += p->getDefMod();
    }

    player->applyPotion(p->getHpMod(), p->getAtkMod(), p->getDefMod());
    std::string potionName = std::string(potionTypeToStr(p->getType()));
    knownPotions.insert(p->getType());
    floor.removePotion(tx, ty);
    playerMove(dir);
    currentAction = " PC uses " + potionName + ".";
}
