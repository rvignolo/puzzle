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
    _picture = imread(filename, CV_LOAD_IMAGE_COLOR);
    
    // check if data is valid
    if(!_picture.data) {
        cout << "Could not open or find the image" << endl ;
        exit(1);
    }
    
    // check if sizes are valid
    if ( ! (_picture.cols % num_x == 0 && _picture.rows % num_y == 0)) {
        cout << "Wrongly formated 'num_x' and 'num_y' sizes" << endl ;
        exit(1);
    }
    
    // set accepted values
    _num_x = num_x;
    _num_y = num_y;
    _delta_x = _picture.cols / _num_x;
    _delta_y = _picture.rows / _num_y;
    
    // tiles
    _tiles = new Tile_t*[_num_x * _num_y];
    
    Tile_t *tile;
    for (int y = 0; y < _num_y; y++) {
        for (int x = 0; x < _num_x; x++) {
            tile = new Tile_t(_picture, x * _delta_x + 1, y * _delta_y + 1, _delta_x - 1, _delta_y - 1);
            _tiles[y * _num_x + x] = tile;
        }
    }
}

Map_t::Map_t(int num_x, int num_y) {
    
    _num_x = num_x;
    _num_y = num_y;
    _tiles = new Tile_t*[_num_x * _num_y];
}

Tile_t *Map_t::getCornerTile(TileType type) {
    
    if (type == INTERNAL || type == UPPER_BORDER || type == LEFT_BORDER || type == RIGHT_BORDER || type == LOWER_BORDER) {
        cout << "search Tile function is only implemented for corner type tiles" << endl ;
        exit(1);
    }
    
    Tile_t *tile;
    for (int y = 0; y < _num_y; y++) {
        for (int x = 0; x < _num_x; x++) {
            tile = _tiles[y * _num_x + x];
            
            if (tile->_type == type)
                return tile;
        }
    }
    
    cout << "corner tile not found" << endl ;
    exit(1);
}

void Map_t::floodFill(Tile_t *current_tile) {
    
    
    
    // 1: search a tile given the current tile neighbours
    
    // 2: si el searched tile es igual al current tile, return 
    
    // 3: si el searched tile no es igual al actual, replace and return
    
    // 4: search to north, south, east and west using the flood fill function
    
}

Map_t::Map_t(const Map_t& orig) {
}

Map_t::~Map_t() {
}

