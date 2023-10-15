#include "../character/models.hpp"

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
    bool mageBasicAbility(Character mage, Character enemy, AbilityS abilityData);
    bool mageFirstAbility();
    bool mageSecondAbility();

    // Marksman ability functions
    bool marksmanBasicAbility();
    bool marksmanFirstAbility();
    bool marksmanSecondAbility();

    // Tank ability functions
    bool tankBasicAbility();
    bool tankFirstAbility();
    bool tankSecondAbility();

    // Healer ability functions
    bool healerBasicAbility();
    bool healerFirstAbility();
    bool healerSecondAbility();

    // Assassin ability functions
    bool assassinBasicAbility();
    bool assassinFirstAbility();
    bool assassinSecondAbility();

public:
    abilityHelper();
    ~abilityHelper();

    void addAbilitiesToCharacters(std::vector<Character*> characters);
};