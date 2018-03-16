
#ifndef __Project3__Board__
#define __Project3__Board__

#include <iostream>
#include "Side.h"
#include <vector>
using namespace std;

class Board
{
public:
    Board(int nHoles, int nInitialBeansPerHole);
    int holes() const;
    int beans(Side s, int hole) const;
    int beansInPlay(Side s) const;
    int totalBeans() const;
    bool sow(Side s, int hole, Side& endSide, int& endHole);
    bool moveToPot(Side s, int hole, Side potOwner);
    bool setBeans(Side s, int hole, int beans);
    
    
private:
    int numberOfHolesPerSide;
    int allTheBeans;
    int numberOfBeansPerHole;
    double vectorMidPoint;
    vector<int> theBoard;
    int northPot;
    int southPot;
    int beansInHand;
    Board& operator=(const Board& source); // assignment operator overridden
    void recursiveSow(Side s, int& hole, int& holesTraveled, int& beansInHand);
    void potPlusOne(Side s);
    int distanceFromHoleToPot(Side s, int hole);
    int thisHole;
};

#endif 
 
 

