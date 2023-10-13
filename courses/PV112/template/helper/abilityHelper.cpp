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
        false,
        0,
        "Deals damage to target enemy and gains 8 mana.",
        nullptr // TODO REWORK
    };
    this->mageAbilities.push_back(basicAttack);

    // First special ability
    AbilityS firstSpecial = {
        "Fireball",
        -45.0f,
        0.0f,
        1.0f,
        false,
        false,
        4,
        "Deals damage to target enemy and shreds defense.",
        nullptr};
    this->mageAbilities.push_back(firstSpecial);

    // Second special ability
    AbilityS secondSpecial = {
        "Aetheric purge",
        -60.0f,
        0.0f,
        0.75f,
        true,
        false,
        6,
        "Deals damage to ALL enemies and dispells buffs on target enemy.",
        nullptr};
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
        false,
        0,
        "Deals damage to target enemy and gains 5 mana.",
        nullptr // TODO REWORK
    };
    this->marksmanAbilities.push_back(basicAttack);

    // First special ability
    AbilityS firstSpecial = {
        "Marksman's fury",
        -20.0f,
        0.4f,
        0.0f,
        false,
        false,
        3,
        "Deals damage to target enemy three times.",
        nullptr};
    this->marksmanAbilities.push_back(firstSpecial);

    // Second special ability
    AbilityS secondSpecial = {
        "Agility",
        -15.0f,
        0.0f,
        0.0f,
        false,
        false,
        2,
        "Gain speed up, attack damage and accuracy up.",
        nullptr};
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
        false,
        0,
        "Deals damage to target enemy, gains 5 mana and defense up(for 2 turns).",
        nullptr // TODO REWORK
    };
    this->tankAbilities.push_back(basicAttack);

    // First special ability
    AbilityS firstSpecial = {
        "Battle cry",
        -25.0f,
        0.4f,
        0.0f,
        true,
        false,
        4,
        "Heals you for a small portion, gives all allies attack and ability damage up"
        "and accuracy up(for 2 turns)."
        "Also gains defense up(for 3 turns).",
        nullptr};
    this->tankAbilities.push_back(firstSpecial);

    // Second special ability
    AbilityS secondSpecial = {
        "Charge forward",
        -15.0f,
        0.2f,
        0.0f,
        false,
        false,
        4,
        "Gain taunt and defense up for 2 turns."
        "Deal damage to target enemy and inflict enemy with defense down and accuracy down.",
        nullptr};
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
        false,
        0,
        "Deals damage to target enemy and gains 5 mana.",
        nullptr // TODO REWORK
    };
    this->healerAbilities.push_back(basicAttack);

    // First special ability
    AbilityS firstSpecial = {
        "Holy guardian",
        -60.0f,
        0.0f,
        0.85f,
        true,
        false,
        4,
        "Heals and dispells all debuffs from all allies.",
        nullptr};
    this->healerAbilities.push_back(firstSpecial);

    // Second special ability
    AbilityS secondSpecial = {
        "Divine support",
        -50.0f,
        0.0f,
        0.5f,
        false,
        false,
        3,
        "Heals target ally and grants speed up, defens up and accuracy up to the ally.",
        nullptr};
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
        false,
        0,
        "Deals damage to target enemy, gains 5 mana."
        "This attack deals more damage when the target is below 50\% health.",
        nullptr // TODO REWORK
    };
    this->assassinAbilities.push_back(basicAttack);

    // First special ability
    AbilityS firstSpecial = {
        "Silent strike",
        -50.0f,
        0.5f,
        0.5f,
        false,
        true,
        5,
        "Deal damage to target enemy, instantly killing the target if it was below 25\% health.",
        nullptr};
    this->assassinAbilities.push_back(firstSpecial);

    // Second special ability
    AbilityS secondSpecial = {
        "Assassin's remark",
        -25.0f,
        0.0f,
        0.0f,
        false,
        false,
        3,
        "Gain speed up, accuracy up, critical chance up and stealth(cannot be targeted) for 1 turn."
        "Inflict accuracy down, defense down, damage down to target enemy.",
        nullptr};
    this->assassinAbilities.push_back(secondSpecial);
}

abilityHelper::abilityHelper()
{
}
// TODO add "init" data to process all abilities
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

void abilityHelper::addAbilitiesToCharacters(std::vector<Character*> characters) {
    // binding abilities to characters
    for (Character* &character : characters)
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
