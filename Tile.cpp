/*
 * File:   Tile.cpp
 * Author: RamiroV
 *
 */

#include "Tile.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Tile_t::Tile_t(Mat source_puzzle, int id, int xi, int yi, int width, int height) {
    
    // set the id number
    _id = id;
    
    // crop the source puzzle
    _crop = source_puzzle(Rect(xi, yi, width, height));
    
    // fill the pixels
    setlTilePixels(width, height);
    
    // set tile type
    setTileType();
}

Tile_t::Tile_t(TileType type, Vec3b pixel_ul, Vec3b pixel_ur, Vec3b pixel_dl, Vec3b pixel_dr) {
    
    _type = type;
    
    _pixel_ul = pixel_ul;
    _pixel_ur = pixel_ur;
    _pixel_dl = pixel_dl;
    _pixel_dr = pixel_dr;
}

bool Tile_t::operator==(const Tile_t& t2) {
    
    // TODO: analizar igualdad caso por caso! o sea si es internal, si es border up etc
    
    if (_type == t2._type) {
        if(_pixel_ul == t2._pixel_ul && _pixel_ur == t2._pixel_ur && _pixel_dl == t2._pixel_dl && _pixel_dr == t2._pixel_dr)
            return true;
        else
            return false;
    } else 
        return false;
}

bool Tile_t::operator!=(const Tile_t& t2) {
    if (_type != t2._type)
        return true;
    else {
        if(_pixel_ul != t2._pixel_ul || _pixel_ur != t2._pixel_ur || _pixel_dl != t2._pixel_dl || _pixel_dr != t2._pixel_dr)
            return true;
        else
            return false;
    }
}

void Tile_t::setlTilePixels(int width, int height) {
    
    _pixel_ul = _crop.at<Vec3b>(0 * (height - 1), 0 * (width - 1));
    _pixel_ur = _crop.at<Vec3b>(0 * (height - 1), 1 * (width - 1));
    _pixel_dl = _crop.at<Vec3b>(1 * (height - 1), 0 * (width - 1));
    _pixel_dr = _crop.at<Vec3b>(1 * (height - 1), 1 * (width - 1));
}

void Tile_t::setTileType() {
    
    // first we check corners because a corner also satisfies a border condition
    if (isUpperLeftCorner()) {
        _type = UPPER_LEFT_CORNER;
        return;
    } else if (isUpperRightCorner()) {
        _type = UPPER_RIGHT_CORNER;
        return;
    } else if (isLowerLeftCorner()) {
        _type = LOWER_LEFT_CORNER;
        return;
    } else if (isLowerRightCorner()) {
        _type = LOWER_RIGHT_CORNER;
        return;
    } else if (isLeftBorder()) {
        _type = LEFT_BORDER;
        return;
    } else if (isUpperBorder()) {
        _type = UPPER_BORDER;
        return;
    } else if (isRightBorder()) {
        _type = RIGHT_BORDER;
        return;
    } else if (isLowerBorder()) {
        _type = LOWER_BORDER;
        return;
    } else if (isInternal()) {
        _type = INTERNAL;
        return;
    } else {
        cout <<"Image wrongly cropped" << endl;
        exit(1);
    }
}

Tile_t::Tile_t(const Tile_t& orig) {
}

Tile_t::~Tile_t() {
}

