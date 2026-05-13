#pragma once
#include <string>
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class NameEntry
{
public:
    NameEntry();
    void draw(RenderWindow& window);
    void handleTextInput(uint32_t unicode);  // keyboard input
    bool handleClick(float mx, float my);       // returns true = Enter pressed
    const string& getName() const { return mName; }
    void reset() { mName = ""; }
    void update(float dt);  //NEW - for cursor blink

    ~NameEntry()
    {
        delete mBgSprite;
        delete mPanelSprite;
    }

private:
    Texture  mBgTex;
    Sprite* mBgSprite;

    Texture  mPanelTex;     
    Sprite* mPanelSprite;

    Font  mFont;
    bool  mFontLoaded;

    string  mName;          // current typed name

    FloatRect mEnterBtnRect; // Enter button rectangle

    bool         mEnterHover;

    // NEW VARIABLES FOR CURSOR BLINK
    float mCursorTimer;
    bool  mShowCursor;

    void drawText(RenderWindow& window,
        const string& str,
        float x, float y,
        int size, sf::Color color);

   
};