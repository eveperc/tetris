#include "block.h"
#include <random>

using namespace std;
default_random_engine gen;

int random(int low, int high) {
  uniform_int_distribution<> dist(low, high);
  return dist(gen);
}

BlockKind randomBlock() {
  auto i = random(0, 5);
  switch (i) {
  case 0:
    return BlockKind::I;
  case 1:
    return BlockKind::O;
  case 2:
    return BlockKind::S;
  case 3:
    return BlockKind::Z;
  case 4:
    return BlockKind::J;
  case 5:
    return BlockKind::L;
  default:
    return BlockKind::T;
  }
}
