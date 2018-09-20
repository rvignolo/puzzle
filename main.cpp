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
    
    for (int y = 0; y < map._num_y; y++) {
        for (int x = 0; x < map._num_x; x++) {
            
            Tile_t *tile = map._tiles[y * map._num_x + x];
            
            if (tile->_type == UPPER_LEFT_CORNER) {
                string name = "upper_left_corner_" + to_string(y * map._num_x + x) + ".png";
                imwrite(name, tile->_crop);
            }
            
            if (tile->_type == UPPER_RIGHT_CORNER) {
                string name = "upper_right_corner_" + to_string(y * map._num_x + x) + ".png";
                imwrite(name, tile->_crop);
            }
            
            if (tile->_type == LOWER_LEFT_CORNER) {
                string name = "lower_left_corner_" + to_string(y * map._num_x + x) + ".png";
                imwrite(name, tile->_crop);
            }
            
            if (tile->_type == LOWER_RIGHT_CORNER) {
                string name = "lower_right_corner_" + to_string(y * map._num_x + x) + ".png";
                imwrite(name, tile->_crop);
            }
            
            if (tile->_type == LEFT_BORDER) {
                string name = "left_border_" + to_string(y * map._num_x + x) + ".png";
                imwrite(name, tile->_crop);
            }
            
            if (tile->_type == UPPER_BORDER) {
                string name = "upper_border_" + to_string(y * map._num_x + x) + ".png";
                imwrite(name, tile->_crop);
            }
            
            if (tile->_type == RIGHT_BORDER) {
                string name = "rigth_border_" + to_string(y * map._num_x + x) + ".png";
                imwrite(name, tile->_crop);
            }
            
            if (tile->_type == LOWER_BORDER) {
                string name = "lower_border_" + to_string(y * map._num_x + x) + ".png";
                imwrite(name, tile->_crop);
            }
        }
    }
    
    // Mat qr = Mat::zeros(map._source.rows, map._source.cols, map._source.type());
    
    Map_t solution; // falta setear todo aca, el tamanyo y sin source image ( o sea hacer un map limpio basicamente)
    
    solution._tiles[0] = map.searchTile(UPPER_LEFT_CORNER);
    
    for (int y = 0; y < solution._num_y; y++) {
        for (int x = 0; x < solution._num_x; x++) {
            
            Tile_t *tile = solution._tiles[y * solution._num_x + x];
            
            if(tile != nullptr) {
                
            }
            
        }
    }
    
    
    for (int y = 0; y < map._num_y; y++) {
        for (int x = 0; x < map._num_x; x++) {
            
            Tile_t *tile = map._tiles[y * map._num_x + x];
            
            if (tile->_type == UPPER_LEFT_CORNER) {
                
                tile->neighbors[0] = tile->neighbors[1] = tile->neighbors[2] = tile->neighbors[3] = tile->neighbors[5] = nullptr;
                
                map.searchTile(type, box[4])
                        
            }
            
        }
        
    }
    
    
    return EXIT_SUCCESS;
}

