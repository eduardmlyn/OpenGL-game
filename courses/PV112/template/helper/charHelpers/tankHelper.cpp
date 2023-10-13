#include <vector>
#include <string>
#include "../abilityHelper.hpp"

class tankHelper
{
private:
    std::string name = "Viktor, the Steelwall";
    ClassE charClass = ClassE::TANK;
    StatPairS health = { 150.0f, 150.0f };
    StatPairS mana = { 60.0f, 60.0f };
    StatPairS attackDamage = { 50.0f, 50.0f };
    StatPairS abilityDamage = { 10.0f, 10.0f };
    StatPairS armor = { 30.0f, 30.0f };
    StatPairS criticalChance = { 0.25f, 0.25f };
    float criticalDamage = 1.55f;
    StatPairS speed = { 60.0f, 60.0f };
    StatPairS accuracy = { 0.7f, 0.7f };
    ModificationS modifications = {};

    Character* createNewTankCharacter();

public:
    tankHelper(/* args */);
    ~tankHelper();

    Character* getTankCharacter();
};

tankHelper::tankHelper(/* args */)
{
}

tankHelper::~tankHelper()
{
}

Character* tankHelper::createNewTankCharacter() {
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
        accuracy,
        modifications
    );
}

Character* tankHelper::getTankCharacter()
{
    return createNewTankCharacter();
}