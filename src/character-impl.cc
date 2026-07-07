module character;

void Character::spawn(Floor& f) {
    x = random(0, MAX_Y_POSITION);
    y = random(0, MAX_X_POSITION);
    while (!f.validSpawn(x, y)) {
        x = random(0, MAX_Y_POSITION);
        y = random(0, MAX_X_POSITION);
    }
}

bool Character::validMove(Floor& f, std::string dir) {
    auto [dx, dy] = toDir(dir);
    if (x + dx < 0 || x + dx > MAX_X_POSITION ||
        y + dy < 0 || y + dy > MAX_Y_POSITION) return false;
    return true;
}

void Character::move(Floor& f, std::string dir) {
    if (!validMove(f, dir)) return;
    auto [dx, dy] = toDir(dir);
    x += dx;
    y += dy;
}

void Character::defend(Floor& f, int atkVal) {
    if (def <= atkVal) {
        def = 0;
        hp -= atkVal;
    } else {
        def -= atkVal;
    }
}
