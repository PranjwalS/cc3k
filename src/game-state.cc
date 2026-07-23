module game;

import <cmath>;
import <iomanip>;

void Game::nextFloor() {
    if (floorNum > numFloors) return;
    int numChambers = floor.getNumChambers();
    ++floorNum;
    floor = Floor(numChambers);
    removeAll();
    player->changeFloor(floor);

    if (maps.empty()) {
        spawnAll();
    } else {
        useNextMap();
    }
}

int Game::calcDamage(int atkVal, int defVal) const {
    return (int)std::ceil((100.0 / (100.0 + defVal)) * atkVal);
}

void Game::quitGame() { forceQuit = true; }

bool Game::isOver() const { return !player->isAlive() || isWon() || forceQuit; }

bool Game::isWon() const { return floorNum > numFloors; }

void Game::displayAction(std::ostream& os) const {
    os << "Action: " << currentAction << "\n";
}

void Game::displayInfo(std::ostream& os) const {
    int lineWidth = constants::board::WIDTH - constants::board::OFFSET;

    // Outputting the first line of info output
    std::string playerRaceStr = std::string(playerRaceToStr(player->getRace()));
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
    os << "Score: " << score << "\n";
}

void Game::display(std::ostream& os) const {
    os << floor;
    displayInfo(os);
}
