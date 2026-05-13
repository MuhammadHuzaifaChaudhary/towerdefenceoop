#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

#include <string> 
#include "Map.h"
#include "Enemy.h"
#include "Tower.h"
#include"UI.h"
#include"MainMenu.h"
#include "NameEntry.h"
#include "Leaderboard.h"
#include "Settings.h"
#include "SoundManager.h"
#include "Instructions.h"
#include "CoinsShop.h"
enum class GameState
{
    MainMenu,
    NameEntry,
    Playing,
    LeaderboardScreen,
    Instructions, CoinsShop, SettingsScreen
};
//enum class GameState 
//{  MainMenu,
//   NameEntry, 
//   Playing
//};

const int MAX_ENEMIES = 100;
const int MAX_TOWERS = 50;
 
const int NUM_WAVES = 5;
const int MAX_WAVE_ENTRIES = 6;

struct WaveEntry { int type; int count; };
struct WaveData { WaveEntry entries[MAX_WAVE_ENTRIES]; int numEntries; };

extern WaveData gWaves[NUM_WAVES];

class Game
{
public:
    Game();
    void run();
    void resetGame();

    ~Game()
    {
        for (int i = 0; i < mTowerCount; i++)
            delete mTowers[i];
        for (int i = 0; i < mEnemyCount; i++)
            delete mEnemies[i];
    } 

private:
    void processEvents();
    void update(float dt);
    void render();
    void spawnEnemy();
    void drawGameText(const std::string& str,
        float x, float y,
        int size, sf::Color color);
    sf::Font mFont;
    bool     mFontLoaded;

    // exit button things 
    void handleExitPanel();
    bool m_exitPanelActive;

    RenderWindow mWindow;    // sf 
    Map mMap;

    Enemy* mEnemies[MAX_ENEMIES];
    int    mEnemyCount;
    float  mSpawnTimer;
    float  mSpawnInterval;
    // ADD these new ones
    int   mCurrentWave;       // which wave we are on (1-5)
    int   mEnemiesToSpawn;    // enemies left to spawn this wave
    int   mWaveEnemyIndex;    // which enemy in wave we are spawning
    bool  mWaveInProgress;    // is wave currently running
    float mWaveCooldown;      // timer between waves
    bool  mGameOver;
    bool  mGameWon;
    int   mLives;

    Tower* mTowers[MAX_TOWERS];
    int    mTowerCount;
    int    mGold;
    int    mSelectedTower;
    UI mUI;  // ADD after mSelectedTower

    // nameEnter 
   

    GameState   mState;
    MainMenu    mMainMenu;

    NameEntry   mNameEntry;
    string mPlayerName;     //std 

    // leaderboard 
    Leaderboard mLeaderboard;

    // settings 
    Settings mSettings;


    // sound
    SoundManager mSound;

    Instructions mInstructions;
    CoinsShop  mCoinsShop;

    
};