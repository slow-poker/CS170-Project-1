#include "puzzle.h"
#include <iostream>
#include <string.h>
#include <cmath>


using namespace std;


Puzzle::Puzzle(int nums[3][3]){
     for(int row = 0; row < 3; row++){
        for(int col = 0; col < 3; col++){
            puzzle[row][col] = nums[row][col];
        }
    }
}

double Puzzle::puzzleEucladian( ){
    double euclidianDistance = 0;
    if (goalPuzzle() == true){
        return 0;
    } else {
        int h;
        int w;

        int goalH;
        int goalW;
        for(int value = 1; value < 9; value++){
            for(int row = 0; row < 3; row++){
                for(int col = 0; col < 3; col++){
                    if(puzzle[row][col] == value){
                        h = row;
                        w = col;
                    }
                    if(goal[row][col] == value){
                        goalH = row;
                        goalW = col;
                    }
                }
            }
            double total = sqrt(pow((goalH-h),2) + pow((goalW-w),2));
            euclidianDistance += total;
        }
    }
    return euclidianDistance;
}

int Puzzle::misplacedTiles(){
    int count = 0;
    for(int row = 0; row < 3; row++){
        for(int col = 0; col < 3; col++){
            if(puzzle[row][col] != goal[row][col] && puzzle[row][col] != 0){
                count++;
            }
        }
    }
    return count;
}

bool Puzzle::goalPuzzle(){

    if(puzzle == goal){
         return true;
    } else {
        return false;
    }
}

void Puzzle::printPuzzle(){
    for(int row = 0; row < 3; row++){
        for(int col = 0; col < 3; col++){
            cout << this->puzzle[row][col] << " ";
        }
        cout << endl;
    }
}

void Puzzle::swap(int number1){ //can add a valid funcion to check whether swap move is valid or not
    int tempR;
    int tempC;
    for(int row = 0; row < 3; row++){
        for(int col = 0; col < 3; col++){
            if(puzzle[row][col] == number1){
                tempR = row;
                tempC = col;
            } else if (puzzle[row][col] == 0){
                puzzle[row][col] = number1;
            }
        }
    }
    puzzle[tempR][tempC] = 0;
}
