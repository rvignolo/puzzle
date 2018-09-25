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
    
    Tile_t *tile;
    for (int y = 0; y < _num_y; y++) {
        for (int x = 0; x < _num_x; x++) {
            tile = new Tile_t(_source_puzzle, x * _delta_x + 1, y * _delta_y + 1, _delta_x - 1, _delta_y - 1);
            _shuffled_tiles[y * _num_x + x] = tile;
        }
    }
}

Tile_t *Map_t::getCornerTile(TileType type) {
    
    if (type == INTERNAL || type == UPPER_BORDER || type == LEFT_BORDER || type == RIGHT_BORDER || type == LOWER_BORDER) {
        cout << "getCornerTile method is only implemented for corner type tiles" << endl ;
        exit(1);
    }
    
    Tile_t *tile;
    for (int y = 0; y < _num_y; y++) {
        for (int x = 0; x < _num_x; x++) {
            tile = _shuffled_tiles[y * _num_x + x];
            
            if (tile->_type == type)
                return tile;
        }
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

void Map_t::floodFill(int x, int y) {
    
    // corners
    if (x == 0 && y == 0) {
        _ordered_tiles[y * _num_x + x] = getCornerTile(UPPER_LEFT_CORNER);
        floodFill(x + 1, y);
    } else if (x == (_num_x - 1) && y == 0) {
        _ordered_tiles[y * _num_x + x] = getCornerTile(UPPER_RIGHT_CORNER);
        floodFill(x, y + 1);
    } else if (x == 0 && y == (_num_y - 1)) {
        _ordered_tiles[y * _num_x + x] = getCornerTile(LOWER_LEFT_CORNER);
        floodFill(x, y - 1);
    } else if (x == (_num_x - 1) && y == (_num_y - 1)) {
        _ordered_tiles[y * _num_x + x] = getCornerTile(LOWER_RIGHT_CORNER);
        floodFill(x - 1, y);
    }
    
    Tile_t *tile;
    Box_t boxes[4];
    // borders
    if (y == 0 && 0 < x < _num_x) {
        boxes[2] = _ordered_tiles[y * _num_x + x - 1]->_boxes[3];
        boxes[3] = _ordered_tiles[y * _num_x + x + 1] != NULL ? _ordered_tiles[y * _num_x + x + 1]->_boxes[2] : NULL;
        tile = getBorderTile(UPPER_BORDER, boxes);
    }
    
    
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
    
    floodFill(0, 0);
    
}

Map_t::Map_t(const Map_t& orig) {
}

Map_t::~Map_t() {
}

