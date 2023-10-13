#include <vector>
#include <string>
#include "../abilityHelper.hpp"

class marksmanHelper
{
private:
    std::string name = "Luna, the Swiftshot";
    ClassE charClass = ClassE::MARKSMAN;
    StatPairS health = { 100.0f, 100.0f };
    StatPairS mana = { 80.0f, 80.0f };
    StatPairS attackDamage = { 70.0f, 70.0f };
    StatPairS abilityDamage = { 0.0f, 0.0f };
    StatPairS armor = { 10.0f, 10.0f };
    StatPairS criticalChance = { 0.5f, 0.5f };
    float criticalDamage = 1.75f;
    StatPairS speed = { 100.0f, 100.0f };
    StatPairS accuracy = { 0.8f, 0.8f };
    ModificationS modifications = {};

    Character* createNewMarksmanCharacter();

public:
    marksmanHelper(/* args */);
    ~marksmanHelper();

    Character* getMarksmanCharacter();
};

marksmanHelper::marksmanHelper(/* args */)
{
}

marksmanHelper::~marksmanHelper()
{
}

Character* marksmanHelper::createNewMarksmanCharacter() {
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

Character* marksmanHelper::getMarksmanCharacter()
{
    return createNewMarksmanCharacter();
}