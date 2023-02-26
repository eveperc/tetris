#include <iostream>
#include <mutex>
#include <thread>

#include "block.h"
#include "controller.h"
#include "game.h"

using namespace std;

void key(Game &game) {
  while (1) {
    if (kbhit()) {
      auto move = [&](unsigned int a, unsigned int b) -> void {
        auto newPos = Position{a, b};
        if (!isCollision(game.field, newPos, game.block))
          game.pos = newPos;
      };
      switch (getchar()) {
      case 'q':
        quit();
      case 'w':
        hardDrop(game);
        if (!landing(game)) {
          gameover(game);
        }
        break;
      case 'a':
        move(game.pos.x - 1, game.pos.y);
        break;
      case 's':
        move(game.pos.x, game.pos.y + 1);
        break;
      case 'd':
        move(game.pos.x + 1, game.pos.y);
        break;
      case 'x':
        rotateRight(game);
        draw(game);
        break;
      case 'z':
        rotateLeft(game);
        draw(game);
        break;
      case ' ':
        hold(game);
        draw(game);
        break;
      default:
        break;
      }
      draw(game);
    }
  }
}

void views(Game &game) {
  while (1) {
    auto sleepMsec = [&]() {
      auto result = 1000 - (game.line/10*100) < 0
        ? game.line
        : 100;
      return result/10 * 100;
    }();
    this_thread::sleep_for(chrono::milliseconds(sleepMsec));
    {
      scoped_lock lock{game.m};
      auto newPos = Position{game.pos.x, game.pos.y + 1};
      if (!isCollision(game.field, newPos, game.block))
        game.pos = newPos;
      else {
        if (!landing(game))
          gameover(game);
      }
      draw(game);
    }
  }
}

int main() {
  auto game = Game{};
  cout << clearDisplay << endl;
  if (!spawnBlock(game))
    quit();
  draw(game);
  try {
    thread t1(views, ref(game));
    thread t2(key, ref(game));
    t1.join();
    t2.join();
  } catch (exception &ex) {
    cerr << ex.what() << endl;
    quit();
  }
  return 0;
}
