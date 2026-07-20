import constants;
import game;
import <iostream>;
import <string>;

constants::Player selectRace() {
    std::string cmd;
    std::cout << "Choose player race: " << std::endl;
    while (std::cin >> cmd) {
        if (isPlayerCmd(cmd)) {
            return cmdToPlayer(cmd).value();
        } else if (cmd == constants::command::QUIT) {
            exit(0);
        } else {
            std::cout << "Please choose valid player race" << std::endl;
        }
    }
    exit(0);
}

int main(int argc, char* argv[]) {
    std::string cmd1, cmd2;

    constants::Player playerRace = selectRace();
    Game game(playerRace);
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
            playerRace = selectRace();
            game = Game(playerRace);
            game.spawnAll();
        } else if (cmd1 == constants::command::QUIT) {
            game.quitGame();
            break;
        }

        game.enemyTurns();
    }

    if (game.isWon()) {
        std::cout << "You win!" << std::endl;
        game.displayScore(std::cout);
    } else if (!game.isOver()) {
        std::cout << "Closing game" << std::endl;
    } else {
        std::cout << "You lose... Try again?" << std::endl;
    }
}