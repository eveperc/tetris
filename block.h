#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <string>
#include <vector>
using namespace std;

enum BlockKind { I, O, S, Z, J, L, T };
// enum BlockColor {

// };
// const vector<string> COLOR_TABLE = {
//     "\x1b[48;2;000;000;000m  ", // 何もなし
//     "\x1b[48;2;127;127;127m__", // 壁
//     "\x1b[48;2;000;000;255m__", // I
//     "\x1b[48;2;000;255;000m__", // O
//     "\x1b[48;2;000;255;255m__", // S
//     "\x1b[48;2;255;000;000m__", // Z
//     "\x1b[48;2;255;000;255m__", // J
//     "\x1b[48;2;255;127;000m__", // L
//     "\x1b[48;2;255;255;000m__", // T
// };
int random(int low, int high);
BlockKind randomBlock();
using BlockShape = vector<vector<int>>;
const BlockShape BLOCKS[7] = {

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
