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

using namespace std;
using namespace cv;

enum TileType {
    UPPER_LEFT_CORNER,
    UPPER_RIGHT_CORNER,
    LOWER_LEFT_CORNER,
    LOWER_RIGHT_CORNER,
    UPPER_BORDER,
    LEFT_BORDER,
    RIGHT_BORDER,
    LOWER_BORDER,
    INTERNAL
};

class Tile_t {
    
public:
    
    /** An id number */
    int _id;
    
    /** An opencv matrix containing the cropped tile */
    Mat _crop;
    
    /** The tile type */
    TileType _type;
    
    /** Each corner pixel */
    Vec3b _pixel_ul;
    Vec3b _pixel_ur;
    Vec3b _pixel_dl;
    Vec3b _pixel_dr;
    
    Tile_t(Mat source_puzzle, int id, int xi, int yi, int width, int height);
    Tile_t(TileType type, Vec3b pixel_ul, Vec3b pixel_ur, Vec3b pixel_dl, Vec3b pixel_dr);
    Tile_t(const Tile_t& orig);
    virtual ~Tile_t();
    
    void fillTilePixels(int width, int height);
    void setTileType();
    
    bool isWhite(Vec3b pixel) { if (pixel.val[0] == 255 && pixel.val[1] == 255 && pixel.val[2] == 255) return true; else return false; }
    bool isBlack(Vec3b pixel) { if (pixel.val[0] == 0   && pixel.val[1] == 0   && pixel.val[2] == 0  ) return true; else return false; }
    bool isColor(Vec3b pixel1, Vec3b pixel2) {
        if (pixel1.val[0] == pixel2.val[0] && pixel1.val[1] == pixel2.val[1]  && pixel1.val[2] == pixel2.val[2]) 
            return true;
        else 
            return false;
    }
    
    bool isLeftBorder() {
        if ((isWhite(_pixel_ul) || isBlack(_pixel_ul)) && (isWhite(_pixel_dl) || isBlack(_pixel_dl)))
            return true;
        else
            return false;
    }
    bool isUpperBorder() {
        if ((isWhite(_pixel_ul) || isBlack(_pixel_ul)) && (isWhite(_pixel_ur) || isBlack(_pixel_ur)))
            return true;
        else
            return false;
    }
    bool isRightBorder() {
        if ((isWhite(_pixel_ur) || isBlack(_pixel_ur)) && (isWhite(_pixel_dr) || isBlack(_pixel_dr)))
            return true;
        else
            return false;
    }
    bool isLowerBorder() {
        if ((isWhite(_pixel_dl) || isBlack(_pixel_dl)) && (isWhite(_pixel_dr) || isBlack(_pixel_dr)))
            return true;
        else
            return false;
    }
    bool isUpperLeftCorner() { 
        if (isLeftBorder() && isUpperBorder())
            return true;
        else
            return false; 
    }
    bool isUpperRightCorner() {
        if (isRightBorder() && isUpperBorder())
            return true;
        else
            return false;
    }
    bool isLowerLeftCorner() {
        if (isLeftBorder() && isLowerBorder())
            return true;
        else
            return false;
    }
    bool isLowerRightCorner() {
        if (isRightBorder() && isLowerBorder())
            return true;
        else
            return false;
    }
    bool isInternal() {
        if ((!isWhite(_pixel_ul) && !isBlack(_pixel_ul)) && (!isWhite(_pixel_ur) && !isBlack(_pixel_ur)) && (!isWhite(_pixel_dl) && !isBlack(_pixel_dl)) && (!isWhite(_pixel_dr) && !isBlack(_pixel_dl)))
            return true;
        else
            return false;
    }
    
    bool operator==(Tile_t t2);
    bool operator!=(Tile_t t2);
};

#endif /* TILE_H */

