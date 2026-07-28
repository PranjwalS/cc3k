import constants;
import game;
import getch;
import <iostream>;
import <string>;
import <string_view>;
import <optional>;
import <algorithm>;
import <fstream>;
import <vector>;
import <sstream>;

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

std::vector<std::string> readMaps(std::istream& s) {
    std::vector<std::string> maps;
    std::string map;
    char ch;

    while (s.get(ch)) {
        if (ch == '\n' || ch == '\r') continue;
        map.push_back(ch);
        if (static_cast<int>(map.size()) == constants::board::WIDTH * constants::board::HEIGHT) {
            maps.push_back(map);
            map.clear();
        }
    }

    if (!map.empty()) {
        if (static_cast<int>(map.size()) == constants::board::WIDTH * constants::board::HEIGHT) {
            maps.push_back(map);
        }
    }

    return maps;
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
    std::ifstream file;
    std::vector<std::string> maps;

    bool useCustom = false;
    bool useGetch = false;
    bool useDLC = false;
    
    int arg = 1;

    // First parameter may possibly be custom floor layout file
    if (arg < argc) {
        file.open(argv[arg]);
        if (file.good()) {
            maps = readMaps(file);
            useCustom = true;
            ++arg;
        }
    }

    // Flags
    while (arg < argc) {
        std::string option = argv[arg];

        if (option == "getch") {
            useGetch = true;
        } else if (option == "dlc") {
            useDLC = true;
        } else {
            std::cerr << "Unknown option: " << option << '\n';
            return 1;
        }
        ++arg;
    }

    std::string cmd1, cmd2;

    while (true) {
        auto playerRace = selectRace();
        if (!playerRace) return 0;
        Game game(playerRace.value(), maps.empty() ? constants::board::NUM_FLOORS : maps.size(),
                  constants::board::NUM_CHAMBERS, maps, useCustom, useDLC);

        while (!game.isOver()) {
            std::cout << '\n';
            game.display(std::cout);
            std::cout << "Enter command: " << std::flush;
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
        game.setMerchantsPassive();

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
