#include "gamewindow.h"
#include "Menu.h"
#include "settings.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const int GAME_EXIT = -1;
const int STATE_MENU = 0;
const int STATE_PLAYING = 1;
const int STATE_SETTINGS = 2;

int main()
{
    const int win_height = 950;
    const int win_width = 600;
    RenderWindow window(VideoMode({win_width, win_height}), "My First SFML Use", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);

    int currentState = 0; // Game starting state
    while (currentState != GAME_EXIT)
    {
        switch (currentState)
        { // game state check every time
        case STATE_MENU:
            MainMenu(window, currentState);
            break;
        case STATE_PLAYING:
            mainGame(window, currentState);
            break;
        case STATE_SETTINGS:
            settings(window,currentState);
            break;
        }
    }
}
