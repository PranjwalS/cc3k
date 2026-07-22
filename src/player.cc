export module player;

import constants;
import character;
import floor;
import <string>;
import <climits>;
import <algorithm>;
import <memory>;

export class Player : public Character {
    protected:
    int gold = 0;
    int score = 0;
    constants::PlayerRace race;
    // Potion potion;
    
    public:
    Player(constants::PlayerRace race, Floor& f) :
        Character{constants::info(race).value(), f}, race{race} {}

    int getGold() const { return gold; }
    int getScore() const { return score; }

    void changeGold(int amount);
    // gainGold and loseGold must take in positive integers
    void gainGold(int amount);
    void loseGold(int amount);
    constants::PlayerRace getRace() const { return race; }
    virtual void onHit(constants::EnemyRace race) {}
    virtual void onKill(constants::EnemyRace race) {}
    virtual void endTurn() {}
    virtual void applyPotion(int hpMod, int atkMod, int defMod) {
        hp = std::min(maxHp, hp + hpMod);
        hp = std::max(0, hp);
        atk = std::max(0, atk + atkMod);
        def = std::max(0, def + defMod);
    }
    bool move(const constants::Direction& dir);
};

export class Shade : public Player {
    public:
    Shade(Floor& f) : Player{constants::PlayerRace::Shade, f} {}
};

export class Drow : public Player {
    public:
    Drow(Floor& f) : Player{constants::PlayerRace::Drow, f} {}
    void applyPotion(int hpMod, int atkMod, int defMod);
};

export class Vampire : public Player {
    public:
    Vampire(Floor& f) : Player{constants::PlayerRace::Vampire, f} {
        maxHp = INT_MAX;
    }
    void onHit(constants::EnemyRace race);
};

export class Troll : public Player {
    public:
    Troll(Floor& f) : Player{constants::PlayerRace::Troll, f} {}
    void endTurn();
};

export class Goblin : public Player {
    public:
    Goblin(Floor& f) : Player{constants::PlayerRace::Goblin, f} {}
    void onKill(constants::EnemyRace race);
};

export std::unique_ptr<Player> newPlayer(constants::PlayerRace race, Floor& f);
