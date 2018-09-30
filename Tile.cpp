/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tile.cpp
 * Author: RamiroV
 * 
 * Created on September 17, 2018, 2:49 PM
 */

#include "Tile.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Tile_t::Tile_t(Mat source_puzzle, int xi, int yi, int width, int height) {
    
    // crop the source puzzle
    _crop = source_puzzle(Rect(xi, yi, width, height));
    
    // fill the pixels
    fillTilePixels(width, height);
    
    // set tile type
    setTileType();
}

void Tile_t::fillTilePixels(int width, int height) {
    
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

