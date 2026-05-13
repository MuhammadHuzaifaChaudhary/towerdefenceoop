#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <string>

#pragma once

using namespace sf;
using namespace std;
const int win_height = 950;
const int win_width = 600;
const int centre_x = win_width / 2;
const int centre_y = win_height / 2;

void settings(RenderWindow &window, int &currentState) {

    //-------------Main settings window--------------------
    RectangleShape settings({ win_width,win_height });
    settings.setFillColor(Color(45, 100, 220));
    settings.setOutlineThickness(3.f);
    settings.setOutlineColor(Color(4, 43, 125));

    #ifdef _WIN32
    // Windows OS: Use a simple relative path assuming font is in the EXE directory,
    // or specify the assets folder structure typical for Windows/IDE builds.
    string myfont = "C:\\assets\\Arial.ttf";
    #elif __linux__
    // Linux OS: Use the relative path common for Linux builds, or a system font path.
    string myfont = "Best-Fit/assets/Arial.ttf";
    #endif

    Font myFont(myfont);

    string userInput;

    //------------string to display input----------
    Text displayText(myFont, "", 20);
    displayText.setFillColor(Color::White);
    displayText.setPosition(Vector2f{ 250.f, 600.f });

    //--------------board for name change----------
    RectangleShape nameBoard({ 100.f,30.f });
    nameBoard.setPosition(Vector2f{ 260.f, 550.f });
    nameBoard.setFillColor(Color{ Color::Yellow });
    nameBoard.setOutlineThickness(2.f);
    nameBoard.setOutlineColor(Color::White);

    //---------------name board name header whatever----------
    Text nameText(myFont, "Username", 20);
    nameText.setFillColor(Color::Black);
    nameText.setPosition(Vector2f{ 260.f, 550.f });


    //-------------- box for the field--------------
    RectangleShape textfieldBox({ 180.f, 50.f });
    textfieldBox.setPosition(Vector2f{ 220.f, 600.f });
    textfieldBox.setFillColor(Color(50, 50, 50));
    textfieldBox.setOutlineThickness(2.f);
    textfieldBox.setOutlineColor(Color(4, 43, 125));

    sf::Clock cursorClock;

  
    bool cursorVisible = true;

    //--------------cursor------------------------------
    RectangleShape cursor;
    cursor.setSize(Vector2f{ 2.f, static_cast<float>(displayText.getCharacterSize() )});
    cursor.setFillColor(Color::White);

    //-------------The board for the back button------------
    RectangleShape backBoard({ 40.f, 40.f });
    backBoard.setPosition(Vector2f{ 30.f, 100.f });
    backBoard.setFillColor(Color(Color::Yellow));
    backBoard.setOutlineThickness(3.f);
    backBoard.setOutlineColor(Color(4, 43, 125));

    //-------------The back button text------------------
    Text backText(myFont, "Back", 14.f);
    backText.setFillColor(Color(Color::Black));
    backText.setPosition(Vector2f{ 32.f,110.f });

    //-------------the board for the text "volume"----------
    RectangleShape Volumeboard({ 60.f,30.f });
    Volumeboard.setPosition(Vector2f{ centre_x-60/2.f, 150.f});
    Volumeboard.setFillColor(Color(Color::Yellow));
    Volumeboard.setOutlineThickness(3.f);
    Volumeboard.setOutlineColor(Color(Color::Yellow));

    //-------------the text "volume"----------
    Text Volumetext(myFont, "Volume", 17.f);
    Volumetext.setFillColor(Color(Color::Black));
    Volumetext.setPosition(Vector2f{ 272.f,154.f });

    //--------------the box storing current volume value------
    RectangleShape Volume({ 30.f, 30.f });
    Volume.setPosition(Vector2f{ 285.f,200.f });
    Volume.setOutlineThickness(3.f);
    Volume.setOutlineColor(Color(Color::White));

    //---------------the box storing - volume sign-------
    RectangleShape subVolume({ 30.f,30.f });
    subVolume.setPosition(Vector2f{ 235.f,200.f });
    subVolume.setOutlineThickness(3.f);
    subVolume.setOutlineColor(Color(235, 192, 52));

    //---------------the box storing mute-------
    RectangleShape mute({ 30.f,30.f });
    mute.setPosition(Vector2f{ 185.f,200.f });
    mute.setOutlineThickness(3.f);
    mute.setOutlineColor(Color(235, 192, 52));

    //---------------the box storing + volume sign-------
    RectangleShape addVolume({ 30.f,30.f });
    addVolume.setPosition(Vector2f{ 335.f,200.f });
    addVolume.setOutlineThickness(3.f);
    addVolume.setOutlineColor(Color(235, 192, 52));
    
    //--------------the  - sign------------
    Text minusVolume(myFont, "-", 40.f);
    minusVolume.setFillColor(Color(Color::Black));
    minusVolume.setPosition(Vector2f{ 243.f,188.f });

    int volumeLevel = 100;//the default volume

    //-------------the mute symbol----------
    Text muteText(myFont, "M", 17.f);
    muteText.setFillColor(Color(Color::Black));
    muteText.setPosition(Vector2f{ 193.f,204.f });
    
    //--------------the + sign---------------
    Text plusVolume(myFont, "+", 40.f);
    plusVolume.setFillColor(Color(Color::Black));
    plusVolume.setPosition(Vector2f{ 339.f,189.f });

    //--------------the backgroundbox--------
    RectangleShape bgBoard({ 100.f,30.f });
    bgBoard.setPosition(Vector2f{ 250.f, 280.f });
    bgBoard.setFillColor(Color(Color::Yellow));
    bgBoard.setOutlineThickness(3.f);
    bgBoard.setOutlineColor(Color(Color::Yellow));


    //--------------the backgroud text-------
    Text bgText(myFont, "Background", 19.f);
    bgText.setFillColor(Color(Color::Black));
    bgText.setPosition(Vector2f{ 250.f,280.f });

    //--------------Background #1___________
    RectangleShape bg1({ 100.f,100.f });
    bg1.setPosition(Vector2f{ 100.f, 350.f });
    bg1.setFillColor(Color(Color::Black));

    //--------------Background #2___________
    RectangleShape bg2({ 100.f,100.f });
    bg2.setPosition(Vector2f{ 250.f, 350.f });
    bg2.setFillColor(Color(Color::Black));

    //--------------Background #3___________
    RectangleShape bg3({ 100.f,100.f });
    bg3.setPosition(Vector2f{ 400.f, 350.f });
    bg3.setFillColor(Color(Color::Black));

    while (window.isOpen() && currentState == 2)
    {
        while (optional event = window.pollEvent())
        {
            float mouse_x = Mouse::getPosition(window).x;//calculating the x coordinate of mouse pointer
            float mouse_y = Mouse::getPosition(window).y;// calculating the y coordnate of mouse pointer


            //below we calculate values x and y for the coordinates of the all the buttons
            float x1 = addVolume.getPosition().x;
            float y1 = addVolume.getPosition().y;
            float x2 = x1 + addVolume.getSize().x;
            float y2 = y1 + addVolume.getSize().y;

            float x12 = subVolume.getPosition().x;
            float y12 = subVolume.getPosition().y;
            float x22 = x12 + subVolume.getSize().x;
            float y22 = y12 + subVolume.getSize().y;

            float x13 = mute.getPosition().x;
            float y13 = mute.getPosition().y;
            float x23 = x13 + mute.getSize().x;
            float y23 = y13 + mute.getSize().y;


            float x14 = backBoard.getPosition().x;
            float y14 = backBoard.getPosition().y;
            float x24 = x14 + backBoard.getSize().x;
            float y24 = y14 + backBoard.getSize().y;

            float x15 = bg1.getPosition().x;
            float y15 = bg1.getPosition().y;
            float x25 = x15 + bg1.getSize().x;
            float y25 = y15 + bg1.getSize().y;

            float x16 = bg2.getPosition().x;
            float y16 = bg2.getPosition().y;
            float x26 = x16 + bg2.getSize().x;
            float y26 = y16 + bg2.getSize().y;

            float x17 = bg3.getPosition().x;
            float y17 = bg3.getPosition().y;
            float x27 = x17 + bg3.getSize().x;
            float y27 = y17 + bg3.getSize().y;

            if (event->is<Event::Closed>()) {
                window.close();
                currentState = -1;

            }
            if ((mouse_x >= x12) and (mouse_x <= x22) and (mouse_y >= y12) and (mouse_y <= y22)) {
                subVolume.setFillColor(Color(235, 192, 52));
                if (event->is<sf::Event::MouseButtonPressed>() and (volumeLevel > 0))
                {
                    auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                    if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left)
                    {
                        volumeLevel -= 10;
                    }
                }
            }
            else {
                subVolume.setFillColor(Color(Color::Yellow));
            }
            if ((mouse_x >= x1) and (mouse_x <= x2) and (mouse_y >= y1) and (mouse_y <= y2)) {
                addVolume.setFillColor(Color(235, 192, 52));
                if (event->is<sf::Event::MouseButtonPressed>() and (volumeLevel < 100))
                {
                    auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                    if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left)
                    {
                        volumeLevel += 10;
                       
                    }
                }
            }
            else {
                addVolume.setFillColor(Color(Color::Yellow));
            }
            if ((mouse_x >= x13) and (mouse_x <= x23) and (mouse_y >= y13) and (mouse_y <= y23)) {
                mute.setFillColor(Color(235, 192, 52));
                if (event->is<sf::Event::MouseButtonPressed>())
                {
                    auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                    if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left)
                    {
                        volumeLevel = 0;

                    }
                }
            }
            else {
                mute.setFillColor(Color(Color::Yellow));
            }
            if ((mouse_x >= x14) and (mouse_x <= x24) and (mouse_y >= y14) and (mouse_y <= y24)) {
                backBoard.setFillColor(Color(235, 192, 52));
                if (event->is<sf::Event::MouseButtonPressed>())
                {
                    auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                    if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left)
                    {
                        currentState = 0;
                        break;

                    }
                }
            }
            else {
                backBoard.setFillColor(Color(Color::Yellow));
            }
            if ((mouse_x >= x15) and (mouse_x <= x25) and (mouse_y >= y15) and (mouse_y <= y25)) {
                bg1.setFillColor(Color(51, 46, 47));
                if (event->is<sf::Event::MouseButtonPressed>())
                {
                    auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                    if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left)
                    {

                        break;

                    }
                }
            }
            else {
                bg1.setFillColor(Color(Color::Black));
            }
            if ((mouse_x >= x16) and (mouse_x <= x26) and (mouse_y >= y16) and (mouse_y <= y26)) {
                bg2.setFillColor(Color(51, 46, 47));
                if (event->is<sf::Event::MouseButtonPressed>())
                {
                    auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                    if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left)
                    {
                        break;

                    }
                }
            }
            else {
                bg2.setFillColor(Color(Color::Black));
            }
            if ((mouse_x >= x17) and (mouse_x <= x27) and (mouse_y >= y17) and (mouse_y <= y27)) {
                bg3.setFillColor(Color(51, 46, 47));
                if (event->is<sf::Event::MouseButtonPressed>())
                {
                    auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                    if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left)
                    {
                        break;

                    }
                }
            }
            else {
                bg3.setFillColor(Color(Color::Black));
            }
            if (event->is<Event::TextEntered>())
            {
                auto textEvent = event->getIf<Event::TextEntered>();
                if (textEvent)
                {
                    //get Unicode value of the character
                    uint32_t unicode = textEvent->unicode;

                    //backspace (ASCII value 8)
                    if (unicode == 8)
                    {
                        if (!userInput.empty())
                        {
                            userInput.pop_back();
                        }
                    }
                    //printable characters (basic ASCII range)
                    else if (unicode >= 32 && unicode <= 126)
                    {
                        userInput += static_cast<char>(unicode);
                    }
                    else if (unicode == 13)
                    {
                        //submit the text
                        std::cout << "User submitted: " << userInput << std::endl;

                        //clear the input field after submitting
                        userInput.clear();
                    }
                }
            }



        }
        string strVolumeLevel = to_string(volumeLevel);
        Text volumeText(myFont, strVolumeLevel, 17);
        volumeText.setFillColor(Color::Black);
        volumeText.setPosition(Vector2f{ 285.f, 205.f });
        displayText.setString(userInput);

        if (cursorClock.getElapsedTime().asSeconds() > 0.5f)
        {
            cursorVisible = !cursorVisible;
            cursorClock.restart();
        }
        float cursorX = displayText.findCharacterPos(userInput.size()).x;
        //set the cursor position
        cursor.setPosition(Vector2f{cursorX, displayText.getPosition().y });

        window.clear();
        window.draw(settings);
        window.draw(backBoard);
        window.draw(backText);
        window.draw(Volumeboard);
        window.draw(Volumetext);
        window.draw(mute);
        window.draw(muteText);
        window.draw(subVolume);
        window.draw(addVolume);
        window.draw(Volume);
        window.draw(volumeText);
        window.draw(minusVolume);
        window.draw(plusVolume);
        window.draw(bgBoard);
        window.draw(bgText);
        window.draw(bg1);
        window.draw(bg2);
        window.draw(bg3);
        window.draw(nameBoard);
        window.draw(nameText);
        window.draw(textfieldBox);
        window.draw(displayText);
        if (cursorVisible)
        {
            window.draw(cursor);
        }
        window.display();
    }
}
