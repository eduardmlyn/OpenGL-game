#include "../character/models.hpp"

class abilityHelper
{
private:
    std::vector<AbilityS> mageAbilities;
    std::vector<AbilityS> marksmanAbilities;
    std::vector<AbilityS> tankAbilities;
    std::vector<AbilityS> healerAbilities;
    std::vector<AbilityS> assassinAbilities;
    void setMageAbilities();
    void setMarksmanAbilities();
    void setTankAbilities();
    void setHealerAbilities();
    void setAssassinAbilities();

public:
    abilityHelper();
    ~abilityHelper();

    void addAbilitiesToCharacters(std::vector<Character*> characters);
};