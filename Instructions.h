#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Instructions
{
public:
    Instructions();
    void draw(RenderWindow& window);
    void handleHover(float mx, float my);
    bool handleClick(float mx, float my);  // true = back
    // destructor 

    ~Instructions() { delete mBgSprite; }

private:
    Texture  mBgTex;
    Sprite* mBgSprite;
    FloatRect mBackRect;
    bool          mBackHover;
};