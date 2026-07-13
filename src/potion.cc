// export module potion;

// export enum class PotionType { RH, BA, BD, PH, WA, WD };

// export class Potion {
//     public:
//     PotionType type;
//     bool known = false;
//     Potion(PotionType t) : type{t} {}
// };


// export module potion;
// import constants;

// export class Potion {
//     public:
//     constants::Potion type;
//     bool known = false;
//     int hpMod, atkMod, defMod;
//     bool permanent;

//     Potion(constants::Potion t) : type{t} {
//         if (t == constants::Potion::RH)  { hpMod=10;  atkMod=0;  defMod=0;  permanent=true; }
//         if (t == constants::Potion::PH)  { hpMod=-10; atkMod=0;  defMod=0;  permanent=true; }
//         if (t == constants::Potion::BA)  { hpMod=0;   atkMod=5;  defMod=0;  permanent=false; }
//         if (t == constants::Potion::WA)  { hpMod=0;   atkMod=-5; defMod=0;  permanent=false; }
//         if (t == constants::Potion::BD)  { hpMod=0;   atkMod=0;  defMod=5;  permanent=false; }
//         if (t == constants::Potion::WD)  { hpMod=0;   atkMod=0;  defMod=-5; permanent=false; }
//     }
// };


// //keeping this for now, have yet to figure what to do with applyPotion

// // export module potion;

// // import <algorithm>;
// // import player;

// // export class Potion {
// //     public:
// //     virtual void apply(Player& p) = 0;
// //     void interact(Player& p) { apply(p); }
// // };

// // export class RH : public Potion {
// //     public:
// //     void apply(Player& p) { p.hp = std::min(p.maxHp, p.hp + 10); }
// // };
// // export class BA : public Potion {
// //     public:
// //     void apply(Player& p) { p.atk += 5; }
// // };
// // export class BD : public Potion {
// //     public:
// //     void apply(Player& p) { p.def += 5; }
// // };
// // export class PH : public Potion {
// //     public:
// //     void apply(Player& p) { p.hp = std::max(0, p.hp - 10); }
// // };
// // export class WA : public Potion {
// //     public:
// //     void apply(Player& p) { p.atk = std::max(0, p.atk - 5); }
// // };
// // export class WD : public Potion {
// //     public:
// //     void apply(Player& p) { p.def = std::max(0, p.def - 5); }
// // };
