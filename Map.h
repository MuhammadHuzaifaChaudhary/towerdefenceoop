#pragma once               // prevent double inclusion
#include <SFML/Graphics.hpp>   // SFML types
#include<iostream>
using namespace std;
using namespace sf;

const int TILE_SIZE = 74;      // each tile is 64x64 pixels
const int MAP_COLS = 16;      // map is 15 tiles wide
const int MAP_ROWS = 13;      // map is 11 tiles tall

const int GRASS = 0;           // grass tile value in grid
const int PATH = 1;           // path tile value in grid

class Map
{
public:
    Map();                                      // constructor loads textures
    void draw(sf::RenderWindow& window);        // draws all tiles
    bool isBuildable(int col, int row);         // returns true if tower can go here
    int  getTile(int col, int row);             // returns tile type at position

    void setBackground(int index);  // 0,1,2
    void setPathTexture(int index); // 0,1,2
    int  getSelectedBg()   const { return mSelectedBg; }
    int  getSelectedPath() const { return mSelectedPath; }

private:
    void loadTextures();                        // loads images from files

    int mGrid[MAP_ROWS][MAP_COLS];             // 2D array storing tile types

    sf::Texture mGrassTex;      // texture (image data) for grass
    sf::Texture mPathTex;       // texture (image data) for path
    sf::Sprite  mGrassSprite;   // sprite (drawable object) for grass
    sf::Sprite  mPathSprite;    // sprite (drawable object) for path
    sf::Texture mBackgroundTex;
    sf::Sprite  mBackgroundSprite;

    int mSelectedBg;
    int mSelectedPath;
};