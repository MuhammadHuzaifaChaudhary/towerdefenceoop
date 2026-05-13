#pragma once
#include "Entity.h"      // Bring in Entity so Enemy can inherit from it.
#include <SFML/Graphics.hpp>
#include <string>
#include<iostream>
using namespace std;
using namespace sf; 

struct Waypoint
{
    float x, y;    
};

const int  NUM_WAYPOINTS = 6;
const Waypoint WAYPOINTS[NUM_WAYPOINTS] =
{
    { 108.f,  36.f },
    { 108.f, 324.f },
    { 972.f, 324.f },
    { 972.f, 612.f },
    { 108.f, 612.f },
    { 108.f, 900.f },
};

class Enemy : public Entity   
    // Enemy class INHERITS from Entity.

{
public:
    Enemy(float x, float y, float speed, float maxHp);  // child class se hi ye sab kuch ata hay .. like basic enemy se floatx float y or saath me do values 

   virtual void update(float dt);
    // Move the enemy along the path. Called every frame.
    // dt = delta time (seconds since last frame) — makes speed consistent
    //      on all computers regardless of frame rate.

    void draw(sf::RenderWindow& window) override;
    // Draw the enemy image on screen. "override" means we are replacing
   // the pure virtual draw() from Entity with our own implementation.

    void takeDamage(float amount);
    // Reduce HP by "amount". If HP reaches 0, set mAlive = false (enemy dies).

    // slow function
    // Slow down this enemy. factor = 0.5 means half speed.
    // Called when BowTower's SlowOrb hits the enemy.

    void applySlow(float factor)
    {
        mSpeed = mBaseSpeed * factor;
        mSlowTimer = 4.f;  // 2 sec ke liye slow
    }

    void heal(float amount)
    {
        mHp += amount;
        if (mHp > mMaxHp) mHp = mMaxHp;  // max se zyada nahi
    }
    float getHp()      const { return mHp; }
    // Returns current HP — used to draw the HP bar.


    float getMaxHp()   const { return mMaxHp; }
    bool  hasEscaped() const { return mEscaped; }

protected:
    float mSpeed;
    float mBaseSpeed;      // original speed for slow recovery
    float mHp;
    float mMaxHp;
    bool  mEscaped;
    int   mCurrentWaypoint;
    // Index of the NEXT waypoint the enemy is heading toward.
    // Starts at 1 because enemy spawns AT waypoint 0.
     float mSlowTimer;  // kitni der slow rahegi

    Texture mTexture;
    Sprite  mSprite;

    void loadTexture(const string& filename);
    void drawHpBar(sf::RenderWindow& window);
    // Helper function — draws the green/yellow/red health bar above the enemy.
};

// ---- CONCRETE ENEMIES ----

class BasicEnemy : public Enemy
{
public:
    BasicEnemy(float x, float y)
        : Enemy(x, y, 80.f, 100.f)
    {
        loadTexture("assets/barbarian.png");
    }
};

class FastEnemy : public Enemy
{
public:
    FastEnemy(float x, float y)
        : Enemy(x, y, 160.f, 40.f)
    {
        loadTexture("assets/goblin.png");
    }
};

class TankEnemy : public Enemy
{
public:
    TankEnemy(float x, float y)
        : Enemy(x, y, 40.f, 400.f)
    {
        loadTexture("assets/peka.png");
    }
};

class FlyingEnemy : public Enemy
{
public:
    FlyingEnemy(float x, float y);
    void update(float dt);

private:
    float mTargetX, mTargetY;
};

class BombEnemy : public Enemy
{
public:
    BombEnemy(float x, float y)
        : Enemy(x, y, 60.f, 150.f)
    {
        loadTexture("assets/golem.png");
    }

    bool hasExploded() const { return mExploded; }
    void takeDamage(float amount);

private:
    bool mExploded = false;
};

class HealEnemy : public Enemy
{
public:
    HealEnemy(float x, float y)
        : Enemy(x, y, 60.f, 200.f)
        , mHealTimer(0.f)// Start heal timer at 0. It counts up to 3.0 seconds.
        , mHealRadius(150.f)// Heals enemies within 150 pixel radius.
        , mHealAmount(20.f) // Each heal restores 20 HP to nearby enemies.

    {
        loadTexture("assets/healer.png");
    }

    void update(float dt, Enemy** enemies, int count);
    // Special update ..... takes the full enemy list as parameters
    // so it can find and heal nearby enemies.
    // "Enemy**" = a pointer to an array of Enemy pointers.


private:
    float mHealTimer;
    float mHealRadius;
    float mHealAmount;
};