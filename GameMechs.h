#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
private:
    char input;
    bool exitFlag;
    bool loseFlag;

    int score;

    int boardSizeX;
    int boardSizeY;

public:
    GameMechs();
    GameMechs(int boardX, int boardY);

    bool getExitFlagStatus();
    bool getLoseFlagStatus();
    void setExitTrue();
    void setLoseFlag();

    char getInput();
    void setInput(char this_input);
    void clearInput();
    void incrementScore();
    void incrementScore(int count);
    int getScore();

    int getBoardSizeX();
    int getBoardSizeY();
};

#endif