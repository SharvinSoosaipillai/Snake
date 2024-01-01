#include "Player.h"
#include "objPos.h"
#include "Food.h"

Player::Player(GameMechs *thisGMRef, Food *thisFoodRef)
{
    // initialize the player object based on the game board
    mainGameMechsRef = thisGMRef;
    foodRef = thisFoodRef;
    myDir = STOP;

    // initialize the player position list
    playerPosList = new objPosArrayList();

    // initialize the player position to the center of the board
    playerPos = objPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');
    playerPosList->insertTail(playerPos);
}

Player::~Player()
{
    delete playerPosList;
}

Player::Player(const Player &player)
{
    // copy constructor
    mainGameMechsRef = player.mainGameMechsRef;
    foodRef = player.foodRef;
    myDir = player.myDir;
    playerPos = player.playerPos;
    playerPosList = player.playerPosList;
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos = playerPos;
}

objPosArrayList *Player::getPlayerPosList()
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // get the input
    char input = mainGameMechsRef->getInput();

    // if null character, do nothing
    if (input == 0)
    {
        return;
    }

    // otherwise, check the input
    switch (input)
    {
        // exit
    case ' ':
        mainGameMechsRef->setExitTrue();
        break;

        // up
    case 'W':
    case 'w':
        if (getDir() != Player::DOWN)
        {
            setDir(Player::UP);
        };
        break;

        // down
    case 'S':
    case 's':
        if (getDir() != Player::UP)
        {
            setDir(Player::DOWN);
        };
        break;

        // left
    case 'A':
    case 'a':
        if (getDir() != Player::RIGHT)
        {
            setDir(Player::LEFT);
        };
        break;

        // right
    case 'D':
    case 'd':
        if (getDir() != Player::LEFT)
        {
            setDir(Player::RIGHT);
        };
        break;

    default:
        break;
    }
}

void Player::movePlayer()
{
    if (getDir() == STOP)
    {
        return;
    }

    objPos head;
    playerPosList->getHeadElement(head);

    // update the player location

    switch (getDir())
    {
    case UP:
        head.y--;
        break;

    case DOWN:
        head.y++;
        break;

    case LEFT:
        head.x--;
        break;

    case RIGHT:
        head.x++;
        break;

    default:
        break;
    }

    // border wraparound
    if (head.x <= 0)
    {
        head.x = mainGameMechsRef->getBoardSizeX() - 2;
    }
    else if (head.x >= mainGameMechsRef->getBoardSizeX() - 1)
    {
        head.x = 1;
    }
    else if (head.y <= 0)
    {
        head.y = mainGameMechsRef->getBoardSizeY() - 2;
    }
    else if (head.y >= mainGameMechsRef->getBoardSizeY() - 1)
    {
        head.y = 1;
    }

    // add the new head position to the list
    playerPosList->insertHead(head);

    // check if player is touching the food

    objPosArrayList *foodBucket = foodRef->getFoodBucket();

    bool foodFlag = false;
    for (int i = 0; i < foodBucket->getSize(); i++)
    {
        objPos foodPos;
        foodBucket->getElement(foodPos, i);

        if (head.isPosEqual(&foodPos))
        {
            // check which type of food
            if (foodPos.symbol == Food::FoodType::NORMAL)
            {
                mainGameMechsRef->incrementScore();
            }
            else if (foodPos.symbol == Food::FoodType::SCORE_INCREASE)
            {
                mainGameMechsRef->incrementScore(10);
            }
            else if (foodPos.symbol == Food::FoodType::LENGTH_INCREASE)
            {
                objPos offscreenPos(-1, -1, '@');

                // increase length by 5
                for (int i = 0; i < 5; i++)
                {
                    playerPosList->insertTail(offscreenPos);
                }

                mainGameMechsRef->incrementScore();
            }

            // generate new food
            foodRef->generateFood(playerPosList);
            foodFlag = true;
            break;
        }
    }

    if (!foodFlag)
    {
        // remove last element
        playerPosList->removeTail();
    }

    // dont delete the tail if the player is touching the food
    // if (foodPos.isPosEqual(&equalPos))
    //{
    //	// check which type of food
    //	if (foodPos.symbol == Food::FoodType::NORMAL)
    //	{
    //		mainGameMechsRef->incrementScore();
    //	}
    //	else if (foodPos.symbol == Food::FoodType::SCORE_INCREASE)
    //	{
    //		mainGameMechsRef->incrementScore(10);
    //	}
    //	else if (foodPos.symbol == Food::FoodType::LENGTH_INCREASE)
    //	{
    //		objPos offscreenPos(-1, -1, '@');

    //		// increase length by 5
    //		for (int i = 0; i < 5; i++)
    //		{
    //			playerPosList->insertTail(offscreenPos);
    //		}

    //		mainGameMechsRef->incrementScore();
    //	}

    //	// generate new food
    //	foodRef->generateFood(playerPosList);
    //}
    // else
    //{
    //	// remove last element
    //	playerPosList->removeTail();
    //}

    // check if player is touching itself
    if (checkSelfCollision())
    {
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseFlag();
    }
}

Player::Dir Player::getDir()
{
    return myDir;
}

bool Player::checkSelfCollision()
{
    objPos head;
    playerPosList->getHeadElement(head);

    // check to see within all of the elements in the list has overlapped
    for (int i = 1; i < playerPosList->getSize(); i++)
    {

        objPos segment;
        playerPosList->getElement(segment, i);

        if (head.isPosEqual(&segment))
        {
            return true;
        }
    }

    return false;
}

void Player::setDir(Dir thisDir)
{
    // set the player direction to the passed in perameters
    myDir = thisDir;
}