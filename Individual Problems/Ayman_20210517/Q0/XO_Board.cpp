// Class definition for XO_Board class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1
#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
#include "XO_Classes.h"
using namespace std;

// Return true  if move is valid and put it on board
// within board boundaries in empty cell
// Return false otherwise
bool Board::update_board (int x, int y, char mark){
   // Only update if move is valid
   // if (mark == '0')
   // {
   //    board[x][y] = '0';
   //    n_moves--;
   //    return true;
   // }
   if (!(x < 0 || x > 2 || y < 0 || y > 2)) {
      board[x][y] = tolower(mark);
      n_moves++;
      return true;
   // }
   // else
      //return false;
      }
      return false;
   }



// Display the board and the pieces on it
void Board::display_board() {
   for (int i: {0,1,2}) {
      cout << "\n| ";
      for (int j: {0,1,2}) {
         cout << "(" << i << "," << j << ")";
         cout << setw(2) << board [i][j] << " |";
      }
      cout << "\n-----------------------------";
   }
   cout << endl;
}

// Returns true if there is any winner
// either X or O
// Written in a complex way. DO NOT DO LIKE THIS.
int Board::is_winner(char player) {
    for (int row = 0; row<3; row++)
    {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
        {
            if (board[row][0]=='o')
                return 10;
            else if (board[row][0]=='x')
                return -10;
        }
    }
 
    for (int col = 0; col<3; col++)
    {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col])
        {
            if (board[0][col]=='o')
                return 10;
 
            else if (board[0][col]=='x')
                return -10;
        }
    }
 
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0]=='o')
            return 10;
        else if (board[0][0]=='x')
            return -10;
    }
 
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2]=='o')
            return 10;
        else if (board[0][2]=='x')
            return -10;
    }
 
    return 0;
}


// Return true if 9 moves are done and no winner
bool Board::is_draw() {
   //  return (n_moves == 9 && (!is_winner('x') || !is_winner('o')));
   return !(isFree());
}

bool Board::isFree()
{
   for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
			if (isPlaceFree(i, j))
				return true;
	return false;
}

bool Board::isPlaceFree(int x ,int y)
{
   if (board[x][y] != 'o' && board[x][y] != 'x')
      return true;

   return false;
}