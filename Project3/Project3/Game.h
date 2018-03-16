#ifndef __Project3__Game__
#define __Project3__Game__

#include <iostream>
#include "Player.h"
#include "Board.h"

class Game
{
public:
    Game(const Board& b, Player* south, Player* north);
    void display() const;
    void status(bool& over, bool& hasWinner, Side& winner) const;
    bool move();
    void play();
    int beans(Side s, int hole) const;
    
private:
    string northName;
    string southName;
    Board bCopy;
    Player* southPlayer;
    Player* northPlayer;
    int pickASide;
    void clearScreen();
    void applySpecialRules();
    Side endSide;
    int endHole;
    bool collectRemainingBeans();
    bool isTheGameOver;
    bool isThereAWinner;
    Side iAmTheWinner;
    void stealAllTheBeans(Side s) const;
    int playerTurnSwitch;
    int specialEventSwitch;
};

#endif 
 



