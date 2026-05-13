#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf; 

class Entity   // its parent class 
{
public:
    Entity(float x, float y)  // tking two positions x and y .....
         : mX(x), mY(y), mAlive(true)
    {
        // cosntructor called automatically when the object of child class will be created 
    }

    virtual ~Entity()   
    {
    // This is the DESTRUCTOR  called automatically when an object is destroyed.
    // why we have used vitual ???? 
    // Without virtual, if we delete a child class through a base pointer,
    // only the base destructor runs memory leak!
    // With virtual, the correct child destructor always runs first.

    }

    
    virtual void draw(RenderWindow& window) = 0;  // ye aik pure virtual function hay 

    // "virtual" = this function CAN be overridden by child classes.
    // "= 0" = this is a PURE VIRTUAL function.....
     // "RenderWindow& window" = reference to the game window to draw on.....
    //  "&" means reference ,,, means we pass the actual window, not a copy of it .... 


    float getX()const 
    { 
        return mX; 
    }
    float getY()const  // it returns the y position of this entity 
    { 
        return mY; 
    }
    bool  isAlive()const 
    {
        return mAlive;    // it is a GETTER function ....returns true if the entity is alive, false if dead.

    }

protected:
    float mX, mY;
    bool  mAlive;
};


// imporatnt thing about virtual abstract class 
 //         It has NO implementation here , every child class MUST write its own.
    //         Because of this "= 0", Entity becomes an ABSTRACT CLASS 
    //         you cannot create "Entity e;" directly. You can only create
    //         objects of concrete children like BasicEnemy or CannonTower.
