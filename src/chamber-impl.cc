module chamber;

bool Chamber::contains(int x, int y) {
    return occupancy[y][x];
}
