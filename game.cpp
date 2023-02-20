#include "game.h"

#include <iostream>
using namespace std;
// view Field
void draw(Game &game) {
  // scoped_lock lock{m};
  auto fieldBuf = game.field;
  for (auto y = 0; y < 4; ++y) {
    for (auto x = 0; x < 4; ++x) {
      if (BLOCKS[game.block][y][x] == 1)
        fieldBuf[y + game.pos.y][x + game.pos.x] = 1;
    }
  }
  cout << "\x1b[H" << endl;
  for (auto y = 0; y < FIELD_HEIGHT; ++y) {
    for (auto x = 0; x < FIELD_WIDTH; ++x) {
      if (fieldBuf[y][x] == 1)
        cout << "[]";
      else
        cout << " .";
    }
    cout << endl;
  }
}
bool isCollision(Field &field, Position &pos, BlockKind &block) {
  for (auto y = 0; y < 4; ++y) {
    for (auto x = 0; x < 4; ++x) {
      if (y + pos.y >= FIELD_HEIGHT || x + pos.x >= FIELD_WIDTH)
        continue;
      if (field[y + pos.y][x + pos.x] && BLOCKS[block][y][x] == 1)
        return true;
    }
  }
  return false;
}
void fixBlock(Game &game) {
  for (auto y = 0; y < 4; ++y) {
    for (auto x = 0; x < 4; ++x) {
      if (BLOCKS[game.block][y][x] == 1)
        game.field[y + game.pos.y][x + game.pos.x] = 1;
    }
  }
}
void eraseLine(Game &game) {
  for (auto y = 1; y < FIELD_HEIGHT - 1; ++y) {
    auto canErase = true;
    for (auto x = 1; x < FIELD_WIDTH - 1; ++x) {
      if (game.field[y][x] == 0) {
        canErase = false;
        break;
      }
    }
    if (canErase) {
      for (auto y2 = 0; y2 <= y - 2; ++y2) {
        const auto y2rev = y - y2;
        game.field[y2rev] = game.field[y2rev - 1];
      }
    }
  }
}