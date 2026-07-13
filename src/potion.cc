export module potion;

import constants;
import random;

export class Potion {
    public:
    constants::PotionType type;
    bool known = false;
    int hpMod, atkMod, defMod;
    bool permanent;

    Potion(constants::PotionType t) : type{t}, hpMod{0}, atkMod{0}, defMod{0}, permanent{false} {
        if (t == constants::PotionType::RH) { hpMod=10;  permanent=true; }
        else if (t == constants::PotionType::PH) { hpMod=-10; permanent=true; }
        else if (t == constants::PotionType::BA) { atkMod=5; }
        else if (t == constants::PotionType::WA) { atkMod=-5; }
        else if (t == constants::PotionType::BD) { defMod=5; }
        else if (t == constants::PotionType::WD) { defMod=-5; }
    }

    constants::PotionType randomPotion() {
        return static_cast<constants::PotionType>(
            randomNum(0, static_cast<int>(constants::PotionType::Count) - 1)
        );
    }
};