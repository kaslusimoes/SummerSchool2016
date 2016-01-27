#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define PI (3.1415926535897932384626433832795028841971693994L)
#define E (2.7182818284590452353602874713526624977572470937L)
#define Beta (0.5L)
#define endl '\n'

const ll N = 5,
 M = 6,
 MAX = N + M + 1,
 MAX_EDGE = 15,
 MAX_DEG = 3,
 ITERATIONS = 10000,
 GENERATIONS = 10000;
double Prop1 = 0.5, Prop2 = 0.2;
double S = 0, T = 0;

double payoff[2][2] =
 {
  {1, T},
  {S, 0}
 },
 payoff_2[2][2] =
 {
  {1, T},
  {S, 0}
 };

int strategy[MAX];
double fitness_value[MAX];
bool visited[MAX];
set<int> G[MAX];
vector<int> G2[MAX];

void print() {
  cout << "-------------------------------------------------" << endl;
  for (int i = 0; i < N; ++i)
    cout << i << ", strategy: " << strategy[i] << endl;
  cout << "----------------------------" << endl;
  for (int i = 0; i < N; ++i)
    cout << i << ", strategy: " << strategy[i] << endl;
  cout << "-------------------------------------------------" << endl;
}


double rand_num() {
  return (double) rand() / RAND_MAX;
}

double interaction(int a, int b) {
  if (a < N && b < N)
    return payoff[strategy[a]][strategy[b]];
  return payoff_2[strategy[a]][strategy[b]];
}

long double change_probability(double fitnessA, double fitnessB) {
  return 1.0 / (1 + pow(E, -Beta * (fitnessA - fitnessB)));
}

double calculate_fitness(ll a) {
  fill_n(visited, MAX, 0);
  double my_fitness = 0;
  for (auto &j: G[a])
    if (!visited[j] && j != a) {
      my_fitness += interaction(a, j);
      visited[j] = 1;
    }
  return fitness_value[a] = my_fitness;
}

void recalculate_all_fitness() {
  for (int i = 0; i < N + M; ++i)
    calculate_fitness(i);
}

double fitness(int a) {
  return fitness_value[a];
}

void build_random() {
  int j = 0;
  while (j < MAX_EDGE) {
    ll k = rand() % N, l = (rand() % M) + N;
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
      ll k = (rand() % M) + N;
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

void set_initial_strategy(double cooperator_percent1, double cooperator_percent2) {
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

  for (int a = 0; a < N + M; ++a) {
    fill_n(visited, MAX, 0);
    for (auto &i : G[a])
      for (auto &j: G[i])
        if (!visited[j] && j != a) {
          G2[a].push_back(j);
          visited[j] = 1;
        }
  }

  set_initial_strategy(Prop1, Prop2);
}

void simulate_synchronous() {

}

void simulate_asynchronous() {
  ll it = ITERATIONS;
  while (it--) {
    ll dude = (it & 1) ? rand() % N : rand() % M + N,
     other_dude;
    if (G2[dude].size() == 0) {
      it++;
      continue;
    }
    other_dude = G2[dude][(rand() % (G2[dude].size()))];
    double l = rand_num();
    long double prob = change_probability(calculate_fitness(dude), calculate_fitness(other_dude));
    if (l <= prob && strategy[dude] != strategy[other_dude]) {
      strategy[dude] = strategy[other_dude];
    }
  }
  cout << "Simulation is over" << endl;
}

void simulate() {
  simulate_asynchronous();
//  simulate_synchronous();
}

int main() {
  srand(time(NULL));
  build_network();
  print();
  simulate();
  print();
  return 0;
}

