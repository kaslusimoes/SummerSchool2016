#include <bits/stdc++.h>

using namespace std;
#define N 5
#define M 6
#define MAX N+M+1
#define MAX_EDGE 15
#define MAX_DEG 3

float payoff[2][2], payoff_2[2][2];
int strategy[2 * MAX], fitness_value[2 * MAX];
set<int> G[MAX];

float rand_num() {
  return (float) rand() / RAND_MAX;
}

float interaction(int a, int b) {
  return payoff[strategy[a]][strategy[b]];
}

void calculate_fitness(int a) {
  fitness_value[a] = 0;
}

void recalculate_all_fitness() {
  for (int i = 0; i < N + M; ++i)
    calculate_fitness(i);
}

float fitness(int a) {
  return fitness_value[a];
}

void build_random() {
  int j = 0;
  while (j < MAX_EDGE) {
    int k = rand() % N, l = (rand() % M) + N;
    if (G[k].find(l) == G[k].end()) {
      G[k].insert(l);
      G[l].insert(k);
      j++;
    }
  }
}

void build_regular_random() {
  for (int i = 0; i < N; ++i) {
    int j = 0;
    while (j < MAX_DEG) {
      int k = (rand() % M) + N;
      if (G[i].find(k) == G[i].end()) {
        G[i].insert(k);
        G[k].insert(i);
        j++;
      }
    }
  }
}

void build_scale_free() {

}

void set_initial_strategy(){

}

void build_network() {
  build_random();
  //build_regular_random();
  //build_scale_free(); // Change here the kind of network we want to work with

  set_initial_strategy();
}

void simulate_synchronous() {

}

void simulate_asynchronous() {

}

void simulate() {
  simulate_asynchronous();
//  simulate_synchronous();
}

int main() {
  srand(time(NULL));
  build_network();
  for (int i = 0; i < N; ++i) {
    cout << i << ":\n\t";
    for (auto &k :G[i]) {
      cout << k << " ";
    }
    cout << endl;
  }
  simulate();
  return 0;
}

