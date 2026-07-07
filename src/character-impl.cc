module character;

void Character::spawn(Floor& f) {
    x = random(0, MAX_Y_POSITION);
    y = random(0, MAX_X_POSITION);
    while (!f.validSpawn(x, y)) {
        x = random(0, MAX_Y_POSITION);
        y = random(0, MAX_X_POSITION);
    }
}
