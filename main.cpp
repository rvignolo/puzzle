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
    
    Map_t map(argv[1], 20, 20);
    
    // search corners
    
    // search borders
    
    
    
    return EXIT_SUCCESS;
}

