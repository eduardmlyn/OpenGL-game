#include <vector>
#include <string>
#include "models.hpp"

Character::Character(/* args */)
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
    return this->health.maxValue;
}

float Character::getCurrentHP()
{
    return this->health.currentValue;
}

float Character::geMaxMana()
{
    return this->mana.maxValue;
}

float Character::getCurrentMana()
{
    return this->mana.currentValue;
}

float Character::getMaxAD()
{
    return this->attackDamage.maxValue;
}

float Character::getCurrentAD()
{
    return this->attackDamage.currentValue;
}

float Character::getMaxAP()
{
    return this->abilityDamage.maxValue;
}

float Character::getCurrentAP()
{
    return this->abilityDamage.currentValue;
}

float Character::getMaxArmor()
{
    return this->armor.maxValue;
}

float Character::getCurrentArmor()
{
    return this->armor.currentValue;
}

float Character::getMaxCriticalChance()
{
    return this->criticalChance.maxValue;
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
    return this->speed.maxValue;
}

float Character::getCurrentSpeed()
{
    return this->speed.currentValue;
}

float Character::getMaxAccuracy()
{
    return this->accuracy.maxValue;
}

float Character::getCurrentAccuracy()
{
    return this->accuracy.currentValue;
}
