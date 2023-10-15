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
<<<<<<< HEAD
    ModificationS modifications = {}; // TODO change this to all variables set to zero?(do in constructor)
    std::vector<AbilityS> abilities;

    void updateAttackDamage();
    void updateAbilityDamage();
    void updateArmor();
    void updateCriticalChance();
    void updateSpeed();
    void updateAccuracy();

=======
    ModificationS modifications;
    std::vector<AbilityS> abilities;

>>>>>>> f10b4960ed46076f57385ee11baace1ccc1396d6
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
<<<<<<< HEAD
        StatPairS accuracy);
=======
        StatPairS accuracy,
        ModificationS modifications
    );
>>>>>>> f10b4960ed46076f57385ee11baace1ccc1396d6
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
<<<<<<< HEAD
    void receiveDamage(float damage);
    void setModifications(ModificationS modifications);
    void updateModificationsAfterTurn();
    void setAbilities(std::vector<AbilityS> abilities);
    void gainMana(float mana);
=======
    void setAbilities(std::vector<AbilityS> abilities);
>>>>>>> f10b4960ed46076f57385ee11baace1ccc1396d6
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
<<<<<<< HEAD
=======
    ModificationTripleS health;
    ModificationTripleS mana;
>>>>>>> f10b4960ed46076f57385ee11baace1ccc1396d6
    ModificationTripleS attackDamage;
    ModificationTripleS abilityDamage;
    ModificationTripleS armor;
    ModificationTripleS criticalChance;
<<<<<<< HEAD
=======
    ModificationTripleS criticalDamage; // is this one needed?
>>>>>>> f10b4960ed46076f57385ee11baace1ccc1396d6
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
<<<<<<< HEAD
    int baseCooldown;
    int currentCooldown;
    std::string description;
    bool (*trigger)(Character character, std::vector<Character> enemies, const AbilityS &ability);
};
=======
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
>>>>>>> f10b4960ed46076f57385ee11baace1ccc1396d6
