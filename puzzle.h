#ifndef __PUZZLE_H__
#define __PUZZLE_H__

class Puzzle{
    private:
    int puzzle[3][3];

    public:
    Puzzle(int[3][3]);
    void printPuzzle();
    double puzzleEucladian();
    int misplacedTiles();
    bool goalPuzzle();
    int goal[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
    void swap(int);

};

#endif