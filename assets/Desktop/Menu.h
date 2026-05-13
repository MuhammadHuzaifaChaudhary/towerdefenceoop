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
void MainMenu(RenderWindow &window, int &currentState)
{
    // Calculate button positions
    float centerX = window.getSize().x/2.0f ;
    float centerY = window.getSize().y/2.0f;

    // Position for the top button (PLAY)
    float playY = centerY - (BUTTON_HEIGHT / 2.0f) - (BUTTON_SPACING / 2.0f);

    // Position for the bottom button (SETTINGS)
    float settingsY = centerY + (BUTTON_HEIGHT / 2.0f) + (BUTTON_SPACING / 2.0f);

    float exitY = (2 * centerY) + (BUTTON_HEIGHT / 2.0f) + (BUTTON_SPACING / 2.0f);

    // --- Setup Button Shapes (Uses sf::Vector2f for 3.0.2 compatibility) ---

    // Play Button (Top)
    sf::RectangleShape playButton({BUTTON_WIDTH+5, BUTTON_HEIGHT+20});
    playButton.setOrigin(Vector2f(BUTTON_WIDTH / 2.0f, BUTTON_HEIGHT / 2.0f));
    playButton.setPosition(Vector2f({centerX, playY-30}));
    playButton.setFillColor(Color::Transparent); 

    // Settings Button (Bottom)
    RectangleShape settingsButton({BUTTON_WIDTH+5, BUTTON_HEIGHT+5});
    settingsButton.setOrigin(Vector2f(BUTTON_WIDTH / 2.0f, BUTTON_HEIGHT / 2.0f));
    settingsButton.setPosition(Vector2f({centerX, settingsY}));
    settingsButton.setFillColor(Color::Transparent);

    RectangleShape exitButton({BUTTON_WIDTH+5, BUTTON_HEIGHT+5});
    exitButton.setOrigin(Vector2f(BUTTON_WIDTH / 2.0f, BUTTON_HEIGHT / 2.0f));
    exitButton.setPosition(Vector2f({centerX, settingsY +100}));
    exitButton.setFillColor(Color::Transparent);

    Texture texture("C:/assets/block.JPEG");
   Sprite sprite(texture);
   sprite.scale({ 1.2f,1.2f });
   Font font("C:/assets/Pixel Game.otf");
   //---------------------------Play button sprite------------------------
   Texture play("C:/assets/play txt.PNG");
   Sprite playsprite(play);
   playsprite.scale({ 0.7f, 0.72f });
   playsprite.setPosition({ 190.f,373.f });
   //-------------------------------Settings Sprite--------------------
   Texture setting("C:/assets/play txt.PNG");
   Sprite settingsprite(play);
   settingsprite.scale({ 0.7f, 0.72f });
   settingsprite.setPosition({ 190.f,473.f });
   //------------------------------------Exit Sprite------------------------------
   Texture exit("C:/assets/exit txt.PNG");
   Sprite exitsprite(exit);
   exitsprite.scale({ 0.66f, 0.7f });
   exitsprite.setPosition({ 195.f,575.f });
    Text text1(font, "BEST FIT",120);
    text1.setPosition({ 150.f,100.f });
    text1.setFillColor({ 255,255,0 });

    // --- Event Loop (Uses std::optional for SFML 3.0.2) ---

    while (window.isOpen() && currentState == 0)
    {   
        //Chceking Mouse position and doing Hover effect -------------------------------------------
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        //----------------------- Set hover colors based on mouse position-------------------------------
        if (playButton.getGlobalBounds().contains(mousePos)) 
        {
            playsprite.setColor(Color(225, 182, 42));
        }
        else
            playsprite.setColor(Color::Yellow);
        if (settingsButton.getGlobalBounds().contains(mousePos))
        {
            settingsprite.setColor(Color(225, 182, 42));
        }
        else
            settingsprite.setColor(Color::Yellow);
        if (exitButton.getGlobalBounds().contains(mousePos)) 
        {
            exitsprite.setColor(Color(225, 182, 42));
        }
            else
            exitsprite.setColor(Color::Yellow);
        while (std::optional event = window.pollEvent())
        {

            if (event->is<Event::Closed>())
            {
                currentState = -1;
                window.close();
            }

            if (event->is<sf::Event::MouseButtonPressed>())   // it will tell button is pressed 
            {
                auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();   // get if is used to tell which specif button is pressed 
                 // its just like opening the mail and see whats inside it .. similarly it will tell the computer which key has been pressed by user 

                // Ensure the event pointer is valid and button is Left
                if (mouseEvent ->button == sf::Mouse::Button::Left)
                {
                    // CRITICAL FIX: Get mouse position from the nested 'position' member
                    sf::Vector2i pixelPos = mouseEvent->position;

                    // Convert pixel position to world coordinates
                    sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
                    // we can also directly use mouseEvent->position instead of pixelPos its just acting like variable 
                    // first we get pixel coordinates than we have to  move in world coordinates that are actual coordinates 
                    // thats why this is used mapPixeltocoords 
                    if (!ExitAttempt)
                    {
                        // Check Play Button Click
                        if (playButton.getGlobalBounds().contains(mousePos))
                        {
                            cout << "Starting Game (Switch to PLAYING state)..." << std::endl;
                            currentState = 1; // Change state to PLAYING
                            break;
                        }

                        // ... (rest of logic remains the same) ...
                        // Check Settings Button Click
                        else if (settingsButton.getGlobalBounds().contains(mousePos))
                            // get golbal bounds will give the boundary of the rectangle .contains will tell either our mouse position is inside the 
                            // bounds of the shape ?? 
                        {
                            std::cout << "Opening Settings (Stay in MENU state)..." <<endl;
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
        window.draw(sprite);
        window.draw(playButton);
        window.draw(playsprite);
        window.draw(settingsButton);
        window.draw(settingsprite);
        window.draw(exitButton);
        window.draw(exitsprite);
        window.draw(text1);
       
        if (ExitAttempt)
        {
            exitPrompt(window,ExitAttempt,currentState);
        }
        window.display();
    }
}
