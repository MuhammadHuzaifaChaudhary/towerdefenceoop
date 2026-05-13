#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include "ExitPrompt.h"

using namespace sf;
using namespace std;
// Constants for button sizing
const float BUTTON_WIDTH = 200.0f;
const float BUTTON_HEIGHT = 50.0f;
const float BUTTON_SPACING = 30.0f;
bool ExitAttempt = 0;

// Function to draw and handle the Menu State
void MainMenu(sf::RenderWindow &window, int &currentState)
{
    // Calculate button positions
    float centerX = window.getSize().x / 2.0f;
    float centerY = window.getSize().y / 2.0f;

    // Position for the top button (PLAY)
    float playY = centerY - (BUTTON_HEIGHT / 2.0f) - (BUTTON_SPACING / 2.0f);

    // Position for the bottom button (SETTINGS)
    float settingsY = centerY + (BUTTON_HEIGHT / 2.0f) + (BUTTON_SPACING / 2.0f);

    float exitY = (2 * centerY) + (BUTTON_HEIGHT / 2.0f) + (BUTTON_SPACING / 2.0f);

    // --- Setup Button Shapes (Uses sf::Vector2f for 3.0.2 compatibility) ---

    // Play Button (Top)
    sf::RectangleShape playButton({BUTTON_WIDTH, BUTTON_HEIGHT});
    playButton.setOrigin(Vector2f(BUTTON_WIDTH / 2.0f, BUTTON_HEIGHT / 2.0f));
    playButton.setPosition(Vector2f({centerX, playY}));
    playButton.setFillColor(sf::Color(0, 150, 0)); // Dark Green

    // Settings Button (Bottom)
    sf::RectangleShape settingsButton({BUTTON_WIDTH, BUTTON_HEIGHT});
    settingsButton.setOrigin(Vector2f(BUTTON_WIDTH / 2.0f, BUTTON_HEIGHT / 2.0f));
    settingsButton.setPosition(Vector2f({centerX, settingsY}));
    settingsButton.setFillColor(sf::Color(50, 50, 50)); // Dark Gray

    sf::RectangleShape exitButton({BUTTON_WIDTH, BUTTON_HEIGHT});
    exitButton.setOrigin(Vector2f(BUTTON_WIDTH / 2.0f, BUTTON_HEIGHT / 2.0f));
    exitButton.setPosition(Vector2f({centerX, settingsY + 50}));
    exitButton.setFillColor(sf::Color(110, 110, 80));

    // --- Event Loop (Uses std::optional for SFML 3.0.2) ---

    while (window.isOpen() && currentState == 0)
    {
        while (std::optional event = window.pollEvent())
        {

            if (event->is<Event::Closed>())
            {
                currentState = -1;
                window.close();
            }

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
                    
                    if (!ExitAttempt)
                    {
                        // Check Play Button Click
                        if (playButton.getGlobalBounds().contains(mousePos))
                        {
                            std::cout << "Starting Game (Switch to PLAYING state)..." << std::endl;
                            currentState = 1; // Change state to PLAYING
                            break;
                        }

                        // ... (rest of logic remains the same) ...
                        // Check Settings Button Click
                        else if (settingsButton.getGlobalBounds().contains(mousePos))
                        {
                            std::cout << "Opening Settings (Stay in MENU state)..." << std::endl;
                            currentState = 2;
                        }

                        else if (exitButton.getGlobalBounds().contains(mousePos))
                        {
                            cout << "Fetching Exit Prompt" << endl;
                            ExitAttempt = 1;
                        }
                    }
                }
            }
        }

        // ... (Drawing remains the same) ...

        // --- Drawing ---
        window.clear(sf::Color(20, 20, 40)); // Dark background
        window.draw(playButton);
        window.draw(settingsButton);
        window.draw(exitButton);
        if (ExitAttempt)
        {
            exitPrompt(window,ExitAttempt,currentState);
        }
        window.display();
    }
}
