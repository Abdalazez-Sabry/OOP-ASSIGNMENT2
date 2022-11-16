// Class definition for XO_GameManager class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1

#include <iostream>
#include "XO_Classes.h"
using namespace std;
void GameManager::run() {
    Board x_o;
    int x, y, choice;
    Player* players[2];
    players[1] = new Player (1, 'x');
    cout << "Press 1 if you want to play with computer: ";
    cin >> choice;
    if (choice != 1)
        players[0] = new Player (2, 'o');
    else
        //Player pointer points to child
        players[0] = new ComputerPlayer ('o', "Player1");

    x_o.display_board();
    while (true) {
        for (int i:{0,1}) {
            players[i]->get_move(x, y, x_o);
            //cout << "hello" << endl;
            //cout << "gmae manager " << x << "-" << y << endl;
            while (!x_o.update_board (x, y, players[i]->get_symbol())){
                players[i]->get_move(x, y, x_o);
            }
            x_o.display_board();
            if (x_o.is_winner(players[i]->get_symbol())){
                cout  << players[i]->to_string() << " wins\n";
                return;
            }
            if (x_o.is_draw()){
                cout << "Draw!\n";
                return;
            }
        }
    }
}
