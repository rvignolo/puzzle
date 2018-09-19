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

Tile_t::Tile_t(Mat source, int xi, int yi, int width, int height) {
    
    // Mat croppedRef(source, Rect(xi, yi, width, height));
    // croppedRef.copyTo(_crop);
    
    _crop = source(Rect(xi, yi, width, height));
    
    // boxes
    int b = 0;
    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 2; x++) {
            // _boxes[b]._pixel = _crop.at<Vec3b>(Point(x * width, y * height));
            _boxes[b]._pixel = _crop.at<Vec3b>(y * (height - 1), x * (width - 1));
            b++;
        }
    }
    
    
    
}

Tile_t::Tile_t(const Tile_t& orig) {
}

Tile_t::setTileType() {
    
    int num = 0;
    for (int b = 0; b < 4; b++) {
            if (_boxes[b].isWhite() || _boxes[b].isBlack())
                num++;
    }
    
}

Tile_t::~Tile_t() {
}

