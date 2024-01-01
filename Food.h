#ifndef FOOD_H
#define FOOD_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Food
{
public:
  // the enum values are equal to the char symbol to show
  enum FoodType
  {
    NORMAL = 88,         // X
    SCORE_INCREASE = 43, // +
    LENGTH_INCREASE = 61 // =
  };

  Food(GameMechs *thisGMRef);

  // copy constructor
  Food(const Food &food);

  ~Food();

  void generateFood(objPosArrayList *blockOff);

  void getFoodPos(objPos &returnPos);
  objPosArrayList *getFoodBucket();

private:
  GameMechs *mainGameMechsRef;
  objPosArrayList *foodBucket;

  char getRandomFoodType();
};

#endif