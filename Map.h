/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mapp.h
 * Author: RamiroV
 *
 * Created on September 17, 2018, 3:27 PM
 */

#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "Node.h"

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Map_t {

public:
    
    /** An opencv matrix containing the source image */
    Mat _source;
    
    /** The number of tiles on the x-axis */
    int _num_x;
    
    /** The number of tiles on the y-axis */
    int _num_y;
    
    /** The size of each tile on the x-axis */
    int _delta_x;
    
    /** The size of each tile on the y-axis */
    int _delta_y;
    
    /** Array of tiles pointers */
    Tile_t **_tiles;
    
    /** A 2d array of nodes */
    Node_t **_nodes;
    
    /** The total energy of the map */
    double _energy;
    
    /** Constructor */
    Map_t(char *filename, int num_x, int num_y);
    
    /** Copy Constructor */
    Map_t(const Map_t& orig);
    
    /** Destructor */
    virtual ~Map_t();

};

#endif /* MAP_H */

