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

#include <iostream>
#include <list>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class Map_t {

public:
    
    /** An opencv matrix containing the source puzzle */
    Mat _source_puzzle;
    
    /** An opencv matrix containing the solved puzzle */
    Mat _solved_puzzle;
    
    /** The number of tiles on the x-axis */
    int _num_x;
    
    /** The number of tiles on the y-axis */
    int _num_y;
    
    /** The size of each tile on the x-axis */
    int _delta_x;
    
    /** The size of each tile on the y-axis */
    int _delta_y;
    
    /** Array of tiles pointers: shuffled tiles are the input and ordered tiles
     *  are the solution (output) of the problem */
    Tile_t **_shuffled_tiles;
    Tile_t **_ordered_tiles;
    
    /** A dynamically sized vector of tiles remaining in the _shuffled_tiles */
    list<Tile_t *> _remaining_tiles;
    
    Tile_t *getCornerTile(TileType type);
    Tile_t *getBorderTile(TileType type, Tile_t *n1, Tile_t *n2, Tile_t *n3);
    Tile_t *getInternalTile(Tile_t *left_neighbour, Tile_t *upper_neighbour, Tile_t *right_neighbour, Tile_t *lower_neighbour);
    
    bool isPuzzlecompleted(Tile_t **tiles);
    
    void FloodFill(int x, int y);
    void solvePuzzle();
    
    /** Constructor */
    Map_t(char *filename, int num_x, int num_y);
    
    /** Copy Constructor */
    Map_t(const Map_t& orig);
    
    /** Destructor */
    virtual ~Map_t();

};

#endif /* MAP_H */

