#include "../character/models.hpp"
#include "./abilityHelper.hpp"
#include "./charHelpers/tankHelper.cpp"
#include "./charHelpers/healerHelper.cpp"
#include "./charHelpers/mageHelper.cpp"
#include "./charHelpers/marksmanHelper.cpp"
#include "./charHelpers/assassinHelper.cpp"
#include <memory>

class characterHelper
{
private:
  std::vector<Character *> playerCharacters;
  std::vector<Character *> enemyCharacters;

  // helpers
  abilityHelper abilityHelper;
  tankHelper tankHelper;
  healerHelper healerHelper;
  mageHelper mageHelper;
  marksmanHelper marksmanHelper;
  assassinHelper assassinHelper;

  void initCharHelpers();
  void initPlayerCharacters();
  void initEnemyCharacters();

public:
  characterHelper();
  ~characterHelper();

  std::vector<Character *> getPlayerCharacters();
  std::vector<Character *> getEnemyCharacters();
};

characterHelper::characterHelper()
{
  initCharHelpers();
  initPlayerCharacters();
  initEnemyCharacters();
}

characterHelper::~characterHelper()
{
}

std::vector<Character *> characterHelper::getPlayerCharacters()
{
  return playerCharacters;
}

std::vector<Character *> characterHelper::getEnemyCharacters()
{
  return enemyCharacters;
}

void characterHelper::initCharHelpers()
{
  abilityHelper = abilityHelper::abilityHelper();
  tankHelper = tankHelper::tankHelper();
  healerHelper = healerHelper::healerHelper();
  mageHelper = mageHelper::mageHelper();
  marksmanHelper = marksmanHelper::marksmanHelper();
  assassinHelper = assassinHelper::assassinHelper();
}

void characterHelper::initPlayerCharacters()
{
  playerCharacters.push_back(tankHelper.getTankCharacter());
  playerCharacters.push_back(healerHelper.getHealerCharacter());
  playerCharacters.push_back(mageHelper.getMageCharacter());
  playerCharacters.push_back(marksmanHelper.getMarksmanCharacter());
  playerCharacters.push_back(assassinHelper.getAssassinCharacter());
  abilityHelper.addAbilitiesToCharacters(playerCharacters);
}

void characterHelper::initEnemyCharacters()
{
  enemyCharacters.push_back(tankHelper.getTankCharacter());
  enemyCharacters.push_back(healerHelper.getHealerCharacter());
  enemyCharacters.push_back(mageHelper.getMageCharacter());
  enemyCharacters.push_back(marksmanHelper.getMarksmanCharacter());
  enemyCharacters.push_back(assassinHelper.getAssassinCharacter());
  abilityHelper.addAbilitiesToCharacters(enemyCharacters);
}
