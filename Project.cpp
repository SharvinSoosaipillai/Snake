#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Food.h"
#include "GameMechs.h"
#include "Player.h"
#include <time.h>

using namespace std;

#define DELAY_CONST 100000

GameMechs *game;
Player *player;
Food *food;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{
    Initialize();

    while (game->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    // generate player, board and food
    game = new GameMechs(30, 15);
    food = new Food(game);
    player = new Player(game, food);

    objPos pos;
    player->getPlayerPos(pos);

    player->getPlayerPosList();

    food->generateFood(player->getPlayerPosList());

    MacUILib_init();
    MacUILib_clearScreen();
}

void GetInput(void)
{
    // get input
    char input = game->getInput();
    game->setInput(input);
}

void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();

    // if not null character
    if (game->getInput() != 0)
    {
        if (game->getInput() == 'l')
        {
            game->setExitTrue();
        }

        if (game->getInput() == 'i')
        {
            game->incrementScore();
        }

        if (game->getInput() == 'r')
        {
            food->generateFood(player->getPlayerPosList());

            objPos foodPos;
            food->getFoodPos(foodPos);
        }
    }

    game->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    //  Draw game instructions
    printf("WASD to move, space to exit\n\n");

    objPos playerHead;
    player->getPlayerPos(playerHead);

    objPosArrayList *playerPosList = player->getPlayerPosList();

    objPos foodPos;
    food->getFoodPos(foodPos);

    objPosArrayList *foodBucket = food->getFoodBucket();

    //  2. Iterate through each character location on the game board
    //     using the nested for-loop row-scanning setup.
    for (int i = 0; i < game->getBoardSizeY(); i++)
    {
        for (int j = 0; j < game->getBoardSizeX(); j++)
        {
            // if border
            if (i == 0 || i == game->getBoardSizeY() - 1 || j == 0 || j == game->getBoardSizeX() - 1)
            {
                // top left corner
                if (i == 0 && j == 0)
                {
                    MacUILib_printf("%c", (char)201);
                }
                // top right corner
                else if (i == 0 && j == game->getBoardSizeX() - 1)
                {
                    MacUILib_printf("%c", (char)187);
                }
                // bottom left corner
                else if (i == game->getBoardSizeY() - 1 && j == 0)
                {
                    MacUILib_printf("%c", (char)200);
                }
                // bottom right corner
                else if (i == game->getBoardSizeY() - 1 && j == game->getBoardSizeX() - 1)
                {
                    MacUILib_printf("%c", (char)188);
                }
                // top and bottom borders
                else if (i == 0 || i == game->getBoardSizeY() - 1)
                {
                    MacUILib_printf("%c", (char)205);
                }
                // left and right borders
                else if (j == 0 || j == game->getBoardSizeX() - 1)
                {
                    MacUILib_printf("%c", (char)186);
                }

                continue;
            }

            // print out food
            bool isFood = false;
            for (int k = 0; k < foodBucket->getSize(); k++)
            {
                objPos pos;
                foodBucket->getElement(pos, k);

                if (pos.x == j && pos.y == i)
                {
                    MacUILib_printf("%c", pos.getSymbol());
                    isFood = true;
                    break;
                }
            }
            if (isFood)
            {
                continue;
            }

            // move the player accordingly
            bool isPlayer = false;
            for (int k = 0; k < playerPosList->getSize(); k++)
            {
                objPos pos;
                playerPosList->getElement(pos, k);

                if (pos.x == j && pos.y == i)
                {
                    MacUILib_printf("%c", pos.getSymbol());
                    isPlayer = true;
                    break;
                }
            }
            if (isPlayer)
            {
                continue;
            }

            printf(" ");
        }
        printf("\n");
    }

    // print current position
    objPos playerPos;
    playerPosList->getHeadElement(playerPos);

    // print score
    MacUILib_printf("Score: %d\n", game->getScore());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();

    if (game->getLoseFlagStatus())
    {
        MacUILib_printf("You lose!\n");
    }

    MacUILib_printf("You scored %d points!\n", game->getScore());

    // free up memory
    delete game;
    delete player;

    MacUILib_uninit();
}
