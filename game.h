#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "block.h"

#include <vector>
#include <array>

using namespace std;
constexpr int W = BlockKind::WALL;

constexpr auto showCursor = "\x1B[?25h";
constexpr auto moveCursorToTop = "\x1b[H";
constexpr auto clearDisplay = "\x1B[2J\x1b[H\x1b[?25l";
// Field Size

const int FIELD_WIDTH = 11 + 2 + 2;
const int FIELD_HEIGHT = 20 + 1 + 1;
using Field = vector<array<int,22>>;

struct Position {
  int x;
  int y;

  Position(int a = 5, int b = 0) {
    this->x = a;
    this->y = b;
  }
};

struct Game {
  Field field;
  Position pos;
  BlockShape block;

  Game() {
    this->field = {
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0},
        {0, W, W, W, W, W, W, W, W, W, W, W, W, W, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    this->pos = Position{};
    this->block = BLOCKS[randomBlock()];
  }
};

Position ghostPosition(Game &game);
void draw(Game &game);
void hardDrop(Game &game);
bool isCollision(Field &field, Position &pos, BlockShape &block);
bool landing(Game &game);
void fixBlock(Game &game);
void eraseLine(Game &game);
bool spawnBlock(Game &game);
void gameover(Game &game);
void quit();
#endif
