#include <bits/stdc++.h>

using namespace std;
#define MAX 100
#define MAX_EDGE 800
#define MAX_DEG 70


int n, m; //Amount of individuals of type1 and type2
float payoff[2][2], payoff_2[2][2];
int strategy[2 * MAX], fitness_value[2 * MAX];
vector<int> G[MAX];

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
  for (int i = 0; i < n + m; ++i)
    calculate_fitness(i);
}

float fitness(int a) {
  return fitness_value[a];
}


void build_random() {
}

void build_regular_random() {
  for (int i = 0; i < n; ++i) {
    int j = 0;
    while (j < MAX_EDGE) {

    }
  }
}

void build_scale_free() {

}

void build_network() {
  //build_random();
  build_regular_random();
  //build_scale_free(); // Change here the kind of network we want to work with
}


void simulate() {
}

int main() {
  cin >> n >> m;
  build_network();
  simulate();
  return 0;
}

