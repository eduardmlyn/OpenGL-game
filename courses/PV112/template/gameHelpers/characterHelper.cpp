#include "characterHelper.hpp"

CharacterAction::CharacterAction()
{
    std::random_device rd;  // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 100);
}

CharacterAction::~CharacterAction()
{
}

bool CharacterAction::dealDamageIsKill(bool isUser, float damage)
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
    return character->health <= 0;
}

// TODO change return value?
inline bool CharacterAction::performBasicAttack(bool isUser)
{
    return this->dealDamageIsKill(isUser, basicAttackDamage);
}

inline bool CharacterAction::performSpecialAttack(bool isUser)
{
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
    // float accuracy = distr(gen) / 100.f; // TODO is this needed?
    // if (accuracy > 0.8f)
    // {
    //     return;
    // }
    character->armor += specialDefenseArmor;
}