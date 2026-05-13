#include "Instructions.h"
#include"Game.h"
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

Instructions::Instructions(): mBgSprite(nullptr), mBackHover(false)
{
    if (!mBgTex.loadFromFile("assets/instructions.png"))
    {
        Image img({ 1400u, 900u },Color(10, 10, 30));
        mBgTex.loadFromImage(img);
    }
    mBgSprite = new Sprite(mBgTex);
    auto s = mBgTex.getSize();
    mBgSprite->setScale({ 1400.f / s.x, 900.f / s.y });
    mBgSprite->setPosition({ 0.f, 0.f });

    // back button  adjust karna
    mBackRect = FloatRect({ 47.f, 42.f }, { 160.f, 60.f });
}

void Instructions::handleHover(float mx, float my)
{
    mBackHover = mBackRect.contains({ mx, my });
}

bool Instructions::handleClick(float mx, float my)
{  
    
    return mBackRect.contains({ mx, my });
}

void Instructions::draw(RenderWindow& window)
{
    window.draw(*mBgSprite);

    if (mBackHover)
    {
        sf::CircleShape r(40);
        r.setPosition({ mBackRect.position.x, mBackRect.position.y });
        r.setFillColor(sf::Color(255, 200, 0, 60));
        r.setOutlineColor(sf::Color(255, 200, 0));
        r.setOutlineThickness(2.f);
        window.draw(r);
    }
}