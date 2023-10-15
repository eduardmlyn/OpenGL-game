#include "../abilityHelper.hpp"

class assassinHelper
{
private:
    std::string name = "Ryuji, the Shadowstrike";
    ClassE charClass = ClassE::ASSASSIN;
    StatPairS health = { 75.0f, 75.0f };
    StatPairS mana = { 100.0f, 100.0f };
    StatPairS attackDamage = { 100.0f, 100.0f };
    StatPairS abilityDamage = { 20.0f, 20.0f };
    StatPairS armor = { 10.0f, 10.0f };
    StatPairS criticalChance = { 0.6f, 0.6f };
    float criticalDamage = 2.0f;
    StatPairS speed = { 100.0f, 100.0f };
    StatPairS accuracy = { 0.9f, 0.9f };

    Character* createNewAssassinCharacter();

public:
    assassinHelper(/* args */);
    ~assassinHelper();

    Character* getAssassinCharacter();
};

assassinHelper::assassinHelper(/* args */)
{
}

assassinHelper::~assassinHelper()
{
}

Character* assassinHelper::createNewAssassinCharacter() {
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
        accuracy
    );
}

Character* assassinHelper::getAssassinCharacter()
{
    return createNewAssassinCharacter();
}