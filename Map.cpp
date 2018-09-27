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
    _source_puzzle = imread(filename, CV_LOAD_IMAGE_COLOR);
    
    // check if data is valid
    if(!_source_puzzle.data) {
        cout << "Could not open or find the puzzle image" << endl ;
        exit(1);
    }
    
    // check if sizes are valid
    if ( ! (_source_puzzle.cols % num_x == 0 && _source_puzzle.rows % num_y == 0)) {
        cout << "Wrongly formated 'num_x' and 'num_y' sizes" << endl ;
        exit(1);
    }
    
    // set accepted values
    _num_x = num_x;
    _num_y = num_y;
    _delta_x = _source_puzzle.cols / _num_x;
    _delta_y = _source_puzzle.rows / _num_y;
    
    // tiles
    _shuffled_tiles = new Tile_t*[_num_x * _num_y]();
    _ordered_tiles = new Tile_t*[_num_x * _num_y]();
    
    // fill the shuffled tiles
    for (int y = 0; y < _num_y; y++) {
        for (int x = 0; x < _num_x; x++) {
            _shuffled_tiles[y * _num_x + x] = new Tile_t(_source_puzzle, x * _delta_x + 1, y * _delta_y + 1, _delta_x - 1, _delta_y - 1);
            _remaining_tiles.push_back(_shuffled_tiles[y * _num_x * x]);
        }
    }
    
    // fill neighbours
    for (int y = 0; y < _num_y; y++) {
        for (int x = 0; x < _num_x; x++) {
            
            int left_index =  y * _num_x + x - 1;
            int upper_index = y * _num_x + x - _num_x;
            int right_index = y * _num_x + x + 1;
            int lower_index = y * _num_x + x + _num_x;
            
            _shuffled_tiles[y * _num_x + x]->_left_neighbour  = 0 <= left_index  < _num_x * _num_y - 1 ? _shuffled_tiles[left_index]  : NULL;
            _shuffled_tiles[y * _num_x + x]->_upper_neighbour = 0 <= upper_index < _num_x * _num_y - 1 ? _shuffled_tiles[upper_index] : NULL;
            _shuffled_tiles[y * _num_x + x]->_right_neighbour = 0 <= right_index < _num_x * _num_y - 1 ? _shuffled_tiles[right_index] : NULL;
            _shuffled_tiles[y * _num_x + x]->_lower_neighbour = 0 <= lower_index < _num_x * _num_y - 1 ? _shuffled_tiles[lower_index] : NULL;
        }
    }
}

Tile_t *Map_t::getCornerTile(TileType type) {
    
    if (type == INTERNAL || type == UPPER_BORDER || type == LEFT_BORDER || type == RIGHT_BORDER || type == LOWER_BORDER) {
        cout << "getCornerTile method is only implemented for corner type tiles" << endl ;
        exit(1);
    }
    
    for (list<Tile_t *>::iterator tile = _remaining_tiles.begin(); tile != _remaining_tiles.end(); tile++) {
        if ((*tile)->_type == type)
            return tile;
    }
    
    cout << "corner tile not found" << endl ;
    exit(1);
}

Tile_t *Map_t::getBorderTile(TileType type, Box_t boxes[4]) {
    
    if (type == INTERNAL || type == UPPER_LEFT_CORNER || type == UPPER_RIGHT_CORNER || type == LOWER_LEFT_CORNER || type == LOWER_RIGHT_CORNER) {
        cout << "getBorderTile method is only implemented for border type tiles" << endl ;
        exit(1);
    }
    
    Tile_t *tile, *tile1, *tile2, *tile3;
    tile1 = tile2 = tile3 = NULL;
    
    for (int y = 0; y < _num_y; y++) {
        for (int x = 0; x < _num_x; x++) {
            tile = _shuffled_tiles[y * _num_x + x];
            
            switch(type) {
                case UPPER_BORDER:
                    if (tile->_type == UPPER_BORDER && tile->_boxes[2].isColor(boxes[2]._pixel) && tile->_boxes[3].isColor(boxes[3]._pixel))
                        tile1 = tile;
                    else if (tile->_type == UPPER_BORDER && tile->_boxes[2].isColor(boxes[2]._pixel))
                        tile2 = tile;
                    else if (tile->_type == UPPER_BORDER && tile->_boxes[3].isColor(boxes[3]._pixel))
                        tile3 = tile;
                    break;
                case LEFT_BORDER:
                    if (tile->_type == LEFT_BORDER && tile->_boxes[1].isColor(boxes[1]._pixel) && tile->_boxes[3].isColor(boxes[3]._pixel))
                        tile1 = tile;
                    else if (tile->_type == LEFT_BORDER && tile->_boxes[1].isColor(boxes[1]._pixel))
                        tile2 = tile;
                    else if (tile->_type == LEFT_BORDER && tile->_boxes[3].isColor(boxes[3]._pixel))
                        tile3 = tile;
                    break;
                case RIGHT_BORDER:
                    if (tile->_type == RIGHT_BORDER && tile->_boxes[0].isColor(boxes[0]._pixel) && tile->_boxes[2].isColor(boxes[2]._pixel))
                        tile1 = tile;
                    else if (tile->_type == RIGHT_BORDER && tile->_boxes[0].isColor(boxes[0]._pixel))
                        tile2 = tile;
                    else if (tile->_type == RIGHT_BORDER && tile->_boxes[2].isColor(boxes[2]._pixel))
                        tile3 = tile;
                    break;
                case LOWER_BORDER:
                    if (tile->_type == LOWER_BORDER && tile->_boxes[1].isColor(boxes[1]._pixel) && tile->_boxes[2].isColor(boxes[2]._pixel))
                        tile1 = tile;
                    else if (tile->_type == LOWER_BORDER && tile->_boxes[1].isColor(boxes[1]._pixel))
                        tile2 = tile;
                    else if (tile->_type == LOWER_BORDER && tile->_boxes[2].isColor(boxes[2]._pixel))
                        tile3 = tile;
                    break;
            }
        }
    }
    
    if (tile1 == NULL && tile2 == NULL && tile3 == NULL) {
        cout << "getBorderTile method did not found a matching Tile" << endl ;
        exit(1);
    }
    
    return tile1 != NULL ? tile1 : tile2 != NULL ? tile2 : tile3;
}

int Map_t::FloodFill(int x, int y) {
    
    // outside the domain
    if (x < 0 || x >= _num_x || y < 0 || y >= _num_y)
        return 0;
    
    // get the current tile
    Tile_t *ordered_tile = _ordered_tiles[y * _num_x + x];
    
    // handle the searched tile
    Tile_t *searched_tile;
    
    // corners
    if (x == 0 && y == 0)
        searched_tile = getCornerTile(UPPER_LEFT_CORNER);
    else if (x == (_num_x - 1) && y == 0)
        searched_tile = getCornerTile(UPPER_RIGHT_CORNER);
    else if (x == 0 && y == (_num_y - 1))
        searched_tile = getCornerTile(LOWER_LEFT_CORNER);
    else if (x == (_num_x - 1) && y == (_num_y - 1))
        searched_tile = getCornerTile(LOWER_RIGHT_CORNER);
    
    // borders
    if (y == 0){
        
        Tile_t *left_neighbor = ordered_tile.getLeftNeighbor();
        
    }
    
    
    
    // borders
    if (y == 0 && 0 < x < _num_x) {
        boxes[2] = _ordered_tiles[y * _num_x + x - 1]->_boxes[3];
        boxes[3] = _ordered_tiles[y * _num_x + x + 1] != NULL ? _ordered_tiles[y * _num_x + x + 1]->_boxes[2] : NULL;
        searched_tile = getBorderTile(UPPER_BORDER, boxes);
    }
    
    // internals
    
    
    if (ordered_tile != NULL && ordered_tile != searched_tile)
        ordered_tile = searched_tile;
    
    
    // 1: search a tile given the current tile neighbours
    
    // 2: si el searched tile es igual al current tile, return 
    
    // 3: si el searched tile no es igual al actual, replace and return
    
    // 4: search to north, south, east and west using the flood fill function
    
}

void Map_t::solvePuzzle() {
    
    // fill the corners
    int c = 0;
    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 2; x++) {
            _ordered_tiles[y * (_num_y - 1) * _num_x + x * (_num_x - 1)] = getCornerTile(static_cast<TileType>(c));
            c++;
        }
    }
    
    FloodFill(0, 0);
    
}

Map_t::Map_t(const Map_t& orig) {
}

Map_t::~Map_t() {
}

