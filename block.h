#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

enum BlockKind { I, O, S, Z, J, L, T };
int random(int low,int high);
BlockKind randomBlock();
using BlockShape = char[4][4];
const BlockShape BLOCKS[7] = {
    // I Block
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
    },
    // O Block
    {
        {0, 0, 0, 0},
        {0, 1, 1, 1},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
    },
    // S Block
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
    },
    // Z Block
    {
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
    },
    // L Block
    {
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
    },
    // T Block
    {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
    },
};

#endif
