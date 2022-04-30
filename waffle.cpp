
#include <iostream>
#include <unistd.h>
#include <vector>
#include <utility>
using namespace std;

void printGrids(char grid[5][5], char grid2[5][5], int curr_x, int curr_y) {
    for(int i=0; i<5; i++) {
        cout << endl << " ";
        // grid 1 print
        for(int j=0; j<5; j++) {
            if(i==curr_x && j==curr_y) {
                cout << " _";
            }
            else {
                cout << " " << grid[i][j];
            }
        }


        cout << "   |  ";
        // grid 2 print
        for(int j=0; j<5; j++) {
            if(i+5==curr_x && j+5==curr_y) {
                cout << " _";
            }
            else {
                cout << " " << grid2[i][j];
            }
        }
    }
}

void calculateMoves(char grid[5][5], char grid2[5][5], 
        vector<vector<pair<pair<int,int>,pair<int,int> > > > paths) {
    


}

int main() {

    char gridGiven[5][5] = {{'x','x','x','x','x'},
                            {'x',' ','x',' ','x'},
                            {'x','x','x','x','x'},
                            {'x',' ','x',' ','x'},
                            {'x','x','x','x','x'}};

    char gridSolved[5][5] = {{'x','x','x','x','x'},
                             {'x',' ','x',' ','x'},
                             {'x','x','x','x','x'},
                             {'x',' ','x',' ','x'},
                             {'x','x','x','x','x'}};

    // Print visual of what the User is supposed to answer
    for(int i=0; i<10; i++) {
        for(int j=0; j<5; j++) {
            if((i==1&&j==1) || (i==3&&j==1) || 
               (i==1&&j==3) || (i==3&&j==3) || 
               (i==6&&j==1) || (i==8&&j==1) || 
               (i==6&&j==3) || (i==8&&j==3)) {
                continue;
            }
            cout << endl << endl << "--GIVEN GRID--|--SOLVED GRID--";
            printGrids(gridGiven, gridSolved, i,j);
            
            cout << endl << "type \"0\" to restart" << endl;
            cout << endl << "Insert letter at underline:";
            // get input from user
            char letter;
            cin >> letter;
            
            if(i<5) {
                gridGiven[i][j] = letter;
            }
            else {
                gridSolved[i-5][j] = letter;
            }

           
           
           
           
            // RESTART GRID 
            if(letter=='0') {
                cout << endl << "---------RESTARTING---------";
                sleep(1);
                for(int l=0; l<5; l++) {
                    for(int m=0; m<5; m++) {
                        if((m==1&&l==1) || (m==3&&l==1) || 
                           (m==1&&l==3) || (m==3&&l==3) ||
                           (m==6&&l==1) || (m==8&&l==1) || 
                           (m==6&&l==3) || (m==8&&l==3)) {
                                continue;
                            }
                        gridGiven[l][m] = 'x';
                        gridSolved[l][m] = 'x';
                    }
                }
                i=0;
                j=-1;
                continue;
            }
        }
    }
    cout << endl << endl << "How many moves would you like to calculate? (max 15)";
    int moves;
    do {
        cin >> moves;
    } while (moves>15 || moves<0);
    



    cout << endl << endl << "CALCULATING MOVES FOR WAFFLEGAME";
    printGrids(gridGiven, gridSolved,-1,-1);

    vector<vector<pair<pair<int,int>,pair<int,int> > > > paths;
    calculateMoves(gridGiven, gridSolved, paths);

    cout << endl;



    return 0;
}

