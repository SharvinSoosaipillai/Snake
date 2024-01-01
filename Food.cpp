#include "Food.h"

#include <cstdlib>
#include <time.h>

#include <iostream>
using namespace std;

Food::Food(GameMechs *thisGMRef)
{
  mainGameMechsRef = thisGMRef;
  foodBucket = new objPosArrayList();

  // temp fill with food
  objPos foodPos;
  foodPos.x = 1;
  foodPos.y = 1;
  foodPos.symbol = 'X';
  foodBucket->insertHead(foodPos);
  foodBucket->insertHead(foodPos);
  foodBucket->insertHead(foodPos);
  foodBucket->insertHead(foodPos);
  foodBucket->insertHead(foodPos);

  srand(static_cast<unsigned>(time(nullptr)));
}

Food::Food(const Food &food)
{
  foodBucket = food.foodBucket;
  mainGameMechsRef = food.mainGameMechsRef;
}

Food::~Food()
{
  delete foodBucket;
}

void Food::generateFood(objPosArrayList *blockOff)
{
  // make sure that there is space for food to be generated
  if (blockOff->getSize() >= (mainGameMechsRef->getBoardSizeX() - 2) * (mainGameMechsRef->getBoardSizeY() - 2) - 5)
  {
    mainGameMechsRef->setExitTrue();
    return;
  }

  objPos foodPos;
  getFoodPos(foodPos);

  // clear the food array list
  for (int i = 0; i < foodBucket->getSize(); i++)
  {
    // foodBucket->removeTail();
  }

  // Ensure the generated position is not the same as blockOff
  for (int j = 0; j < 5; j++)
  {
    while (true)
    {
      foodPos.x = rand() % (mainGameMechsRef->getBoardSizeX() - 2) + 1;
      foodPos.y = rand() % (mainGameMechsRef->getBoardSizeY() - 2) + 1;
      foodPos.symbol = getRandomFoodType();

      bool hitFlag = false;
      // colliding with blockOff
      for (int i = 0; i < blockOff->getSize(); i++)
      {
        objPos pos;
        blockOff->getElement(pos, i);

        if (foodPos.x == pos.x && foodPos.y == pos.y)
        {
          hitFlag = true;
          break;
        }
      }
      // check if colliding with existing food
      for (int i = 0; i < foodBucket->getSize(); i++)
      {
        objPos pos;
        foodBucket->getElement(pos, i);

        if (foodPos.x == pos.x && foodPos.y == pos.y)
        {
          hitFlag = true;
          break;
        }
      }

      if (!hitFlag)
      {
        foodBucket->removeHead();
        foodBucket->insertTail(foodPos);
        break;
      }
    }
  }
}

void Food::getFoodPos(objPos &returnPos)
{
  objPos foodPos;
  foodBucket->getElement(foodPos, 0);
  returnPos = foodPos;
}

objPosArrayList *Food::getFoodBucket()
{
  return foodBucket;
}

char Food::getRandomFoodType()
{
  // 2 / 3 chance of normal food
  if (rand() % 3 == 0 || rand() % 3 == 1)
  {
    return FoodType::NORMAL;
  }
  else
  {
    // 1 / 6 chance of score increase or length increase food
    if (rand() % 2 == 0)
    {
      return FoodType::SCORE_INCREASE;
    }
    else
    {
      return FoodType::LENGTH_INCREASE;
    }
  }
}
