#include "Leaderboard.h"
#include <fstream>
#include <cstring>
#include<iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

Leaderboard::Leaderboard()
    : mBgSprite(nullptr)
    , mFontLoaded(false)
    , mScoreCount(0)
    , mBackHover(false)
{
    // initialize scores array
    for (int i = 0; i < MAX_SCORES; i++)
    {
        mScores[i].name[0] = '\0';
        mScores[i].score = 0;
    }

    // background
    if (!mBgTex.loadFromFile("assets/l3.png"))
    {
        Image img({ 1400u, 900u },Color(10, 10, 30));
        mBgTex.loadFromImage(img);
    }
    mBgSprite = new Sprite(mBgTex);
    auto s = mBgTex.getSize();
    mBgSprite->setScale({ 1400.f/s.x,900.f/s.y });
    mBgSprite->setPosition({ 0.f, 0.f });

    mFontLoaded = mFont.openFromFile("assets/kn.otf");

    // back button rectangle - adjust karna
    mBackRect = FloatRect({ 658.f, 762.f }, { 85.f, 65.f });

    loadFromFile();
}

void Leaderboard::loadFromFile()
{
    ifstream file("scores.txt");
    if (!file.is_open()) return;

    mScoreCount = 0;
    while (mScoreCount < MAX_SCORES)
    {
        string name;
        int score;
        if (!(file >> name >> score)) break;

        // copy name safely
        int len = (int)name.size();
        if (len > 8) len = 8;
        for (int i = 0; i < len; i++)
            mScores[mScoreCount].name[i] = name[i];
        mScores[mScoreCount].name[len] = '\0';
        mScores[mScoreCount].score = score;
        mScoreCount++;
    }
    file.close();
}

void Leaderboard::saveToFile()
{
    ofstream file("scores.txt");
    if (!file.is_open()) return;

    for (int i = 0; i < mScoreCount; i++)
        file << mScores[i].name << " " << mScores[i].score << "\n";

    file.close();
}

void Leaderboard::addScore(const std::string& name, int score)
{
    // agar score 0 hai to save mat karo
    if (score <= 0) return;

    // naya entry banao
    ScoreEntry newEntry;
    int len = (int)name.size();
    if (len > 8) len = 8;
    for (int i = 0; i < len; i++)
        newEntry.name[i] = name[i];
    newEntry.name[len] = '\0';
    newEntry.score = score;

    // agar 5 se kam scores hain to seedha add karo
    if (mScoreCount < MAX_SCORES)
    {
        mScores[mScoreCount++] = newEntry;
    }
    else
    {
        // check karo minimum score se compare
        int minIdx = 0;
        for (int i = 1; i < MAX_SCORES; i++)
            if (mScores[i].score < mScores[minIdx].score)
                minIdx = i;

        // sirf replace karo agar naya score zyada ho
        if (newEntry.score > mScores[minIdx].score)
            mScores[minIdx] = newEntry;
        else
            return;  // score leaderboard mein add hone layak nahi
    }

    // bubble sort - descending order
    for (int i = 0; i < mScoreCount - 1; i++)
        for (int j = 0; j < mScoreCount - i - 1; j++)
            if (mScores[j] < mScores[j + 1])    // direct < operator is being used 
            {
                ScoreEntry temp = mScores[j];
                mScores[j] = mScores[j + 1];
                mScores[j + 1] = temp;
            }

    saveToFile();
}

void Leaderboard::handleHover(float mx, float my)
{
    mBackHover = mBackRect.contains({ mx, my });
}

bool Leaderboard::handleClick(float mx, float my)
{
    return mBackRect.contains({ mx, my });
}

void Leaderboard::draw(RenderWindow& window)
{
   
    window.draw(*mBgSprite);
    // scores list
    if (mScoreCount == 0)
    {
        drawText(window, "No scores yet!", 640.f, 220.f, 40,
            Color(180, 180, 180));
    }
    else
    {
        for (int i = 0; i < mScoreCount; i++)
        {
            float y = 220.f + i * 110.f;

            // rank number
            Color rowColor = (i == 0) ?   Color(255, 200, 0) :    // gold for 1st
            Color(220, 220, 220);   // white for rest

            // name
            drawText(window,
                std::string(mScores[i].name),
                610.f, y, 40, rowColor);

            // score
            drawText(window,to_string(mScores[i].score), 790.f, y, 36, rowColor);
        }
    }

    // back button hover
    if (mBackHover)
    {
       CircleShape r(40);
      //  r.setSize({ mBackRect.size.x, mBackRect.size.y });
       r.setPosition({ mBackRect.position.x+2.f, mBackRect.position.y-10.f});
       r.setFillColor(Color(255, 200, 0, 60));
       r.setOutlineColor(Color(255, 200, 0));
       r.setOutlineThickness(2.f);
        window.draw(r);
    }

   // drawText(window, "BACK", 700.f, 833.f, 28, sf::Color(220, 180, 0));
}

void Leaderboard::drawText(RenderWindow& window,
    const string& str,
    float x, float y,
    int size, sf::Color color)
{
    if (!mFontLoaded) return;
    Text text(mFont);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition({ x, y });
    window.draw(text);
}