#include "NameEntry.h"
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

NameEntry::NameEntry()
    : mBgSprite(nullptr)
    , mPanelSprite(nullptr)
    , mFontLoaded(false)
    , mEnterHover(false)
    , mCursorTimer(0.f)      // ADD
    , mShowCursor(true)      //ADD
{
    // background image of golem holding enter name 
    if (!mBgTex.loadFromFile("assets/en.png"))
    {
        Image img({ 1400u, 900u },Color(20, 10, 5));
        mBgTex.loadFromImage(img);
    }
    mBgSprite = new Sprite(mBgTex);
    auto s = mBgTex.getSize();
    mBgSprite->setScale({ 0.5f,0.5f });
    mBgSprite->setPosition({ 400.f, 100.f });
    
    // background image 
    if (!mPanelTex.loadFromFile("assets/namebg3.jpeg"))
    {
        Image img({ 1400u, 900u },Color(30, 20, 10));
        mPanelTex.loadFromImage(img);
    }
    mPanelSprite = new Sprite(mPanelTex);
   Vector2u panelSize = mPanelTex.getSize();
    mPanelSprite->setScale({ 1400.f/panelSize.x,900.f/panelSize.y});
    mPanelSprite->setPosition({ 1.f, 0.f });

    //font load 

    mFontLoaded = mFont.openFromFile("assets/f4.otf");

    // Enter button rectangle   apni image ke hisaab se adjust karna
    mEnterBtnRect = FloatRect({ 580.f, 632.f }, { 200.f,48.f });
}

// NEW UPDATE FUNCTION - for cursor blink
void NameEntry::update(float dt)
{
    mCursorTimer += dt;
    if (mCursorTimer >= 0.5f)  // Har 0.5 second mein blink
    {
        mCursorTimer = 0.f;
        mShowCursor = !mShowCursor;
    }
}

void NameEntry::handleTextInput(uint32_t unicode)
{
    // Backspace
    if (unicode == 8)
    {
        if (!mName.empty())
            mName.pop_back();
        return;
    }

    // Only alphabets
    if (!((unicode >= 65 && unicode <= 90) ||
        (unicode >= 97 && unicode <= 122)))
        return;

    // Max 8 characters
    if (mName.size() >= 8) return;

    mName += static_cast<char>(unicode);
}

bool NameEntry::handleClick(float mx, float my)
{
    // hover update
    mEnterHover = mEnterBtnRect.contains({ mx, my });

    // Enter button click - only if name not empty
    if (mEnterBtnRect.contains({ mx, my }) && !mName.empty())
        return true;

    return false;
}

void NameEntry::draw(RenderWindow& window)
{  
    window.draw(*mPanelSprite);
    window.draw(*mBgSprite);

    // typed name display, position adjust karna (COORDINATES SAME)
    drawText(window, mName, 590.f, 523.f, 40, sf::Color(255, 220, 0));

    //VERTICAL CURSOR with blink effect (COORDINATES SAME)
    if (mShowCursor)
    {
        // Vertical line cursor - jaise keyboard mein hota hai
        float cursorX = 580.f + mName.size()*24.f;
        float cursorY = 530.f;

        RectangleShape cursor(Vector2f(3.f, 45.f));  // 3px wide, 45px tall
        cursor.setFillColor(Color(255, 220, 0));
        cursor.setPosition({ cursorX, cursorY });
        window.draw(cursor);
    }

    // Enter button hover effect (SAME)
    if (mEnterHover && !mName.empty())
    {
        RectangleShape r;
        r.setSize({ mEnterBtnRect.size.x, mEnterBtnRect.size.y });
        r.setPosition({ mEnterBtnRect.position.x, mEnterBtnRect.position.y });
        r.setFillColor(sf::Color(100, 255, 100, 100));
        window.draw(r);
    }
}

void NameEntry::drawText(RenderWindow& window,
    const 
    string& str,
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