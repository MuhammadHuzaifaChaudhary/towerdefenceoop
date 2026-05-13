#pragma once
#include <string>
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Settings
{
public:
    Settings();
    void draw(RenderWindow& window);
    void handleHover(float mx, float my);
    int  handleClick(float mx, float my);
    // returns: -1=nothing, 0=back, 1=volMinus, 2=volPlus,
    //          3=mute, 10/11/12=bg0/1/2, 20/21/22=path0/1/2

    int  getVolume()      const { return mVolume; }
    bool isMuted()        const { return mMuted; }
    int  getSelectedBg()  const { return mSelectedBg; }
    int  getSelectedPath()const { return mSelectedPath; }

    // map selection - 3 boxes
    FloatRect mBgRect[3];
    int           mSelectedBg;

    // path selection - 3 boxes
    FloatRect mPathRect[3];
    int           mSelectedPath;

    void setVolume(int vol) { mVolume = vol; }
    void setMuted(bool m) { mMuted = m; }

    ~Settings()
    {
        delete mBgSprite;
        for (int i = 0; i < 3; i++)
        {
            delete mMapPreviewSprite[i];
            delete mPathPreviewSprite[i];
        }
    }
private:
    Texture  mBgTex;
    Sprite* mBgSprite;

    Font     mFont;
    bool         mFontLoaded;

    // volume
    int   mVolume;      // 0-100
    bool  mMuted;
    FloatRect mVolMinusRect;
    FloatRect mVolBoxRect;
    FloatRect mVolPlusRect;
    FloatRect mMuteRect;

 

    // back button
    FloatRect mBackRect;

    // hover states
    bool mVolMinusHover;
    bool mVolPlusHover;
    bool mMuteHover;
    bool mBgHover[3];
    bool mPathHover[3];
    bool mBackHover;

    // map/path preview textures
    Texture  mMapPreviewTex[3];
    Sprite* mMapPreviewSprite[3];
    Texture  mPathPreviewTex[3];
    Sprite* mPathPreviewSprite[3];

    void drawHoverRect(RenderWindow& window,FloatRect rect,Color color);
    void drawText(RenderWindow& window,const string& str, float x, float y, int size, Color color);

   
};