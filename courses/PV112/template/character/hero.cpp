#include "models.hpp"

Character::Character(std::string name,
    ClassE charClass,
    StatPairS health,
    StatPairS mana,
    StatPairS attackDamage,
    StatPairS abilityDamage,
    StatPairS armor,
    StatPairS criticalChance,
    float criticalDamage,
    StatPairS speed,
    StatPairS accuracy,
    ModificationS modifications)
{
}

Character::~Character()
{
}

ClassE Character::getClass()
{
    return this->charClass;
}

bool Character::isTaunting()
{
    return this->modifications.taunt == 0;
}

float Character::getMaxHP()
{
    return this->health.baseValue;
}

float Character::getCurrentHP()
{
    return this->health.currentValue;
}

float Character::geMaxMana()
{
    return this->mana.baseValue;
}

float Character::getCurrentMana()
{
    return this->mana.currentValue;
}

float Character::getMaxAD()
{
    return this->attackDamage.baseValue;
}

float Character::getCurrentAD()
{
    return this->attackDamage.currentValue;
}

float Character::getMaxAP()
{
    return this->abilityDamage.baseValue;
}

float Character::getCurrentAP()
{
    return this->abilityDamage.currentValue;
}

float Character::getMaxArmor()
{
    return this->armor.baseValue;
}

float Character::getCurrentArmor()
{
    return this->armor.currentValue;
}

float Character::getMaxCriticalChance()
{
    return this->criticalChance.baseValue;
}

float Character::getCurrentCriticalChance()
{
    return this->criticalChance.currentValue;
}

float Character::getCriticalDamage()
{
    return this->criticalDamage;
}

float Character::getMaxSpeed()
{
    return this->speed.baseValue;
}

float Character::getCurrentSpeed()
{
    return this->speed.currentValue;
}

float Character::getMaxAccuracy()
{
    return this->accuracy.baseValue;
}

float Character::getCurrentAccuracy()
{
    return this->accuracy.currentValue;
}

void Character::setAbilities(std::vector<AbilityS> abilities) {
    this->abilities = abilities;
}
