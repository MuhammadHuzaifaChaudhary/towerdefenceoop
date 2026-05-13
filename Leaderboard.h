#pragma once
#include <string>
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

const int MAX_SCORES = 5;

struct ScoreEntry
{
    char name[9];   // 8 chars + null terminator
    int  score;

    // opertator overloading 

    bool operator>(const ScoreEntry& other) const
    {
        return score > other.score;
    }

    bool operator<(const ScoreEntry& other) const
    {
        return score < other.score;
    }
};

class Leaderboard
{
public:
    Leaderboard();
    void loadFromFile();
    void saveToFile();
    void addScore(const string& name, int score);  // add and sort top 5
    void draw(RenderWindow& window);
    void handleHover(float mx, float my);
    bool handleClick(float mx, float my);  // true = back button

    ~Leaderboard() { delete mBgSprite; }

private:
    ScoreEntry    mScores[MAX_SCORES];
    int           mScoreCount;

    Texture   mBgTex;
    Sprite* mBgSprite;

    Font   mFont;
    bool   mFontLoaded;

    FloatRect mBackRect;
    bool  mBackHover;

    void drawText(RenderWindow& window,
        const string& str,
        float x, float y,
        int size, Color color);

};