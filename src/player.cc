export module player;

import character;
class Floor;

export class Player : public Character {
    Player();
};
export class Shade : public Player {};
export class Drow : public Player {};
export class Vampire : public Player {};
export class Troll : public Player {};
export class Goblin : public Player {};