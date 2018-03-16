

#include "Game.h"
#include <cstdlib>
using namespace std;

Game::Game(const Board& b, Player* south, Player* north)
:bCopy(b), southName(south->name()), northName(north->name()), southPlayer(south), northPlayer(north), pickASide(-1), endHole(-1), endSide(SOUTH), playerTurnSwitch(-1), specialEventSwitch(0)
{

} // Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.

void Game::clearScreen()
{
    cout << string(50,'\n');
}

void Game::display() const
{
    cout << '\n';
    ///// PLAYER NAMES /////
    
    double n = 0;
    while(n < bCopy.holes())
        {
            cout << "=============";
            n++;
        }
    double topBoarder = bCopy.holes(); // this is used as a baseline for scaling purposes
    
    cout
        << '\n'
        << '\n';
    n = 0;
    
    while (n < topBoarder)
        {
            cout<< "    ";
            n++;
        }
    
    switch(playerTurnSwitch)
    {
        case -1:
        {
            cout
            << "(NORTH)"<< northName
            << " vs. (SOUTH)"<< southName << "'s Turn"<<
            endl;
            break;
        }
        case 1:
        {
            cout
            << "(NORTH)"<< northName << "'s Turn"
            << " vs. (SOUTH)" << southName <<
            endl;
            break;
        }
    }
    
    ///// NORTH HOLES /////

    cout << '\n';
    n = 0;
    
    while(n < topBoarder)
        {
            cout << " ";
            n++;
        }
    n = 1;
    while (n != bCopy.holes()+1)
        {
            for(int k=0; k != topBoarder; k++)
                {cout << " ";}
            
            cout
                << "(" << n << ")"
                << bCopy.beans(NORTH,n);
            n++;
        }
    cout << '\n';
    
    ///// POT VALUES /////
    
    cout << '\n';
    cout
         << northName
         << "'s Pot: "
         << bCopy.beans(NORTH,0);
    
    n = 0;
    while (n < topBoarder)
        {
            cout << "   ";
            n++;
        }
    switch (specialEventSwitch) // 0 for not set
    {
        case -1:
        {
            cout <<southName<<" goes again!";
            break;
        }
        case -10:
        {
            cout <<southName<<" captured hole " << endHole;
            break;
        }
        case 1:
        {
            cout <<northName<<" goes again!";
            break;
        }
        case 10:
        {
            cout <<northName<<" captured hole " << endHole;
        }
        case 0:
        {
            int n = 0;
            while(n!=topBoarder)
            {
                cout<<"  ";
                n++;
            }
            break;
        }
    }// (SOUTH), -1 for extra turn, -10 for capture
                                // (NORTH), 1 for extra turn, 10 for capture
    n = 0;
    while (n < topBoarder)
    {
        cout << "   ";
        n++;
    }
    cout
        << southName
        << "'s Pot: "
        << bCopy.beans(SOUTH,0)
        << endl;
    
    ///// SOUTH HOLES /////
    
    cout << '\n';
    n = 0;
    while(n < topBoarder)
        {
            cout << " ";
            n++;
        }
    n = 1;
    while (n != bCopy.holes()+1) // LEAVE THE +1
        {
            for(int k=0; k != topBoarder; k++)
                {cout << " ";}
            
            cout
                << "(" << n << ")"
                << bCopy.beans(SOUTH,n);
            n++;
        }
    cout
        << '\n'
        << '\n';
    n = 0;
    while(n < topBoarder)
        {
            cout << "=============";
            n++;
        }
    cout
        << '\n'
        << '\n';

} // Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.

bool Game::collectRemainingBeans()
{
    /// SOUTH WINS ///
    
    if (bCopy.beansInPlay(SOUTH) == 0)
        {
            for (int n = 1;
                     n != bCopy.holes()+1;
                     n++)
                {
                    bCopy.moveToPot(NORTH, n, NORTH);
                }
            return true;
        } // if south wins, take all of north's remaining beans
    
    /// NORTH WINS ///
    
    if (bCopy.beansInPlay(NORTH) == 0)
        {
            for (int n = 1;
                 n !=bCopy.holes()+1;
                 n++)
                {
                    bCopy.moveToPot(SOUTH, n, SOUTH);
                }
        
            return true;
        } // if north wins, take all of south's remaining beans
    
    return false;
} // when one side wins, all of the beans from the other side goes into winning pot

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    if (bCopy.beansInPlay(SOUTH) >= 1
     || bCopy.beansInPlay(NORTH) >= 1)
        {
            over = false;
        }
    
    if (bCopy.beansInPlay(SOUTH) == 0
     || bCopy.beansInPlay(NORTH) == 0)
        {
            over = true;
            
            if (bCopy.beansInPlay(SOUTH) == 0)
            {
                hasWinner = true;
            }
            
            if (bCopy.beansInPlay(NORTH) == 0)
            {
                hasWinner = true;
            }
            
            if (hasWinner)
            {
                if (bCopy.beans(NORTH,0) > bCopy.beans(SOUTH,0))
                {
                    winner = NORTH;
                }
                if (bCopy.beans(NORTH,0) < bCopy.beans(SOUTH,0))
                {
                    winner = SOUTH;
                }
            }
            
            if (bCopy.beans(SOUTH,0)
                == bCopy.beans(NORTH,0))
            {
                hasWinner = false;
            }
        }
} // If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else. Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.

void Game::applySpecialRules()
{
    /// SET STATUS ///
    status(isTheGameOver,isThereAWinner,iAmTheWinner);
    if(isThereAWinner)
    {
        collectRemainingBeans();
        display();
        status(isTheGameOver,isThereAWinner,iAmTheWinner);
        
        if(isThereAWinner)
        {
            if (iAmTheWinner == SOUTH)
            {
                cout << endl;
                cout
                << "The winner is "
                << southName
                << endl;
            }
            if (iAmTheWinner == NORTH)
            {
                cout << endl;
                cout
                << "The winner is "
                << northName
                << endl;
            }
        }
        if(!isThereAWinner)
        {
            cout << endl;
            cout << "It's a tie!";
        }
    }

    
    if (pickASide == 1) // currently north's turn
        {

            /// MULTIPLE TURNS ///
        
            if (endSide == SOUTH && endHole == 0 && bCopy.beansInPlay(SOUTH) != 0)
                {
                    specialEventSwitch = -1; // used to display on board
                    int holeChosenS = southPlayer->chooseMove(bCopy, SOUTH);
                    bCopy.sow(SOUTH, holeChosenS, endSide, endHole);
                    if (!southPlayer->isInteractive())
                    {
                        cout
                        << southName
                        << " chose hole "
                        << holeChosenS
                        << endl;
                    } // announce hole chosen by north
                    pickASide = -1; // ensure south goes again

                } // if bean lands in south's pot, south is allowed another turn
        
            /// CAPTURE ///
            if (endHole!=0)
            {
                if (endSide == SOUTH && beans(SOUTH,endHole) == 1 && beans(NORTH,endHole) >= 1)
                {
                    specialEventSwitch = -10;
                    bCopy.moveToPot(SOUTH, endHole, SOUTH);
                    bCopy.moveToPot(NORTH, endHole, SOUTH);
                    cerr << southName
                    << " captured hole "
                    << endHole << endl;
                }
            }
        }
    
    if (pickASide == -1) // currently south's turn
        {
            
            /// MULTIPLE TURNS ///
        
            if (endSide == NORTH
             && endHole == 0
             && bCopy.beansInPlay(NORTH) != 0)
                {
                    specialEventSwitch=1;
                    int holeChosenN = northPlayer->chooseMove(bCopy, NORTH);
                    bCopy.sow(NORTH, holeChosenN, endSide, endHole);
                    if (!northPlayer->isInteractive())
                    {
                        cout
                        << northName
                        << " chose hole "
                        << holeChosenN
                        << endl;
                    } // announce hole chosen by north
                    pickASide = 1; // ensure north goes again
                }
        
            /// CAPTURE ///
            if (endHole!=0)
            {
                if (endSide == NORTH
                    && beans(NORTH,endHole) == 1
                    && beans(SOUTH,endHole) >= 1)
                {
                    specialEventSwitch=10;
                    bCopy.moveToPot(SOUTH, endHole, NORTH);
                    bCopy.moveToPot(NORTH, endHole, NORTH);
                    cerr << northName << " captured hole " << endHole << endl;
                }
            }
        }
}


bool Game::move()
{
    playerTurnSwitch = pickASide; // -1 for south, 1 for north
    if (bCopy.beansInPlay(SOUTH) <= 0
     || bCopy.beansInPlay(NORTH) <= 0)
        {
            return false;
        }
    else
        {
            if (pickASide == -1)
            {
                // SOUTH MOVES
                // make the move
                int holeChosenS = 0;
                holeChosenS = southPlayer->chooseMove(bCopy, SOUTH);
                bCopy.sow(SOUTH, holeChosenS, endSide, endHole);
                pickASide *= -1; // switch turns
                applySpecialRules(); // capture or take another turn if necessary
                if (!southPlayer->isInteractive())
                {
                    cout
                    << southName
                    << " chose hole "
                    << holeChosenS
                    << endl;
                } // announce hole chosen by south
                specialEventSwitch=0;//reset switch
                return true;
            }
    
            if (pickASide==1)
            {
                // NORTH MOVES
                int holeChosenN = 0;
                holeChosenN = northPlayer->chooseMove(bCopy, NORTH);
                bCopy.sow(NORTH, holeChosenN, endSide, endHole); // make the move
                pickASide *= -1; // switch turns
                applySpecialRules(); // capture or take another turn if necessary
                if (!northPlayer->isInteractive())
                {
                    cout
                    << northName
                    << " chose hole "
                    << holeChosenN
                    << endl;
                } // announce hole chosen by north
                specialEventSwitch=0;//reset switch
                return true;
            }
        }
return false;
} // If the game is over, return false. Otherwise, make a complete move for the player whose turn it is (so that it becomes the other player's turn) and return true. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. If the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening.


void Game::play()
{
    status(isTheGameOver,isThereAWinner,iAmTheWinner);
    
    display(); // show the board
    while(!isTheGameOver)
        {
            move(); // move the beans + set status
            cout << endl;
            cout << "Press Enter to refresh";
            cin.ignore(1000, '\n');
            display(); // refresh
        }
} // Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function.

int Game::beans(Side s, int hole) const
{
    if (hole < 0 || hole > bCopy.holes())
        {
            return -1;
        }
    else
        {
            return bCopy.beans(s,hole);
        }
} // Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.

