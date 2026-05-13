#include "Settings.h"
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

Settings::Settings(): mBgSprite(nullptr), mFontLoaded(false)    , mVolume(300), mMuted(false), mSelectedBg(0), mSelectedPath(0), mVolMinusHover(false), mVolPlusHover(false), mMuteHover(false), mBackHover(false)
{
    for (int i = 0; i < 3; i++)
    {
        mBgHover[i] = false;
        mPathHover[i] = false;
        mMapPreviewSprite[i] = nullptr;
        mPathPreviewSprite[i] = nullptr;
    }

    // settings background
    if (!mBgTex.loadFromFile("assets/settings.png"))
    {
        Image img({ 1400u, 900u }, sf::Color(15, 10, 25));
        mBgTex.loadFromImage(img);
    }
    mBgSprite = new Sprite(mBgTex);
    auto s = mBgTex.getSize();
    mBgSprite->setScale({ 1400.f / s.x, 900.f / s.y });
    mBgSprite->setPosition({ 0.f, 0.f });

    mFontLoaded = mFont.openFromFile("assets/Arial.ttf");

    // volume controls - center of screen
    mVolMinusRect = FloatRect({ 450.f, 150.f }, { 80.f,  80.f });
    mVolPlusRect = sf::FloatRect({ 852.f, 150.f }, { 78.f, 78.f });
    mMuteRect = sf::FloatRect({ 1275.f, 43.f }, { 70.f,69.f });

    // managing indeoendently 
    
    float mapBox1_X = 315.f;    // Box 1 ka X
    float mapBox2_X = 590.f;    // Box 2 ka X
    float mapBox3_X = 857.f;    // Box 3 ka X
    float mapBox_Y = 325.f;     // Sab boxes ka Y

    mBgRect[0] = { { mapBox1_X, mapBox_Y }, { 238.f, 180.f } };
    mBgRect[1] = { { mapBox2_X, mapBox_Y }, { 235.f, 180.f } };
    mBgRect[2] = { { mapBox3_X, mapBox_Y }, { 227.f, 181.f } };

    // path preview boxes
    float pathStartX = 398.f;
    float pathY = 597.f;
    for (int i = 0; i < 3; i++)
    {                             // positions                      // sizes
        mPathRect[i] = FloatRect({ pathStartX + i * 213.f, pathY }, { 169.f, 173.f });
    }

    // back button
    mBackRect = FloatRect({ 53.f, 783.f }, { 223.f, 68.f });

    // load map preview textures
    const char* bgFiles[3] = {
        "assets/map1.png",
        "assets/bg2.png",
        "assets/p4.png"
    };
    const char* pathFiles[3] = {
        "assets/path1.jpeg",
        "assets/mud.png",
        "assets/p5.png"
    };

    for (int i = 0; i < 3; i++)
    {
        // map previews
        if (!mMapPreviewTex[i].loadFromFile(bgFiles[i]))
        {
            Image img({ 280u, 180u },Color(30 + i * 20, 50, 30));
            mMapPreviewTex[i].loadFromImage(img);
        }
        mMapPreviewSprite[i] = new Sprite(mMapPreviewTex[i]);
        auto ms = mMapPreviewTex[i].getSize();

        // scalex, scale y help us to make sizes of boxes individually 

        float scaleX = mBgRect[i].size.x / ms.x;   // Rectangle width / texture width
        float scaleY = mBgRect[i].size.y / ms.y;   // Rectangle height / texture height

         //  mMapPreviewSprite[i]->setScale({ 238.f / ms.x, 180.f / ms.y });
        // new one 
        mMapPreviewSprite[i]->setScale({ scaleX,scaleY });

        // path previews
        if (!mPathPreviewTex[i].loadFromFile(pathFiles[i]))
        {
            Image img({ 280u, 120u },Color(100 + i * 20, 80, 50));
            mPathPreviewTex[i].loadFromImage(img);
        }
        mPathPreviewSprite[i] = new Sprite(mPathPreviewTex[i]);
        auto ps = mPathPreviewTex[i].getSize();
        mPathPreviewSprite[i]->setScale({ 169.f / ps.x, 173.f / ps.y });
    }
}

void Settings::drawHoverRect(RenderWindow& window, FloatRect rect,Color color)
{
    RectangleShape r;
    r.setSize({ rect.size.x, rect.size.y });
    r.setPosition({ rect.position.x, rect.position.y });
    r.setFillColor(sf::Color(color.r, color.g, color.b, 60));
    r.setOutlineColor(color);
    r.setOutlineThickness(2.f);
    window.draw(r);
}

void Settings::handleHover(float mx, float my)
{
    mVolMinusHover = mVolMinusRect.contains({ mx, my });
    mVolPlusHover = mVolPlusRect.contains({ mx, my });
    mMuteHover = mMuteRect.contains({ mx, my });
    mBackHover = mBackRect.contains({ mx, my });
    for (int i = 0; i < 3; i++)
    {
        mBgHover[i] = mBgRect[i].contains({ mx, my });
        mPathHover[i] = mPathRect[i].contains({ mx, my });
    }
}

int Settings::handleClick(float mx, float my)
{
    if (mBackRect.contains({ mx, my }))     return 0;
    if (mVolMinusRect.contains({ mx, my })) return 1;
    if (mVolPlusRect.contains({ mx, my }))  return 2;
    if (mMuteRect.contains({ mx, my }))     return 3;
    for (int i = 0; i < 3; i++)
        if (mBgRect[i].contains({ mx, my }))   return 10 + i;
    for (int i = 0; i < 3; i++)
        if (mPathRect[i].contains({ mx, my })) return 20 + i;
    return -1;
}

void Settings::draw(RenderWindow& window)
{
    window.draw(*mBgSprite);

   
    // minus button
    drawHoverRect(window, mVolMinusRect,
        mVolMinusHover ? Color(255, 100, 100) : Color(0,0,0,0));
 

    // volume box
    RectangleShape volBox;
    volBox.setSize({ mVolBoxRect.size.x, mVolBoxRect.size.y });
    volBox.setPosition({ mVolBoxRect.position.x, mVolBoxRect.position.y });
    volBox.setFillColor(Color(30, 20, 10));
    volBox.setOutlineColor(Color(180, 130, 0));
    volBox.setOutlineThickness(2.f);
    window.draw(volBox);

    // volume text inside box
    string volStr = mMuted ? "MUTED" :to_string(mVolume);
   drawText(window, volStr, 650.f, 165.f, 34,Color(255, 200, 0));

    // plus button
    drawHoverRect(window, mVolPlusRect,
        mVolPlusHover ? Color(100, 255, 100) :Color(0,0,0,0));

    // mute button
    drawHoverRect(window, mMuteRect,
        mMuteHover ? Color(255, 50, 50) :Color(0,0,0,0));

    // MAP SECTION 
    for (int i = 0; i < 3; i++)
    {
        // preview image
        mMapPreviewSprite[i]->setPosition({
            mBgRect[i].position.x, mBgRect[i].position.y });
        window.draw(*mMapPreviewSprite[i]);

        // selected highlight - gold border
        if (i == mSelectedBg)
        {
            RectangleShape sel;
            sel.setSize({ mBgRect[i].size.x, mBgRect[i].size.y });
            sel.setPosition({ mBgRect[i].position.x, mBgRect[i].position.y });
            sel.setFillColor(sf::Color(0, 0, 0, 0));
            sel.setOutlineColor(sf::Color(255, 200, 0));
            sel.setOutlineThickness(4.f);
            window.draw(sel);
        }
        else if (mBgHover[i])
            drawHoverRect(window, mBgRect[i], sf::Color(255, 200, 0));
    }

    // ===== PATH SECTION =====

    for (int i = 0; i < 3; i++)
    {
        // preview image
        mPathPreviewSprite[i]->setPosition({
            mPathRect[i].position.x, mPathRect[i].position.y });
        window.draw(*mPathPreviewSprite[i]);

        // selected highlight
        if (i == mSelectedPath)
        {
            RectangleShape sel;
            sel.setSize({ mPathRect[i].size.x, mPathRect[i].size.y });
            sel.setPosition({ mPathRect[i].position.x, mPathRect[i].position.y });
            sel.setFillColor(Color(0, 0, 0, 0));
            sel.setOutlineColor(Color(255, 200, 0));
            sel.setOutlineThickness(4.f);
            window.draw(sel);
        }
        else if (mPathHover[i])
        {
            drawHoverRect(window, mPathRect[i],Color(255, 200, 0));
        }
    }

    // back button
    if (mBackHover)
    {
        drawHoverRect(window, mBackRect, Color(255, 200, 0));
    }

  //drawText(window, "BACK", 100.f, 833.f, 28, sf::Color(220, 180, 0));
}

void Settings::drawText(RenderWindow& window,
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