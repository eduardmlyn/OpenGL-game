#include <random>
// #include <time.h>

struct CharacterData
{
    float health;
    float armor;
};

class CharacterAction
{
private:
    CharacterData userChar;
    CharacterData enemyChar;
    float basicAttackDamage = 15.f;
    float specialAttackDamage = 25.f;
    float specialDefenseArmor = 30.f;
    float critChance = 0.2f;
    float accuracy = 0.8f;
    std::uniform_int_distribution<> distr;
    std::mt19937 gen;
    bool dealDamageIsKill(bool isUser, float damage);

public:
    CharacterAction(/* args */);
    ~CharacterAction();
    bool performBasicAttack(bool isUser);
    bool performSpecialAttack(bool isUser);
    void performSpecialDefense(bool isUser);
};
