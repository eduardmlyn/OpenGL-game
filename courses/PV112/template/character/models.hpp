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
    ModificationS modifications = {}; // TODO change this to all variables set to zero?(do in constructor)
    // TODO think of buffs vs debuffs and the implementation
    std::vector<AbilityS> abilities;

    void updateAttackDamage();
    void updateAbilityDamage();
    void updateArmor();
    void updateCriticalChance();
    void updateSpeed();
    void updateAccuracy();

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
        StatPairS accuracy);
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
    void receiveDamage(float damage);
    void setModifications(ModificationS modifications);
    void updateModificationsAfterTurn();
    void setAbilities(std::vector<AbilityS> abilities);
    void setMana(float mana);
    void setAbilities(std::vector<AbilityS> abilities);
    void healHealth(float health);
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
    ModificationTripleS attackDamage;
    ModificationTripleS abilityDamage;
    ModificationTripleS armor;
    ModificationTripleS criticalChance;
    ModificationTripleS speed;
    ModificationTripleS accuracy;
    int taunt;
};
