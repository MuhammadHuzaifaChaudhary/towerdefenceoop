#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include<iostream>
using namespace std;
using namespace sf;

class MainMenu
{
public:
    MainMenu();
    void draw(RenderWindow& window);
    void handleHover(float mx, float my);
    int  handleClick(float mx, float my);
    // returns: 0=Play, 1=Leaderboard, 2=Settings, 3=Exit, -1=nothing
    ~MainMenu() { delete mBgSprite; }

private:
    Texture  mBgTex;
    Sprite* mBgSprite;

    // 3 center buttons
    FloatRect mPlayRect;
    FloatRect mLeaderRect;
    FloatRect mSettingsRect;

    // 2 corner circles
    FloatRect mScrollRect;   // top left
    FloatRect mCoinsRect;    // top right

    // exit button bottom right
    FloatRect mExitRect;

    // hover states
    bool mPlayHover;
    bool mLeaderHover;
    bool mSettingsHover;
    bool mScrollHover;
    bool mCoinsHover;
    bool mExitHover;

    void drawHoverRect(RenderWindow& window,
        FloatRect rect, Color color);
    void drawNormalRect(RenderWindow& window,
        FloatRect rect,Color color);

    
};