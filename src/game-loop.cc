// just ideas; to match game-impl spirit
import constants;

constants::Direction playerRace;
while (!constants::command::isPlayerRace(cmd)) {
    if (cmd == constants::command::QUIT) {
        cout << "Closing game" << endl;
    } else {
        cout << "Please choose valid player race: ..." << endl;
    }
}
playerRace = constants::command::toPlayerRace(cmd);
game
while (!game.isOver) {
    // basically first do playerAttack and then do enemyTurns, which loops through all alive enemies
    game.display();
    if (cmd == constants::command::ATTACK) { // "a"
        game.playerAttack(dir);
        game.enemyTurns();
    } else if (constants::command::isDirection(cmd)) { // no,so,ea,...
        constants::Direction dir = constants::command::toDirection(cmd);
        game.playerMove(dir);
        game.enemyTurns();
    } else if (cmd == constants::command::USE) { // "u"
        game.usePotion(dir);
        game.enemyTurns();
    } else if (cmd == constants::command::QUIT) {
        game.endGame();
        cout << "Closing game" << endl;
        break;
    } else 
} if (game.isWon) {
    cout << "you win!!" << endl;
    game.displayScore();
} else {
    cout << "you lose... Try again?" << endl;
}
