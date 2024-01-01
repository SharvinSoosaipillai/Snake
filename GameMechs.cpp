#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
  exitFlag = false;
  loseFlag = false;
  boardSizeX = 20;
  boardSizeY = 20;
  input = 0;
  score = 0;
}

GameMechs::GameMechs(int boardX, int boardY)
{
  exitFlag = false;
  loseFlag = false;
  boardSizeX = boardX;
  boardSizeY = boardY;
  input = 0;
  score = 0;
}

bool GameMechs::getExitFlagStatus()
{
  return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
  return loseFlag;
}

char GameMechs::getInput()
{
  if (MacUILib_hasChar() != 0)
  {
    input = MacUILib_getChar();
  }
  return input;
}

void GameMechs::incrementScore()
{
  score++;
}

void GameMechs::incrementScore(int count)
{
  score += count;
}

int GameMechs::getScore()
{
  return score;
}

int GameMechs::getBoardSizeX()
{
  return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
  return boardSizeY;
}

void GameMechs::setExitTrue()
{
  exitFlag = true;
}

void GameMechs::setLoseFlag()
{
  loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
  input = this_input;
}

void GameMechs::clearInput()
{
  input = 0;
}
