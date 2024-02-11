#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <alut.h>
#include <filesystem>

struct CharacterData
{
    float health;
    float armor;
    int specialAttackCD;
    int specialDefenseCD;
};

struct SoundData
{
    ALCdevice *device;
    ALCcontext *context;

    ALuint source;
    ALuint buffer;

    ALsizei size, freq;
    ALenum format;
    ALvoid *data;
    ALboolean loop = AL_FALSE;
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
    std::filesystem::path lecture_folder_path;
    SoundData soundData;
    void dealDamageIsKill(bool isUser, float damage);
    void initSound();
    void freeSound();

public:
    CharacterAction(std::filesystem::path lecture_folder_path);
    CharacterAction();
    ~CharacterAction();
    void performBasicAttack(bool isUser);
    void performSpecialAttack(bool isUser);
    void performSpecialDefense(bool isUser);
    bool isCharDead(bool isUser);
    float getCharHealth(bool isUser);
    float getCharArmor(bool isUser);
    int getSpecialAttackCD(bool isUser);
    int getSpecialDefenseCD(bool isUser);
};
