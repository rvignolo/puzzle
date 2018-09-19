/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Box.h
 * Author: RamiroV
 *
 * Created on September 17, 2018, 2:55 PM
 */

#ifndef BOX_H
#define BOX_H

#include "Node.h"
#include "Color.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Box_t {

public:
    
    /** The associated node */
    Node_t _node;
    
    /** The total energy of the box (color differences between boxes add 1) */
    double _energy;
    
    /** The color of the box */
    Vec3b _pixel;
    
    Box_t();
    Box_t(const Box_t& orig);
    virtual ~Box_t();
    
    bool isWhite();
    bool isBlack();
    bool isColor(Vec3b color);
};

#endif /* BOX_H */

