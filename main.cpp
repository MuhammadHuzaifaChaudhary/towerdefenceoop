#include <SFML/Graphics.hpp>    // include sfml libraray 
#include"Game.h";   // include our class game 
int main()
{
	Game game;   // it creates one game object ( and constructor will be called automatically)
	game.run(); // it starts the game loop ( it runs untill the window is closed )
	return 0;
}


// .h files are just for declaration 
// .cpp contains actual code and definition 
// pragma once 
//Agar Enemy.h ko Game.h bhi include kare aur Tower.h bhi include kare,
// aur phir dono ko main.cpp include kare toh Enemy.h 2 baar include ho jaati.
// #pragma once is masle ko rokta hai


