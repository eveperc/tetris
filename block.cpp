#include "block.h"
#include <random>

using namespace std;
default_random_engine gen;

int random(int low, int high) {
  uniform_int_distribution<> dist(low, high);
  return dist(gen);
}

int randomBlock() {
  return random(0, 6);
}
