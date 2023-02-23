#include "controller.h"
#include <fcntl.h>
#include <mutex>
#include <termios.h>
#include <type_traits>
#include <unistd.h>

using namespace std;
int kbhit(void) {
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if (ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}

bool checkedSub() { return false; }

tuple<bool, Position> superRotation(Field &field, Position &pos,
                                    BlockShape &block) {
  Position diffPos[4] = {
      Position{pos.x, pos.y - 1},
      Position{pos.x + 1, pos.y},
      Position{pos.x, pos.y + 1},
      Position{pos.x - 1, pos.y},
  };
  for (auto p : diffPos) {
    if (!isCollision(field, p, block))
      return forward_as_tuple(true, p);
  }
  return forward_as_tuple(false, pos);
}

void rotateRight(Game &game) {
  auto newShape = game.block;
  for (auto y = 0; y < 4; ++y) {
    for (auto x = 0; x < 4; ++x) {
      newShape[y][x] = game.block[4 - 1 - x][y];
    }
  }
  if (!isCollision(game.field, game.pos, newShape))
    game.block = newShape;
  else {
    auto [b, pos] = superRotation(game.field, game.pos, newShape);
    if(b){
      game.pos = pos;
      game.block = newShape;
    }
  }
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
  else {
    auto [b, pos] = superRotation(game.field, game.pos, newShape);
    if(b){
      game.pos = pos;
      game.block = newShape;
    }
  }
}
