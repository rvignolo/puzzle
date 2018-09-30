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
    
    /** The tile type */
    TileType _type;
    
    /** Each corner pixel */
    Vec3b _pixel_ul;
    Vec3b _pixel_ur;
    Vec3b _pixel_dl;
    Vec3b _pixel_dr;
    
    /** Neighbours */
    Tile_t *_left_neighbour;
    Tile_t *_upper_neighbour;
    Tile_t *_right_neighbour;
    Tile_t *_lower_neighbour;
    
    Tile_t(Mat source_puzzle, int xi, int yi, int width, int height);
    Tile_t(const Tile_t& orig);
    virtual ~Tile_t();
    
    void fillTilePixels(int width, int height);
    void setTileType();
    
    int isWhite(Vec3b pixel) { if (pixel.val[0] == 255 && pixel.val[1] == 255 && pixel.val[2] == 255) return 1; else return 0; }
    int isBlack(Vec3b pixel) { if (pixel.val[0] == 0   && pixel.val[1] == 0   && pixel.val[2] == 0  ) return 1; else return 0; }
    int isColor(Vec3b pixel1, Vec3b pixel2) {
        if (pixel1.val[0] == pixel2.val[0] && pixel1.val[1] == pixel2.val[1]  && pixel1.val[2] == pixel2.val[2]) 
            return 1;
        else 
            return 0;
    }
    
    int isLeftBorder() {
        if ((isWhite(_pixel_ul) || isBlack(_pixel_ul)) && (isWhite(_pixel_dl) || isBlack(_pixel_dl)))
            return 1;
        else
            return 0;
    }
    int isUpperBorder() {
        if ((isWhite(_pixel_ul) || isBlack(_pixel_ul)) && (isWhite(_pixel_ur) || isBlack(_pixel_ur)))
            return 1;
        else
            return 0;
    }
    int isRightBorder() {
        if ((isWhite(_pixel_ur) || isBlack(_pixel_ur)) && (isWhite(_pixel_dr) || isBlack(_pixel_dr)))
            return 1;
        else
            return 0;
    }
    int isLowerBorder() {
        if ((isWhite(_pixel_dl) || isBlack(_pixel_dl)) && (isWhite(_pixel_dr) || isBlack(_pixel_dr)))
            return 1;
        else
            return 0;
    }
    int isUpperLeftCorner() { 
        if (isLeftBorder() && isUpperBorder())
            return 1;
        else
            return 0; 
    }
    int isUpperRightCorner() {
        if (isRightBorder() && isUpperBorder()) 
            return 1;
        else
            return 0;
    }
    int isLowerLeftCorner() {
        if (isLeftBorder() && isLowerBorder()) 
            return 1;
        else
            return 0;
    }
    int isLowerRightCorner() {
        if (isRightBorder() && isLowerBorder())
            return 1;
        else
            return 0;
    }
    int isInternal() {
        if ((!isWhite(_pixel_ul) && !isBlack(_pixel_ul)) && (!isWhite(_pixel_ur) && !isBlack(_pixel_ur)) && (!isWhite(_pixel_dl) && !isBlack(_pixel_dl)) && (!isWhite(_pixel_dr) && !isBlack(_pixel_dl)))
            return 1;
        else
            return 0;
    }
};

#endif /* TILE_H */

