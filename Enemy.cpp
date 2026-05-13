#include "Enemy.h"
#include <cmath>   // for sqrt, used in distance calculation
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf; 

// ---- Enemy base class ----

Enemy::Enemy(float x, float y, float speed, float maxHp)

    : Entity(x, y)         // Call Entity's constructor FIRST, passing x and y...... // This sets up mX, mY, mAlive — which Enemy inherits from Entity.
    // A child MUST call its parent's constructor in the initializer list.
    , mSpeed(speed)
    , mHp(maxHp) // Start HP at max (full health at the beginning).
    , mMaxHp(maxHp) // Store the max HP separately so we can calculate HP bar ratio later.
    , mBaseSpeed(speed)   // Store original speed separately — needed to restore speed after slow.
    , mEscaped(false) // Enemy has not escaped yet — starts as false.
    , mCurrentWaypoint(1)   // start heading to waypoint 1 (already at 0)
    , mSprite(mTexture)     // attach texture to sprite
                           // NOTE: texture is empty right now  loadTexture() fills it later.
    , mSlowTimer(0.f)   
{
    // Constructor body is empty — all setup done in initializer list above.
}

void Enemy::loadTexture(const std::string& filename)    // is tarah bhi load ho sakta hay .. dossra tareeka wohi 
                                                          //texture ka object create kar kay 
                                                        //sprite load karain har aik kay liye alaidha alaidha 
{
    if (!mTexture.loadFromFile(filename))
    {
        // fallback: red square if image not found
        sf::Image img({ 32u, 32u }, sf::Color(200, 50, 50));
        mTexture.loadFromImage(img);
    }
    mSprite = Sprite(mTexture);

    // center the sprite origin so it sits on tile correctly
    auto size = mTexture.getSize();
    // auto = Compiler khud type deduce(pata lagata) hai ki variable kis type ka hai.
    mSprite.setOrigin({ size.x / 2.f, size.y / 2.f });

    // scale sprite to fit nicely on tile
    mSprite.setScale({ 0.05f, 0.05f });
}

void Enemy::update(float dt)
// dt is delta time .. means do frames kay darmayan kay time ka difference 
// suppose frmae one is at 0.1 sec and frame 2 is at 0.2 sec to dt kya ho ga 0.1 
// jitnay frame ziada utna dt kam ... ab agr dt ka use na kartay to jin kay frames ziada honay thay uder enemeis fast move karnay tahy 
// is liye dt ka use kartay ku kay us se product same ata .. like distance=speed x time ... jis ki speed ziada us ka dt yani time kam 
{
    if (!mAlive || mEscaped) 
        return;   // skip if dead or escaped
   
    if (mSlowTimer > 0.f)
    {
        mSlowTimer -= dt;
        //Agar enemy slow hai (BowTower ne slow kiya hai) 
        // to timer kam karo. Jab timer zero ho jaye to speed wapas normal karo.
        if (mSlowTimer <= 0.f)
            mSpeed = mBaseSpeed;  // normal speed wapas
    }

    if (mCurrentWaypoint >= NUM_WAYPOINTS)
    {
        // reached final waypoint = escaped
        mEscaped = true; 
        // Mark as escaped — Game will deduct a life
        mAlive = false;
        // Mark as not alive — Game will remove this enemy
        // Enemy ko remove kar do.
        return;
    }

    // get target waypoint position
    // waypoints aik array hay jis may differentr coordinates hain ..
    // or currentwaypoints just particular index batata hay .. 
    // just like int arr[5]={1,2,3,4,5}
    // arr[0]=1 yahan 0 current waypoint hay or 1 element ahy .. agr elemets aisay hotay {1,2},{3,4} is tarah 
    // to 1=x hona tha or 2=y or yehi target x or target y may store karwaya hay 
    // // lakin hum nay current ko 1 se start kiay is liye target 108 92 ata hay or mx my 108 36 tha 
    // yani har index par particular position ho gi ...
    // or us position ko target x or y may store kar liya right ...

    float targetX = WAYPOINTS[mCurrentWaypoint].x;
    float targetY = WAYPOINTS[mCurrentWaypoint].y;

    // calculate direction vector toward target
    float dx = targetX - mX;
    float dy = targetY - mY;

    // calculate distance to target
    float dist = std::sqrt(dx * dx + dy * dy);

    // mx or my entity class my thay or wahan se intialize huwe ... 
    // ye wohi jo previous ya current position hay like 108 and my =36
    // taget x or target y next position batata hay 
    if (dist < 5.f)
    {
        // close enough to waypoint - snap to it and move to next
        mX = targetX;
        mY = targetY;
        mCurrentWaypoint++;
    }
    else   // agr target tak nhi pohancha hay .. usay move karwatay rao 
    {
        // normalize direction and move toward waypoint
        mX += (dx / dist) * mSpeed * dt;
        mY += (dy / dist) * mSpeed * dt;
    }
}

void Enemy::draw(sf::RenderWindow& window)
{
    if (!mAlive) return;   // dont draw dead enemies

    // draw enemy sprite at current position
    mSprite.setPosition({ mX, mY });
    window.draw(mSprite);

    // draw HP bar above enemy
    drawHpBar(window);
}

void Enemy::takeDamage(float amount)
{
    mHp -= amount;              // reduce HP
    // Subtract damage from current HP.
    if (mHp <= 0.f)
    {
        mHp = 0.f;
        // Clamp HP at 0 (no negative HP display).

        mAlive = false;         
        // Mark enemy as dead — will be removed and gold awarded.

    }
}

void Enemy::drawHpBar(sf::RenderWindow& window)
{
    float barWidth = 40.f;     // total width of HP bar
    float barHeight = 6.f;      // height of HP bar
    float barX = mX - barWidth / 2.f;   // center above enemy
    float barY = mY - 30.f;             // above enemy sprite

    // dark background bar
    sf::RectangleShape bg;
    bg.setSize({ barWidth, barHeight });
    bg.setFillColor(sf::Color(60, 60, 60));
    bg.setPosition({ barX, barY });
    window.draw(bg);

    // green fill bar based on current HP ratio
    float ratio = mHp / mMaxHp;              // 0.0 to 1.0
    // max hp =10... current hp = 10 ...10/10=1 means green 

    sf::RectangleShape fill;
    fill.setSize({ barWidth * ratio, barHeight });

    // color changes red when low HP
    if (ratio > 0.5f)
        fill.setFillColor(sf::Color(50, 200, 50));    // green
    else if (ratio > 0.25f)
        fill.setFillColor(sf::Color(220, 180, 0));    // yellow
    else
        fill.setFillColor(sf::Color(220, 50, 50));    // red

    fill.setPosition({ barX, barY });
    window.draw(fill);
}

// ---- FlyingEnemy ----

FlyingEnemy::FlyingEnemy(float x, float y)
    : Enemy(x, y, 120.f, 80.f)    // medium speed, low-medium HP
    , mTargetX(WAYPOINTS[NUM_WAYPOINTS - 1].x)   // flies straight to exit
    // yani is kay liye target hay hi end place hay .. ayni mx jab tak target tak nhi jay ga
    // tab tak nhi position chnage karay ga ... 
    // yani direct end tak jay ga 
    , mTargetY(WAYPOINTS[NUM_WAYPOINTS - 1].y)
{
    loadTexture("assets/baloon.png");
    mSprite.setScale({ 0.08f, 0.08f });
}

void FlyingEnemy::update(float dt)
{
    if (!mAlive || mEscaped)
        return;

    // fly straight toward exit point, ignoring waypoints
    float dx = mTargetX - mX;
    float dy = mTargetY - mY;
    float dist = std::sqrt(dx * dx + dy * dy);

    if (dist < 5.f)
    {
        mEscaped = true;
        mAlive = false;
        return;
    }

    // move straight toward exit
    mX += (dx / dist) * mSpeed * dt;
    mY += (dy / dist) * mSpeed * dt;
}

// ---- BombEnemy ----

void BombEnemy::takeDamage(float amount)
{
    mHp -= amount;
    if (mHp <= 0.f)
    {
        mHp = 0.f;
        mAlive = false;
        mExploded = true;   // trigger explosion flag
        // explosion damage handled in Game.cpp later
    }
}

//---heal enemy 

void HealEnemy::update(float dt, Enemy** enemies, int count)
{
    // pehle normal movement
    Enemy::update(dt);

    if (!mAlive || mEscaped) return;

    // heal timer
    mHealTimer += dt;
    if (mHealTimer >= 3.f)
    { // When 3 seconds have passed, trigger a heal.

        mHealTimer = 0.f;
        // Reset timer back to 0 to count another 3 seconds.

        // nearby enemies ko heal karo
        for (int i = 0; i < count; i++)
        {   // Loop through all enemies in the game

            if (enemies[i] == nullptr) 
                continue;   // Skip null/empty slots in the array.

            if (!enemies[i]->isAlive()) 
                continue; // Skip dead enemies.
            if (enemies[i] == this) 
                continue;  // khud ko nahi

            float dx = enemies[i]->getX() - mX;
            // Horizontal distance to the other enemy.
            float dy = enemies[i]->getY() - mY;
            // Vertical distance to the other enemy.
            float dist = std::sqrt(dx * dx + dy * dy);
            // Straight-line distance.

            if (dist <= mHealRadius)
                // If within healing range:
                enemies[i]->heal(mHealAmount);  // heal function
        }
    }
}