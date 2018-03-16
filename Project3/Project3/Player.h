
#ifndef __Project3__Player__
#define __Project3__Player__

#include <iostream>
#include <string>
#include "Board.h"
using namespace std;

///// PLAYER /////

class Player
{
public:
    Player(string name);
    string name() const;
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const = 0;
    virtual ~Player();
    
private:
    string playerName;
    
};

///// HUMAN PLAYER /////

class HumanPlayer : public Player
{
public:
    HumanPlayer(string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~HumanPlayer();
    
private:
    
};

///// BAD PLAYER /////

class BadPlayer : public Player
{
public:
    BadPlayer(string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~BadPlayer();
    
private:
    
    
};

///// SMART PLAYER /////

class SmartPlayer: public Player
{
public:
    SmartPlayer(string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~SmartPlayer();
private:
    int calculateMove(Board b, Side s) const;
};

#endif /* defined(__Project3__Player__) */

