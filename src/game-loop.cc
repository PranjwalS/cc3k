// just ideas; to match game-impl spirit

while (!game.isOver) {
    // basically first do playerAttack and then do enemyTurns, which loops through all alive enemies
    game.display();
    if (cmd == "a") {
        game.playerAttack(dir);
        game.enemyTurns();
    } else if (cmd == "no" || ...) {
        game.playerMove(dir);
        game.enemyTurns();
    } else if (cmd == "u") {
        game.usePotion(dir);
        game.enemyTurns();
    } else if (cmd == "q") {
        game.endGame();
        break;
    }
} if (game.isWon) {
    cout << "you win!!" << endl;
    game.displayScore();
} else {
    cout << "you lose... Try again?" << endl;
    game.displayScore();
}
