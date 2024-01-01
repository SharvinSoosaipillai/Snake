#include "objPos.h"

objPos::objPos()
{
    // initialize the objpos object
    x = 0;
    y = 0;
    symbol = 0; // NULL
}

objPos::objPos(objPos &o)
{
    // set the x,y and symbol to the object passed in
    x = o.x;
    y = o.y;
    symbol = o.symbol;
}

objPos::objPos(int xPos, int yPos, char sym)
{
    // set the x and y positions and the character symbol to the desired symbols
    x = xPos;
    y = yPos;
    symbol = sym;
}

void objPos::setObjPos(objPos o)
{
    // set the object position based on what is passed in
    x = o.x;
    y = o.y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    // set the object position on the board
    x = xPos;
    y = yPos;
    symbol = sym;
}

void objPos::getObjPos(objPos &returnPos)
{
    // sets the object x and y pos on the board with the symbol
    returnPos.setObjPos(x, y, symbol);
}

char objPos::getSymbol()
{
    return symbol;
}

bool objPos::isPosEqual(const objPos *refPos)
{
    // returns weather or not the positions are the same
    return (refPos->x == x && refPos->y == y);
}

char objPos::getSymbolIfPosEqual(const objPos *refPos)
{
    if (isPosEqual(refPos))
        return getSymbol();
    else
        return 0;
}
