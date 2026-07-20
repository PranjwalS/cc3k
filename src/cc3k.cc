import constants;
import game;
import <iostream>;
import <string>;
import <optional>;

std::optional<constants::Player> selectRace() {
    std::string cmd;
    std::cout << "Choose player race: " << std::endl;
    while (std::cin >> cmd) {
        if (isPlayerCmd(cmd)) {
            return cmdToPlayer(cmd).value();
        } else if (cmd == constants::command::QUIT) {
            return std::nullopt;
        } else {
            std::cout << "Please choose valid player race" << std::endl;
        }
    }
    return std::nullopt;
}


int main(int argc, char* argv[]) {
    std::string cmd1, cmd2;

    while (true) {
        auto playerRace = selectRace();
        if (!playerRace) return 0;
        Game game(playerRace.value());
        game.spawnAll();

        while (!game.isOver()) {
            game.display(std::cout);
            game.setAction("");

            std::cin >> cmd1;

            if (cmd1 == constants::command::ATTACK ||
                cmd1 == constants::command::USE_POTION) {
                std::cin >> cmd2;
                constants::Direction dir = strToDir(cmd2);
                if (cmd1 == constants::command::ATTACK) {
                    game.playerAttack(dir);
                } else {
                    game.usePotion(dir);
                }
            } else if (isDirection(cmd1)) {
                game.playerMove(strToDir(cmd1));
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