#include "SodokuBoard.h"
#include <fstream>

int main()
{
    // std::ofstream ofs("puzzle.txt");
    // ofs << ".....6.3.9......5.....386..4..76.59.....89...8..4...7...2..4......65...373......4";
    // ofs.close();
    std::fstream ifs("puzzle.txt");
    SodokuBoard puzzle(ifs);
    puzzle.printBoard();
    while(puzzle.update())
        puzzle.printBoard();
    puzzle.printBoard();
}