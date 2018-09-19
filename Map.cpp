/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mapp.cpp
 * Author: RamiroV
 * 
 * Created on September 17, 2018, 3:27 PM
 */

#include "Map.h"

Map_t::Map_t(char * filename, int num_x, int num_y) {
    
    // load the image
    _source = imread(filename, CV_LOAD_IMAGE_COLOR);
    
    // check if data is valid
    if(!_source.data) {
        cout << "Could not open or find the image" << endl ;
        exit(1);
    }
    
    // check if sizes are valid
    if ( ! (_source.cols % num_x == 0 && _source.rows % num_y == 0)) {
        cout << "Wrongly formated 'num_x' and 'num_y' sizes" << endl ;
        exit(1);
    }
    
    // set accepted values
    _num_x = num_x;
    _num_y = num_y;
    _delta_x = _source.cols / _num_x;
    _delta_y = _source.rows / _num_y;
    
    // tiles
    _tiles = new Tile_t*[_num_x * _num_y];
    
    Tile_t *tile;
    for (int y = 0; y < _num_y; y++) {
        for (int x = 0; x < _num_x; x++) {
            tile = new Tile_t(_source, x * _delta_x + 1, y * _delta_y + 1, _delta_x - 1, _delta_y - 1);
            _tiles[y * _num_x + x] = tile;
        }
    }
    
}

Map_t::Map_t(const Map_t& orig) {
}

Map_t::~Map_t() {
}

