/*
/*
 * File:   Tile.h
 * Author: RamiroV
 *
 */

#ifndef TILE_H
#define TILE_H

#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

enum TileType {
    UPPER_LEFT_CORNER,
    UPPER_RIGHT_CORNER,
    LOWER_LEFT_CORNER,
    LOWER_RIGHT_CORNER,
    UPPER_BORDER,
    LEFT_BORDER,
    RIGHT_BORDER,
    LOWER_BORDER,
    INTERNAL
};

// TODO: classes should have private members as commented below and incorporate
// get-set functions to externally access to those members if needed. Follow the
// OpenMoC's Track.h file for completeness.
class Tile_t {

private:

    /** An id number */
    int _id;

    /** An opencv matrix containing the cropped tile */
    Mat _crop;

    /** The tile type */
    TileType _type;

    /** Each corner pixel */
    Vec3b _pixel_ul;
    Vec3b _pixel_ur;
    Vec3b _pixel_dl;
    Vec3b _pixel_dr;

public:

    /** Constructor */
    Tile_t(Mat source_puzzle, int id, int xi, int yi, int width, int height);
    Tile_t(TileType type, Vec3b pixel_ul, Vec3b pixel_ur, Vec3b pixel_dl, Vec3b pixel_dr);

    /** Copy Constructor */
    Tile_t(const Tile_t& orig);

    /** Destructor */
    virtual ~Tile_t();

    /** sets */
    void setId(int id) { _id = id; }
    void setCrop(Mat crop) { _crop = crop; }
    void setTileType();
    void setPixelUl(Vec3b pixel_ul) { _pixel_ul = pixel_ul; }
    void setPixelUr(Vec3b pixel_ur) { _pixel_ur = pixel_ur; }
    void setPixelDl(Vec3b pixel_dl) { _pixel_dl = pixel_dl; }
    void setPixelDr(Vec3b pixel_dr) { _pixel_dr = pixel_dr; }
    void setlTilePixels(int width, int height);

    /** gets */
    int getId() { return _id; }
    Mat getCrop() { return _crop; }
    TileType getTileType() { return _type; }
    Vec3b getPixelUl() { return _pixel_ul; }
    Vec3b getPixelUr() { return _pixel_ur; }
    Vec3b getPixelDl() { return _pixel_dl; }
    Vec3b getPixelDr() { return _pixel_dr; }

    bool isWhite(Vec3b pixel) { if (pixel.val[0] == 255 && pixel.val[1] == 255 && pixel.val[2] == 255) return true; else return false; }
    bool isBlack(Vec3b pixel) { if (pixel.val[0] == 0   && pixel.val[1] == 0   && pixel.val[2] == 0  ) return true; else return false; }
    bool isColor(Vec3b pixel1, Vec3b pixel2) {
        if (pixel1.val[0] == pixel2.val[0] && pixel1.val[1] == pixel2.val[1]  && pixel1.val[2] == pixel2.val[2])
            return true;
        else
            return false;
    }
    bool isLeftBorder() {
        if ((isWhite(_pixel_ul) || isBlack(_pixel_ul)) && (isWhite(_pixel_dl) || isBlack(_pixel_dl)))
            return true;
        else
            return false;
    }
    bool isUpperBorder() {
        if ((isWhite(_pixel_ul) || isBlack(_pixel_ul)) && (isWhite(_pixel_ur) || isBlack(_pixel_ur)))
            return true;
        else
            return false;
    }
    bool isRightBorder() {
        if ((isWhite(_pixel_ur) || isBlack(_pixel_ur)) && (isWhite(_pixel_dr) || isBlack(_pixel_dr)))
            return true;
        else
            return false;
    }
    bool isLowerBorder() {
        if ((isWhite(_pixel_dl) || isBlack(_pixel_dl)) && (isWhite(_pixel_dr) || isBlack(_pixel_dr)))
            return true;
        else
            return false;
    }
    bool isUpperLeftCorner() {
        if (isLeftBorder() && isUpperBorder())
            return true;
        else
            return false;
    }
    bool isUpperRightCorner() {
        if (isRightBorder() && isUpperBorder())
            return true;
        else
            return false;
    }
    bool isLowerLeftCorner() {
        if (isLeftBorder() && isLowerBorder())
            return true;
        else
            return false;
    }
    bool isLowerRightCorner() {
        if (isRightBorder() && isLowerBorder())
            return true;
        else
            return false;
    }
    bool isInternal() {
        if ((!isWhite(_pixel_ul) && !isBlack(_pixel_ul)) && (!isWhite(_pixel_ur) && !isBlack(_pixel_ur)) && (!isWhite(_pixel_dl) && !isBlack(_pixel_dl)) && (!isWhite(_pixel_dr) && !isBlack(_pixel_dl)))
            return true;
        else
            return false;
    }

    /** overloads */
    bool operator==(const Tile_t& t2);
    bool operator!=(const Tile_t& t2);
};

#endif /* TILE_H */
