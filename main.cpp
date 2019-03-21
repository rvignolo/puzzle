/*
 * File:   main.c
 * Author: RamiroV
 *
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include "Puzzle.h"

using namespace cv;
using namespace std;

int main (int argc, char** argv) {

    // check number of arguments
    if(argc != 2) {
        cout <<" Usage: ./challenge pic_name" << endl;
        return EXIT_FAILURE;
    }

    // read the source puzzle
    Puzzle_t puzzle(argv[1], 20, 20);
    
    // solve the puzzle
    puzzle.solvePuzzle();

    return EXIT_SUCCESS;
}
