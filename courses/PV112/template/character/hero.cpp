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
                     StatPairS accuracy)
{
    this->name = name;
    this->charClass = charClass;
    this->health = health;
    this->mana = mana;
    this->attackDamage = attackDamage;
    this->abilityDamage = abilityDamage;
    this->armor = armor;
    this->criticalChance = criticalChance;
    this->criticalDamage = criticalDamage;
    this->speed = speed;
    this->accuracy = accuracy;
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

void Character::setAbilities(std::vector<AbilityS> abilities)
{
    this->abilities = abilities;
}

void Character::receiveDamage(float damage)
{
    this->health.currentValue -= damage;
}

void Character::setModifications(ModificationS modifications)
{
    if (modifications.attackDamage.duration > this->modifications.attackDamage.duration)
    {
        this->modifications.attackDamage = modifications.attackDamage;
    }
    if (modifications.abilityDamage.duration > this->modifications.abilityDamage.duration)
    {
        this->modifications.abilityDamage = modifications.abilityDamage;
    }
    if (modifications.armor.duration > this->modifications.armor.duration)
    {
        this->modifications.armor = modifications.armor;
    }
    if (modifications.criticalChance.duration > this->modifications.criticalChance.duration)
    {
        this->modifications.criticalChance = modifications.criticalChance;
    }
    if (modifications.speed.duration > this->modifications.speed.duration)
    {
        this->modifications.speed = modifications.speed;
    }
    if (modifications.accuracy.duration > this->modifications.accuracy.duration)
    {
        this->modifications.accuracy = modifications.accuracy;
    }
    if (modifications.taunt > this->modifications.taunt)
    {
        this->modifications.taunt = modifications.taunt;
    }
}

void Character::updateModificationsAfterTurn()
{
    this->updateAttackDamage();
    this->updateAbilityDamage();
    this->updateArmor();
    this->updateCriticalChance();
    this->updateSpeed();
    this->updateAccuracy();
    if (this->modifications.taunt != 0)
    {
        this->modifications.taunt--;
    }
}

void Character::updateAttackDamage()
{
    if (this->modifications.attackDamage.duration == 1)
    {
        if (this->modifications.attackDamage.percentage)
        {
            this->attackDamage.currentValue -= this->attackDamage.baseValue * this->modifications.attackDamage.value;
        }
        else
        {
            this->attackDamage.currentValue -= this->modifications.attackDamage.value;
        }
        this->modifications.attackDamage.duration--;
    }
    if (this->modifications.attackDamage.duration != 0)
    {
        this->modifications.attackDamage.duration--;
    }
}

void Character::updateAbilityDamage()
{
    if (this->modifications.abilityDamage.duration == 1)
    {
        if (this->modifications.abilityDamage.percentage)
        {
            this->abilityDamage.currentValue -= this->abilityDamage.baseValue * this->modifications.abilityDamage.value;
        }
        else
        {
            this->abilityDamage.currentValue -= this->modifications.abilityDamage.value;
        }
        this->modifications.abilityDamage.duration--;
    }
    if (this->modifications.abilityDamage.duration != 0)
    {
        this->modifications.abilityDamage.duration--;
    }
}

void Character::updateArmor()
{
    if (this->modifications.armor.duration == 1)
    {
        if (this->modifications.armor.percentage)
        {
            this->armor.currentValue -= this->armor.baseValue * this->modifications.armor.value;
        }
        else
        {
            this->armor.currentValue -= this->modifications.armor.value;
        }
        this->modifications.armor.duration--;
    }
    if (this->modifications.armor.duration != 0)
    {
        this->modifications.armor.duration--;
    }
}

void Character::updateCriticalChance()
{
    if (this->modifications.criticalChance.duration == 1)
    {
        if (this->modifications.criticalChance.percentage)
        {
            this->criticalChance.currentValue -= this->criticalChance.baseValue * this->modifications.criticalChance.value;
        }
        else
        {
            this->armor.currentValue -= this->modifications.criticalChance.value;
        }
        this->modifications.criticalChance.duration--;
    }
    if (this->modifications.criticalChance.duration != 0)
    {
        this->modifications.criticalChance.duration--;
    }
}

void Character::updateSpeed()
{
    if (this->modifications.speed.duration == 1)
    {
        if (this->modifications.speed.percentage)
        {
            this->armor.currentValue -= this->speed.baseValue * this->modifications.speed.value;
        }
        else
        {
            this->armor.currentValue -= this->modifications.speed.value;
        }
        this->modifications.speed.duration--;
    }
    if (this->modifications.speed.duration != 0)
    {
        this->modifications.speed.duration--;
    }
}

void Character::updateAccuracy()
{
    if (this->modifications.accuracy.duration == 1)
    {
        if (this->modifications.accuracy.percentage)
        {
            this->accuracy.currentValue -= this->accuracy.baseValue * this->modifications.accuracy.value;
        }
        else
        {
            this->accuracy.currentValue -= this->modifications.accuracy.value;
        }
        this->modifications.accuracy.duration--;
    }
    if (this->modifications.accuracy.duration != 0)
    {
        this->modifications.accuracy.duration--;
    }
}

void Character::gainMana(float mana)
{
    this->mana.currentValue += mana;
}