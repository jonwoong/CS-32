

#include "Player.h"
#include <cassert>
using namespace std;

///// PLAYER /////

Player::Player(string name)
: playerName(name)
{
    
} // Create a Player with the indicated name.

string Player::name() const
{
    return playerName;
} // Return the name of the player.

bool Player::isInteractive() const
{
    return false;
} // Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.

int Player::chooseMove(const Board& b, Side s) const
{
    return -999;
} // Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.

Player::~Player()
{
    
}

///// HUMAN PLAYER /////

HumanPlayer::HumanPlayer(string name)
:Player(name)
{
    
}

bool HumanPlayer::isInteractive() const
{
    return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
    if (b.beansInPlay(SOUTH) >= 1 && b.beansInPlay(NORTH) >= 1)
        {
        A:
            cout << name() << " chose hole ";
            string answer;
            getline(cin, answer);
            cout << endl;
            int value = atoi(answer.c_str());
        
            if (value < 1 || value > b.holes())
                {
                    goto A;
                }
            if (b.beans(s,value) == 0)
                {
                goto A;
                }
            return value;
        }
return -1;
}

HumanPlayer::~HumanPlayer()
{
    
}

///// BAD PLAYER /////

BadPlayer::BadPlayer(string name)
:Player(name)
{
    
}


bool BadPlayer::isInteractive() const
{
    return false;
}
int BadPlayer::chooseMove(const Board& b, Side s) const
{
    for (int n=1; n!= b.holes()+1; n++) // if player cannot take another turn or capture,
    {
        if (b.beans(s,n) > 0) // last resort: pick any hole with beans in it
        {
            return n;
        }
    }
return 0;
}
BadPlayer::~BadPlayer()
{
    
}

///// SMART PLAYER /////

SmartPlayer::SmartPlayer(string name)
:Player(name)
{
    
}

bool SmartPlayer::isInteractive() const
{
    return false;
}

int SmartPlayer::calculateMove(Board b, Side s) const
{
    if ( s == SOUTH)
    {
        for (int n=1; n!= b.holes()+1; n++)
        {
            if (b.beans(s,n)+n == b.holes()+1 && b.beans(s,n) != 0)// if the player can ensure another turn, do it
            {
                return n;
            }
            if (b.beans(opponent(s),b.beans(s,n)+n) != 0 && b.beans(s, b.beans(s,n)+n) == 0) // if the player can ensure a capture, do it
            {
                Board bCopy(b);
                int endHole = 0;
                Side endSide;
                bCopy.sow(s, n, endSide, endHole);
                if (bCopy.beans(s,endHole) == 1)
                {
                    return n;
                }
            }
        }
        for (int n=1; n!= b.holes()+1; n++) // if player cannot take another turn or capture,
        {
            if (b.beans(s,n)+n > b.holes()) // pick one so that the player ends up on the opposite side
            {
                return n;
            }
            
            if (b.beans(s,n) > 0) // last resort: pick any hole with beans in it
            {
                return n;
            }
        }
    }
    
    if ( s == NORTH)
    {
        for (int n=1; n!= b.holes()+1; n++)
        {
            if ((b.beans(s,n) - n) == 0 && b.beans(s,n) != 0)
            {
                return n;
            }
            if (b.beans(opponent(s),b.beans(s,n)+n) != 0 && b.beans(s, b.beans(s,n)-n) == 0)
            {
                Board bCopy(b);
                int endHole = 0;
                Side endSide;
                bCopy.sow(s, n, endSide, endHole);
                if (bCopy.beans(s,endHole) == 1)
                {
                    return n;
                }
            }
        }
        for (int h=1; h!= b.holes()+1; h++)
        {
            if (b.beans(s,h) > 0)
            {
                return h;
            }
        }
    }
    return 0;
}


int SmartPlayer::chooseMove(const Board& b, Side s) const
{
    int k = calculateMove(b, s);
    return k;
}

SmartPlayer::~SmartPlayer()
{
    
}




