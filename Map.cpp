/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mapp.cpp
 * Author: RamiroV
 * 
 * Created on September 17, 2018, 3:27 PM
 */

#include "Map.h"
#include <list>

using namespace std;
using namespace cv;

Map_t::Map_t(char * filename, int num_x, int num_y) {
    
    // load the image
    _source_puzzle = imread(filename, CV_LOAD_IMAGE_COLOR);
    
    // check if data is valid
    if(!_source_puzzle.data) {
        cout << "Could not open or find the puzzle image" << endl ;
        exit(1);
    }
    
    // check if sizes are valid
    if ( ! (_source_puzzle.cols % num_x == 0 && _source_puzzle.rows % num_y == 0)) {
        cout << "Wrongly formated 'num_x' and 'num_y' sizes" << endl ;
        exit(1);
    }
    
    // set accepted values
    _num_x = num_x;
    _num_y = num_y;
    _delta_x = _source_puzzle.cols / _num_x;
    _delta_y = _source_puzzle.rows / _num_y;
    
    // init tiles
    _shuffled_tiles = new Tile_t*[_num_x * _num_y]();
    _ordered_tiles  = new Tile_t*[_num_x * _num_y]();
    
    // fill the shuffled tiles
    for (int y = 0; y < _num_y; y++) {
        for (int x = 0; x < _num_x; x++) {
            _shuffled_tiles[y * _num_x + x] = new Tile_t(_source_puzzle, x * _delta_x + 1, y * _delta_y + 1, _delta_x - 1, _delta_y - 1);
            _remaining_tiles.push_back(_shuffled_tiles[y * _num_x * x]);
        }
    }
}

Tile_t *Map_t::getCornerTile(TileType type) {
    
    if (type == INTERNAL || type == UPPER_BORDER || type == LEFT_BORDER || type == RIGHT_BORDER || type == LOWER_BORDER) {
        cout << "getCornerTile method is only implemented for corner type tiles" << endl ;
        exit(1);
    }
    
    for (list<Tile_t *>::iterator tile = _remaining_tiles.begin(); tile != _remaining_tiles.end(); tile++) {
        if ((*tile)->_type == type)
            return (*tile);
    }
    
    cout << "corner tile not found" << endl ;
    exit(1);
}

Tile_t *Map_t::getBorderTile(TileType type, Tile_t *n1, Tile_t *n2, Tile_t *n3) {
    
    if (type == INTERNAL || type == UPPER_LEFT_CORNER || type == UPPER_RIGHT_CORNER || type == LOWER_LEFT_CORNER || type == LOWER_RIGHT_CORNER) {
        cout << "getBorderTile method is only implemented for border type tiles" << endl ;
        exit(1);
    }
    
    Tile_t *searched_tile;
    
    Vec3b pixel_ul;
    Vec3b pixel_ur;
    Vec3b pixel_dl;
    Vec3b pixel_dr;
    
    // initialize them as blacks or whites
    for (int i = 0; i < 3; i++) {
        pixel_ul.val[i] = 0;
        pixel_ur.val[i] = 0;
        pixel_dl.val[i] = 0;
        pixel_dr.val[i] = 0;
    }
    
    int incomplete;
    int complete;
    int perfect_match = 0;
    int soft_match = 0;
    
    // set the pixels
    switch(type) {
        case LEFT_BORDER:
            
            if (n1 != NULL && n2 != NULL && n3 != NULL) {
                
                // checks
                if (n1->_pixel_dr != n2->_pixel_ul) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }
                
                if (n2->_pixel_dl != n3->_pixel_ur) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }
                
                // sets
                pixel_ur = n2->_pixel_ul;
                pixel_dr = n2->_pixel_dl;
                
                complete = 1;
                
            } else if (n1 != NULL && n2 != NULL && n3 == NULL) {
                
                // checks
                if (n1->_pixel_dr != n2->_pixel_ul) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }
                
                // sets
                pixel_ur = n2->_pixel_ul;
                pixel_dr = n2->_pixel_dl;
                
                complete = 1;
                
            } else if (n1 != NULL && n2 == NULL && n3 != NULL) {
                
                // sets
                pixel_ur = n1->_pixel_dr;
                pixel_dr = n3->_pixel_ur;
                
                complete = 1;
                
            } else if (n1 == NULL && n2 != NULL && n3 != NULL) {
                
                // cheks
                if (n2->_pixel_dl != n3->_pixel_ur) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }
                
                // sets
                pixel_ur = n2->_pixel_ul;
                pixel_dr = n2->_pixel_dl;
                
                complete = 1;
                
            } else if (n1 != NULL && n2 == NULL && n3 == NULL) {
                
                // sets
                pixel_ur = n1->_pixel_dr;
                
                incomplete = 1;
                
            } else if (n1 == NULL && n2 != NULL && n3 == NULL) {
                
                // sets
                pixel_ur = n2->_pixel_ul;
                pixel_dr = n2->_pixel_dl;
                
                complete = 1;
                
            } else if (n1 == NULL && n2 == NULL && n3 != NULL) {
                
                // sets
                pixel_dr = n3->_pixel_ur;
                
                incomplete = 1;
                
            } else if (n1 == NULL && n2 == NULL && n3 == NULL) {
                return NULL;
            }
            break;
            
        case UPPER_BORDER:
            
            if (n1 != NULL && n2 != NULL && n3 != NULL) {
                
                // checks
                if (n1->_pixel_dr != n3->_pixel_ul) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }
                
                if (n2->_pixel_dl != n3->_pixel_ur) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }
                
                // sets
                pixel_dl = n3->_pixel_ul;
                pixel_dr = n3->_pixel_ur;
                
                complete = 1;
                
            } else if (n1 != NULL && n2 != NULL && n3 == NULL) {
                
                // sets
                pixel_dl = n1->_pixel_dr;
                pixel_dr = n2->_pixel_dl;
                
                complete = 1;
                
            } else if (n1 != NULL && n2 == NULL && n3 != NULL) {
                
                // checks
                if (n1->_pixel_dr != n3->_pixel_ul) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }
                
                // sets
                pixel_dl = n3->_pixel_ul;
                pixel_dr = n3->_pixel_ur;
                
                complete = 1;
                
            } else if (n1 == NULL && n2 != NULL && n3 != NULL) {
                
                // cheks
                if (n2->_pixel_dl != n3->_pixel_ur) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }
                
                // sets
                pixel_dl = n3->_pixel_ul;
                pixel_dr = n3->_pixel_ur;
                
                complete = 1;
                
            } else if (n1 != NULL && n2 == NULL && n3 == NULL) {
                
                // sets
                pixel_dl = n1->_pixel_dr;
                
                incomplete = 1;
                
            } else if (n1 == NULL && n2 != NULL && n3 == NULL) {
                
                // sets
                pixel_dr = n2->_pixel_dl;
                
                incomplete = 1;
                
            } else if (n1 == NULL && n2 == NULL && n3 != NULL) {
                
                // sets
                pixel_dl = n3->_pixel_ul;
                pixel_dr = n3->_pixel_ur;
                
                complete = 1;
                
            } else if (n1 == NULL && n2 == NULL && n3 == NULL) {
                return NULL;
            }
            break;
            
        case RIGHT_BORDER:
            
            if (n1 != NULL && n2 != NULL && n3 != NULL) {
                
                // checks
                if (n1->_pixel_ur != n2->_pixel_dl) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }
                
                if (n1->_pixel_dr != n3->_pixel_ul) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }
                
                // sets
                pixel_ul = n1->_pixel_ur;
                pixel_dl = n1->_pixel_dr;
                
                complete = 1;
                
            } else if (n1 != NULL && n2 != NULL && n3 == NULL) {
                
                // checks
                if (n1->_pixel_ur != n2->_pixel_dl) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }
                
                // sets
                pixel_ul = n1->_pixel_ur;
                pixel_dl = n1->_pixel_dr;
                
                complete = 1;
                
            } else if (n1 != NULL && n2 == NULL && n3 != NULL) {
                
                // checks
                if (n1->_pixel_dr != n3->_pixel_ul) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }
                
                // sets
                pixel_ul = n1->_pixel_ur;
                pixel_dl = n1->_pixel_dr;
                
                complete = 1;
                
            } else if (n1 == NULL && n2 != NULL && n3 != NULL) {
                
                // sets
                pixel_ul = n2->_pixel_dl;
                pixel_dl = n3->_pixel_ul;
                
                complete = 1;
                
            } else if (n1 != NULL && n2 == NULL && n3 == NULL) {
                
                // sets
                pixel_ul = n1->_pixel_ur;
                pixel_dl = n1->_pixel_dr;
                
                complete = 1;
                
            } else if (n1 == NULL && n2 != NULL && n3 == NULL) {
                
                // sets
                pixel_ul = n2->_pixel_dl;
                
                incomplete = 1;
                
            } else if (n1 == NULL && n2 == NULL && n3 != NULL) {
                
                // sets
                pixel_dl = n3->_pixel_ul;
                
                incomplete = 1;
                
            } else if (n1 == NULL && n2 == NULL && n3 == NULL) {
                return NULL;
            }
            break;
            
        case LOWER_BORDER:
            
            if (n1 != NULL && n2 != NULL && n3 != NULL) {
                
                // checks
                if (n1->_pixel_ur != n2->_pixel_dl) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }
                
                if (n2->_pixel_dr != n3->_pixel_ul) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }
                
                // sets
                pixel_ul = n2->_pixel_dl;
                pixel_ur = n2->_pixel_dr;
                
                complete = 1;
                
            } else if (n1 != NULL && n2 != NULL && n3 == NULL) {
                
                // checks
                if (n1->_pixel_ur != n2->_pixel_dl) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }
                
                // sets
                pixel_ul = n2->_pixel_dl;
                pixel_ur = n2->_pixel_dr;
                
                complete = 1;
                
            } else if (n1 != NULL && n2 == NULL && n3 != NULL) {
                
                // sets
                pixel_ul = n1->_pixel_ur;
                pixel_ur = n3->_pixel_ul;
                
                complete = 1;
                
            } else if (n1 == NULL && n2 != NULL && n3 != NULL) {
                
                if (n2->_pixel_dr != n3->_pixel_ul) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }
                
                // sets
                pixel_ul = n2->_pixel_dl;
                pixel_ur = n2->_pixel_dr;
                
                complete = 1;
                
            } else if (n1 != NULL && n2 == NULL && n3 == NULL) {
                
                // sets
                pixel_ul = n1->_pixel_ur;
                
                incomplete = 1;
                
            } else if (n1 == NULL && n2 != NULL && n3 == NULL) {
                
                // sets
                pixel_ul = n2->_pixel_dl;
                pixel_ur = n2->_pixel_dr;
                
                complete = 1;
                
            } else if (n1 == NULL && n2 == NULL && n3 != NULL) {
                
                // sets
                pixel_ur = n3->_pixel_ul;
                
                incomplete = 1;
                
            } else if (n1 == NULL && n2 == NULL && n3 == NULL) {
                return NULL;
            }
            break;
    }
    
    // recorremos todos los remaining tiles
    for (list<Tile_t *>::iterator tile = _remaining_tiles.begin(); tile != _remaining_tiles.end(); tile++) {
        
        // si el tile es del tipo que buscamos
        if((*tile)->_type == type) {
            
            switch(type) {
                case LEFT_BORDER:
                    
                    if (complete) {
                        if(pixel_ur == (*tile)->_pixel_ur && pixel_dr == (*tile)->_pixel_dr) {
                            perfect_match++;
                            searched_tile = (*tile);
                        }
                    } else if(incomplete) {
                        if (pixel_ur == (*tile)->_pixel_ur || pixel_dr == (*tile)->_pixel_dr) {
                            soft_match++;
                            searched_tile = (*tile);
                        }
                    }
                    break;
                    
                case UPPER_BORDER:
                    
                    if (complete) {
                        if(pixel_dl == (*tile)->_pixel_dl && pixel_dr == (*tile)->_pixel_dr) {
                            perfect_match++;
                            searched_tile = (*tile);
                        }
                    } else if(incomplete) {
                        if (pixel_dl == (*tile)->_pixel_dl || pixel_dr == (*tile)->_pixel_dr) {
                            soft_match++;
                            searched_tile = (*tile);
                        }
                    }
                    break;
                    
                case RIGHT_BORDER:
                    if (complete) {
                        if(pixel_ul == (*tile)->_pixel_ul && pixel_dl == (*tile)->_pixel_dl) {
                            perfect_match++;
                            searched_tile = (*tile);
                        }
                    } else if(incomplete) {
                        if (pixel_ul == (*tile)->_pixel_ul || pixel_dl == (*tile)->_pixel_dl) {
                            soft_match++;
                            searched_tile = (*tile);
                        }
                    }
                    break;
                    
                case LOWER_BORDER:
                    if (complete) {
                        if(pixel_ul == (*tile)->_pixel_ul && pixel_ur == (*tile)->_pixel_ur) {
                            perfect_match++;
                            searched_tile = (*tile);
                        }
                    } else if(incomplete) {
                        if (pixel_ul == (*tile)->_pixel_ul || pixel_ur == (*tile)->_pixel_ur) {
                            soft_match++;
                            searched_tile = (*tile);
                        }
                    }
                    break;
            }
        }
        
    }
    
    // we return the tile if only one case can be found in the remaining tiles
    if (perfect_match == 1 || soft_match == 1) 
        return searched_tile;
    else
        return NULL;
}

Tile_t *Map_t::getInternalTile(Tile_t *left_neighbour, Tile_t *upper_neighbour, Tile_t *right_neighbour, Tile_t *lower_neighbour) {
    
    
    
}

void Map_t::FloodFill(int x, int y) {
    
    // outside the domain
    if (x < 0 || x >= _num_x || y < 0 || y >= _num_y)
        return;
    
    // get the current ordered tile and return if it has already been set
    Tile_t *ordered_tile;
    if ((ordered_tile = _ordered_tiles[y * _num_x + x]) != NULL)
        return;
    
    // TODO: FALTA REMOVER LOS CORNERS DE LA REMAINING!
    
    // corners can be found without any 
    if (x == 0 && y == 0)
        ordered_tile = getCornerTile(UPPER_LEFT_CORNER);
    else if (x == (_num_x - 1) && y == 0)
        ordered_tile = getCornerTile(UPPER_RIGHT_CORNER);
    else if (x == 0 && y == (_num_y - 1))
        ordered_tile = getCornerTile(LOWER_LEFT_CORNER);
    else if (x == (_num_x - 1) && y == (_num_y - 1))
        ordered_tile = getCornerTile(LOWER_RIGHT_CORNER);
    else {
        
        // get current neighbours
        int left_index =  y * _num_x + x - 1;
        int upper_index = y * _num_x + x - _num_x;
        int right_index = y * _num_x + x + 1;
        int lower_index = y * _num_x + x + _num_x;
        
        // get the neighbours
        Tile_t *left_neighbour  = (0 <= left_index  && left_index  < _num_x * _num_y) ? _ordered_tiles[left_index]  : NULL;
        Tile_t *upper_neighbour = (0 <= upper_index && upper_index < _num_x * _num_y) ? _ordered_tiles[upper_index] : NULL;
        Tile_t *right_neighbour = (0 <= right_index && right_index < _num_x * _num_y) ? _ordered_tiles[right_index] : NULL;
        Tile_t *lower_neighbour = (0 <= lower_index && lower_index < _num_x * _num_y) ? _ordered_tiles[lower_index] : NULL;
        
        // TODO: FALTA REMOVER LOS BORDERS AND INTERNALS DE LA REMAINING!
        
        // border and internal tiles
        if (x == 0)
            ordered_tile = getBorderTile(LEFT_BORDER, upper_neighbour, right_neighbour, lower_neighbour);
        else if (y == 0)
            ordered_tile = getBorderTile(UPPER_BORDER, left_neighbour, right_neighbour, lower_neighbour);
        else if (x == _num_x - 1)
            ordered_tile = getBorderTile(RIGHT_BORDER, left_neighbour, upper_neighbour, lower_neighbour);
        else if (y == _num_y - 1)
            ordered_tile = getBorderTile(LOWER_BORDER, left_neighbour, right_neighbour, upper_neighbour);
        else
            ordered_tile = getInternalTile(left_neighbour, upper_neighbour, right_neighbour, lower_neighbour);
    }
    
    // left, up, right, down searches
    FloodFill(x - 1, y + 0);
    FloodFill(x + 0, y - 1);
    FloodFill(x + 1, y - 0);
    FloodFill(x - 0, y + 1);
    
    return;
}

void Map_t::solvePuzzle() {
    
    // fill the corners
    FloodFill(0, 0);
    
}

Map_t::Map_t(const Map_t& orig) {
}

Map_t::~Map_t() {
}

