#include "Tower.h"
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

Tower::Tower(float x, float y, float range, float damage, float fireRate)
    : Entity(x, y)
    , mRange(range)
    , mDamage(damage)
    , mFireRate(fireRate)
    , mFireTimer(0.f)
    , mRotation(0.f)
    , mRecoilOffset(0.f)
    , mSprite(mTexture)
    , mProjectileCount(0)  // ADD THIS
{
    for (int i = 0; i < MAX_PROJECTILES; i++)
        mProjectiles[i] = nullptr;
}

void Tower::loadTexture(const std::string& filename)
{
    if (!mTexture.loadFromFile(filename))
    {
        sf::Image img({ 64u, 64u }, sf::Color(100, 100, 120));
        mTexture.loadFromImage(img);
    }
    mSprite = sf::Sprite(mTexture);
    auto size = mTexture.getSize();
    mSprite.setOrigin({ size.x / 2.f, size.y / 2.f });
    if (filename == "assets/electric.png")
    {
        mSprite.setScale({ 0.09f, 0.09f });  // Bada
    }
    //if (filename == "assets/inf3.png")
    //{
    //    mSprite.setScale({ 0.2f, 0.2f });  // Bada
    //}
    else
    {
        mSprite.setScale({ 0.15f, 0.15f });  // Normal
    }
}

void Tower::rotateToward(Enemy* target)
{ 
    float currentScale = std::abs(mSprite.getScale().x);
    if (!target) return;
    float dx = target->getX() - mX;
   /* if (dx > 0)
        mSprite.setScale({ 0.15f, 0.15f });
    else
        mSprite.setScale({ -0.15f, 0.15f });*/

    // now its variable .. it will take size of each tower then it will do rotation according to their size 

    if (dx > 0)
        mSprite.setScale({ currentScale,currentScale });
    else
        mSprite.setScale({ -currentScale,currentScale });
}

void Tower::updateProjectiles(float dt)
{
    for (int i = 0; i < mProjectileCount; i++)
    {
        if (mProjectiles[i] == nullptr) continue;

        mProjectiles[i]->update(dt);

        if (!mProjectiles[i]->isAlive())
        {
            delete mProjectiles[i];
            mProjectiles[i] = nullptr;

            for (int j = i; j < mProjectileCount - 1; j++)
                mProjectiles[j] = mProjectiles[j + 1];

            mProjectiles[mProjectileCount - 1] = nullptr;
            mProjectileCount--;
            i--;
        }
    }
}

void Tower::drawProjectiles(sf::RenderWindow& window)
{
    for (int i = 0; i < mProjectileCount; i++)
        if (mProjectiles[i] != nullptr)
            mProjectiles[i]->draw(window);
}

Enemy* Tower::findNearestEnemy(Enemy** enemies, int enemyCount)
{
    if (enemies == nullptr) return nullptr;

    Enemy* nearest = nullptr;
    float  minDist = mRange;

    for (int i = 0; i < enemyCount; i++)
    {
        if (enemies[i] == nullptr) continue;
        if (!enemies[i]->isAlive()) continue;

        float dx = enemies[i]->getX() - mX;
        float dy = enemies[i]->getY() - mY;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist < minDist)
        {
            minDist = dist;
            nearest = enemies[i];
        }
    }
    return nearest;
}

void Tower::update(float dt, Enemy** enemies, int enemyCount)
{
    // FIRST: Check and apply projectile hits
    for (int i = 0; i < mProjectileCount; i++)
    {
        if (mProjectiles[i] == nullptr) continue;
        if (!mProjectiles[i]->hasHit()) continue;
        if (mProjectiles[i]->mHitApplied) continue;

        // Find enemy near impact point
        for (int j = 0; j < enemyCount; j++)
        {
            if (enemies[j] == nullptr) continue;
            if (!enemies[j]->isAlive()) continue;

            float dx = enemies[j]->getX() - mProjectiles[i]->mTargetX;
            float dy = enemies[j]->getY() - mProjectiles[i]->mTargetY;
            float dist = std::sqrt(dx * dx + dy * dy);

            if (dist < 50.f)
            {
                //enemies[j]->takeDamage(mProjectiles[i]->getDamage());
                if (mProjectiles[i]->getDamage() > 0)
                {
                    enemies[j]->takeDamage(mProjectiles[i]->getDamage());
                }
                mProjectiles[i]->mHitApplied = true;
                break;  // Exit once damage is applied
            }
        }
    }

    // SECOND: Update projectiles (this will remove exploded ones)
    updateProjectiles(dt);

    // THIRD: Find target and fire new projectiles
    Enemy* target = findNearestEnemy(enemies, enemyCount);

    if (target && target->isAlive())  // Check if target is still alive
    {
        rotateToward(target);

        mFireTimer += dt;
        if (mFireRate > 0.f && mFireTimer >= 1.f / mFireRate)
        {
            mFireTimer = 0.f;
            fire(target);
            mRecoilOffset = 8.f;
        }
    }

    if (mRecoilOffset > 0.f)
    {
        mRecoilOffset -= 40.f * dt;
        if (mRecoilOffset < 0.f) mRecoilOffset = 0.f;
    }
}

void Tower::draw(sf::RenderWindow& window)
{      
    // Recoil shake
    float offsetX = (rand() % 7 - 3) * (mRecoilOffset / 10.f);
    float offsetY = (rand() % 7 - 3) * (mRecoilOffset / 10.f);

    mSprite.setPosition({ mX + offsetX, mY + offsetY });

    // if dont want recoil then just draw this and comment upper code 
   // mSprite.setPosition({ mX, mY });
    window.draw(mSprite);

    sf::CircleShape rangeCircle(mRange);
    rangeCircle.setFillColor(sf::Color(255, 255, 255, 10));
    rangeCircle.setOutlineColor(sf::Color(255, 255, 255, 30));
    rangeCircle.setOutlineThickness(1.f);
    rangeCircle.setOrigin({ mRange, mRange });
    rangeCircle.setPosition({ mX, mY });
    window.draw(rangeCircle);

    drawProjectiles(window);
}

void CannonTower::fire(Enemy* target)
{
    if (!target || !target->isAlive()) return;
    if (mProjectileCount >= MAX_PROJECTILES) return;

    mProjectiles[mProjectileCount++] = new Projectile(
        mX, mY, target->getX(), target->getY(),
        mDamage, 300.f, ProjectileType::Cannonball);
}

void ArcherTower::fire(Enemy* target)
{
    if (!target || !target->isAlive()) return;
    if (mProjectileCount >= MAX_PROJECTILES) return;

    mProjectiles[mProjectileCount++] = new Projectile(
        mX, mY, target->getX(), target->getY(),
        mDamage, 450.f, ProjectileType::Arrow);
}

void WizardTower::fire(Enemy* target)
{
    if (!target || !target->isAlive()) return;
    if (mProjectileCount >= MAX_PROJECTILES) return;

    mProjectiles[mProjectileCount++] = new Projectile(
        mX, mY, target->getX(), target->getY(),
        mDamage, 250.f, ProjectileType::Fireball);
}

void ElectricTower::fire(Enemy* target)
{
    if (!target || !target->isAlive()) return;
    if (mProjectileCount >= MAX_PROJECTILES) return;

    mProjectiles[mProjectileCount++] = new Projectile(
        mX, mY, target->getX(), target->getY(),
        mDamage, 400.f, ProjectileType::Electric);
}

void BowTower::fire(Enemy* target)
{
    if (!target || !target->isAlive()) return;
    if (mProjectileCount >= MAX_PROJECTILES) return;

    target->applySlow(0.5f);

    mProjectiles[mProjectileCount++] = new Projectile(
        mX, mY, target->getX(), target->getY(),
        10.f, 500.f, ProjectileType::SlowOrb);  // 350 speed of projectile 
    // 10 damage
}