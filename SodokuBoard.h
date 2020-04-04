#include <vector>
#include <fstream>
#include <iostream>
class SodokuBoard
{
private:
    int zeroes;
    int board[9][9]={
        {0, 7, 0,  0, 0, 0,  9, 0, 0},//0   
		{0, 0, 6,  0, 0, 0,  0, 0, 8},//1
		{0, 0, 0,  2, 7, 9,  0, 6, 1},//2

		{5, 0, 0,  0, 0, 6,  3, 0, 0},//3
		{0, 0, 7,  0, 1, 0,  2, 4, 0},//4
		{0, 0, 1,  3, 0, 0,  0, 0, 5},//5'

		{7, 4, 0,  8, 3, 2,  0, 0, 0},//6
		{3, 0, 0,  0, 0, 0,  7, 0, 0},//7
		{0, 0, 2,  0, 0, 0,  0, 5, 0},//8
    };
    bool isNumValid(int, int, int); //given an index and a number, determines if the corrosponding cell can be that number
    int possible[9][9][10]; //contains all possible numbers any given cell can be
    void set(int, int, int); //sets a cell to a number, updates the number of zeroes, and 
    void updateRow(int, int);
    void updateColumn(int, int);
    void updateSector(int, int, int);
    void checkPossibilities();
    void updatePossibilities();
    void checkSector(int,int,int);
    void checkRow(int,int);
    void checkColumn(int,int);
  
    void removePossibility(int, int, int);


public:
    bool update();
    SodokuBoard();
    SodokuBoard(std::fstream&);
    void printBoard();
  

};