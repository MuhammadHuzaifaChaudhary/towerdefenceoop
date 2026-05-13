#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include<iostream>

using namespace std;
using namespace sf;
class CoinsShop
{
public:
    CoinsShop();
    void draw(RenderWindow& window, int gold);
    void handleHover(float mx, float my);
    bool handleClick(float mx, float my);

    ~CoinsShop() { delete mBgSprite; }


private:
    Texture   mBgTex;
    Sprite* mBgSprite;
    Font      mFont;
    bool          mFontLoaded;
    FloatRect mBackRect;
    bool          mBackHover;

    void drawText(RenderWindow& window,
        const string& str,
        float x, float y,
        int size, sf::Color color);

};