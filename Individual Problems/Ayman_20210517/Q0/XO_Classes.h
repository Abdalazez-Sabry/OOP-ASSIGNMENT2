// Class definition for XO game classes
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1
#ifndef _XO_CLASSES_H
#define _XO_CLASSES_H

#include <iostream>

using namespace std;

// This class represents a 3 x 3 board
// used in X_O game

class Board {
protected:
   char board[3][3] = {{0}};
   int  n_moves = 0;

public:
   bool isFree();
   bool isPlaceFree(int x ,int y);
   // Return true  if move is valid and put it on board
   // within board boundaries in empty cell
   // Return false otherwise
   bool update_board (int x, int y, char symbol);
   // Returns true if there is any winner
   // either X or O
   // Written in a complex way. DO NOT DO LIKE THIS.
   int is_winner(char);
   // Return true if 9 moves are done and no winner
   bool is_draw();
   // Display the board and the pieces on it
   void display_board();
};

///////////////////////////////////////////
// This class represents a player who has
// a name and a symbol to put on board
class Player {
    protected:
        string name;
        char symbol;
    public:
        Player() {symbol = 'x';};
        // Two constructors to initiate player
        // Give player a symbol to use in playing
        // It can be X or O or others
        // Optionally, you can give him ID or order
        // Like Player 1 and Player 2
        Player (char symbol); // Needed for computer players
        Player (int order, char symbol);
        // Get desired move: x y (each between 0 and 2)
        // Virtual (can change for other player types)
        virtual void get_move(int& x, int& y, Board& board);
        // Give player info as a string
        string to_string();
        // Get symbol used by player
        char get_symbol();
};

class ComputerPlayer : public Player
{
private:
    
    int minimax(Board& board, int depth, bool isMax);
public:
    ComputerPlayer(char sym, string name);
    void get_move(int& x, int& y, Board& board);    
    
};






///////////////////////////////////////////
// This class represents the engine that runs
// X-O games and gives players turns, sees if
// either of them won or it is draw.
// It has one method to start and run the game.
class GameManager {
    public:
        void run();
        // This method creates board and players
        // It displays board
        // While True
        //   For each player
        //      It takes a valid move as x, y pair (between 0 - 2)
        //      It updates board and displays otit
        //      If winner, declare so and end
        //      If draw, declare so and end

};

#endif
