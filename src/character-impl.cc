module character;
import floor;
import random;

void Character::spawn(Floor& f) {
    x = random(0, 78);
    y = random(0, 29);
    while (!f.validSpawn(x, y)) {
        x = random(0, 78);
        y = random(0, 29);
    }
}

