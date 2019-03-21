/*
 * File:   Mapp.h
 * Author: RamiroV
 *
 */

#ifndef PUZZLE_H
#define PUZZLE_H

#include "Tile.h"

#include <iostream>
#include <list>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class Puzzle_t {

private:

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

public:

    /** Constructor */
    Puzzle_t(char *filename, int num_x, int num_y);

    /** Copy Constructor */
    Puzzle_t(const Puzzle_t& orig);

    /** Destructor */
    virtual ~Puzzle_t();

    /** sets */
    void setSourcePuzzle(Mat source_puzzle) { _source_puzzle = source_puzzle; }
    void setSolvedPuzzle(Mat solved_puzzle) { _solved_puzzle = solved_puzzle; }
    void setNumX(int num_x) { _num_x = num_x; }
    void setNumY(int num_y) { _num_y = num_y; };
    void setDeltaX(int delta_x) { _delta_x = delta_x; }
    void setDeltaY(int delta_y) { _delta_y = delta_y; }

    /** gets */
    Mat getSourcePuzzle() { return _source_puzzle; }
    Mat getSolvedPuzzle() { return _solved_puzzle; }
    int getNumX() { return _num_x; }
    int getNumY() { return _num_y; }
    int getDeltaX() { return _delta_x; }
    int getDeltaY() { return _delta_y; }
    Tile_t *getCornerTile(TileType type);
    Tile_t *getBorderTile(TileType type, Tile_t *n1, Tile_t *n2, Tile_t *n3);
    Tile_t *getInternalTile(Tile_t *left_neighbour, Tile_t *upper_neighbour, Tile_t *right_neighbour, Tile_t *lower_neighbour);

    void FloodFill(int x, int y);
    void solvePuzzle();
    bool isPuzzleSolved();
};

#endif /* PUZZLE_H */
