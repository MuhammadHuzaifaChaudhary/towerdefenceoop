#include <SFML/Graphics.hpp>
#include <string>

#pragma once

using namespace std;
using namespace sf;

#ifdef _WIN32
// Windows OS: Use a simple relative path assuming font is in the EXE directory,
// or specify the assets folder structure typical for Windows/IDE builds.
string myfont = "C:\\assets\\Arial.ttf";
#elif __linux__
// Linux OS: Use the relative path common for Linux builds, or a system font path.
string Myfont = "Best-Fit/assets/Arial.ttf";
#endif
Font myfont(Myfont);

void exitPrompt(RenderWindow &window, bool &ExitState, int &currentState)
{
    RectangleShape backGround(Vector2f{400.f, 200.f});
    backGround.setFillColor(Color(59, 25, 19));
    backGround.setPosition(Vector2f{100.f, 375.f});

    Text Question(myfont, "Are you sure you want to exit?", 25.f);
    Question.setPosition(Vector2f{130.f, 400.f});

    RectangleShape OptionY(Vector2f{100.f, 50.f});
    OptionY.setOrigin(Vector2f{100.f / 2, 50.f / 2});
    OptionY.setFillColor(Color::Green);
    OptionY.setPosition(Vector2f{150.f, 500.f});

    RectangleShape OptionX(Vector2f{100.f, 50.f});
    OptionX.setOrigin(Vector2f{100.f / 2, 50.f / 2});
    OptionX.setFillColor(Color::Red);
    OptionX.setPosition(Vector2f{340.f, 500.f});
    while(window.isOpen() && ((ExitState == 1) && (currentState != -1)))
    {
        
        while (std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();

                // Ensure the event pointer is valid and button is Left
                if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left)
                {
                    // CRITICAL FIX: Get mouse position from the nested 'position' member
                    sf::Vector2i pixelPos = mouseEvent->position;

                    // Convert pixel position to world coordinates
                    sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

                    if (OptionY.getGlobalBounds().contains(mousePos))
                    {
                        std::cout << "Exiting" << std::endl;
                        currentState = -1; // Change state to PLAYING
                        ExitState = 0;
                        break;
                    }
                    else if (OptionX.getGlobalBounds().contains(mousePos))
                    {
                        cout << "No Exit" << endl;
                        ExitState = 0;
                        currentState = 0;
                        break;
                    }
                }
            }
        }
        
        window.draw(backGround);
        window.draw(Question);
        window.draw(OptionY);
        window.draw(OptionX);
        window.display();
    }
}
