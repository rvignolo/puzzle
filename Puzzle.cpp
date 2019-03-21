/*
 * File:   Puzzle.cpp
 * Author: RamiroV
 *
 */

#include "Puzzle.h"
#include <list>

using namespace std;
using namespace cv;

Puzzle_t::Puzzle_t(char * filename, int num_x, int num_y) {

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
            _shuffled_tiles[y * _num_x + x] = new Tile_t(_source_puzzle, y * _num_x + x, x * _delta_x + 1, y * _delta_y + 1, _delta_x - 1, _delta_y - 1);
            _remaining_tiles.push_back(_shuffled_tiles[y * _num_x + x]);
        }
    }
}

Tile_t *Puzzle_t::getCornerTile(TileType type) {

    if (!(type == UPPER_LEFT_CORNER || type == UPPER_RIGHT_CORNER  || type == LOWER_LEFT_CORNER  || type == LOWER_RIGHT_CORNER)) {
        cout << "getCornerTile method is only implemented for corner type tiles" << endl ;
        exit(1);
    }

    Tile_t *tile;
    for (list<Tile_t *>::iterator it = _remaining_tiles.begin(); it != _remaining_tiles.end(); it++) {
        if ((*it)->getTileType() == type) {
            tile = *it;
            _remaining_tiles.erase(it);
            return tile;
        }
    }

    cout << "corner tile not found" << endl ;
    exit(1);
}

Tile_t *Puzzle_t::getBorderTile(TileType type, Tile_t *n1, Tile_t *n2, Tile_t *n3) {

    if (!(type == LEFT_BORDER || type == UPPER_BORDER || type == RIGHT_BORDER || type == LOWER_BORDER)) {
        cout << "getBorderTile method is only implemented for border type tiles" << endl ;
        exit(1);
    }

    Vec3b pixel_ul;
    Vec3b pixel_ur;
    Vec3b pixel_dl;
    Vec3b pixel_dr;

    // initialize them as black
    for (int i = 0; i < 3; i++) {
        pixel_ul.val[i] = 0;
        pixel_ur.val[i] = 0;
        pixel_dl.val[i] = 0;
        pixel_dr.val[i] = 0;
    }

    // set the pixels
    int complete;
    switch(type) {
        case LEFT_BORDER:

            if (n1 != NULL && n2 != NULL && n3 != NULL) {

                // checks
                if (n1->getPixelDr() != n2->getPixelUl()) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }

                if (n2->getPixelDl() != n3->getPixelUr()) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }

                // sets
                pixel_ur = n2->getPixelUl();
                pixel_dr = n2->getPixelDl();

                complete = 1;

            } else if (n1 != NULL && n2 != NULL && n3 == NULL) {

                // checks
                if (n1->getPixelDr() != n2->getPixelUl()) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }

                // sets
                pixel_ur = n2->getPixelUl();
                pixel_dr = n2->getPixelDl();

                complete = 1;

            } else if (n1 != NULL && n2 == NULL && n3 != NULL) {

                // sets
                pixel_ur = n1->getPixelDr();
                pixel_dr = n3->getPixelUr();

                complete = 1;

            } else if (n1 == NULL && n2 != NULL && n3 != NULL) {

                // cheks
                if (n2->getPixelDl() != n3->getPixelUr()) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }

                // sets
                pixel_ur = n2->getPixelUl();
                pixel_dr = n2->getPixelDl();

                complete = 1;

            } else if (n1 != NULL && n2 == NULL && n3 == NULL) {

                // sets
                pixel_ur = n1->getPixelDr();

                complete = 0;

            } else if (n1 == NULL && n2 != NULL && n3 == NULL) {

                // sets
                pixel_ur = n2->getPixelUl();
                pixel_dr = n2->getPixelDl();

                complete = 1;

            } else if (n1 == NULL && n2 == NULL && n3 != NULL) {

                // sets
                pixel_dr = n3->getPixelUr();

                complete = 0;

            } else if (n1 == NULL && n2 == NULL && n3 == NULL) {
                return NULL;
            }
            break;

        case UPPER_BORDER:

            if (n1 != NULL && n2 != NULL && n3 != NULL) {

                // checks
                if (n1->getPixelDr() != n3->getPixelUl()) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }

                if (n2->getPixelDl() != n3->getPixelUr()) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }

                // sets
                pixel_dl = n3->getPixelUl();
                pixel_dr = n3->getPixelUr();

                complete = 1;

            } else if (n1 != NULL && n2 != NULL && n3 == NULL) {

                // sets
                pixel_dl = n1->getPixelDr();
                pixel_dr = n2->getPixelDl();

                complete = 1;

            } else if (n1 != NULL && n2 == NULL && n3 != NULL) {

                // checks
                if (n1->getPixelDr() != n3->getPixelUl()) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }

                // sets
                pixel_dl = n3->getPixelUl();
                pixel_dr = n3->getPixelUr();

                complete = 1;

            } else if (n1 == NULL && n2 != NULL && n3 != NULL) {

                // cheks
                if (n2->getPixelDl() != n3->getPixelUr()) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }

                // sets
                pixel_dl = n3->getPixelUl();
                pixel_dr = n3->getPixelUr();

                complete = 1;

            } else if (n1 != NULL && n2 == NULL && n3 == NULL) {

                // sets
                pixel_dl = n1->getPixelDr();

                complete = 0;

            } else if (n1 == NULL && n2 != NULL && n3 == NULL) {

                // sets
                pixel_dr = n2->getPixelDl();

                complete = 0;

            } else if (n1 == NULL && n2 == NULL && n3 != NULL) {

                // sets
                pixel_dl = n3->getPixelUl();
                pixel_dr = n3->getPixelUr();

                complete = 1;

            } else if (n1 == NULL && n2 == NULL && n3 == NULL) {
                return NULL;
            }
            break;

        case RIGHT_BORDER:

            if (n1 != NULL && n2 != NULL && n3 != NULL) {

                // checks
                if (n1->getPixelUr() != n2->getPixelDl()) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }

                if (n1->getPixelDr() != n3->getPixelUl()) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }

                // sets
                pixel_ul = n1->getPixelUr();
                pixel_dl = n1->getPixelDr();

                complete = 1;

            } else if (n1 != NULL && n2 != NULL && n3 == NULL) {

                // checks
                if (n1->getPixelUr() != n2->getPixelDl()) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }

                // sets
                pixel_ul = n1->getPixelUr();
                pixel_dl = n1->getPixelDr();

                complete = 1;

            } else if (n1 != NULL && n2 == NULL && n3 != NULL) {

                // checks
                if (n1->getPixelDr() != n3->getPixelUl()) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }

                // sets
                pixel_ul = n1->getPixelUr();
                pixel_dl = n1->getPixelDr();

                complete = 1;

            } else if (n1 == NULL && n2 != NULL && n3 != NULL) {

                // sets
                pixel_ul = n2->getPixelDl();
                pixel_dl = n3->getPixelUl();

                complete = 1;

            } else if (n1 != NULL && n2 == NULL && n3 == NULL) {

                // sets
                pixel_ul = n1->getPixelUr();
                pixel_dl = n1->getPixelDr();

                complete = 1;

            } else if (n1 == NULL && n2 != NULL && n3 == NULL) {

                // sets
                pixel_ul = n2->getPixelDl();

                complete = 0;

            } else if (n1 == NULL && n2 == NULL && n3 != NULL) {

                // sets
                pixel_dl = n3->getPixelUl();

                complete = 0;

            } else if (n1 == NULL && n2 == NULL && n3 == NULL) {
                return NULL;
            }
            break;

        case LOWER_BORDER:

            if (n1 != NULL && n2 != NULL && n3 != NULL) {

                // checks
                if (n1->getPixelUr() != n2->getPixelDl()) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }

                if (n2->getPixelDr() != n3->getPixelUl()) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }

                // sets
                pixel_ul = n2->getPixelDl();
                pixel_ur = n2->getPixelDr();

                complete = 1;

            } else if (n1 != NULL && n2 != NULL && n3 == NULL) {

                // checks
                if (n1->getPixelUr() != n2->getPixelDl()) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }

                // sets
                pixel_ul = n2->getPixelDl();
                pixel_ur = n2->getPixelDr();

                complete = 1;

            } else if (n1 != NULL && n2 == NULL && n3 != NULL) {

                // sets
                pixel_ul = n1->getPixelUr();
                pixel_ur = n3->getPixelUl();

                complete = 1;

            } else if (n1 == NULL && n2 != NULL && n3 != NULL) {

                if (n2->getPixelDr() != n3->getPixelUl()) {
                    cout << "inconsistency found when searching a border tile" << endl ;
                    exit(1);
                }

                // sets
                pixel_ul = n2->getPixelDl();
                pixel_ur = n2->getPixelDr();

                complete = 1;

            } else if (n1 != NULL && n2 == NULL && n3 == NULL) {

                // sets
                pixel_ul = n1->getPixelUr();

                complete = 0;

            } else if (n1 == NULL && n2 != NULL && n3 == NULL) {

                // sets
                pixel_ul = n2->getPixelDl();
                pixel_ur = n2->getPixelDr();

                complete = 1;

            } else if (n1 == NULL && n2 == NULL && n3 != NULL) {

                // sets
                pixel_ur = n3->getPixelUl();

                complete = 0;

            } else if (n1 == NULL && n2 == NULL && n3 == NULL) {
                return NULL;
            }
            break;
    }

    int perfect_match = 0;
    int soft_match = 0;
    list<Tile_t *>::iterator searched_tile;
    for (list<Tile_t *>::iterator it = _remaining_tiles.begin(); it != _remaining_tiles.end(); it++) {

        // si el tile es del tipo que buscamos
        if((*it)->getTileType() == type) {

            switch(type) {
                case LEFT_BORDER:

                    if (complete) {
                        if(pixel_ur == (*it)->getPixelUr() && pixel_dr == (*it)->getPixelDr()) {
                            perfect_match++;
                            searched_tile = it;
                        }
                    } else {
                        if (pixel_ur == (*it)->getPixelUr() || pixel_dr == (*it)->getPixelDr()) {
                            soft_match++;
                            searched_tile = it;
                        }
                    }
                    break;

                case UPPER_BORDER:

                    if (complete) {
                        if(pixel_dl == (*it)->getPixelDl() && pixel_dr == (*it)->getPixelDr()) {
                            perfect_match++;
                            searched_tile = it;
                        }
                    } else {
                        if (pixel_dl == (*it)->getPixelDl() || pixel_dr == (*it)->getPixelDr()) {
                            soft_match++;
                            searched_tile = it;
                        }
                    }
                    break;

                case RIGHT_BORDER:
                    if (complete) {
                        if(pixel_ul == (*it)->getPixelUl() && pixel_dl == (*it)->getPixelDl()) {
                            perfect_match++;
                            searched_tile = it;
                        }
                    } else {
                        if (pixel_ul == (*it)->getPixelUl() || pixel_dl == (*it)->getPixelDl()) {
                            soft_match++;
                            searched_tile = it;
                        }
                    }
                    break;

                case LOWER_BORDER:
                    if (complete) {
                        if(pixel_ul == (*it)->getPixelUl() && pixel_ur == (*it)->getPixelUr()) {
                            perfect_match++;
                            searched_tile = it;
                        }
                    } else {
                        if (pixel_ul == (*it)->getPixelUl() || pixel_ur == (*it)->getPixelUr()) {
                            soft_match++;
                            searched_tile = it;
                        }
                    }
                    break;
            }
        }
    }

    // TODO: tanto si el soft como el perfect match encuentran mas de un tile pero que son completamente equivalentes, retornar uno de ellos
    // we return the tile if only one case can be found in the remaining tiles
    Tile_t *tile;
    if (perfect_match == 1 || soft_match == 1) {
        tile = *searched_tile;
        _remaining_tiles.erase(searched_tile);
        return tile;
    } else
        return NULL;
}

Tile_t *Puzzle_t::getInternalTile(Tile_t *n1, Tile_t *n2, Tile_t *n3, Tile_t *n4) {

    Vec3b pixel_ul;
    Vec3b pixel_ur;
    Vec3b pixel_dl;
    Vec3b pixel_dr;

    // initialize them as black
    for (int i = 0; i < 3; i++) {
        pixel_ul.val[i] = 0;
        pixel_ur.val[i] = 0;
        pixel_dl.val[i] = 0;
        pixel_dr.val[i] = 0;
    }

    // checks
    if (n1 != NULL && n2 != NULL) {
        if (n1->getPixelUr() != n2->getPixelDl()) {
            cout << "inconsistency found when searching an internal tile" << endl ;
            exit(1);
        }
    }

    if (n2 != NULL && n3 != NULL) {
        if (n2->getPixelDr() != n3->getPixelUl()) {
            cout << "inconsistency found when searching an internal tile" << endl ;
            exit(1);
        }
    }

    if (n3 != NULL && n4 != NULL) {
        if (n3->getPixelDl() != n4->getPixelUr()) {
            cout << "inconsistency found when searching an internal tile" << endl ;
            exit(1);
        }
    }

    if (n4 != NULL && n1 != NULL) {
        if (n4->getPixelUl() != n1->getPixelDr()) {
            cout << "inconsistency found when searching an internal tile" << endl ;
            exit(1);
        }
    }

    // set case
    int complete;
    if ((n1 != NULL && n3 != NULL) || (n2 != NULL && n4 != NULL))
        complete = 1;
    else
        complete = 0;

    // set the pixels
    if (n1 != NULL) {
        pixel_ul = n1->getPixelUr();
        pixel_dl = n1->getPixelDr();
    }

    if (n2 != NULL) {
        pixel_ul = n2->getPixelDl();
        pixel_ur = n2->getPixelDr();
    }

    if (n3 != NULL) {
        pixel_ur = n3->getPixelUl();
        pixel_dr = n3->getPixelDl();
    }

    if (n4 != NULL) {
        pixel_dl = n4->getPixelUl();
        pixel_dr = n4->getPixelUr();
    }

    // create the needed tile
    Tile_t dummy(INTERNAL, pixel_ul, pixel_ur, pixel_dl, pixel_dr);

    int perfect_match = 0;
    int soft_match = 0;
    list<Tile_t *>::iterator searched_tile;
    for (list<Tile_t *>::iterator it = _remaining_tiles.begin(); it != _remaining_tiles.end(); it++) {

        if (complete) {

            // use the overloaded operator==
            if((**it) == dummy) {
                perfect_match++;
                searched_tile = it;
            }
        } else {

            if((*it)->getTileType() == dummy.getTileType()) {

                if ((dummy.isBlack(dummy.getPixelUl()) || (!dummy.isBlack(dummy.getPixelUl()) && dummy.getPixelUl() == (*it)->getPixelUl())) &&
                    (dummy.isBlack(dummy.getPixelUr()) || (!dummy.isBlack(dummy.getPixelUr()) && dummy.getPixelUr() == (*it)->getPixelUr())) &&
                    (dummy.isBlack(dummy.getPixelDl()) || (!dummy.isBlack(dummy.getPixelDl()) && dummy.getPixelDl() == (*it)->getPixelDl())) &&
                    (dummy.isBlack(dummy.getPixelDr()) || (!dummy.isBlack(dummy.getPixelDr()) && dummy.getPixelDr() == (*it)->getPixelDr()))) {
                    soft_match++;
                    searched_tile = it;
                }
            }
        }
    }

    // we return the tile if only one case is found in the remaining tiles
    Tile_t *tile;
    if (perfect_match == 1 || soft_match == 1) {
        tile = *searched_tile;
        _remaining_tiles.erase(searched_tile);
        return tile;
    } else
        return NULL;
}

void Puzzle_t::FloodFill(int x, int y) {

    // outside the domain
    if (x < 0 || x >= _num_x || y < 0 || y >= _num_y)
        return;

    // get the current ordered tile and return if it has already been set
    if (_ordered_tiles[y * _num_x + x] != NULL)
        return;

    Tile_t *ordered_tile;

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

        // border and internal tiles
        if (x == 0)
            ordered_tile = getBorderTile(LEFT_BORDER, upper_neighbour, right_neighbour, lower_neighbour);
        else if (y == 0)
            ordered_tile = getBorderTile(UPPER_BORDER, left_neighbour, right_neighbour, lower_neighbour);
        else if (x == _num_x - 1)
            ordered_tile = getBorderTile(RIGHT_BORDER, left_neighbour, upper_neighbour, lower_neighbour);
        else if (y == _num_y - 1)
            ordered_tile = getBorderTile(LOWER_BORDER, left_neighbour, upper_neighbour, right_neighbour);
        else
            ordered_tile = getInternalTile(left_neighbour, upper_neighbour, right_neighbour, lower_neighbour);
    }

    // set
    _ordered_tiles[y * _num_x + x] = ordered_tile;

    return;
}

void Puzzle_t::solvePuzzle() {

    int n_iter = 0;
    while(!isPuzzleSolved() && n_iter < 50) {
        for (int y = 0; y < _num_y; y++) {
            for (int x = 0; x < _num_x; x++) {
                FloodFill(x, y);
            }
        }
        n_iter++;
    }

    Mat V;
    Mat whiteBox = Mat::ones(_ordered_tiles[0]->getCrop().rows, _ordered_tiles[0]->getCrop().cols, _ordered_tiles[0]->getCrop().type());
    for (int y = 0; y < _num_y; y++) {

        Mat H;
        for (int x = 1; x < _num_x; x++) {
            if (x == 1)
                hconcat(_ordered_tiles[y * _num_x + x - 1] != NULL ? _ordered_tiles[y * _num_x + x - 1]->getCrop() : whiteBox, _ordered_tiles[y * _num_x + x] != NULL ? _ordered_tiles[y * _num_x + x]->getCrop() : whiteBox, H);
            else
                hconcat(H, _ordered_tiles[y * _num_x + x] != NULL ? _ordered_tiles[y * _num_x + x]->getCrop() : whiteBox, H);
        }

        if (y == 0)
            V = H;
        else
            vconcat(V, H, V);
    }

    _solved_puzzle = V;

    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", _solved_puzzle);

    waitKey(0);
}

bool Puzzle_t::isPuzzleSolved() {

    int n_tiles = 0;
    for (int y = 0; y < _num_y; y++) {
        for (int x = 0; x < _num_x; x++) {
            if (_ordered_tiles[y * _num_x + x] != NULL)
                n_tiles++;
        }
    }

    return n_tiles == _num_x * _num_y ? true : false;
}

Puzzle_t::Puzzle_t(const Puzzle_t& orig) {
}

Puzzle_t::~Puzzle_t() {
}
