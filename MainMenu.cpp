#include "MainMenu.h"
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

MainMenu::MainMenu()
    : mBgSprite(nullptr)
    , mPlayHover(false)
    , mLeaderHover(false)
    , mSettingsHover(false)
    , mScrollHover(false)
    , mCoinsHover(false)
    , mExitHover(false)
{
    // background image load karo
    if (!mBgTex.loadFromFile("assets/menu3.png"))
    {
        Image img({ 1400u, 900u },Color(20, 10, 5));
        mBgTex.loadFromImage(img);
    }
    mBgSprite = new Sprite(mBgTex);
    auto s = mBgTex.getSize();
    mBgSprite->setScale({1400.f/s.x,900.f/s.y});
    //mBgSprite->setScale({0.8f,0.8f});
    mBgSprite->setPosition({ 0.f, 0.f });

    // 3 center buttons - coordinates adjust karna
    mPlayRect = FloatRect({ 565.f, 390.f }, { 255.f, 73.f });
    mLeaderRect = FloatRect({ 560.f, 507.f }, { 265.f, 80.f });
    mSettingsRect = FloatRect({ 565.f, 630.f }, { 255.f, 80.f });

    // 2 corner circles
    mScrollRect = FloatRect({ 140.f,  50.f }, { 160.f, 160.f });
    mCoinsRect = FloatRect({ 1100.f, 30.f }, { 160.f, 160.f });

    // exit button bottom right
    mExitRect = FloatRect({ 1210.f, 820.f }, { 120.f, 50.f });
}

void MainMenu::drawNormalRect(RenderWindow& window,FloatRect rect,Color color)
{
    RectangleShape r;
    r.setSize({ rect.size.x, rect.size.y });
    r.setPosition({ rect.position.x, rect.position.y });
    r.setFillColor(sf::Color(100,255,300,70));  // Transparent fill
    window.draw(r);
}

void MainMenu::drawHoverRect(sf::RenderWindow& window, sf::FloatRect rect, sf::Color color)
{

    RectangleShape r;
    r.setSize({ rect.size.x, rect.size.y });
    r.setPosition({ rect.position.x, rect.position.y });
    r.setFillColor(sf::Color(color.r, color.g, color.b, 60));
    window.draw(r);
}

void MainMenu::draw(sf::RenderWindow& window)
{
    window.draw(*mBgSprite);
    if (mPlayHover)
        drawHoverRect(window, mPlayRect, sf::Color(255, 200, 0, 200));
    if (mLeaderHover)
        drawHoverRect(window, mLeaderRect, sf::Color(255, 200, 0, 200));
    if (mSettingsHover)
        drawHoverRect(window, mSettingsRect, sf::Color(255, 200, 0, 200));
   /* if (mScrollHover)
        drawHoverRect(window, mScrollRect, sf::Color(100, 200, 255));
    if (mCoinsHover)
        drawHoverRect(window, mCoinsRect, sf::Color(255, 200, 0));*/
    if (mExitHover)
        drawHoverRect(window, mExitRect, sf::Color(255, 50, 50));
}

void MainMenu::handleHover(float mx, float my)
{
    mPlayHover = mPlayRect.contains({ mx, my });
    mLeaderHover = mLeaderRect.contains({ mx, my });
    mSettingsHover = mSettingsRect.contains({ mx, my });
    mScrollHover = mScrollRect.contains({ mx, my });
    mCoinsHover = mCoinsRect.contains({ mx, my });
    mExitHover = mExitRect.contains({ mx, my });
}

int MainMenu::handleClick(float mx, float my)
{
    if (mPlayRect.contains({ mx, my }))   
        return 0;  // Play
    if (mLeaderRect.contains({ mx, my }))   
        return 1;  // Leaderboard
    if (mSettingsRect.contains({ mx, my })) 
        return 2;  // Settings
    if (mScrollRect.contains({ mx, my }))  
        return 4;  //instructions
    if (mCoinsRect.contains({ mx, my }))    
        return 5;  // CoinsShop
    if (mExitRect.contains({ mx, my }))    
        return 3;  // Exit
    return -1;
}