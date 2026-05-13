#include "Map.h"
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

static int layout[MAP_ROWS][MAP_COLS] =
{
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // row 0
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // row 1
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // row 2
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // row 3
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0}, // row 4 middle
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0}, // row 5
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0}, // row 6
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0}, // row 7
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0}, // row 8
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // row 9
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // row 10
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // row 11
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // row 12 exit
};

Map::Map()
    : mGrassSprite(mGrassTex)
    , mPathSprite(mPathTex)
    , mBackgroundSprite(mBackgroundTex)  // initialize background sprite

{
    loadTextures();

    for (int r = 0; r < MAP_ROWS; r++)
        for (int c = 0; c < MAP_COLS; c++)
            mGrid[r][c] = layout[r][c];
    mSelectedBg = 0;
    mSelectedPath = 0;

}
void Map::setBackground(int index)
{
    mSelectedBg = index;
    std::string files[3] = {
        "assets/map1.png",
        "assets/bg2.png",
        "assets/p4.png"
    };
    if (!mBackgroundTex.loadFromFile(files[index]))
    {
        sf::Image img({ 1184u, 962u }, sf::Color(34, 85, 34));
        mBackgroundTex.loadFromImage(img);
    }
    mBackgroundSprite = sf::Sprite(mBackgroundTex);
    auto bgSize = mBackgroundTex.getSize();
    float scaleX = (float)(MAP_COLS * TILE_SIZE) / bgSize.x;
    float scaleY = (float)(MAP_ROWS * TILE_SIZE) / bgSize.y;
    mBackgroundSprite.setScale({ scaleX, scaleY });
}

void Map::setPathTexture(int index)
{
    mSelectedPath = index;
    std::string files[3] = {
        "assets/path1.jpeg",
        "assets/mud.png",
        "assets/p5.png"
    };
    if (!mPathTex.loadFromFile(files[index]))
    {
        sf::Image img({ (unsigned)TILE_SIZE, (unsigned)TILE_SIZE },
            sf::Color(139, 115, 85));
        mPathTex.loadFromImage(img);
    }
    mPathSprite = sf::Sprite(mPathTex);
    auto pathSize = mPathTex.getSize();
    float sx = (float)TILE_SIZE / pathSize.x;
    float sy = (float)TILE_SIZE / pathSize.y;
    mPathSprite.setScale({ sx, sy });
}
void Map::loadTextures()
{
    // load background image
    if (!mBackgroundTex.loadFromFile("assets/bg3.png"))
    {
        // fallback plain green
        sf::Image img({ 1184u, 962u }, sf::Color(34, 85, 34));
        mBackgroundTex.loadFromImage(img);
    }
    mBackgroundSprite = sf::Sprite(mBackgroundTex);

    // scale background to fit full map size
    auto bgSize = mBackgroundTex.getSize();
    float scaleX = (float)(MAP_COLS * TILE_SIZE) / bgSize.x;
    float scaleY = (float)(MAP_ROWS * TILE_SIZE) / bgSize.y;
    mBackgroundSprite.setScale({ scaleX, scaleY });
   // mBackgroundSprite.setScale({ 1.45f, 1.45f });

    // load path image
    if (!mPathTex.loadFromFile("assets/path1.png"))
    {
        sf::Image img({ (unsigned)TILE_SIZE, (unsigned)TILE_SIZE },
            sf::Color(139, 115, 85));
        mPathTex.loadFromImage(img);
    }
    mPathSprite = sf::Sprite(mPathTex);

    // scale path tile to match TILE_SIZE
    auto pathSize = mPathTex.getSize();
    float pathScaleX = (float)TILE_SIZE / pathSize.x;
    float pathScaleY = (float)TILE_SIZE / pathSize.y;
    mPathSprite.setScale({ pathScaleX, pathScaleY });
}

void Map::draw(sf::RenderWindow& window)
{
    // draw full background first
    window.draw(mBackgroundSprite);

    // draw only PATH tiles on top
    // 
    for (int r = 0; r < MAP_ROWS; r++)
    {
        for (int c = 0; c < MAP_COLS; c++)
        {
            float x = (float)(c * TILE_SIZE);
            float y = (float)(r * TILE_SIZE);

            if (mGrid[r][c] == PATH)
            {
                mPathSprite.setPosition({ x, y });
                window.draw(mPathSprite);
            }
        }
    }
}

bool Map::isBuildable(int col, int row)
{
    if (col < 0 || col >= MAP_COLS) return false;
    if (row < 0 || row >= MAP_ROWS) return false;
    return mGrid[row][col] == GRASS;
}

int Map::getTile(int col, int row)
{
    if (col < 0 || col >= MAP_COLS) return -1;
    if (row < 0 || row >= MAP_ROWS) return -1;
    return mGrid[row][col];
}