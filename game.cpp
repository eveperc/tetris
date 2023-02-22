#include "game.h"

#include <iostream>
using namespace std;
using namespace BlockKind;
using namespace ColorTable;

Position ghostPosition(Game &game) {
  auto ghost = game.pos;
  while (1) {
    auto newPos = Position{ghost.x, ghost.y + 1};
    if (!isCollision(game.field, newPos, game.block))
      ghost.y += 1;
    else
      break;
  }
  return ghost;
}
// view Field
void draw(Game &game) {
  // scoped_lock lock{m};
  auto fieldBuf = game.field;
  auto ghost = ghostPosition(game);
  for (auto y = 0; y < 4; ++y) {
    for (auto x = 0; x < 4; ++x) {
      if (game.block[y][x] != NONE)
        fieldBuf[y + ghost.y][x + ghost.x] = GHOST;
    }
  }
  for (auto y = 0; y < 4; ++y) {
    for (auto x = 0; x < 4; ++x) {
      if (game.block[y][x] != NONE)
        fieldBuf[y + game.pos.y][x + game.pos.x] = game.block[y][x];
    }
  }
  cout << moveCursorToTop << endl;
  for (auto y = 0; y < FIELD_HEIGHT - 1; ++y) {
    for (auto x = 1; x < FIELD_WIDTH - 1; ++x) {
      cout << COLOR_TABLE[fieldBuf[y][x]];
    }
    cout << endl;
  }
}
void hardDrop(Game &game) {
  while (1) {
    auto newPos = Position{game.pos.x, game.pos.y + 1};
    if (!isCollision(game.field, newPos, game.block))
      game.pos.y += 1;
    else
      break;
  }
}

bool isCollision(Field &field, Position &pos, BlockShape &block) {
  for (auto y = 0; y < 4; ++y) {
    for (auto x = 0; x < 4; ++x) {
      if (y + pos.y >= FIELD_HEIGHT || x + pos.x >= FIELD_WIDTH)
        continue;
      if (block[y][x] != NONE && field[y + pos.y][x + pos.x] != NONE)
        return true;
    }
  }
  return false;
}

bool landing(Game &game) {
  fixBlock(game);
  eraseLine(game);
  return spawnBlock(game);
}

void fixBlock(Game &game) {
  for (auto y = 0; y < 4; ++y) {
    for (auto x = 0; x < 4; ++x) {
      if (game.block[y][x] != NONE)
        game.field[y + game.pos.y][x + game.pos.x] = game.block[y][x];
    }
  }
}

void eraseLine(Game &game) {
  for (auto y = 1; y < FIELD_HEIGHT - 2; ++y) {
    auto canErase = true;
    for (auto x = 1; x < FIELD_WIDTH - 2; ++x) {
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

bool spawnBlock(Game &game) {
  game.pos = Position{};
  game.block = BLOCKS[randomBlock()];
  if (isCollision(game.field, game.pos, game.block))
    return false;
  else
    return true;
}

void gameover(Game &game) {
  draw(game);
  cout << "GAMEOVER" << endl;
  quit();
}

void quit() {
  cout << showCursor << endl;
  exit(0);
}
