#include <random>
// #include <algorithm>

struct CharacterData
{
    float health;
    float armor;
    int specialAttackCD;
    int specialDefenseCD;
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
    void dealDamageIsKill(bool isUser, float damage);

public:
    CharacterAction();
    ~CharacterAction();
    void performBasicAttack(bool isUser);
    void performSpecialAttack(bool isUser);
    void performSpecialDefense(bool isUser);
    bool isCharDead(bool isUser);
};
