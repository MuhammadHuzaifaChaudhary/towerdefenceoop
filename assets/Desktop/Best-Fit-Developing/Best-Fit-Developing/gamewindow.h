#include <iostream>
#include "GameBoard.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include "GameWindowElements.h"
#include <random>
#include "Animations.h"
#pragma once

using namespace std;
using namespace sf;

void UpdateScore(int &TotalScore, int &RowsDestroyed, int &TotalDestroyed, float &Level)
{
    int NewScore = 0;

    switch (RowsDestroyed)
    {
    case 1:
        NewScore = 40;
        break;
    case 2:
        NewScore = 100;
        break;
    case 3:
        NewScore = 300;
        break;
    case 4:
        NewScore = 1200;
        break;
    }
    TotalDestroyed += RowsDestroyed;
    RowsDestroyed = 0;

    TotalScore += NewScore * (static_cast<int>(Level) + 1); //----------SCORE isn't adding up right///////////
}

void mainGame(RenderWindow &window, int &currentState)
{
    int RowsDestroyed = 0;  // Rows destroyed in that turn
    int TotalScore;         // total Score
    int TotalDestroyed = 0; // Total Rows destroyed in the game session
    float Level = 1.0f;     // Game level
    int NextPieceId = rand() % 7;
    bool gameOver = 1; // Game Over
    bool Pause = 1;    // Game Pause

    //---------------grid values---------------
    const float Width = 400;  // grid height
    const float Height = 500; // grid height
    const int Columns = 10;
    const int Rows = 20;
    RectangleShape rectangle({Width, Height});
    rectangle.setFillColor({Color::White});
    rectangle.setPosition({0.f, 350.f});

    //------------Cell Values------------------
    const float CellWidth = 40.f;
    const float CellHeight = 40.f;
    const float startofgrid = 100.f; // start of grid
    RectangleShape grid(Vector2f{CellWidth, CellHeight});
    grid.setFillColor(Color::White);
    grid.setOutlineColor(Color::Black);
    grid.setOutlineThickness(1);

//------------FONT---------------------------
#ifdef _WIN32
    // Windows OS: Use a simple relative path assuming font is in the EXE directory,
    // or specify the assets folder structure typical for Windows/IDE builds.
    string ScoreFont = "C:\\assets\\PixelifySans.ttf";
#elif __linux__
    // Linux OS: Use the relative path common for Linux builds, or a system font path.
    string ScoreFont = "Best-Fit/assets/PixelifySans.ttf";
#endif

    Font myfont(ScoreFont);
    if (!myfont.openFromFile(ScoreFont))
    {
        std::cout << "ERROR: Could not load ARIAL.TTF" << std::endl;
    }
    //-------------------displayingFont---------------
    TotalScore = 0;

    sf::Text scoreText(myfont, "Score : 0", 25);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(sf::Vector2f{450.f, 160.f});

    //--------time and functions---------
    srand(time(0));
    Spawn(gameOver);
    Clock gameClock;
    float timeSinceLastFall = 0.0f;
    float Speed = 1.0f;
    const float Speed_Decrease = 0.2f;

    Clock AnimClock;


    Clock keyClock; // for keystroke delays
    const float keyDelay = 0.15f;
    RectangleShape Warning_Sign(Vector2f{100.f, 50.f});
    Warning_Sign.setPosition(Vector2f{0.f, 150.f});
    Warning_Sign.setFillColor(Color::White);
    Warning_Sign.setOutlineColor(Color::Red);
    Warning_Sign.setOutlineThickness(10.f);

    //----------------backGroundSetup--------------------
    #ifdef _WIN32
    // Windows OS: Use a simple relative path assuming font is in the EXE directory,
    // or specify the assets folder structure typical for Windows/IDE builds.
    Texture BackGroundTexture("C:\\assets\\BackGround1.jpg");
    #elif __linux__
    // Linux OS: Use the relative path common for Linux builds, or a system font path.
    Texture BackGroundTexture("Best-Fit/assets/BackGround1.jpg");
    #endif
    Sprite BackGroundSprite(BackGroundTexture);
    BackGroundSprite.setScale(Vector2f{0.7f, 0.75f});
    BackGroundSprite.setOrigin(Vector2f{1.5f, 1.f});

    while (window.isOpen()) // while window is open. when i used true, the window stayed open but the program didnt stop, it kept running.
    {

        while (optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
            {
                window.close();
                currentState = -1;
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::K))
            {
                if (keyClock.getElapsedTime().asSeconds() > keyDelay)
                {

                    Pause = !(Pause);
                }
            }
        }
        //---------------------Input Checking and Application------------------------------------------------
        if (gameOver && Pause)
        {
            if (Keyboard::isKeyPressed(Keyboard::Key::Up))
            {
                if (keyClock.getElapsedTime().asSeconds() > keyDelay)
                {
                    Rotate();
                    keyClock.restart(); // reset timer}
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Right))
            {
                if (canMove(xValue + 1, yValue, currentPiece))
                {
                    if (keyClock.getElapsedTime().asSeconds() > keyDelay)
                    {
                        xValue++;
                        keyClock.restart(); // reset timer
                    }
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Left))
            {
                if (canMove(xValue - 1, yValue, currentPiece))
                {
                    if (keyClock.getElapsedTime().asSeconds() > keyDelay)
                    {
                        xValue--;
                        keyClock.restart(); // reset timer
                    }
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Down))
            {
                if (canMove(xValue, yValue + 1, currentPiece))
                {
                    if (keyClock.getElapsedTime().asSeconds() > keyDelay - 0.1f)
                    {
                        yValue++;
                        keyClock.restart(); // reset timer
                    }
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Space))
            {
                if (keyClock.getElapsedTime().asSeconds() > keyDelay + 0.2f)
                {
                    while (canMove(xValue, yValue + 1, currentPiece))
                    {
                        yValue++;
                    }
                    keyClock.restart(); // reset timer
                }
            }
        }
        //---------------------------------------------------------------------------------------------------

        if (TotalDestroyed >= 10)
        {
            Level += 1;
            TotalDestroyed -= 10;
        }
        window.clear(Color::Red); // to set the color of the window
        window.draw(BackGroundSprite);
        window.draw(rectangle);

        //-----------------------Speed Check and update-------------------------
        float NewSpeed = 1.0f - ((Level - 1) * Speed_Decrease);

        Speed = (NewSpeed < 0.0f) ? 0.0f : NewSpeed;

        //----------------Setting the grid-----------------------
        for (int i = 0; i < Columns; i++)
        {
            for (int j = 0; j < Rows; j++)
            {
                grid.setPosition(Vector2f(i * CellWidth, startofgrid + j * CellHeight));
                window.draw(grid);
            }
        }
        //--------------------Updating the game---------------------
        updateandDrawGame(window, gameClock, timeSinceLastFall, Speed, startofgrid, RowsDestroyed, gameOver, nextPieceID); // located in GameBoard.h
        UpdateScore(TotalScore, RowsDestroyed, TotalDestroyed, Level);

        //---------------Score update-------------------
        stringstream ss;
        ss << "Score: " << TotalScore;
        scoreText.setString(ss.str());

        //----------------Score Display-------------------
        Scoreboard(window); // GameWindowElements.h
        window.draw(scoreText);
        Leaderboard(window);
        nextBlock(window);
        BlockDisplay(window, nextPieceID);
        float const delta_time = AnimClock.restart().asSeconds();

        RunAnim(window,AnimClock,delta_time);

        //---------------------Drawing the GameOver Sign------------------------------
        if (!gameOver)
        {
            currentState = 0;
            break;
        }

        window.display(); // to display all
    }
}
