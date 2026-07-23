export module potion;

import constants;
import random;

export class Potion {
    constants::PotionType type;
    int hpMod, atkMod, defMod;
    bool permanent;

    public:

    Potion(constants::PotionType t) : type{t} {
        const constants::PotionInfo& info = constants::info(t).value();
        hpMod = info.hpMod;
        atkMod = info.atkMod;
        defMod = info.defMod;
        permanent = info.permanent;
    }

    constants::PotionType getType() const { return type; }
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
