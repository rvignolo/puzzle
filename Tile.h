/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tile.h
 * Author: RamiroV
 *
 * Created on September 17, 2018, 2:49 PM
 */

#ifndef TILE_H
#define TILE_H

#include <opencv2/core/core.hpp>
#include <list>
#include "Box.h"

using namespace std;
using namespace cv;

enum TileType {
    UPPER_LEFT_CORNER = 0,
    UPPER_RIGHT_CORNER = 1,
    LOWER_LEFT_CORNER = 2,
    LOWER_RIGHT_CORNER = 3,
    UPPER_BORDER = 4,
    LEFT_BORDER = 5,
    RIGHT_BORDER = 6,
    LOWER_BORDER = 7,
    INTERNAL = 8
};

class Tile_t {
    
public:
    
    /** An opencv matrix containing the cropped tile */
    Mat _crop;
    
    /** Each corner box */
    Box_t _boxes[4];
    
    /** The tile type */
    TileType _type;
    
    /** The tile neighbors */
    Tile_t *neighbors[8];
    
    /** The azimuthal angle */
    double _theta;
    
    /** The total energy of the tile */
    double _energy;
    
    Tile_t(Mat source, int xi, int yi, int width, int height);
    Tile_t(const Tile_t& orig);
    virtual ~Tile_t();
    
    void fillBoxes(int width, int height);
    void setTileType();
};

#endif /* TILE_H */

