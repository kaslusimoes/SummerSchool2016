#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
const ll N = 10,
 M = 6,
 MAX = N + M + 1,
 MAX_EDGE = 15,
 MAX_DEG = 3,
 ITERATIONS = 10000,
 GENERATIONS = 10000;
long double Prop1 = 0.5, Prop2 = 0.2;

float payoff[2][2], payoff_2[2][2];
int strategy[MAX], fitness_value[MAX];
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

void set_initial_strategy(float cooperator_percent1, float cooperator_percent2) {
  fill_n(strategy, MAX, 1);
  for (int i = 0; i < cooperator_percent1 * N; ++i)
    strategy[i] = 0;
  for (int i = N; i < cooperator_percent2 * M; ++i)
    strategy[i] = 0;
}

void build_network() {
  build_random();
  //build_regular_random();
  //build_scale_free(); // Change here the kind of network we want to work with

  set_initial_strategy(Prop1, Prop2);
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
    cout << i << ": strategy:" << strategy[i] << "\n";
    for (auto &k :G[i]) {
      cout << k << " ";
    }
    cout << endl;
  }
  simulate();
  return 0;
}

