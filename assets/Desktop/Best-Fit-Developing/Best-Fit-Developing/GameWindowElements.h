#include "SFML/Graphics.hpp"

#pragma once

using namespace sf;

const float Endofgrid = 400.f;

void Leaderboard(RenderWindow &window)
{
    //-------Leaderboard---------------------
    RectangleShape Leaderboard(Vector2f{150.f, 200.f});
    Leaderboard.setPosition(Vector2f{Endofgrid + 20.f, 300.f});
    Leaderboard.setFillColor(Color::Black);
    Leaderboard.setOutlineThickness(10);
    Leaderboard.setOutlineColor(Color::White);
    window.draw(Leaderboard);
}

void Scoreboard(RenderWindow &window)
{
    //--------Score board---------------
    RectangleShape scoreBoard(Vector2f{150.f, 80.f});
    scoreBoard.setPosition(Vector2f{Endofgrid + 20.f, 120.f});
    scoreBoard.setFillColor(Color::White);
    scoreBoard.setOutlineColor(Color::Black);
    scoreBoard.setOutlineThickness(3.f);

    window.draw(scoreBoard);
}

void nextBlock(RenderWindow &window)
{

    RectangleShape NextblockContainer(Vector2f{150.f, 150.f});
    NextblockContainer.setPosition(Vector2f{Endofgrid + 20.f, 550.f});
    NextblockContainer.setFillColor(Color::White);
    NextblockContainer.setOutlineColor(Color::Green);
    NextblockContainer.setOutlineThickness(3.f);

    window.draw(NextblockContainer);
}


