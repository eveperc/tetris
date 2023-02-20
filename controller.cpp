#include "controller.h"
using namespace std;

void rotateRight(Game &game) {
  auto newShape = game.block;
  for (auto y = 0; y < 4; ++y) {
    for (auto x = 0; x < 4; ++x) {
      newShape[y][x] = game.block[4 - 1 - x][y];
    }
  }
  if (!isCollision(game.field, game.pos, newShape))
    game.block = newShape;
}

void rotateLeft(Game &game) {
  auto newShape = game.block;
  for (auto y = 0; y < 4; ++y) {
    for (auto x = 0; x < 4; ++x) {
      newShape[4 - 1 - x][y] = game.block[y][x];
    }
  }
  if (!isCollision(game.field, game.pos, newShape))
    game.block = newShape;
}
