import constants;
import game;
import <iostream>;
import <string>;

int main(int argv, char* argc[]) {
    std::string cmd1; 
    std::string cmd2; 
    constants::Player playerRace;
    bool quit = false;
    std::cout << "Choose player race: " << std::endl;
    while (std::cin >> cmd1) {
        if (isPlayerCmd(cmd1)) {
            playerRace = cmdToPlayer(cmd1).value();
            break;
        } else if (cmd1 == constants::command::QUIT) {
            quit = true;
            break;
        } else {
            std::cout << "Please choose valid player race" << std::endl;
        }
    }
    if (quit) {
        std::cout << "Closing game" << std::endl;
        return 0;
    }
    Game game(playerRace);
    game.spawnAll();

    while (!game.isOver()) {
        game.display(std::cout);
        // basically first do playerAttack and then do enemyTurns, which loops through all alive enemies
        std::cin >> cmd1;
        std::cin >> cmd2;
        if (cmd1 == constants::command::ATTACK) { // "a"
            constants::Direction dir = strToDir(cmd2);
            game.playerAttack(dir);
        } else if (isDirection(cmd1)) { // no,so,ea,...
            constants::Direction dir = strToDir(cmd2);
            game.playerMove(dir);
        } else if (cmd1 == constants::command::USE_POTION) { // "u"
            constants::Direction dir = strToDir(cmd2);
            game.usePotion(dir);
        } else if (cmd1 == constants::command::QUIT) { // "q"
            game.quitGame();
            std::cout << "Closing game" << std::endl;
            quit = true;
            break;
        }
        game.enemyTurns();
    } if (game.isWon()) {
        std::cout << "you win!!" << std::endl;
        game.displayScore(std::cout);
    } else if (quit) {
        std::cout << "Closing game" << std::endl;
    } else {
        std::cout << "you lose... Try again?" << std::endl;
    }
}
