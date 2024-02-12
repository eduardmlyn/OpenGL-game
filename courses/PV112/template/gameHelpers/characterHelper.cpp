#include "characterHelper.hpp"

CharacterAction::CharacterAction(ALuint soundSource)
{
    userChar = {100.f, 30.f, 0, 0};
    enemyChar = {100.f, 30.f, 0, 0};
    this->soundSource = soundSource;
}

CharacterAction::CharacterAction()
{
}

CharacterAction::~CharacterAction()
{
}

void CharacterAction::dealDamageIsKill(bool isUser, float damage)
{
    CharacterData *character;
    if (!isUser)
    {
        character = &userChar;
    }
    else
    {
        character = &enemyChar;
    }
    float accuracy = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) + 1.0f);
    if (accuracy > 0.8f)
    {
        return;
    }
    float critChance = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) + 1.0f);
    if (critChance > 0.8f)
    {
        damage *= 1.2f;
    }
    if (character->armor > 0)
    {
        character->armor -= damage;
        if (character->armor < 0)
        {
            character->health += character->armor;
            character->armor = 0.f;
        }
    }
    else
    {
        character->health -= damage;
    }
    alSourcePlay(soundSource);
}

void CharacterAction::performBasicAttack(bool isUser)
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

    this->dealDamageIsKill(isUser, basicAttackDamage);
}

void CharacterAction::performSpecialAttack(bool isUser)
{
    if (isUser)
    {
        if (userChar.specialAttackCD != 0)
        {
            return;
        }
        userChar.specialDefenseCD = std::max(0, userChar.specialDefenseCD - 1);
        userChar.specialAttackCD = 3;
    }
    else
    {
        if (enemyChar.specialAttackCD != 0)
        {
            return;
        }
        enemyChar.specialDefenseCD = std::max(0, enemyChar.specialDefenseCD - 1);
        enemyChar.specialAttackCD = 3;
    }

    this->dealDamageIsKill(isUser, specialAttackDamage);
}

void CharacterAction::performSpecialDefense(bool isUser)
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
    if (character->specialDefenseCD != 0)
    {
        return;
    }
    character->specialAttackCD = std::max(0, character->specialAttackCD - 1);
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

float CharacterAction::getCharHealth(bool isUser)
{
    return isUser ? userChar.health : enemyChar.health;
}

float CharacterAction::getCharArmor(bool isUser)
{
    return isUser ? userChar.armor : enemyChar.armor;
}

int CharacterAction::getSpecialAttackCD(bool isUser)
{
    return isUser ? userChar.specialAttackCD : enemyChar.specialAttackCD;
}

int CharacterAction::getSpecialDefenseCD(bool isUser)
{
    return isUser ? userChar.specialDefenseCD : enemyChar.specialDefenseCD;
}
