#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <array>
#include <string>
#include <vector>
#include <deque>
using namespace std;

namespace BlockKind {
constexpr int NONE = 0;
constexpr int WALL = 1;
constexpr int GHOST = 2;
constexpr int I = 3;
constexpr int O = 4;
constexpr int S = 5;
constexpr int Z = 6;
constexpr int J = 7;
constexpr int L = 8;
constexpr int T = 9;
};

constexpr int BLOCK_KIND_MAX = 7;

namespace ColorTable {
const array<basic_string<char>, 10> COLOR_TABLE = {
    "\x1b[48;2;000;000;000m  ", // 何もなし
    "\x1b[48;2;127;127;127m__", // 壁
    "\x1b[48;2;000;000;000m[]", // ゴースト
    "\x1b[48;2;000;000;255m__", // I
    "\x1b[48;2;000;255;000m__", // O
    "\x1b[48;2;000;255;255m__", // S
    "\x1b[48;2;255;000;000m__", // Z
    "\x1b[48;2;255;000;255m__", // J
    "\x1b[48;2;255;127;000m__", // L
    "\x1b[48;2;255;255;000m__", // T
};
}
int random(int low, int high);
int randomBlock();

using BlockShape = vector<array<int,4>>;
using namespace BlockKind;

const BlockShape BLOCKS[BLOCK_KIND_MAX] = {
    //I Block
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {I, I, I, I},
        {0, 0, 0, 0},
    },
    // O Block
    {
        {0, 0, 0, 0},
        {0, O, O, 0},
        {0, O, O, 0},
        {0, 0, 0, 0},
    },
    // S Block
    {
        {0, 0, 0, 0},
        {0, S, S, 0},
        {S, S, 0, 0},
        {0, 0, 0, 0},
    },
    // Z Block
    {
        {0, 0, 0, 0},
        {Z, Z, 0, 0},
        {0, Z, Z, 0},
        {0, 0, 0, 0},
    },
    // J Block
    {{
        {0, 0, 0, 0},
        {J, 0, 0, 0},
        {J, J, J, 0},
        {0, 0, 0, 0},
    }},
    // L Block
    {
        {0, 0, 0, 0},
        {0, 0, L, 0},
        {L, L, L, 0},
        {0, 0, 0, 0},
    },
    // T Block
    {
        {0, 0, 0, 0},
        {0, T, 0, 0},
        {T, T, T, 0},
        {0, 0, 0, 0},
    },
};

deque<BlockShape> genBlock();
#endif
