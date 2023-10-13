#include <vector>
#include <string>

// --------------------------
// CLASSES
// --------------------------

class Character
{
private:
    std::string name;
    ClassE charClass;
    StatPairS health;
    StatPairS mana;
    StatPairS attackDamage;
    StatPairS abilityDamage;
    StatPairS armor;
    StatPairS criticalChance;
    float criticalDamage;
    StatPairS speed;
    StatPairS accuracy;
    ModificationS modifications;
    std::vector<AbilityS> abilities;

public:
    Character();
    Character(
        std::string name,
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
        ModificationS modifications
    );
    ~Character();

    // TODO check if all functions are needed regularly
    ClassE getClass();
    bool isTaunting();
    float getMaxHP();
    float getCurrentHP();
    float geMaxMana();
    float getCurrentMana();
    float getMaxAD();
    float getCurrentAD();
    float getMaxAP();
    float getCurrentAP();
    float getMaxArmor();
    float getCurrentArmor();
    float getMaxCriticalChance();
    float getCurrentCriticalChance();
    float getCriticalDamage();
    float getMaxSpeed();
    float getCurrentSpeed();
    float getMaxAccuracy();
    float getCurrentAccuracy();
    void setAbilities(std::vector<AbilityS> abilities);
};

// --------------------------
// CHARACTER ENUMS
// --------------------------
typedef enum ClassE
{
    MAGE,
    TANK,
    HEALER,
    ASSASSIN,
    MARKSMAN
};

// --------------------------
// CHARACTER STRUCTS
// --------------------------
struct ModificationTripleS
{
    bool percentage;
    float value;
    int duration;
};

struct StatPairS
{
    float currentValue;
    float baseValue;
};

struct ModificationS
{
    ModificationTripleS health;
    ModificationTripleS mana;
    ModificationTripleS attackDamage;
    ModificationTripleS abilityDamage;
    ModificationTripleS armor;
    ModificationTripleS criticalChance;
    ModificationTripleS criticalDamage; // is this one needed?
    ModificationTripleS speed;
    ModificationTripleS accuracy;
    int taunt;
};

struct AbilityS
{
    std::string name;
    float manaCost;
    float adRatio;
    float apRatio;
    bool isAOE;
    bool startOnCooldown;
    int cooldown;
    std::string description;
    void (*trigger)(Character character, std::vector<Character> enemies, const AbilityS &ability);
};

// struct CharacterS {
//     std::string name;
//     ClassE clazz;
//     float health;
//     float mana;
//     float attackDamage;
//     float abilityDamage;
//     float armor;
//     float criticalChance;
//     float criticalDamage;
//     float speed;
//     float accuracy;
//     bool isTaunting;
//     ModificationS modifications;
//     std::vector<AbilityS> abilities;
//     void useAbility(const AbilityS& ability) {
//         // TODO add some other functionality?
//         ability.trigger(*this, ability);
//     }
// };
