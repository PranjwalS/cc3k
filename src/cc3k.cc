import constants;
import game;
import getch;
import <iostream>;
import <string>;
import <optional>;
import <algorithm>;
import <fstream>;
import <vector>;

std::optional<constants::PlayerRace> selectRace() {
    std::string cmd;
    std::cout << "Choose player race: " ;
    while (std::cin >> cmd) {
        if (isPlayerRaceCmd(cmd)) {
            return cmdToPlayerRace(cmd).value();
        } else if (cmd == constants::command::QUIT) {
            return std::nullopt;
        } else {
            std::cout << "Please choose valid player race" << std::endl;
            std::cout << "Choose player race: " ;
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

void input(std::string& s, bool useGetch=false) {
    if (useGetch) {
        char c = getch();
        s = c;
    } else {
        std::cin >> s;
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> maps;
    bool useGetch = false;

    if (argc > 1) {
        std::ifstream file(argv[1]);
        if (file.good()) maps = std::move(readMaps(file));

        for (int i = file.good() + 1; i < std::min(argc, 3); i++) {
            if (std::string(argv[i]) == "getch") {
                useGetch = true;
            }
        }
    }

    std::string cmd1, cmd2;

    while (true) {
        auto playerRace = selectRace();
        if (!playerRace) return 0;
        Game game(playerRace.value(), maps.empty() ? constants::board::NUM_FLOORS : maps.size(),
                  constants::board::NUM_CHAMBERS, maps);

        while (!game.isOver()) {
            std::cout << '\n';
            game.display(std::cout);
            game.setAction("");

            input(cmd1, useGetch);
            if (cmd1 == constants::command::ATTACK ||
                cmd1 == constants::command::USE_POTION) {
                input(cmd2, useGetch);
                constants::Direction dir = cmd2.size() == 1 ? cmdToDir(szxcToDir(cmd2)) : cmdToDir(cmd2);
                if (cmd1 == constants::command::ATTACK) {
                    game.playerAttack(dir);
                } else {
                    game.usePotion(dir);
                }
            } else if (isDirection(cmd1) || isDirection(szxcToDir(cmd1))) {
                game.playerMove(cmd1.size() == 1 ? cmdToDir(szxcToDir(cmd1)) : cmdToDir(cmd1));
            } else if (cmd1 == constants::command::FREEZE) {
                game.toggleFreeze();
            } else if (cmd1 == constants::command::RESTART) {
                break;  // breaks inner loop, outer loop prompts new race
            } else if (cmd1 == constants::command::QUIT) {
                std::cout << "Closing game" << std::endl;
                return 0;
            } else {
                std::cout << "Invalid command!" << std::endl;
                continue;
            }
            game.enemyTurns();
        }

        if (game.isWon()) {
            std::cout << "You win!" << std::endl;
            game.displayScore(std::cout);
        } else if (game.isOver() && !game.isWon()) {
            std::cout << "You lose..." << std::endl;
        }

        std::cout << "Play again huh? (y/n): " << std::endl;
        input(cmd1, useGetch);
        if (cmd1 != "y") {
            std::cout << "Closing game" << std::endl;
            return 0;
        }
    }
}
