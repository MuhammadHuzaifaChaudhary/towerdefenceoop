#include "Projectile.h"
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

Projectile::Projectile(float startX, float startY,
    float targetX, float targetY,
    float damage, float speed,
    ProjectileType type)
    : mX(startX)
    , mY(startY)
    , mTargetX(targetX)
    , mTargetY(targetY)
    , mDamage(damage)
    , mSpeed(speed)
    , mAlive(true)
    , mHit(false)
    , mHitApplied(false)
    , mType(type)
    , mExplosionTimer(0.f)
    , mExploding(false)
{
    // calculate direction toward target
    float dx = targetX - startX;
    float dy = targetY - startY;
    float dist = std::sqrt(dx * dx + dy * dy);

    if (dist > 0.f)
    {
        mVx = (dx / dist) * mSpeed;
        mVy = (dy / dist) * mSpeed;
    }
}

void Projectile::update(float dt)
{
    if (!mAlive) return;

    if (mExploding)
    {
        // explosion lasts 0.3 seconds then disappears
        mExplosionTimer += dt;
        if (mExplosionTimer > 0.3f)
            mAlive = false;
        return;
    }

    // move toward target
    mX += mVx * dt;
    mY += mVy * dt;

    // check if reached target
    float dx = mTargetX - mX;
    float dy = mTargetY - mY;
    float dist = std::sqrt(dx * dx + dy * dy);

    if (dist < 7.f)
    {
        mHit = true;
        mExploding = true;  // trigger explosion
        mExplosionTimer = 0.f;
    }
}

void Projectile::draw(sf::RenderWindow& window)
{
    if (!mAlive) return;

    if (mExploding)
    {
        // draw explosion circle expanding
        float radius = 10.f + mExplosionTimer * 60.f;
        sf::CircleShape exp(radius);
        exp.setOrigin({ radius, radius });
        exp.setPosition({ mX, mY });

        if (mType == ProjectileType::Cannonball)
            exp.setFillColor(sf::Color(200, 100, 0, 150));
        else if (mType == ProjectileType::Fireball)
            exp.setFillColor(sf::Color(255, 80, 0, 150));
        else if (mType == ProjectileType::Electric)
            exp.setFillColor(sf::Color(100, 150, 255, 150));
        else
            exp.setFillColor(sf::Color(200, 200, 255, 150));

        window.draw(exp);
        return;
    }

    // draw projectile based on type
    if (mType == ProjectileType::Cannonball)
    {
        // dark gray circle
        sf::CircleShape ball(6.f);
        ball.setOrigin({ 6.f, 6.f });
        ball.setFillColor(sf::Color(60, 60, 60));
        ball.setOutlineColor(sf::Color(30, 30, 30));
        ball.setOutlineThickness(1.f);
        ball.setPosition({ mX, mY });
        window.draw(ball);
    }
    else if (mType == ProjectileType::Arrow)
    {
        // thin fast line
        sf::RectangleShape arrow({ 20.f, 3.f });
        arrow.setOrigin({ 10.f, 1.5f });
        arrow.setFillColor(sf::Color(180, 140, 60));
        arrow.setPosition({ mX, mY });
        float angle = std::atan2(mVy, mVx) * 180.f / 3.14159f;
        arrow.setRotation(sf::degrees(angle));
        window.draw(arrow);
    }
    else if (mType == ProjectileType::Fireball)
    {
        // orange glowing circle
        sf::CircleShape outer(10.f);
        outer.setOrigin({ 10.f, 10.f });
        outer.setFillColor(sf::Color(255, 100, 0, 150));
        outer.setPosition({ mX, mY });
        window.draw(outer);

        sf::CircleShape inner(5.f);
        inner.setOrigin({ 5.f, 5.f });
        inner.setFillColor(sf::Color(255, 220, 0));
        inner.setPosition({ mX, mY });
        window.draw(inner);
    }
    else if (mType == ProjectileType::Electric)
    {
        // blue circle
        sf::CircleShape bolt(7.f);
        bolt.setOrigin({ 7.f, 7.f });
        bolt.setFillColor(sf::Color(50, 150, 255));
        bolt.setOutlineColor(sf::Color(200, 230, 255));
        bolt.setOutlineThickness(2.f);
        bolt.setPosition({ mX, mY });
        window.draw(bolt);
    }
    else if (mType == ProjectileType::SlowOrb)
    {
        //// purple orb
        //sf::CircleShape orb(7.f);
        //orb.setOrigin({ 7.f, 7.f });
        //orb.setFillColor(sf::Color(180, 50, 220, 200));
        //orb.setOutlineColor(sf::Color(220, 150, 255));
        //orb.setOutlineThickness(1.f);
        //orb.setPosition({ mX, mY });
        //window.draw(orb);



        //secodn effect 

        //sf::VertexArray lightning(sf::PrimitiveType::LineStrip, 5);

        //// Start point (projectile position)
        //lightning[0].position = sf::Vector2f(mX, mY);
        //lightning[0].color = sf::Color(100, 200, 255);

        //// Zig-zag points (random jagged)
        //lightning[1].position = sf::Vector2f(mX + 8.f, mY - 12.f);
        //lightning[1].color = sf::Color(150, 220, 255);

        //lightning[2].position = sf::Vector2f(mX + 15.f, mY + 5.f);
        //lightning[2].color = sf::Color(80, 180, 255);

        //lightning[3].position = sf::Vector2f(mX + 22.f, mY - 8.f);
        //lightning[3].color = sf::Color(200, 230, 255);

        //lightning[4].position = sf::Vector2f(mX + 28.f, mY + 2.f);
        //lightning[4].color = sf::Color(50, 150, 255);

        //window.draw(lightning);


        // third effect 
         // thin fast line
        sf::RectangleShape arr({ 40.f, 3.f });
        arr.setOrigin({ 10.f, 1.5f });
        arr.setFillColor(sf::Color(255, 100, 0, 150));
        arr.setPosition({ mX, mY });
        float angle = std::atan2(mVy, mVx) * 180.f / 3.14159f;
        arr.setRotation(sf::degrees(angle));
        window.draw(arr);

    }
}