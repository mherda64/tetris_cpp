//
// Created by musiek on 11/21/20.
//

#ifndef TETRIS_CPP_SPIECE_H
#define TETRIS_CPP_SPIECE_H


#include "Point.h"
#include "Piece.h"

class SPiece : public Piece {
    static Point punkty[4][4];
public:
    SPiece(std::string tileset, int rotation, int spawnX);
};



#endif //TETRIS_CPP_SPIECE_H