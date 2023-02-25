#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <array>
#include <deque>
#include <mutex>
#include <optional>
#include <vector>

#include "block.h"
using namespace std;
constexpr int W = BlockKind::WALL;

constexpr auto showCursor = "\x1B[?25h";
constexpr auto moveCursorToTop = "\x1b[H";
constexpr auto clearDisplay = "\x1B[2J\x1b[H\x1b[?25l";
constexpr auto moveCursorToHold = "\x1b[2;28HHOLD";
constexpr auto moveCursorStart = "\x1b[";
constexpr auto moveCursorEnd = ";28H";
constexpr auto moveCursorToNext = "\x1b[8;28HNEXT";
constexpr auto resetColor = "\x1b[0m";
constexpr auto moveCursorScore = "\x1b[22;28H";

// Field Size
constexpr int FIELD_WIDTH = 11 + 2 + 2;
constexpr int FIELD_HEIGHT = 20 + 1 + 1;
using Field = vector<array<int, 22>>;

struct Position {
  int x;
  int y;

  Position(int a = 5, int b = 0) {
    this->x = a;
    this->y = b;
  }
};
const array<int, 5> SCORE_TABLE = {0, 1, 5, 25, 100};
constexpr int NEXT_LENGTH = 3;
struct Game {
  Field field;
  Position pos;
  BlockShape block;
  optional<BlockShape> hold;
  bool holded;
  deque<BlockShape> next;
  deque<BlockShape> nextBuf;
  int score;
  mutex m;

  Game() {
    field = {
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
    pos = Position{};
    block = BLOCKS[randomBlock()];
    hold = nullopt;
    holded = false;
    next = genBlock();
    nextBuf = genBlock();
    score = 0;
  }
};

Position ghostPosition(Game &game);
void draw(Game &game);
void hardDrop(Game &game);
bool isCollision(Field &field, Position &pos, BlockShape &block);
void hold(Game &game);
bool landing(Game &game);
void fixBlock(Game &game);
int eraseLine(Game &game);
bool spawnBlock(Game &game);
void gameover(Game &game);
void quit();
#endif
