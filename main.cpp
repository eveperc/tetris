#include <fcntl.h>
#include <iostream>
#include <mutex>
#include <termios.h>
#include <thread>
#include <unistd.h>

#include "game.h"
#include "controller.h"

using namespace std;

mutex m;

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

void key(Game &game) {
  // auto fieldBuf = field;
  // auto posBuf = pos;
  while (1) {
    if (kbhit()) {
      auto move = [&](int a, int b) -> void {
        auto newPos = Position{a, b};
        if (!isCollision(game.field, newPos, game.block))
          game.pos = newPos;
      };
      switch (getchar()) {
      case 'q':
        cout << "\x1B[?25h" << endl;
        exit(0);
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
      default:
        break;
      }
      draw(game);
    }
  }
}

void views(Game &game) {
  // thread::spawn
  while (1) {
    this_thread::sleep_for(chrono::seconds(1));
    // create field
    auto newPos = Position{game.pos.x, game.pos.y + 1};
    if (!isCollision(game.field, newPos, game.block))
      game.pos = newPos;
    else {
      // stop block
      fixBlock(game);
      eraseLine(game);
      if(!spawnBlock(game))
        gameover(game);
    }
    draw(game);
  }
}

int main() {
  auto game = Game{};
  // clear display
  cout << "\x1B[2J\x1b[H\x1b[?25l" << endl;
  // view field
  draw(game);
  try {
    thread t1(views, ref(game));
    thread t2(key, ref(game));
    t1.join();
    t2.join();
  } catch (exception &ex) {
    cerr << ex.what() << endl;
  }
  cout << "\x1B[?25h" << endl;

  return 0;
}
