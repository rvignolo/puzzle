/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: RamiroV
 *
 * Created on September 17, 2018, 10:18 AM
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include "Map.h"

using namespace cv;
using namespace std;

int main (int argc, char** argv) {
    
    // check number of arguments
    if(argc != 2)
    {
        cout <<" Usage: ./challenge pic_name" << endl;
        return EXIT_FAILURE;
    }
    
    // read the source image as a map
    Map_t map(argv[1], 20, 20);
    
    // solution map
    Map_t solution(map._num_x, map._num_y);
    
    // fill the corners
    int c = 0;
    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 2; x++) {
            solution._tiles[y * (solution._num_y - 1) * solution._num_x + x * (solution._num_x - 1)] = map.getCornerTile(static_cast<TileType>(c));
            c++;
        }
    }
    
    solution.floodFill();
    
    return EXIT_SUCCESS;
}

