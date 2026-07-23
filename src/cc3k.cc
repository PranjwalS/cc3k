import constants;
import game;
import <iostream>;
import <string>;
import <optional>;
import <algorithm>;
import <fstream>;
import <vector>;

std::optional<constants::PlayerRace> selectRace() {
    std::string cmd;
    std::cout << "Choose player race: " << std::endl;
    while (std::cin >> cmd) {
        if (isPlayerRaceCmd(cmd)) {
            return cmdToPlayerRace(cmd).value();
        } else if (cmd == constants::command::QUIT) {
            return std::nullopt;
        } else {
            std::cout << "Please choose valid player race" << std::endl;
        }
    }
    return std::nullopt;
}

std::vector<std::string> readMaps(std::ifstream& s) {
    std::vector<std::string> maps;

    while (true) {
        std::string map;
        for (int h = 0; h < constants::board::HEIGHT; h++) {
            std::string line;
            std::getline(s, line);
            if (s.eof()) {
                return maps;
            }
            map += line;
        }

        maps.push_back(map);
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> maps;
    if (argc > 1) {
        std::ifstream file(argv[1]);
        maps = std::move(readMaps(file));
    }

    std::string cmd1, cmd2;

    while (true) {
        auto playerRace = selectRace();
        if (!playerRace) return 0;
        Game game(playerRace.value(), maps.empty() ? constants::board::NUM_FLOORS : maps.size(),
                  constants::board::NUM_CHAMBERS, maps);

        while (!game.isOver()) {
            game.display(std::cout);
            game.setAction("");

            std::cin >> cmd1;

            if (cmd1 == constants::command::ATTACK ||
                cmd1 == constants::command::USE_POTION) {
                std::cin >> cmd2;
                constants::Direction dir = cmdToDir(cmd2);
                if (cmd1 == constants::command::ATTACK) {
                    game.playerAttack(dir);
                } else {
                    game.usePotion(dir);
                }
            } else if (isDirection(cmd1)) {
                game.playerMove(cmdToDir(cmd1));
            } else if (cmd1 == constants::command::FREEZE) {
                game.toggleFreeze();
            } else if (cmd1 == constants::command::RESTART) {
                break;  // breaks inner loop, outer loop prompts new race
            } else if (cmd1 == constants::command::QUIT) {
                std::cout << "Closing game" << std::endl;
                return 0;
            }
            game.enemyTurns();
        }

        if (game.isWon()) {
            std::cout << "You win!" << std::endl;
            game.displayScore(std::cout);
        } else if (game.isOver() && !game.isWon()) {
            std::cout << "You lose..." << std::endl;
        }

        std::cout << "Play again huh? (y/n): ";
        std::cin >> cmd1;
        if (cmd1 != "y") {
            std::cout << "Closing game" << std::endl;
            return 0;
        }
    }
}
