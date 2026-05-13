
#include "Game.h"   // includes game.h that have all game class declarations 
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

Game::Game()                                                       // to make window non resizeable 
    : mWindow(sf::VideoMode({ 1400u, 900u }), "Castle Conflict ",Style::Titlebar | sf::Style::Close)
    , mEnemyCount(0)  // no enemy 
    , mSpawnTimer(0.f)   // time starts from zero 
    , mSpawnInterval(1.5f)  // har 1.5 sec may enemy spawn ho gi 
    , mTowerCount(0)
    , mGold(200)     // ye defualt gold hay start me 
    , mSelectedTower(0)
    , mCurrentWave(0)
    , mEnemiesToSpawn(0)
    , mWaveEnemyIndex(0)
    , mWaveInProgress(false)
    , mWaveCooldown(3.f)   // wave start honay se pahle 3 sec ka wait ho ga 
    , mGameOver(false)
    , mGameWon(false)
    , mLives(5)     // there are 5 lives 
    , m_exitPanelActive(false)    // exit panel is off 
    , mState(GameState::MainMenu)

    // initilizer list sets the value before constructor body ... means ye fatser hay 
{
    mWindow.setFramerateLimit(60);   // screen will update 60 times per second 
    for (int i = 0; i < MAX_TOWERS; i++) 
        mTowers[i] = nullptr;   // first set all pointers to nullptr 
    for (int i = 0; i < MAX_ENEMIES; i++) 
        mEnemies[i] = nullptr;   // set all enemies poinetrs to nullptr 
    mFontLoaded = mFont.openFromFile("assets/f4.otf");   // load the font file 
    mSound.playMenuMusic(); // menu screen kay liye back ground music play ho ga 
}

WaveData gWaves[NUM_WAVES] =
{
    { {{0,8},{1,2}}, 2 },

    // Wave 2: 5 Basic + 5 Fast + 2 Tank
    { {{0,5},{1,5},{2,2}}, 3 },

    // Wave 3: 3 Fast + 4 Tank + 3 Flying + 2 Healer
    { {{1,3},{2,4},{3,3},{5,2}}, 4 },

    // Wave 4: 5 Basic + 5 Fast + 4 Tank + 4 Flying + 3 Healer + 2 Bomb
    { {{0,5},{1,5},{2,4},{3,4},{5,3},{4,2}}, 6 },

    // Wave 5 (Final): Sab kuch + zyada Healer + Bomb
    { {{0,6},{1,6},{2,5},{3,5},{4,4},{5,4}}, 6 }
};

void Game::run()
{
    sf::Clock clock;
    while (mWindow.isOpen())
    {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents()
{ 
    while (auto event = mWindow.pollEvent())
    {
        // Close window
        if (event->is<sf::Event::Closed>())
            mWindow.close();
        // MainMenu state
        if (mState == GameState::MainMenu)
        {
            if (const auto* mm = event->getIf<sf::Event::MouseMoved>())
                mMainMenu.handleHover((float)mm->position.x, (float)mm->position.y);

            if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mb->button == sf::Mouse::Button::Left)
                {
                    int choice = mMainMenu.handleClick(
                        (float)mb->position.x, (float)mb->position.y);

                    if (choice == 0)  // Play
                    {
                        mSound.playClick();
                        mState = GameState::NameEntry;
                    }
                    else if (choice == 1)  // Leaderboard
                    {
                        mSound.playClick();
                        mState = GameState::LeaderboardScreen;
                    }
                    else if (choice == 2)  // Settings
                    {
                        mSound.playClick();
                        mSettings.setVolume(mSound.getVolume());  // sync karo
                        mSettings.setMuted(mSound.isMuted());     // mute bhi sync
                        mState = GameState::SettingsScreen;
                    }
                    else if (choice == 4)  //instructions
                    { 
                        mSound.playClick();
                        mState = GameState::Instructions;
                    }
                    else if (choice == 5)  
                    {
                        mSound.playClick();
                        mState = GameState::CoinsShop;
                    }

                    else if (choice == 3)  // Exit
                    {
                        mSound.playClick();
                        mWindow.close();
                    }
                    // leaderboard aur settings baad mein
                }
            }
            continue;  // baaki events process mat karo
        }

        // enter name 
        // Name Entry state
        if (mState == GameState::NameEntry)
        {
            // text input
            if (const auto* te = event->getIf<sf::Event::TextEntered>())
                mNameEntry.handleTextInput(te->unicode);

            // mouse hover
            if (const auto* mm = event->getIf<sf::Event::MouseMoved>())
                mNameEntry.handleClick((float)mm->position.x, (float)mm->position.y);

            // mouse click
            if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mb->button == sf::Mouse::Button::Left)
                {
                    if (mNameEntry.handleClick(
                        (float)mb->position.x, (float)mb->position.y))
                    {
                        // name confirm - game start
                        mPlayerName = mNameEntry.getName();
                        mSound.playClick();
                        mSound.playInGame();
                        mState = GameState::Playing;
                    }
                }
            }

            // Enter key se bhi confirm ho
            if (const auto* k = event->getIf<sf::Event::KeyPressed>())
            {
                if (k->code == sf::Keyboard::Key::Enter
                    && !mNameEntry.getName().empty())
                {
                    mPlayerName = mNameEntry.getName();
                    mSound.playClick();
                    mSound.playInGame();
                    mState = GameState::Playing;
                }
            }
            continue;
        }

        // now leaderboard state 
        if (mState == GameState::LeaderboardScreen)
        {
            if (const auto* mm = event->getIf<sf::Event::MouseMoved>())
                mLeaderboard.handleHover((float)mm->position.x, (float)mm->position.y);

            if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mb->button == sf::Mouse::Button::Left)
                {
                    if (mLeaderboard.handleClick((float)mb->position.x, (float)mb->position.y))
                    {
                        mSound.playClick();
                        mState = GameState::MainMenu;
                    }
                }
            }
            continue;
        }

        // instructions menu 
        if (mState == GameState::Instructions)
        {
            if (const auto* mm = event->getIf<sf::Event::MouseMoved>())
                mInstructions.handleHover((float)mm->position.x, (float)mm->position.y);
            if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>())
                if (mb->button == sf::Mouse::Button::Left)
                    if (mInstructions.handleClick((float)mb->position.x, (float)mb->position.y))
                        mState = GameState::MainMenu;
            continue;
        }
        //coins shop[ 
         if (mState == GameState::CoinsShop)
        {
            if (const auto* mm = event->getIf<sf::Event::MouseMoved>())
                mCoinsShop.handleHover((float)mm->position.x, (float)mm->position.y);

            if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>())
                if (mb->button == sf::Mouse::Button::Left)
                    if (mCoinsShop.handleClick((float)mb->position.x, (float)mb->position.y))
                    {
                        mSound.playClick();
                        mState = GameState::MainMenu;
                    }
            continue;
        }
        // now settings state 
        if (mState == GameState::SettingsScreen)
        {
            if (const auto* mm = event->getIf<sf::Event::MouseMoved>())
                mSettings.handleHover((float)mm->position.x, (float)mm->position.y);

            if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mb->button == sf::Mouse::Button::Left)
                {
                    int choice = mSettings.handleClick(
                        (float)mb->position.x, (float)mb->position.y);

                    if (choice == 0)   // back
                    {
                        mSound.playClick();
                        mState = GameState::MainMenu;
                    }
                    else if (choice == 1)  // vol minus
                    {
                       
                        mSound.setVolume(mSound.getVolume() - 30);
                        mSettings.setVolume(mSound.getVolume());
                        mSound.playClick();
                    }
                    else if (choice == 2)  // vol plus
                    {
                        
                        mSound.setVolume(mSound.getVolume() + 30);
                        mSettings.setVolume(mSound.getVolume());
                        mSound.playClick();
                    }
                    else if (choice == 3)  // mute
                    {
                        
                        mSound.toggleMute();
                        mSettings.setMuted(mSound.isMuted());
                        mSound.playClick();

                    }
                    else if (choice >= 10 && choice <= 12)  // bg select
                    { 
                        mSettings.mSelectedBg = choice - 10;
                        mMap.setBackground(choice - 10);
                    }
                    else if (choice >= 20 && choice <= 22)  // path select
                    {
                        mSettings.mSelectedPath = choice - 20;
                        mMap.setPathTexture(choice - 20);
                    }
                }
            }
            continue;
        }
        // Keyboard
        if (const auto* k = event->getIf<sf::Event::KeyPressed>())
        {
            if (k->code == sf::Keyboard::Key::Escape)
                mWindow.close();
            if (k->code == sf::Keyboard::Key::Num1)
                mSelectedTower = 0;
            if (k->code == sf::Keyboard::Key::Num2)
                mSelectedTower = 1;
            if (k->code == sf::Keyboard::Key::Num3)
                mSelectedTower = 2;
            if (k->code == sf::Keyboard::Key::Num4)
                mSelectedTower = 3;
            if (k->code == sf::Keyboard::Key::Num5)
                mSelectedTower = 4;
        }

        // Mouse move (hover effects)
        if (const auto* mm = event->getIf<sf::Event::MouseMoved>())
        {
            mUI.handleExitButtonHover((float)mm->position.x, (float)mm->position.y);

            if (mUI.isExitPanelVisible())
            {
                mUI.handleExitPanelClick((float)mm->position.x, (float)mm->position.y);
            }

            if (mUI.isEndScreenVisible())
            {
                mUI.updateEndScreenHover((float)mm->position.x, (float)mm->position.y);
            }
        }

        // Mouse click
        if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mb->button == sf::Mouse::Button::Left)
            {
                float mouseX = (float)mb->position.x;
                float mouseY = (float)mb->position.y;

                // FIRST: Check End Screen (Win/Lose)
                if (mUI.isEndScreenVisible())
                {
                    int choice = mUI.handleEndScreenClick(mouseX, mouseY);
                    if (choice == 1)  // Play Again
                    {
                        mSound.playClick();
                        mSound.playInGame();
                        resetGame();
                    }
                    else if (choice == 2)  // Main Menu
                    {
                        mSound.playClick();
                        mSound.playMenuMusic();
                        mState = GameState::MainMenu;
                        resetGame(); 
                    }
                    return;
                }

                // SECOND: Check Exit Panel
                if (mUI.isExitPanelVisible())
                {
                    int choice = mUI.handleExitPanelClick(mouseX, mouseY);
                    if (choice == 1)  // YES
                    {
                        mSound.playClick();
                        mSound.playMenuMusic();
                        mState = GameState::MainMenu;
                        resetGame();
                    }
                    else if (choice == 0)  // NO
                    {
                        mSound.playClick();
                      //  mSound.playMenuMusic();
                        mUI.showExitPanel(false);
                    }
                    return;
                }

                // THIRD: Check Exit Button
                if (mUI.isExitButtonClicked(mouseX, mouseY))
                {
                    mUI.showExitPanel(true);
                    return;
                }
                // FOURTH: Tower placement
                if (!mGameOver && !mGameWon && !mUI.isEndScreenVisible())
                {
                    int col = (int)mouseX / TILE_SIZE;
                    int row = (int)mouseY / TILE_SIZE;

                    if (mMap.isBuildable(col, row) && mTowerCount < MAX_TOWERS)
                    {
                        float tx = (float)(col * TILE_SIZE + TILE_SIZE / 2);
                        float ty = (float)(row * TILE_SIZE + TILE_SIZE / 2);

                        // Check if tile is occupied
                        bool tileOccupied = false;
                        for (int i = 0; i < mTowerCount; i++)
                        {
                            if (mTowers[i] == nullptr) continue;
                            if (mTowers[i]->getX() == tx && mTowers[i]->getY() == ty)
                            {
                                tileOccupied = true;
                                break;
                            }
                        }

                        //SIRF TAB PLACE KARO AGAR TILE OCCUPIED NAHI HAI
                        if (!tileOccupied)
                        {
                            if (mSelectedTower == 0 && mGold >= 100)
                            {
                                mTowers[mTowerCount++] = new CannonTower(tx, ty);
                                mGold -= 100;
                            }
                            else if (mSelectedTower == 1 && mGold >= 75)
                            {
                                mTowers[mTowerCount++] = new ArcherTower(tx, ty);
                                mGold -= 75;
                            }
                            else if (mSelectedTower == 2 && mGold >= 150)
                            {
                                mTowers[mTowerCount++] = new WizardTower(tx, ty);
                                mGold -= 150;
                            }
                            else if (mSelectedTower == 3 && mGold >= 80)
                            {
                                mTowers[mTowerCount++] = new ElectricTower(tx, ty);
                                mGold -= 80;
                            }
                            else if (mSelectedTower == 4 && mGold >= 90)
                            {
                                mTowers[mTowerCount++] = new BowTower(tx, ty);
                                mGold -= 90;
                            }
                        }
                    }
                }
            }
        }
    }
}

void Game::spawnEnemy()
{
    if (mEnemyCount >= MAX_ENEMIES) return;
    if (mEnemiesToSpawn <= 0) return;

    float startX = WAYPOINTS[0].x;
    float startY = WAYPOINTS[0].y;

    WaveData& wave = gWaves[mCurrentWave];
    int spawnType = 0;

    int remaining = mEnemiesToSpawn;
    for (int i = wave.numEntries - 1; i >= 0; i--)
    {
        if (remaining <= wave.entries[i].count)
        {
            spawnType = wave.entries[i].type;
            break;
        }
        remaining -= wave.entries[i].count;
    }

    if (spawnType == 0)
        mEnemies[mEnemyCount++] = new BasicEnemy(startX, startY);
    else if (spawnType == 1)
        mEnemies[mEnemyCount++] = new FastEnemy(startX, startY);
    else if (spawnType == 2)
        mEnemies[mEnemyCount++] = new TankEnemy(startX, startY);
    else if (spawnType == 3)
        mEnemies[mEnemyCount++] = new FlyingEnemy(startX, startY);
    else if (spawnType == 4)
        mEnemies[mEnemyCount++] = new BombEnemy(startX, startY);
    // spawnEnemy() mein
    else if (spawnType == 5)
        mEnemies[mEnemyCount++] = new HealEnemy(startX, startY);

    mEnemiesToSpawn--;
}

void Game::update(float dt)
{ 
    // Agar end screen visible hai to game update mat karo

    if (mUI.isExitPanelVisible()) return;
    if (mUI.isEndScreenVisible()) return;
    if (mState == GameState::NameEntry)
    {
        mNameEntry.update(dt);  //YEH LINE ADD KARO
        return;
    }
    if (mState != GameState::Playing) return;  // ADD THIS
    

    // Wave management
    if (!mWaveInProgress)
    {
        mWaveCooldown -= dt;
        if (mWaveCooldown <= 0.f)
        {
            if (mCurrentWave < NUM_WAVES)
            {
                // Start next wave
                mWaveInProgress = true;
                mSpawnTimer = 0.f;

                int total = 0;
                for (int i = 0; i < gWaves[mCurrentWave].numEntries; i++)
                    total += gWaves[mCurrentWave].entries[i].count;
                mEnemiesToSpawn = total;
            }
            else if (mEnemyCount == 0)
            {
                mGameWon = true;
                mUI.showEndScreen(true);  // Victory screen
               /* mGameWon = true;
                int score = mCurrentWave * 100 + mGold + mLives * 50;
                mLeaderboard.addScore(mPlayerName, score);
                mUI.showEndScreen(true);*/
            }
        }
    }
    else
    {
        // Spawning enemies
        if (mEnemiesToSpawn > 0)
        {
            mSpawnTimer += dt;
            if (mSpawnTimer >= mSpawnInterval)
            {
                mSpawnTimer = 0.f;
                spawnEnemy();
            }
        }
        else if (mEnemiesToSpawn == 0 && mEnemyCount == 0)
        {
            // Wave finished
            mWaveInProgress = false;
            if (mCurrentWave + 1 >= NUM_WAVES)
            {
                //mGameWon = true;
                //mUI.showEndScreen(true);  // Victory screen
                mGameWon = true;
                int score = mCurrentWave * 100 + mGold + mLives * 50;
                mLeaderboard.addScore(mPlayerName, score);
                mSound.stopMusic();
                mUI.showEndScreen(true);
            }
            else
            {
                mCurrentWave++;
                mWaveCooldown = 3.f;
            }
        }
    }

    //// Update enemies
    //for (int i = 0; i < mEnemyCount; i++)
    //    if (mEnemies[i] != nullptr)
    //        mEnemies[i]->update(dt);

    // Remove dead or escaped enemies
    for (int i = 0; i < mEnemyCount; i++)
    {
        if (mEnemies[i] == nullptr) continue;
        // HealEnemy ko alag se update karo
        HealEnemy* healer = dynamic_cast<HealEnemy*>(mEnemies[i]);
        if (healer)
            healer->update(dt, mEnemies, mEnemyCount);
        else
            mEnemies[i]->update(dt);

        if (!mEnemies[i]->isAlive())
        {
            if (mEnemies[i]->hasEscaped())
            {
                mLives--;
                if (mLives <= 0)
                {
                    //mGameOver = true;
                    //mUI.showEndScreen(false);  // Game Over screen
                    mGameOver = true;
                    int score = mCurrentWave * 100 + mGold + mLives * 50;
                    mLeaderboard.addScore(mPlayerName, score);
                    mSound.stopMusic();
                    mUI.showEndScreen(false);
                }
            }
            else
            {
                mGold += 25;
                BombEnemy* bomb = dynamic_cast<BombEnemy*>(mEnemies[i]);
                if (bomb && bomb->hasExploded())
                {
                    // nearby enemies ko damage karo
                    for (int j = 0; j < mEnemyCount; j++)
                    {
                        if (mEnemies[j] == nullptr) continue;
                        if (!mEnemies[j]->isAlive()) continue;
                        if (j == i) continue;  // khud ko nahi

                        float dx = mEnemies[j]->getX() - bomb->getX();
                        float dy = mEnemies[j]->getY() - bomb->getY();
                        float dist = std::sqrt(dx * dx + dy * dy);

                        if (dist < 100.f)  // explosion radius
                            mEnemies[j]->takeDamage(50.f);  // explosion damage
                    }
                }
            }

            delete mEnemies[i];
            mEnemies[i] = nullptr;

            for (int j = i; j < mEnemyCount - 1; j++)
                mEnemies[j] = mEnemies[j + 1];

            mEnemies[mEnemyCount - 1] = nullptr;
            mEnemyCount--;
            i--;
        }
    }

    // Update towers
    for (int i = 0; i < mTowerCount; i++)
        if (mTowers[i] != nullptr)
            mTowers[i]->update(dt, mEnemies, mEnemyCount);
}

void Game::resetGame()
{
    // Clean up towers
    for (int i = 0; i < mTowerCount; i++)
    {
        delete mTowers[i];
        mTowers[i] = nullptr;
    }
    mTowerCount = 0;

    // Clean up enemies
    for (int i = 0; i < mEnemyCount; i++)
    {
        delete mEnemies[i];
        mEnemies[i] = nullptr;
    }
    mEnemyCount = 0;

    // Reset game variables
    mGold = 200;
    mLives = 5;
    mCurrentWave = 0;
    mEnemiesToSpawn = 0;
    mWaveInProgress = false;
    mWaveCooldown = 3.f;
    mGameOver = false;
    mGameWon = false;
    mSpawnTimer = 0.f;
    mSelectedTower = 0;
    mUI.hideEndScreen();
    mUI.showExitPanel(false);
    mNameEntry.reset();  // name clear karo
  //  mState = GameState::NameEntry;  // pehle name phir game
}

void Game::drawGameText(const std::string& str, float x, float y, int size, sf::Color color)
{
    if (!mFontLoaded) return;
    sf::Text text(mFont);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition({ x, y });
    mWindow.draw(text);
}

void Game::handleExitPanel() {}

void Game::render()
{ 
    mWindow.clear(sf::Color(20, 20, 20));

    if (mState == GameState::MainMenu)
    {
        mMainMenu.draw(mWindow);
        mWindow.display();
        return;
    }

    if (mState == GameState::NameEntry)
    {
        mNameEntry.draw(mWindow);
        mWindow.display();
        return;
    }

    if (mState == GameState::LeaderboardScreen)
    {
        mLeaderboard.draw(mWindow);
        mWindow.display();
        return;
    }
    // instructions 

    if (mState == GameState::Instructions)
    {
        mInstructions.draw(mWindow);
        mWindow.display();
        return;
    }
    if (mState == GameState::SettingsScreen)
    {
        mSettings.draw(mWindow);
        mWindow.display();
        return;
    }
    if (mState == GameState::CoinsShop)
    {
        mCoinsShop.draw(mWindow, mGold);
        mWindow.display();
        return;
    }
    mWindow.clear(sf::Color(20, 20, 20));

    mMap.draw(mWindow);

    for (int i = 0; i < mTowerCount; i++)
        if (mTowers[i] != nullptr)
            mTowers[i]->draw(mWindow);

    for (int i = 0; i < mEnemyCount; i++)
        if (mEnemies[i] != nullptr)
            mEnemies[i]->draw(mWindow);

    // Draw UI
    mUI.draw(mWindow, mCurrentWave, NUM_WAVES, mGold, mLives, mSelectedTower);

    // Draw end screen (Win/Lose) - this overrides everything
    mUI.drawEndScreen(mWindow);

    mWindow.display();
}