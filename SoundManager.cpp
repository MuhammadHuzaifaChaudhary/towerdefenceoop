#include "SoundManager.h"

#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

SoundManager::SoundManager()
    : mVolume(300)
    , mMuted(false)
{
    mClickSound = nullptr;
    // click sound load karo
    if (mClickBuffer.loadFromFile("assets/click.wav"))
    {
        mClickSound=new sf::Sound(mClickBuffer);
        mClickSound->setVolume(300.f);
    }

    // menu music load karo
    if (mMenuMusic.openFromFile("assets/hero.ogg"))
    {
        mMenuMusic.setLooping(true);
        mMenuMusic.setVolume((float)mVolume);
    }

    // game music load karo
    if (mGameMusic.openFromFile("assets/assem.ogg"))
    {
        mGameMusic.setLooping(true);
        mGameMusic.setVolume((float)mVolume);
    }
}

void SoundManager::playClick()
{
    if (mMuted) return;
    if (mClickSound != nullptr)
        mClickSound->play();
}

void SoundManager::playMenuMusic()
{
    mGameMusic.stop();
    if (mMuted) return;
    if (mMenuMusic.getStatus() != sf::Music::Status::Playing)
        mMenuMusic.play();
}

void SoundManager::playInGame()
{
    mMenuMusic.stop();
    if (mMuted) return;
    if (mGameMusic.getStatus() != sf::Music::Status::Playing)
        mGameMusic.play();
}

void SoundManager::stopMusic()
{
    mMenuMusic.stop();
    mGameMusic.stop();
}

void SoundManager::setVolume(int vol)
{
    mVolume = vol;
    if (mVolume < 0)   mVolume = 0;
    if (mVolume > 300) mVolume = 300;

    if (!mMuted)
    {
        mMenuMusic.setVolume((float)mVolume);
        mGameMusic.setVolume((float)mVolume);
        if (mClickSound != nullptr)
            mClickSound->setVolume((float)mVolume);
    }
}

void SoundManager::toggleMute()
{
    mMuted = !mMuted;
    if (mMuted)
    {
        mMenuMusic.setVolume(0.f);
        mGameMusic.setVolume(0.f);
        if (mClickSound != nullptr)
            mClickSound->setVolume(0.f);   // dot ki jagah arrow
    }
    else
    {
        mMenuMusic.setVolume((float)mVolume);
        mGameMusic.setVolume((float)mVolume);
        if (mClickSound != nullptr)
            mClickSound->setVolume((float)mVolume);  // arrow
    }
}