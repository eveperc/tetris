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
  cout << moveCursorToHold << endl;
  if (game.hold.has_value()) {
    for (auto y = 0; y < 4; ++y) {
      cout << moveCursorStart << (y + 3) << moveCursorEnd;
      for (auto x = 0; x < 4; ++x) {
        cout << COLOR_TABLE[game.hold.value()[y][x]];
      }
    }
  }
  cout << moveCursorToNext << endl;
  int index = 0;
  for (auto v : game.next) {
    if(index == NEXT_LENGTH)
      break;
    for (auto y = 0; y < 4; ++y) {
      cout << moveCursorStart << (index * 4 + y + 9) << moveCursorEnd;
      for (auto x = 0; x < 4; ++x) {
        cout << COLOR_TABLE[v[y][x]];
      }
      cout << endl;
    }
    ++index;
  }
  cout << moveCursorScore << game.score;
  cout << moveCursorToTop << endl;
  for (auto y = 0; y < FIELD_HEIGHT - 1; ++y) {
    for (auto x = 1; x < FIELD_WIDTH - 1; ++x) {
      cout << COLOR_TABLE[fieldBuf[y][x]];
    }
    cout << endl;
  }
  cout << resetColor;
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

void hold(Game &game) {
  if (game.holded)
    return;
  if (game.hold.has_value()) {
    swap(game.hold.value(), game.block);
    game.pos = Position{};
  } else {
    game.hold = game.block;
    spawnBlock(game);
  }
}

bool landing(Game &game) {
  fixBlock(game);
  auto line = eraseLine(game);
  game.score += SCORE_TABLE[line];
  game.line += line;
  game.holded = false;
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

int eraseLine(Game &game) {
  auto count = 0;
  for (auto y = 1; y < FIELD_HEIGHT - 2; ++y) {
    auto canErase = true;
    for (auto x = 1; x < FIELD_WIDTH - 2; ++x) {
      if (game.field[y][x] == 0) {
        canErase = false;
        break;
      }
    }
    if (canErase) {
      count += 1;
      for (auto y2 = 0; y2 <= y - 2; ++y2) {
        const auto y2rev = y - y2;
        game.field[y2rev] = game.field[y2rev - 1];
      }
    }
  }
  return count;
}

bool spawnBlock(Game &game) {
  game.pos = Position{};
  game.block = game.next.front();
  game.next.pop_front();
  game.next.push_back(BLOCKS[randomBlock()]);
  if (game.nextBuf.empty())
    game.nextBuf = genBlock();
  game.next.push_back(game.nextBuf.front());
  game.nextBuf.pop_front();
  // デバッグ表示
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
