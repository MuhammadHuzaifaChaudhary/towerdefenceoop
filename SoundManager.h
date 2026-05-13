#pragma once
#pragma once
#include <SFML/Audio.hpp>
#include<iostream>
using namespace std;
using namespace sf;

class SoundManager
{
public:
    SoundManager();

    void playClick();       // button click sound
    void playInGame();      // in-game music loop
    void playMenuMusic();   // menu music loop
    void stopMusic();       // music band karo
    void setVolume(int vol); // 0-100
    void toggleMute();
    bool isMuted() const { return mMuted; }
    int  getVolume() const { return mVolume; }
    ~SoundManager() { delete mClickSound; }

private:
    // sound buffers  click sound ke liye
    SoundBuffer mClickBuffer;
    Sound* mClickSound;

    // music  separate tracks
    Music  mMenuMusic;
    Music  mGameMusic;

    int  mVolume;
    bool mMuted;

    
};