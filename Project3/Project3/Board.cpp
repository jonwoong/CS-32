

#include "Board.h"
#include <cassert>

using namespace std;

Board::Board(int nHoles, int nInitialBeansPerHole)
:
numberOfHolesPerSide(nHoles),
numberOfBeansPerHole(nInitialBeansPerHole),
northPot(0),
southPot(0)
{
    for (int n = 0;
             n != (2*nHoles)+1 ;
             n++)
        {
            theBoard.assign(n,numberOfBeansPerHole);
        }
    vectorMidPoint = holes();
    allTheBeans = totalBeans();
} // Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole.

int Board::holes() const
{
    return numberOfHolesPerSide;
} // Return the number of holes on a side (not counting the pot).

int Board::beans(Side s, int hole) const
{
    if ( hole == 0)
        {
            if (s == SOUTH)
                {return southPot;}
            
            if (s == NORTH)
                {return northPot;}
        }
    
    if ( hole < 0
      || hole > holes())
        {return -1;}
    
    if ( s == SOUTH )
        {return theBoard[hole-1];}
    
    if ( s == NORTH)
        {return theBoard[theBoard.size()-hole];}
    
    return -1;
} // Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.

int Board::beansInPlay(Side s) const
{
    int beanCounter = 0;
    for (int n=1;
         n != holes()+1;
         n++)
    {beanCounter += beans(s,n);}
    
    return beanCounter;
} // Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.

int Board::totalBeans() const
{
    int allTheBeans = 0;
    allTheBeans += beansInPlay(NORTH);
    allTheBeans += beansInPlay(SOUTH);
    allTheBeans += southPot;
    allTheBeans += northPot;
    return allTheBeans;
} // Return the total number of beans in the game.

void Board::potPlusOne(Side s)
{
    if (s == SOUTH)
    {
        southPot++;
        beansInHand--;
    }
    if (s == NORTH)
    {
        northPot++;
        beansInHand--;
    }
}

void Board::recursiveSow(Side s, int& hole, int& holesTraveled, int& beansInHand)
{
    switch (s)
    {
        case SOUTH:
            if (beansInHand <= 0) // exit recursion in this case
                {return;}
            
            if (holesTraveled == 2*holes() || hole == 2*holes()-1) // allows for looping through the board
                {hole = -1; // start loop again at south's hole 1
                 holesTraveled = 0;}
            
            if (hole == holes() && beansInHand != 0) // add to pot if reached
                {potPlusOne(s);}
            
            if (beansInHand <= 0) // exit recursion in this case
                {return;}
            
            theBoard[hole]++; // start 1 after hole player picks from
            hole++;
            holesTraveled++;
            beansInHand--;
            
            if (beansInHand <= 0) // exit recursion in this case
                {return;}
            
            recursiveSow(SOUTH, hole, holesTraveled,beansInHand);
            
        case NORTH:
            if (beansInHand <= 0) // exit recursion in this case
                {return;}
            
            if (hole == 1 && beansInHand !=0)
                {
                holesTraveled = 0;
                potPlusOne(s);
                hole = 2*holes()+1;
                }
            
            if (beansInHand <= 0) // exit recursion in this case
                {return;}
            
            if (holesTraveled == 2*holes()) // allows for looping through the board
                {
                    hole = 2*holes()+1;
                    potPlusOne(s); // add to pot if reached
                    holesTraveled = 0; // start loop again at south's hole 1
                }
            
            if (beansInHand <= 0) // exit recursion in this case
                {return;}
            
            theBoard[2*holes()-hole+1]++; // start 1 after hole player picks from
            hole--;
            holesTraveled++;
            beansInHand--;
            
            if (beansInHand <= 0) // exit recursion in this case
                {return;}
            
            recursiveSow(NORTH, hole, holesTraveled,beansInHand);
    }
}

int Board::distanceFromHoleToPot(Side s, int hole)
{
    if (s == SOUTH)
        {return holes()+1-hole;}
    
    if (s == NORTH)
        {return hole;}
    
return 0;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    /// CASES ///
    
    if (beans(s,hole) == 0) // if hole is empty, return false
    {return false;}
    
    if (hole <= holes()) // if hole is valid, sow
    {
        beansInHand = beans(s,hole); // PICK UP BEANS
        
        int endCondition = 0; // 0 = condition not set
                              // 1 = did not reach pot
                              // 2 = ended in pot
                              // 3 = passed pot
        
        // SET ENDING CONDITION
        
        if (beansInHand < distanceFromHoleToPot(s,hole)) // player does not reach pot
            {endCondition = 1;}
        
        if (beansInHand == distanceFromHoleToPot(s,hole)) // player ends at pot
            {endCondition = 2;}
        
        if (beansInHand > distanceFromHoleToPot(s,hole)) // player passes pot
            {endCondition = 3;};
        
        int holesTraveled = 0; // how many holes have been reached after sowing
        
        // MOVE BEANS
        
        if (s == SOUTH)
        {
            theBoard[hole-1] = 0; // pick them up
            if (beansInHand > 0)
            {
                holesTraveled=0;
                thisHole=hole;
                recursiveSow(s, hole, holesTraveled, beansInHand); // DROP BEANS
            }
            
            // ASSIGN END CONDITION
            switch (endCondition) // ASSIGN END VARIABLES
            {
                case 1: // does not end in pot
                    endHole = thisHole + (holesTraveled); // SET ENDHOLE
                    endSide = SOUTH; // SET ENDSIDE
                    return true;
                    
                case 2: // ended in pot
                    endHole = 0; // SET ENDHOLE
                    endSide = SOUTH; // SET ENDSIDE
                    return true;
                    
                case 3: // passed pot
                    // based on holesTraveled, calculate endHole & endSide
                    if (holesTraveled+thisHole == holes()+1)
                    {
                        endHole = thisHole;
                        endSide = NORTH;
                        return true;
                    }
                    if (holesTraveled+thisHole <= holes())
                    {
                        endHole = holesTraveled;
                        endSide = SOUTH;
                        return true;
                    }
                    if (holesTraveled+thisHole > holes())
                    {
                        endHole = hole-holesTraveled;
                        endSide = NORTH;
                        return true;
                    }
            }
        }
        if ( s == NORTH)
        {
            theBoard[2*holes()-hole] = 0; // pick them up
            
            if (beansInHand > 0)
            {
                holesTraveled=0;
                thisHole=hole;
                recursiveSow(s, hole, holesTraveled, beansInHand); // DROP BEANS
            }
            
            // ASSIGN END CONDITION
            switch (endCondition) // ASSIGN END VARIABLES
            {
                case 1: // does not end in pot
                    endHole = thisHole-holesTraveled; // SET ENDHOLE
                    endSide = NORTH; // SET ENDSIDE
                    return true;
                    
                case 2: // ended in pot
                    endHole = 0; // SET ENDHOLE
                    endSide = NORTH; // SET ENDSIDE
                    return true;
                    
                case 3: // passed pot
                    // based on holesTraveled, calculate endHole & endSide
                    if (holesTraveled+thisHole == holes()+1)
                    {
                        endHole = 0;
                        endSide = SOUTH;
                        return true;
                    }
                    if (holesTraveled+thisHole <= holes())
                    {
                        endHole = holesTraveled;
                        endSide = SOUTH;
                        return true;
                    }
                    if (holesTraveled+thisHole > holes())
                    {
                        endHole = (holes()+1)-(holesTraveled-holes());
                        endSide = NORTH;
                        return true;
                    }
            }
        }
    }
return false;
}
 // If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The parameters endSide and endHole are set to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    if (hole <= holes() && hole > 0)
        {
            if ( s == SOUTH )
                {
                    beansInHand = beans(s, hole); // count beans to move to pot
                    theBoard[hole-1] = 0; // pick up beans
            
                    if (potOwner == NORTH)
                        {
                            northPot += beansInHand;
                            return true;
                        }
                    if (potOwner == SOUTH)
                        {
                            southPot += beansInHand;
                            return true;
                        }
                }
        
            if ( s == NORTH)
                {
                    beansInHand = beans(s, hole); // count beans to move to pot
                    theBoard[(2*holes())-hole] = 0; // pick up beans
            
                    if (potOwner == NORTH)
                        {
                            northPot += beansInHand;
                            return true;
                        }
                    if (potOwner == SOUTH)
                        {
                            southPot += beansInHand;
                            return true;
                        }

                }
        
        }
    return false;
} // If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.

bool Board::setBeans(Side s, int hole, int beans)
{
    if (hole > holes()
     || hole < 0
     || beans < 0)
        {return false;}
    
    if ( s == SOUTH)
        {
            theBoard[hole-1] = beans;
            return true;
        }
    
    if ( s == NORTH )
        {
            theBoard[(2*holes())-hole] = beans;
            return true;
        }
    
    return false;
    
} // If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This may change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program: None of your code that implements the member functions of any class is allowed to call this function directly or indirectly.

Board& Board::operator=(const Board& source) // wrote this just to have it
{
    northPot = source.northPot;
    southPot = source.southPot;
    numberOfBeansPerHole = source.numberOfBeansPerHole;
    numberOfHolesPerSide = source.holes();
    allTheBeans = (2 * source.numberOfHolesPerSide * source.numberOfBeansPerHole);
    
    for (int n=0;
             n != (2*numberOfHolesPerSide);
             n++)
        {theBoard.assign(n,numberOfBeansPerHole);}
    
    vectorMidPoint = (theBoard.size()/2) + 1;
    return *this;
}

