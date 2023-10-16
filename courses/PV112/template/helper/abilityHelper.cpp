#include <iostream>
#include "./abilityHelper.hpp"

void abilityHelper::setMageAbilities()
{
    // Basic ability
    AbilityS basicAttack = {
        "Basic attack",
        8.0f,
        1.0f,
        0.0f,
        false,
        0,
        0,
        "Deals damage to target enemy and gains 8 mana.",
        mageBasicAbility
    };
    this->mageAbilities.push_back(basicAttack);

    // First special ability
    AbilityS firstSpecial = {
        "Fireball",
        -45.0f,
        0.0f,
        1.0f,
        false,
        4,
        0,
        "Deals damage to target enemy and shreds defense for 2 turns.",
        mageFirstAbility
    };
    this->mageAbilities.push_back(firstSpecial);

    // Second special ability
    AbilityS secondSpecial = {
        "Aetheric purge",
        -60.0f,
        0.0f,
        0.75f,
        true,
        6,
        0,
        "Deals damage to ALL enemies and dispells buffs on target enemy.",
        mageSecondAbility
    };
    this->mageAbilities.push_back(secondSpecial);
}

void abilityHelper::setMarksmanAbilities()
{
    // Basic ability
    AbilityS basicAttack = {
        "Basic attack",
        5.0f,
        0.8f,
        0.0f,
        false,
        0,
        0,
        "Deals damage to target enemy and gains 5 mana.",
        marksmanBasicAbility
    };
    this->marksmanAbilities.push_back(basicAttack);

    // First special ability
    AbilityS firstSpecial = {
        "Marksman's fury",
        -20.0f,
        0.4f,
        0.0f,
        false,
        3,
        0,
        "Deals damage to target enemy three times.",
        marksmanFirstAbility
    };
    this->marksmanAbilities.push_back(firstSpecial);

    // Second special ability
    AbilityS secondSpecial = {
        "Agility",
        -15.0f,
        0.0f,
        0.0f,
        false,
        2,
        0,
        "Gain speed up, attack damage and accuracy up.",
        marksmanSecondAbility
    };
    this->marksmanAbilities.push_back(secondSpecial);
}

void abilityHelper::setTankAbilities()
{
    // Basic ability
    AbilityS basicAttack = {
        "Basic attack",
        5.0f,
        0.6f,
        0.0f,
        false,
        0,
        0,
        "Deals damage to target enemy, gains 5 mana and defense up(for 2 turns).",
        tankBasicAbility
    };
    this->tankAbilities.push_back(basicAttack);

    // First special ability
    AbilityS firstSpecial = {
        "Battle cry",
        -25.0f,
        0.4f,
        0.0f,
        true,
        4,
        0,
        "Heals you for a small portion, gives all allies attack and ability damage up"
        "and accuracy up(for 2 turns)."
        "Also gains defense up(for 3 turns).",
        tankFirstAbility
    };
    this->tankAbilities.push_back(firstSpecial);

    // Second special ability
    AbilityS secondSpecial = {
        "Charge forward",
        -15.0f,
        0.2f,
        0.0f,
        false,
        4,
        0,
        "Gain taunt and defense up for 2 turns."
        "Deal damage to target enemy and inflict enemy with defense down and accuracy down for 1 turn.",
        tankSecondAbility
    };
    this->tankAbilities.push_back(secondSpecial);
}

void abilityHelper::setHealerAbilities()
{

    // Basic ability
    AbilityS basicAttack = {
        "Basic attack",
        5.0f,
        1.0f,
        0.3f,
        false,
        0,
        0,
        "Deals damage to target enemy and gains 5 mana.",
        healerBasicAbility
    };
    this->healerAbilities.push_back(basicAttack);

    // First special ability
    AbilityS firstSpecial = {
        "Holy guardian",
        -60.0f,
        0.0f,
        0.85f,
        true,
        4,
        0,
        "Heals and dispells all debuffs from all allies.",
        healerFirstAbility
    };
    this->healerAbilities.push_back(firstSpecial);

    // Second special ability
    AbilityS secondSpecial = {
        "Divine support",
        -50.0f,
        0.0f,
        0.5f,
        false,
        3,
        0,
        "Heals target ally and grants speed up, defense up and accuracy up to the ally for 2 turns.",
        healerSecondAbility
    };
    this->healerAbilities.push_back(secondSpecial);
}

void abilityHelper::setAssassinAbilities()
{
    // Basic ability
    AbilityS basicAttack = {
        "Basic attack",
        5.0f,
        0.2f,
        0.0f,
        false,
        0,
        0,
        "Deals damage to target enemy, gains 5 mana."
        "This attack deals more damage when the target is below 50\% health.",
        assassinBasicAbility
    };
    this->assassinAbilities.push_back(basicAttack);

    // First special ability
    AbilityS firstSpecial = {
        "Silent strike",
        -50.0f,
        0.5f,
        0.5f,
        false,
        5,
        5,
        "Deal damage to target enemy, instantly killing the target if it was below 25\% health.",
        assassinFirstAbility
    };
    this->assassinAbilities.push_back(firstSpecial);

    // Second special ability
    AbilityS secondSpecial = {
        "Assassin's remark",
        -25.0f,
        0.0f,
        0.0f,
        false,
        3,
        0,
        "Gain speed up, accuracy up, critical chance up and stealth(cannot be targeted) for 1 turn."
        "Inflict accuracy down, defense down, damage down to target enemy.",
        assassinSecondAbility
    };
    this->assassinAbilities.push_back(secondSpecial);
}

abilityHelper::abilityHelper()
{
    // setting up the characters abilities
    setMageAbilities();
    setTankAbilities();
    setHealerAbilities();
    setAssassinAbilities();
    setMarksmanAbilities();
}

abilityHelper::~abilityHelper()
{
}

void abilityHelper::addAbilitiesToCharacters(std::vector<Character *> characters)
{
    // binding abilities to characters
    for (Character *&character : characters)
    {
        switch (character->getClass())
        {
        case MAGE:
            character->setAbilities(mageAbilities);
            break;
        case TANK:
            character->setAbilities(tankAbilities);
            break;
        case HEALER:
            character->setAbilities(healerAbilities);
            break;
        case ASSASSIN:
            character->setAbilities(assassinAbilities);
            break;
        case MARKSMAN:
            character->setAbilities(marksmanAbilities);
            break;
        default:
            break;
        }
    }
}

bool getChanceBoolean(float charChance)
{
    // Set random "random" seed  each time fnc is called
    srand((unsigned)time(NULL));
    // Get a random number and convert it to float
    float chance = rand() % 100 / 100;

    return charChance >= chance;
}

bool abilityHelper::mageBasicAbility(Character* mage, Character* enemy, Character* ally, std::vector<Character*> alies, std::vector<Character*> enemies, AbilityS abilityData)
{
    mage->setMana(8.0f);
    float damageDealt = mage->getCurrentAD() * abilityData.adRatio;
    if (getChanceBoolean(mage->getCurrentCriticalChance()))
    {
        damageDealt *= mage->getCriticalDamage();
    }
    if (!getChanceBoolean(mage->getCurrentAccuracy()))
    {
        return false;
    }
    damageDealt -= enemy->getCurrentArmor();
    enemy->receiveDamage(damageDealt);
    return true;
}


bool abilityHelper::mageFirstAbility(Character* mage, Character* enemy, Character* ally, std::vector<Character*> alies, std::vector<Character*> enemies, AbilityS abilityData) {
    mage->setMana(-45.0f);
    abilityData.currentCooldown = abilityData.baseCooldown;
    float damageDealt = mage->getCurrentAP() * abilityData.apRatio;
    if (getChanceBoolean(mage->getCurrentCriticalChance()))
    {
        damageDealt *= mage->getCriticalDamage();
    }
    if (!getChanceBoolean(mage->getCurrentAccuracy()))
    {
        return false;
    }
    ModificationS debuffModifications = {
        { false, 0.0f, 0 },  // AD
        { false, 0.0f, 0 },  // AP
        { true, -0.25f, 2 }, // armor
        { false, 0.0f, 0 },  // crit chance
        { false, 0.0f, 0 },  // speed
        { false, 0.0f, 0 },  // accuracy
        0                    // taunt
    };
    enemy->setModifications(debuffModifications);
    damageDealt -= enemy->getCurrentArmor();
    enemy->receiveDamage(damageDealt);
    return true;
}

bool abilityHelper::mageSecondAbility(Character* mage, Character* enemy, Character* ally, std::vector<Character*> alies, std::vector<Character*> enemies, AbilityS abilityData)
{
    mage->setMana(-60.0f);
    abilityData.currentCooldown = abilityData.baseCooldown;
    float damageDealt = mage->getCurrentAP() * abilityData.apRatio;
    if (getChanceBoolean(mage->getCurrentCriticalChance()))
    {
        damageDealt *= mage->getCriticalDamage();
    }
    if (!getChanceBoolean(mage->getCurrentAccuracy()))
    {
        return false;
    }
    for (Character *&character : enemies) {
        character->receiveDamage(damageDealt - character->getCurrentArmor());
    }
    // TODO dispelling buffs?
    return true;
}

bool abilityHelper::marksmanBasicAbility(Character* marksman, Character* enemy, Character* ally, std::vector<Character*> alies, std::vector<Character*> enemies, AbilityS abilityData) {
    marksman->setMana(5.0f);
    float damageDealt = marksman->getCurrentAD() * abilityData.adRatio;
    if (getChanceBoolean(marksman->getCurrentCriticalChance()))
    {
        damageDealt *= marksman->getCriticalDamage();
    }
    if (!getChanceBoolean(marksman->getCurrentAccuracy()))
    {
        return false;
    }
    damageDealt -= enemy->getCurrentArmor();
    enemy->receiveDamage(damageDealt);
    return true;
}

bool abilityHelper::marksmanFirstAbility(Character* marksman, Character* enemy, Character* ally, std::vector<Character*> alies, std::vector<Character*> enemies, AbilityS abilityData) {
    marksman->setMana(-20.0f);
    abilityData.currentCooldown = abilityData.baseCooldown;
    if (!getChanceBoolean(marksman->getCurrentAccuracy()))
    {   
        return false;
    }
    float damageDealt = marksman->getCurrentAD() * abilityData.adRatio;
    for (size_t i = 0; i < 3; i++)
    {  
        if (getChanceBoolean(marksman->getCurrentCriticalChance()))
        {
            damageDealt *= marksman->getCriticalDamage();
        }    
        damageDealt -= enemy->getCurrentArmor();
        enemy->receiveDamage(damageDealt);
        damageDealt += enemy->getCurrentArmor();
    }
    return true;
}

bool abilityHelper::marksmanSecondAbility(Character* marksman, Character* enemy, Character* ally, std::vector<Character*> alies, std::vector<Character*> enemies, AbilityS abilityData) {
    marksman->setMana(-15.0f);
    abilityData.currentCooldown = abilityData.baseCooldown;
    ModificationS buffModifications = {
        { false, 15.0f, 1 }, // AD
        { false, 0.0f, 0 },  // AP
        { false, 0.0f, 0 },  // armor
        { false, 0.0f, 0 },  // crit chance
        { false, 20.0f, 1 }, // speed
        { false, 0.2f, 1 },  // accuracy
        0                    // taunt
    };
    marksman->setModifications(buffModifications);
    return true;
}


bool abilityHelper::tankBasicAbility(Character* tank, Character* enemy, Character* ally, std::vector<Character*> alies, std::vector<Character*> enemies, AbilityS abilityData) {
    tank->setMana(5.0f);
    float damageDealt = tank->getCurrentAD() * abilityData.adRatio;
    if (getChanceBoolean(tank->getCurrentCriticalChance()))
    {
        damageDealt *= tank->getCriticalDamage();
    }
    if (!getChanceBoolean(tank->getCurrentAccuracy()))
    {
        return false;
    }
    ModificationS buffModifications = {
        { false, 0.0f, 0 }, // AD
        { false, 0.0f, 0 }, // AP
        { false, 5.0f, 2 }, // armor
        { false, 0.0f, 0 }, // crit chance
        { false, 0.0f, 0 }, // speed
        { false, 0.0f, 0 }, // accuracy
        0                   // taunt
    };
    tank->setModifications(buffModifications);
    damageDealt -= enemy->getCurrentArmor();
    enemy->receiveDamage(damageDealt);
    return true;
}

bool abilityHelper::tankFirstAbility(Character* tank, Character* enemy, Character* ally, std::vector<Character*> alies, std::vector<Character*> enemies, AbilityS abilityData) {
    tank->setMana(-25.0f);
    abilityData.currentCooldown = abilityData.baseCooldown;
    tank->healHealth(10.0f);
    ModificationS buffModifications = {
        { false, 10.0f, 1 }, // AD
        { false, 10.0f, 1 }, // AP
        { false, 0.0f, 0 },  // armor
        { false, 0.0f, 0 },  // crit chance
        { false, 0.0f, 0 },  // speed
        { false, 0.05f, 1 }, // accuracy
        0                    // taunt
    };
    for (Character *&character : alies) {
        if (character->getClass() == TANK)
        {
            buffModifications.armor = { false, 10.0f, 1 };
            character->setModifications(buffModifications);
            buffModifications.armor = { false, 0.0f, 0 };
            continue;
        }
        character->setModifications(buffModifications);
    }
    return true;
}

bool abilityHelper::tankSecondAbility(Character* tank, Character* enemy, Character* ally, std::vector<Character*> alies, std::vector<Character*> enemies, AbilityS abilityData) {
    tank->setMana(-15.0f);
    abilityData.currentCooldown = abilityData.baseCooldown;
    float damageDealt = tank->getCurrentAD() * abilityData.adRatio;
    if (getChanceBoolean(tank->getCurrentCriticalChance()))
    {
        damageDealt *= tank->getCriticalDamage();
    }
    if (!getChanceBoolean(tank->getCurrentAccuracy()))
    {
        return false;
    }
    ModificationS buffModifications = {
        { false, 0.0f, 0 },  // AD
        { false, 0.0f, 0 },  // AP
        { false, 15.0f, 2 }, // armor
        { false, 0.0f, 0 },  // crit chance
        { false, 0.0f, 0 },  // speed
        { false, 0.0f, 0 },  // accuracy
        2                    // taunt
    };
    tank->setModifications(buffModifications);
    ModificationS debuffModifications = {
        { false, 0.0f, 0 },   // AD
        { false, 0.0f, 0 },   // AP
        { false, -15.0f, 2 }, // armor
        { false, 0.0f, 0 },   // crit chance
        { false, 0.0f, 0 },   // speed
        { false, -0.15f, 2 }, // accuracy
        0                     // taunt
    };
    damageDealt -= enemy->getCurrentArmor();
    enemy->receiveDamage(damageDealt);
    enemy->setModifications(debuffModifications);
    return true;
}


bool abilityHelper::healerBasicAbility(Character* healer, Character* enemy, Character* ally, std::vector<Character*> alies, std::vector<Character*> enemies, AbilityS abilityData)
{
    healer->setMana(5.0f);
    float damageDealt = healer->getCurrentAD() * abilityData.adRatio + healer->getCurrentAP() * abilityData.apRatio;
    if (getChanceBoolean(healer->getCurrentCriticalChance()))
    {
        damageDealt *= healer->getCriticalDamage();
    }
    if (!getChanceBoolean(healer->getCurrentAccuracy()))
    {
        return false;
    }
    damageDealt -= enemy->getCurrentArmor();
    enemy->receiveDamage(damageDealt);
    return true;
}

bool abilityHelper::healerFirstAbility(Character* healer, Character* enemy, Character* ally, std::vector<Character*> alies, std::vector<Character*> enemies, AbilityS abilityData)
{
    healer->setMana(-60.0f);
    abilityData.currentCooldown = abilityData.baseCooldown;
    for (Character* &character: alies)
    {
        character->healHealth(healer->getCurrentAP() * abilityData.apRatio);
        // TODO dispelling debuffs
    }
    return true;
}

// TODO this could be easily changed to target instead of enemy/ally -> might be easier to implement in the long run as well
bool abilityHelper::healerSecondAbility(Character* healer, Character* enemy, Character* ally, std::vector<Character*> alies, std::vector<Character*> enemies, AbilityS abilityData)
{
    healer->setMana(-50.0f);
    abilityData.currentCooldown = abilityData.baseCooldown;
    ally->healHealth(healer->getCurrentAP() * abilityData.apRatio);
    ModificationS buffModifications = {
        { false, 0.0f, 0 },  // AD
        { false, 0.0f, 0 },  // AP
        { false, 10.0f, 1 }, // armor
        { false, 0.0f, 0 },  // crit chance,
        { false, 25.0f, 1 }, // speed
        { false, 0.1f, 1 },  // accuracy
        0                    // taunt
    };
    ally->setModifications(buffModifications);
    return true;
}

bool abilityHelper::assassinBasicAbility(Character* assassin, Character* enemy, Character* ally, std::vector<Character*> alies, std::vector<Character*> enemies, AbilityS abilityData)
{
    assassin->setMana(5.0f);
    float damageDealt = assassin->getCurrentAD() * abilityData.adRatio;
    if (enemy->getCurrentHP() < 0.5 * enemy->getMaxHP())
    {
        damageDealt += assassin->getCurrentAP() * abilityData.apRatio;
    }
    
    if (getChanceBoolean(assassin->getCurrentCriticalChance()))
    {
        damageDealt *= assassin->getCriticalDamage();
    }
    if (!getChanceBoolean(assassin->getCurrentAccuracy()))
    {
        return false;
    }
    damageDealt -= enemy->getCurrentArmor();
    enemy->receiveDamage(damageDealt);
    return true;
}

bool abilityHelper::assassinFirstAbility(Character* assassin, Character* enemy, Character* ally, std::vector<Character*> alies, std::vector<Character*> enemies, AbilityS abilityData)
{
    assassin->setMana(-50.0f);
    abilityData.currentCooldown = abilityData.baseCooldown;
    float damageDealt = assassin->getCurrentAD() * abilityData.adRatio + assassin->getCurrentAP() * abilityData.apRatio;
    if (enemy->getCurrentHP() < 0.25 * enemy->getMaxHP())
    {
        damageDealt = 9999.0f; // "guarantee" killing blow
    }
    
    if (getChanceBoolean(assassin->getCurrentCriticalChance()))
    {
        damageDealt *= assassin->getCriticalDamage();
    }
    if (!getChanceBoolean(assassin->getCurrentAccuracy()))
    {
        return false;
    }
    damageDealt -= enemy->getCurrentArmor();
    enemy->receiveDamage(damageDealt);
    return true;
}

bool assassinSecondAbility(Character* assassin, Character* enemy, Character* ally, std::vector<Character*> alies, std::vector<Character*> enemies, AbilityS abilityData) {
    assassin->setMana(-25.0f);
    abilityData.currentCooldown = abilityData.baseCooldown;
    ModificationS buffModifications = {
        { false, 0.0f, 0 },  // AD
        { false, 0.0f, 0 },  // AP
        { false, 0.0f, 0 },  // armor
        { false, 0.15f, 1 }, // crit chance
        { false, 20.0f, 1 }, // speed
        { false, 0.1f, 1 },  // accuracy
        0                    // taunt
    };
    assassin->setModifications(buffModifications);
    ModificationS debuffModifications = {
        { false, -5.0f, 1 },  // AD
        { false, -5.0f, 1 },  // AP
        { false, -10.0f, 1 }, // armor
        { false, 0.0f, 0 },   // crit chance
        { false, 0.0f, 0 },   // speed
        { false, -0.1f, 1 },  // accuracy
        0                     // taunt
    };
    enemy->setModifications(debuffModifications);
}
