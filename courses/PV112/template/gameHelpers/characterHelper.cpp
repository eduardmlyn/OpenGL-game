#include "characterHelper.hpp"

CharacterAction::CharacterAction(std::filesystem::path lecture_folder_path)
{
    userChar = {100.f, 30.f, 0, 0};
    enemyChar = {100.f, 30.f, 0, 0};
    this->lecture_folder_path = lecture_folder_path;
    initSound();
}

CharacterAction::CharacterAction()
{
}

CharacterAction::~CharacterAction()
{
    freeSound();
}

void CharacterAction::dealDamageIsKill(bool isUser, float damage)
{
    CharacterData *character;
    if (!isUser)
    {
        character = &userChar;
    }
    else
    {
        character = &enemyChar;
    }
    float accuracy = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) + 1.0f);
    if (accuracy > 0.8f)
    {
        return;
    }
    float critChance = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) + 1.0f);
    if (critChance > 0.8f)
    {
        damage *= 1.2f;
    }
    if (character->armor > 0)
    {
        character->armor -= damage;
        if (character->armor < 0)
        {
            character->health += character->armor;
            character->armor = 0.f;
        }
    }
    else
    {
        character->health -= damage;
    }
    alSourcePlay(soundData.source);
    std::cout << "played sound" << std::endl;
}

void CharacterAction::performBasicAttack(bool isUser)
{
    if (isUser)
    {
        userChar.specialAttackCD = std::max(0, userChar.specialAttackCD - 1);
        userChar.specialDefenseCD = std::max(0, userChar.specialDefenseCD - 1);
    }
    else
    {
        enemyChar.specialAttackCD = std::max(0, enemyChar.specialAttackCD - 1);
        enemyChar.specialDefenseCD = std::max(0, enemyChar.specialDefenseCD - 1);
    }

    this->dealDamageIsKill(isUser, basicAttackDamage);
}

void CharacterAction::performSpecialAttack(bool isUser)
{
    if (isUser)
    {
        if (userChar.specialAttackCD != 0)
        {
            return;
        }
        userChar.specialDefenseCD = std::max(0, userChar.specialDefenseCD - 1);
        userChar.specialAttackCD = 3;
    }
    else
    {
        if (enemyChar.specialAttackCD != 0)
        {
            return;
        }
        enemyChar.specialDefenseCD = std::max(0, enemyChar.specialDefenseCD - 1);
        enemyChar.specialAttackCD = 3;
    }

    this->dealDamageIsKill(isUser, specialAttackDamage);
}

void CharacterAction::performSpecialDefense(bool isUser)
{
    CharacterData *character;
    if (isUser)
    {
        character = &userChar;
    }
    else
    {
        character = &enemyChar;
    }
    if (character->specialDefenseCD != 0)
    {
        return;
    }
    character->specialAttackCD = std::max(0, character->specialAttackCD - 1);
    character->specialDefenseCD = 3;
    character->armor += specialDefenseArmor;
}

bool CharacterAction::isCharDead(bool isUser)
{
    if (isUser)
    {
        return userChar.health <= 0;
    }
    return enemyChar.health <= 0;
}

float CharacterAction::getCharHealth(bool isUser)
{
    return isUser ? userChar.health : enemyChar.health;
}

float CharacterAction::getCharArmor(bool isUser)
{
    return isUser ? userChar.armor : enemyChar.armor;
}

int CharacterAction::getSpecialAttackCD(bool isUser)
{
    return isUser ? userChar.specialAttackCD : enemyChar.specialAttackCD;
}

int CharacterAction::getSpecialDefenseCD(bool isUser)
{
    return isUser ? userChar.specialDefenseCD : enemyChar.specialDefenseCD;
}

int testOpenAlError(const char *_msg)
{
    ALCenum error = alGetError();
    if (error != AL_NO_ERROR)
    {

        fprintf(stderr, _msg, "\n");
        return -1;
    }
    return 0;
}

void CharacterAction::initSound()
{
    soundData.device = alcOpenDevice(nullptr);
    if (soundData.device)
    {
        soundData.context = alcCreateContext(soundData.device, NULL);
        alcMakeContextCurrent(soundData.context);
    }
    alutInit(NULL, NULL);

    alGenSources(1, &soundData.source);
    // check for errors
    testOpenAlError("source generation");

    alSourcef(soundData.source, AL_PITCH, 1);
    // check for errors
    testOpenAlError("source PITCH");
    alSourcef(soundData.source, AL_GAIN, 1);
    // check for errors
    testOpenAlError("source GAIN");
    alSource3f(soundData.source, AL_POSITION, 0, 0, 0);
    // check for errors
    testOpenAlError("source POSITION");
    alSource3f(soundData.source, AL_VELOCITY, 0, 0, 0);
    // check for errors
    testOpenAlError("source VELOCITY");
    alSourcei(soundData.source, AL_LOOPING, AL_FALSE);
    testOpenAlError("source LOOPING");

    alGenBuffers(1, &soundData.buffer);
    testOpenAlError("buffer generation");

    std::filesystem::path sound_path = lecture_folder_path / "sounds" / "Bomb.wav";
    // std::cout << sound_path << std::endl;
    ALfloat freq2;
    soundData.data = alutLoadMemoryFromFile(sound_path.string().c_str(), &soundData.format, &soundData.size, &freq2);
    soundData.freq = (ALsizei)freq2;
    alBufferData(soundData.buffer, soundData.format, soundData.data, soundData.size, soundData.freq);
    testOpenAlError("buffer copy");
    std::cout << "test line" << std::endl;

    alSourcei(soundData.source, AL_BUFFER, soundData.buffer);
    testOpenAlError("buffer binding");
}

void CharacterAction::freeSound()
{
    alDeleteSources(1, &soundData.source);
    alDeleteBuffers(1, &soundData.buffer);
    alutExit();
    ALCdevice *device = alcGetContextsDevice(soundData.context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(soundData.context);
    alcCloseDevice(device);
}
