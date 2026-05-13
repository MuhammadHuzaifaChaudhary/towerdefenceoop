#pragma once
#include "Entity.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include "Projectile.h"
#include<iostream>
using namespace std;
using namespace sf; 

const int MAX_PROJECTILES = 200;

class Tower : public Entity
{
public:
    Tower(float x, float y, float range, float damage, float fireRate);
    virtual ~Tower() {}

    // NOT override - Tower has its own update signature
    virtual void update(float dt, Enemy** enemies, int enemyCount);
    virtual void draw(sf::RenderWindow& window);        // draws tower + range circle
    virtual void fire(Enemy* target) = 0;               // pure virtual

    float getRange()  const { return mRange; }
    float getDamage() const { return mDamage; }
    // projectile settings 
    void updateProjectiles(float dt);
    void drawProjectiles(sf::RenderWindow& window);

protected:
    float mRange;
    float mDamage;
    float mFireRate;
    float mFireTimer;
    float mRotation;
    float mRecoilOffset;
    // projectile 
    Projectile* mProjectiles[MAX_PROJECTILES];
    int         mProjectileCount;
    sf::Texture mTexture;
    sf::Sprite  mSprite;

    Enemy* findNearestEnemy(Enemy** enemies, int enemyCount);
    void   loadTexture(const std::string& filename);
    void   rotateToward(Enemy* target);
};

// ---- CONCRETE TOWERS ----

class CannonTower : public Tower
{
public:
    CannonTower(float x, float y)
        : Tower(x, y, 150.f, 30.f, 1.f)    // 150 range ,  50 damage , 1 speed 
    {
        loadTexture("assets/cannon2.png");
        mSprite.setScale({ 0.25f, 0.25f });  // Bada
    }

    void fire(Enemy* target) override;
};

class ArcherTower : public Tower
{
public:
    ArcherTower(float x, float y)
        : Tower(x, y, 250.f, 5.f, 7.f)
    {
        loadTexture("assets/archery.png");
        mSprite.setScale({ 0.25f, 0.25f });  // Bada
    }

    void fire(Enemy* target) override;
};

class WizardTower : public Tower
{
public:
    WizardTower(float x, float y)
        : Tower(x, y, 180.f, 75.f, 0.7f)
    {
        loadTexture("assets/wizard.png");
    }

    void fire(Enemy* target) override;
};

class ElectricTower : public Tower
{
public:
    ElectricTower(float x, float y)
        : Tower(x, y, 120.f, 10.f, 3.f)
    {
        loadTexture("assets/electric.png");

    }

    void fire(Enemy* target) override;
};

class BowTower : public Tower
{
public:
    BowTower(float x, float y)
        : Tower(x, y, 200.f, 10.f, 1.5f)
    {
        loadTexture("assets/inf3.png");
        mSprite.setScale({ 0.16f, 0.16f });  // Bada
    }

    void fire(Enemy* target) override;
};