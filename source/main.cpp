#include "../header/Game/Game.h"
#include "../header/Menu/Button.h"
#include "../header/Menu/Menu.h"
#include "../header/Menu/Leaderboard.h"
#include "../header/Menu/GameOver.h"


int main() {

    //TODO unite all the pointers as a structure to clean up
    //TODO button textures
    //TODO logo on the main screen
    //TODO throw out crucial functions from class constructors so you don't have to create new objects every time you leave menu

    //TODO change the controls

    int volume = 0;
    int score = 0;
    int level = 1;
    int boardWidth = 10;
    int boardHeight = 20;
    int gameState = MENU;
    bool ghostFlag = true;

    sf::RenderWindow window(sf::VideoMode(800, 800), "Tetris");
    window.setVerticalSyncEnabled(true);

    ResourceManager resourceManager;

    Menu menu(&window, &boardWidth, &boardHeight, &volume, &gameState, &ghostFlag, &resourceManager);


    while (window.isOpen()) {
        if (gameState == EXIT)
            break;

        switch (gameState) {
            case MENU: {
                menu.run();
                break;
               }

            case GAME: {
                Game game(&window, boardWidth, boardHeight, (float)volume, &gameState, &score, &level, ghostFlag, &resourceManager);
                game.run();
                break;
            }

            case GAMEOVER: {
                GameOver gameOver(&window, "scores.txt", volume, &gameState, &score, &level, &resourceManager);
                gameOver.run();
                break;
            }

            case LEADERBOARD: {
                Leaderboard leaderboard(&window, "scores.txt", &gameState, &score, &resourceManager);
                leaderboard.run();
                break;
            }

            default:
                gameState = EXIT;
                break;
        }
    }

    return 0;
}
