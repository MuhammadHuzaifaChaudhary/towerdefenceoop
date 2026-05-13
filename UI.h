#pragma once
#include <string>

#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
 
class UI
{
public:
    UI();
    void draw(sf::RenderWindow& window, int currentWave, int totalWaves,int gold, int lives,int selectedTower);

    // font helper - tum call kar sakte ho
    void drawText(sf::RenderWindow& window,
        const std::string& str,
        float x, float y,
        int size,
        sf::Color color);

    // exit button 
    void handleExitButtonHover(float mouseX, float mouseY);
    bool isExitButtonClicked(float mouseX, float mouseY);
    void showExitPanel(bool show);
    bool isExitPanelVisible() const { return m_showExitPanel; }
    int handleExitPanelClick(float mouseX, float mouseY);

    // Win/Lose Screen
    void showEndScreen(bool isWin);  // true = win, false = lose
    bool isEndScreenVisible() const { return m_showEndScreen; }
    int handleEndScreenClick(float mouseX, float mouseY);  // 0=PlayAgain, 1=MainMenu
    void updateEndScreenHover(float mouseX, float mouseY);
    void drawEndScreen(sf::RenderWindow& window);
    void hideEndScreen() { m_showEndScreen = false; }

    ~UI()
    {
        delete mPanelSprite;
        delete mBtnSprite;
        delete mCoinSprite;
        delete mHeartSprite;
        delete mExitBtnSprite;
        delete mExitPanelSprite;
        delete m_endScreenSprite;
        for (int i = 0; i < 5; i++)
            delete mTowerSprite[i];
    }

private:
    sf::Font     mFont;
    bool         mFontLoaded;
    sf::Texture  mPanelTex;
    sf::Sprite* mPanelSprite;
    sf::Texture mBtnTex;
    sf::Sprite* mBtnSprite;
    sf::Texture mCoinTex;
    sf::Sprite* mCoinSprite;
    sf::Texture mHeartTex;
    sf::Sprite* mHeartSprite;
    sf::Texture mTowerTex[5];
    sf::Sprite* mTowerSprite[5];

    // exit button 
    // 
     // Exit Button (top right)
    sf::Texture mExitBtnTex;
    sf::Sprite* mExitBtnSprite;
    sf::FloatRect mExitBtnRect;
    bool mExitButtonHover = false;

    // Exit Panel (popup)
    sf::Texture mExitPanelTex;
    sf::Sprite* mExitPanelSprite;
    sf::FloatRect mYesBtnRect;
    sf::FloatRect mNoBtnRect;

   bool mYesHover = false;
   bool mNoHover = false;
   bool m_showExitPanel = false;

   // Win/Lose Screen
   sf::Texture m_endScreenTex;
   sf::Sprite* m_endScreenSprite;
   bool m_showEndScreen;
   bool m_isWin;  // true=win, false=lose

   // Sirf DO Rectangles (Dono screens ke liye same)
   sf::FloatRect m_playAgainRect;
   sf::FloatRect m_mainMenuRect;
   bool m_playAgainHover;
   bool m_mainMenuHover;

   
  
};