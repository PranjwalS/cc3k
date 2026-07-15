import game;
import constants;
import <iostream>;

int main(int argv, char* argc[]) {
    Game game(constants::Player::Shade);
    game.spawnAll();
    std::cout << game << std::endl;
}
