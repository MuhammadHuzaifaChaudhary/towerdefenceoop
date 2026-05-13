#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include<iostream>
using namespace std;
using namespace sf;

// projectile types - each looks different
enum class ProjectileType
{
    Cannonball,   // gray/black circle
    Arrow,        // thin fast line
    Fireball,     // orange circle with glow
    Electric,     // blue zigzag
    SlowOrb       // purple circle
};

class Projectile
{
public:
    Projectile(float startX, float startY,
        float targetX, float targetY,
        float damage, float speed,
        ProjectileType type);
    bool mHitApplied = false;  // prevents damage being applied twice

    void update(float dt);
    void draw(sf::RenderWindow& window);

    bool isAlive()    const { return mAlive; }
    bool hasHit()     const { return mHit; }
    float getDamage() const { return mDamage; }

    float getX() const { return mX; }
    float getY() const { return mY; }

    // target position (to check collision)
    float mTargetX, mTargetY;

private:
    float mX, mY;
    float mVx, mVy;        // velocity direction
    float mDamage;
    float mSpeed;
    bool  mAlive;
    bool  mHit;

    ProjectileType mType;

    // explosion effect
    float mExplosionTimer;
    bool  mExploding;
};


