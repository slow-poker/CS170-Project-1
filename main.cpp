#include <iostream>
#include <cmath>
#include "puzzle.h"
#include "tree.h"
#include "node.h"

using namespace std;





int main() {

    cout << "Welcome to fbash006 8 puzzle solver." << endl; 
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl; 

    int puzzleType; 
    int puzzleNum;
    int puzzleArr[3][3];
    int algorithmChoice;
     
    cin >> puzzleType; 

    if (puzzleType == 2){
        cout << "Enter your puzzle, use zero to represent the blank" << endl; 
        cout << "Enter the first row, use space or tabs between numbers" << endl; 

        //user inputs first row of array
        for (int i = 0; i < 3; i++) {
            cin >> puzzleArr[0][i];
        }

        cout << "Enter the second row, use space or tabs between numbers" << endl; 

        //user inputs second row of array
        for (int i = 0; i < 3; i++) {
            cin >> puzzleArr[1][i];
        }

        cout << "Enter the third row, use space or tabs between numbers" << endl; 

        //user inputs third row of array
        for (int i = 0; i < 3; i++) {
            cin >> puzzleArr[2][i];
        }
    }
    
    else if (puzzleType == 1) {
        puzzleArr[0][0] = 1; puzzleArr[0][1] = 4; puzzleArr[0][2] = 3;
        puzzleArr[1][0] = 2; puzzleArr[1][1] = 5; puzzleArr[1][2] = 6;
        puzzleArr[2][0] = 7; puzzleArr[2][1] = 8; puzzleArr[2][2] = 0;
    }

    Puzzle* thePuzzle = new Puzzle(puzzleArr);
    Tree* theTree = new Tree(thePuzzle);

    cout << "Enter your choice of algorithm" << endl; 
    cout << "Uniform Cost Search" << endl;
    cout << "A* with the Misplaced Tile heuristic." << endl;
    cout << "A* with the Euclidean distance heuristic." << endl;

    cin >> algorithmChoice;

    if (algorithmChoice ==1){
        theTree->explore(1);
    }
    else if(algorithmChoice == 2){
        theTree->explore(2);
    }
    else if(algorithmChoice ==3){
        theTree->explore(3);
    }

    cout << "Goal!!!" << endl << endl; 
    cout << "To solve this problem the search algorithm expanded a total of " << "insert nodes here " << " nodes."<< endl; 
    cout << "The maximum number of nodes in the queue at any one time: ";
    cout << "YYY" << endl;
    cout << "The depth of the goal node was"; 
    cout << "ZZZ"<< endl; 


    //double dist = thePuzzle.puzzleEucladian();

    //cout << dist << "\n";

    //thePuzzle.swap(8);

    //thePuzzle.printPuzzle();

    //cout << "number misplaced: " << thePuzzle.misplacedTiles() << endl;
    
    
    return 0;

}

//problem space in tree, 4 children per (child1, child2, child3), include puzzle (.puzzle), h(n) (heurisitc), f(n) (node), .visited (boolean)
//store puzzle in 3D array   (puzzle) 
// store frontier in priorty queue (frontier)


//puzzle and swapping, euclidian distance

//tree, priority queue 

//main : input, output, enter input into puzzle 



