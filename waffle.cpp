
#include <iostream>
#include <unistd.h>
#include <vector>
#include <utility>
using namespace std;

// Print both grids for visual use
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

// returns a vector of (x,y) points that dont match on both grids
vector<pair<int,int> > findIncorrect(char grid[5][5], char grid2[5][5]) {
    vector<pair<int,int> > incorrects;
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            if(grid[i][j] != grid2[i][j]) {
                pair<int,int> point;
                point.first = i;
                point.second = j;
                incorrects.push_back(point);
            }
        }
    }
    return incorrects;
}

// Recursion to find all possible solution paths
void calculateMoves(char grid[5][5], char grid2[5][5], 
        vector<pair<pair<int,int>,pair<int,int> > > paths, 
        int curr_move, int max_move) {
    


    // // debugging prints
    
    // for(unsigned int i=0; i<paths.size(); i++) {
    //     cout << "!@#(" << paths[i].first.first << ", " << paths[i].first.second 
    //             << ")-(" << paths[i].second.first << ", " << paths[i].second.second 
    //             << ")" << endl;
    // }

    // cout << endl << "     on move " << curr_move << endl;
    // for(unsigned int i=0; i<paths.size(); i++) {
    //     cout << "  (" << paths[i].first.first << ", " << paths[i].first.second 
    //             << ")-(" << paths[i].second.first << ", " << paths[i].second.second 
    //             << ")" << endl;
    // }
    // cout << endl << endl;   



    // max number of moves reached.. return
    if(curr_move>max_move) {
        cout << "failed attempt" << endl;
        return;
    }

    vector<pair<int,int> > incorrects;
    incorrects = findIncorrect(grid,grid2);
    // grid is solved.. return
    if(incorrects.size() == 0 ) {
        printGrids(grid, grid2,-1,-1);
        cout << endl << "Solved in " << curr_move << " moves:" << endl;
        for(unsigned int i=0; i<paths.size(); i++) {
            cout << "   (" << paths[i].first.first << ", " << paths[i].first.second 
                 << ") <-> (" << paths[i].second.first << ", " << paths[i].second.second 
                 << ")" << endl;
        }
        cout << endl << endl;
        return;
    }

    // recursion .. tries every possible combination 
    for(unsigned int i=0; i<incorrects.size()-1; i++) {
        for(unsigned int j=i+1; j<incorrects.size(); j++) {
            // Get 2 points that need to be swapped
            pair<int,int> point1 = incorrects[i];
            pair<int,int> point2 = incorrects[j];

            // Swap the characters in the grid
            char temp = grid[point1.first][point1.second];
            grid[point1.first][point1.second] = grid[point2.first][point2.second];
            grid[point2.first][point2.second] = temp;

            // add the swapped points to our path vector to keep track
            pair<pair<int,int>, pair<int,int> > swappedPoints;
            swappedPoints.first = point1;
            swappedPoints.second = point2;
            paths.push_back(swappedPoints);

            // recurse
            calculateMoves(grid, grid2, paths, curr_move+1, max_move);
            paths.pop_back();
        }
    }
    return;
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

    // // Debug code -- comment everything above out
    // char gridGiven[5][5] = {{'B','A','A','A','A'},
    //                         {'C',' ','A',' ','A'},
    //                         {'A','A','A','A','A'},
    //                         {'A',' ','A',' ','A'},
    //                         {'A','A','A','A','A'}};

    // char gridSolved[5][5] = {{'A','A','A','A','B'},
    //                          {'A',' ','A',' ','C'},
    //                          {'A','A','A','A','A'},
    //                          {'A',' ','A',' ','A'},
    //                          {'A','A','A','A','A'}};

    // vector<pair<int,int> > incorrects;
    // incorrects = findIncorrect(gridGiven,gridSolved);
    // cout << incorrects.size() << endl;
    // for(int i=0; i<incorrects.size(); i++) {
    //     cout << "(" << incorrects[i].first << ", " << incorrects[i].second << ") "; 
    // }

    // vector<pair<pair<int,int>,pair<int,int> > > paths;
    // calculateMoves(gridGiven, gridSolved, paths, 0, moves);

    // // END TESTING

    vector<pair<pair<int,int>,pair<int,int> > > paths;
    calculateMoves(gridGiven, gridSolved, paths, 0, moves);

    cout << endl;



    return 0;
}

