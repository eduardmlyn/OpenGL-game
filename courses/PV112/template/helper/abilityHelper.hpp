#include "../character/models.hpp"

struct AbilityS
{
    std::string name;
    float manaCost;
    float adRatio;
    float apRatio;
    bool isAOE;
    int baseCooldown;
    int currentCooldown;
    std::string description;
    bool (abilityHelper::*trigger)(Character *character, Character *enemy, Character *ally, std::vector<Character *> alies, std::vector<Character *> enemies, AbilityS ability);
};

class abilityHelper
{
private:
    std::vector<AbilityS> mageAbilities;
    std::vector<AbilityS> marksmanAbilities;
    std::vector<AbilityS> tankAbilities;
    std::vector<AbilityS> healerAbilities;
    std::vector<AbilityS> assassinAbilities;

    // Ability setters
    void setMageAbilities();
    void setMarksmanAbilities();
    void setTankAbilities();
    void setHealerAbilities();
    void setAssassinAbilities();

    // Mage ability functions
    bool mageBasicAbility(Character *mage, Character *enemy, Character *ally, std::vector<Character *> alies, std::vector<Character *> enemies, AbilityS abilityData);
    bool mageFirstAbility(Character *mage, Character *enemy, Character *ally, std::vector<Character *> alies, std::vector<Character *> enemies, AbilityS abilityData);
    bool mageSecondAbility(Character *mage, Character *enemy, Character *ally, std::vector<Character *> alies, std::vector<Character *> enemies, AbilityS abilityData);

    // Marksman ability functions
    bool marksmanBasicAbility(Character *marksman, Character *enemy, Character *ally, std::vector<Character *> alies, std::vector<Character *> enemies, AbilityS abilityData);
    bool marksmanFirstAbility(Character *marksman, Character *enemy, Character *ally, std::vector<Character *> alies, std::vector<Character *> enemies, AbilityS abilityData);
    bool marksmanSecondAbility(Character *marksman, Character *enemy, Character *ally, std::vector<Character *> alies, std::vector<Character *> enemies, AbilityS abilityData);

    // Tank ability functions
    bool tankBasicAbility(Character *tank, Character *enemy, Character *ally, std::vector<Character *> alies, std::vector<Character *> enemies, AbilityS abilityData);
    bool tankFirstAbility(Character *tank, Character *enemy, Character *ally, std::vector<Character *> alies, std::vector<Character *> enemies, AbilityS abilityData);
    bool tankSecondAbility(Character *tank, Character *enemy, Character *ally, std::vector<Character *> alies, std::vector<Character *> enemies, AbilityS abilityData);

    // Healer ability functions
    bool healerBasicAbility(Character *healer, Character *enemy, Character *ally, std::vector<Character *> alies, std::vector<Character *> enemies, AbilityS abilityData);
    bool healerFirstAbility(Character *healer, Character *enemy, Character *ally, std::vector<Character *> alies, std::vector<Character *> enemies, AbilityS abilityData);
    bool healerSecondAbility(Character *healer, Character *enemy, Character *ally, std::vector<Character *> alies, std::vector<Character *> enemies, AbilityS abilityData);

    // Assassin ability functions
    bool assassinBasicAbility(Character *assassin, Character *enemy, Character *ally, std::vector<Character *> alies, std::vector<Character *> enemies, AbilityS abilityData);
    bool assassinFirstAbility(Character *assassin, Character *enemy, Character *ally, std::vector<Character *> alies, std::vector<Character *> enemies, AbilityS abilityData);
    bool assassinSecondAbility(Character *assassin, Character *enemy, Character *ally, std::vector<Character *> alies, std::vector<Character *> enemies, AbilityS abilityData);

public:
    abilityHelper();
    ~abilityHelper();

    void addAbilitiesToCharacters(std::vector<Character *> characters);
};