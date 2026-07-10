// just ideas; to match game-impl spirit

// basically first do playerAttack and then do enemyTurns, which loops through all alive enemies
if (cmd == "a") {
    game.playerAttack(dir);
    game.enemyTurns();
} else if (cmd == "no" || ...) {
    game.playerMove(dir);
    game.enemyTurns();
} else if (cmd == "u") {
    game.usePotion(dir);
    game.enemyTurns();
}