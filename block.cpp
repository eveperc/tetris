#include <random>
#include "block.h"

using namespace std;
mt19937 mt {random_device{}()};

int random(int low, int high) {
  uniform_int_distribution<> dist(low, high);
  return dist(mt);
}

int randomBlock() {
  return random(0, 6);
}

deque<BlockShape> genBlock(){
  vector<int> que = {I,O,S,Z,J,L,T};
  shuffle(que.begin(),que.end(),mt);
  deque<BlockShape> blocks;
  for (auto i:que){
    blocks.push_back(BLOCKS[i]);
  }
  return blocks;
}
