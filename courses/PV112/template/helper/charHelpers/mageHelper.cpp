#include <vector>
#include <string>
#include "../abilityHelper.hpp"

class mageHelper
{
private:
    std::string name = "Elysian, the Arcanist";
    ClassE charClass = ClassE::MAGE;
    StatPairS health = {100.0f, 100.0f};
    StatPairS mana = {120.0f, 120.0f};
    StatPairS attackDamage = {10.0f, 10.0f};
    StatPairS abilityDamage = {30.0f, 30.0f};
    StatPairS armor = {10.0f, 10.0f};
    StatPairS criticalChance = {0.25f, 0.25f};
    float criticalDamage = 1.65f;
    StatPairS speed = {80.0f, 80.0f};
    StatPairS accuracy = {0.95f, 0.95f};

    Character *createNewMageCharacter();

public:
    mageHelper(/* args */);
    ~mageHelper();

    Character *getMageCharacter();
};

mageHelper::mageHelper(/* args */)
{
}

mageHelper::~mageHelper()
{
}

Character *mageHelper::createNewMageCharacter()
{
    return new Character(
        name,
        charClass,
        health,
        mana,
        attackDamage,
        abilityDamage,
        armor,
        criticalChance,
        criticalDamage,
        speed,
        accuracy);
}

Character *mageHelper::getMageCharacter()
{
    return createNewMageCharacter();
}