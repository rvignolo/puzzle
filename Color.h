/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Color.h
 * Author: RamiroV
 *
 * Created on September 17, 2018, 3:08 PM
 */

#ifndef COLOR_H
#define COLOR_H

class Color_t {

public:
    
    /** The color in rgb format */
    int R, G, B;
    
    Color_t();
    Color_t(const Color_t& orig);
    virtual ~Color_t();
};

#endif /* COLOR_H */

