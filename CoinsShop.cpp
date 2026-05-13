#include "CoinsShop.h"
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

CoinsShop::CoinsShop()
    : mBgSprite(nullptr)
    , mFontLoaded(false)
    , mBackHover(false)
{
    if (!mBgTex.loadFromFile("assets/coin1.png"))
    {
        Image img({ 1400u, 900u },Color(10, 20, 10));
        mBgTex.loadFromImage(img);
    }
    mBgSprite = new Sprite(mBgTex);
    auto s = mBgTex.getSize();
    mBgSprite->setScale({ 1400.f / s.x, 900.f / s.y });
    mBgSprite->setPosition({ 0.f, 0.f });

    mFontLoaded = mFont.openFromFile("assets/Arial.ttf");

    // back button , adjust karna
    mBackRect = FloatRect({ 65.f, 780.f }, { 245.f, 65.f });
}

void CoinsShop::handleHover(float mx, float my)
{
    mBackHover = mBackRect.contains({ mx, my });
}

bool CoinsShop::handleClick(float mx, float my)
{
    return mBackRect.contains({ mx, my });
}

void CoinsShop::draw(RenderWindow& window, int gold)
{
    window.draw(*mBgSprite);

    // title text
    drawText(window, "INVENTORY", 560.f, 110.f, 48, sf::Color(255, 200, 0));

    // gold amount
    drawText(window,to_string(gold), 680.f, 265.f, 45,Color(255, 200, 0));

    // back button hover
    if (mBackHover)
    {
        sf::RectangleShape r;
        r.setSize({ mBackRect.size.x, mBackRect.size.y });
        r.setPosition({ mBackRect.position.x, mBackRect.position.y });
        r.setFillColor(Color(255, 200, 0, 60));
        r.setOutlineColor(Color(255, 200, 0));
        r.setOutlineThickness(2.f);
        window.draw(r);
    }
}

void CoinsShop::drawText(RenderWindow& window,
    const string& str,
    float x, float y,
    int size, Color color)
{
    if (!mFontLoaded) return;
    Text text(mFont);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition({ x, y });
    window.draw(text);
}