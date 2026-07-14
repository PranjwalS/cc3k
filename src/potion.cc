export module potion;

import constants;
import random;

export class Potion {
    constants::PotionType type;
    bool known = false;
    int hpMod, atkMod, defMod;
    bool permanent;

    public:

    Potion(constants::PotionType t) : type{t}, hpMod{0}, atkMod{0}, defMod{0}, permanent{false} {
        if (t == constants::PotionType::RH) { hpMod=10;  permanent=true; }
        else if (t == constants::PotionType::PH) { hpMod=-10; permanent=true; }
        else if (t == constants::PotionType::BA) { atkMod=5; }
        else if (t == constants::PotionType::WA) { atkMod=-5; }
        else if (t == constants::PotionType::BD) { defMod=5; }
        else if (t == constants::PotionType::WD) { defMod=-5; }
    }

    constants::PotionType getType() const { return type; }
    bool isKnown() const { return known; }
    void becomeKnown() { known = true; }
    int getHpMod() const { return hpMod; }
    int getAtkMod() const { return atkMod; }
    int getDefMod() const { return defMod; }
    bool isPermanent() const { return permanent; }
};

export constants::PotionType randomPotion()  {
    return static_cast<constants::PotionType>(
        randomNum(0, constants::NUM_POTION_TYPES - 1)
    );
}