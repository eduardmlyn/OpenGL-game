#include "characterHelper.hpp"

CharacterAction::CharacterAction()
{
    std::random_device rd;  // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 100);
    userChar = {100.f, 30.f, 0, 0};
    enemyChar = {100.f, 30.f, 0, 0};
}

CharacterAction::~CharacterAction()
{
}

void CharacterAction::dealDamageIsKill(bool isUser, float damage)
{
    CharacterData *character;
    if (isUser)
    {
        character = &userChar;
    }
    else
    {
        character = &enemyChar;
    }
    float accuracy = distr(gen) / 100.f;
    if (accuracy > 0.8f)
    {
        return;
    }
    float critChance = distr(gen) / 100.f;

    if (critChance > 0.8f)
    {
        damage *= 1.2f;
    }
    if (character->armor > 0)
    {
        character->armor -= damage;
    }
    if (character->armor < 0)
    {
        character->health += character->armor;
        character->armor = 0.f;
    }
}

inline void CharacterAction::performBasicAttack(bool isUser)
{
    if (isUser)
    {
        userChar.specialAttackCD = std::max(0, userChar.specialAttackCD - 1);
        userChar.specialDefenseCD = std::max(0, userChar.specialDefenseCD - 1);
    }
    else
    {
        enemyChar.specialAttackCD = std::max(0, enemyChar.specialAttackCD - 1);
        enemyChar.specialDefenseCD = std::max(0, enemyChar.specialDefenseCD - 1);
    }

    return this->dealDamageIsKill(isUser, basicAttackDamage);
}

inline void CharacterAction::performSpecialAttack(bool isUser)
{
    if (isUser)
    {
        userChar.specialAttackCD = 3;
    }
    else
    {
        enemyChar.specialAttackCD = 3;
    }

    return this->dealDamageIsKill(isUser, specialAttackDamage);
}

inline void CharacterAction::performSpecialDefense(bool isUser)
{
    CharacterData *character;
    if (isUser)
    {
        character = &userChar;
    }
    else
    {
        character = &enemyChar;
    }
    character->specialDefenseCD = 3;
    character->armor += specialDefenseArmor;
}

bool CharacterAction::isCharDead(bool isUser)
{
    if (isUser)
    {
        return userChar.health <= 0;
    }
    return enemyChar.health <= 0;
}
