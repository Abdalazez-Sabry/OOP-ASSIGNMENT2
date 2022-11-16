// Class definition for XO_Player class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1
#include<iostream>
#include<random>
#include<iomanip>
#include<algorithm>
#include "XO_Classes.h"
using namespace std;

// Give player a symbol to use in playing
// It can be X or O or others
// This is needed for computer players
// as it does not ask for a name
Player::Player(char symbol) {
    this->symbol = symbol;
}

// Optionally, you can give him ID or order
// Like Player 1 and Player 2
Player::Player (int order, char symbol) {
    cout << "Welcome player " << order << endl;
    cout << "Please enter your name: ";
    cin >> name;
    this->symbol = symbol;
}

// Get desired move: x y (each between 0 and 2)
// Virtual (can change for other player types)
void Player::get_move (int& x, int& y, Board& board) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Give player info as a string
string Player::to_string(){
    return "Player: " + name ;
}

// Get symbol used by player
char Player::get_symbol() {
    return symbol;
}


ComputerPlayer::ComputerPlayer(char sym, string name)
{
    name = name;
    symbol = sym;
}

void ComputerPlayer::get_move(int& x, int& y, Board& board)
{
    int bestVal = -1000;
    x = -1;
    y = -1;
    //cout << "hello" << endl;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            //cout << "hello" << endl;
            if (board.isPlaceFree(i, j))
            {
                //cout << "hello" << endl;
                board.update_board(i, j, 'o');
                //cout << "hello2" << endl;
                int movVal = minimax(board, 0, false);
                //cout << movVal << endl;
                

                //cout << "get move: " << movVal << "-" << bestVal << endl;
                if (movVal > bestVal)
                {
                    x = i;
                    y = j;
                    bestVal = movVal;
                    //cout << "get move: " << x << "-" << y << endl;
                }
                board.update_board(i, j, '0');

            }
            //cout << i << "-" << j << endl;
            
        }
    }
}

int ComputerPlayer::minimax(Board& board, int depth, bool isMax)
{
    //cout << "is mini true" << endl;
    int score = board.is_winner(symbol);
    
    if (score == 10)
    {
        return score - depth;
    }

    if (score == -10)
    {
        return score + depth;
    }
    
    if (!board.isFree())
    {
        return 0;
    }

    if (isMax)
    {
        int best = -1000;

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (board.isPlaceFree(i, j))
                {
                    
                    board.update_board(i, j, 'o');
                    // cout << "best 1: " << best << endl;
                    best = max(best, minimax(board, depth+1, !isMax));
                    //if (i == 0 && j == 2) {cout << "movbest: " << best << endl;}
                    board.update_board(i, j, '0');
                }
            }
        }
        // cout << "best 2: " << best << endl;
        return best;
    }
    else
    {
        int best = 1000;

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (board.isPlaceFree(i, j))
                {
                    board.update_board(i, j, 'x');
                    //cout << "is mini true2" << endl;
                    best = min(best, minimax(board, depth+1, !isMax));
                    //if (i == 0 && j == 2) {cout << "movbestmini: " << best << endl;}
                    board.update_board(i, j, '0');
                }
            }
        }
        return best;
    }
}