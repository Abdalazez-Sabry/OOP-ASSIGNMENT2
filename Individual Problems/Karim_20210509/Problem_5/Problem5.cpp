#include<iostream>
#include<vector>
#include <Windows.h>
#define SIZE 10
#define DEAD '-'
#define ALIVE '1'

using namespace std;

class Universe{
    public:
    char grid[SIZE+2][SIZE+2];
    void reset();
    void initalize();
    void display();
    int count_neighbors(int row, int col);
    void next_generation();
    void run(int numOfRuns);
    Universe(){
        initalize();
        // display();
    }
};

void Universe::initalize(){
    reset();
    grid[3][3] = ALIVE;
    grid[4][4] = ALIVE;
    grid[5][2] = ALIVE;
    grid[5][3] = ALIVE;
    grid[5][4] = ALIVE;
}

void Universe::reset(){
    for(int i = 0; i<= SIZE+1; i++){
        for(int j = 0; j<= SIZE+1; j++){
            grid[i][j] = DEAD;
        }
    }
}

void Universe::display(){
    system("cls");
    cout << "------------------------" << endl;
    for(int i = 0; i<= SIZE+1; i++){
        for(int j = 0; j<= SIZE+1; j++){
           cout << grid[i][j] << ' ';
        }
        cout << endl;
    }
}

int Universe::count_neighbors(int row, int col){
    int neighbors = 0;
    for(int i = -1; i <=1; i++){
        for(int j = -1; j<=1; j++){
            if (grid[row+i][col+j] == ALIVE )
            {
                neighbors++;
            }
        }
        
    }
    if (grid[row][col] == ALIVE)
                {
                    neighbors--;
                }
    return neighbors;
}

void Universe::next_generation(){
    char newGrid[SIZE+2][SIZE+2] = {DEAD};
    for(int i = 0; i<= SIZE+1; i++){
        for(int j = 0; j<= SIZE+1; j++){
            newGrid[i][j] = DEAD;
        }
    }

    cout << " new grid " << newGrid[4][4] << endl;
    for(int i = 1; i<= SIZE; i++){
        for(int j = 1; j<= SIZE; j++){
            // cout << "i: " << i << "  j: " << j << ' ' << count_neighbors(i,j) << endl;
            if (grid[i][j] == ALIVE)
            {
                if (count_neighbors(i,j) == 3 || count_neighbors(i,j) == 2)
                {
                    newGrid[i][j] = ALIVE;
                }else{
                    newGrid[i][j] = DEAD;
                }
            }else{
                if (count_neighbors(i,j) == 3)
                {
                    newGrid[i][j] = ALIVE;
                }else{
                    newGrid[i][j] = DEAD;
                }
                
            }
        }
    }
    for(int i = 0; i<= SIZE+1; i++){
        for(int j = 0; j<= SIZE+1; j++){
            grid[i][j] = newGrid[i][j];
        }
    }
    
}

void Universe::run(int numOfRuns){
    for(int i = 0; i< numOfRuns; i++){
        next_generation();
        display();
        Sleep(1000);
    }
}

int main(){
   Universe test;
   test.display();

   int runs = 1;
   
   while(runs > 0){
    cout << "\nEnter the number of runs you want to make -> ";
    cin >> runs;
    test.display();
    test.run(runs);
   }
//    int k;
    // test.display();
    // cin >> k;
    // test.run(5);
    // test.next_generation();
    
    // test.display();

}