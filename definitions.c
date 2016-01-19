#DEFINE BEESIZE     100
#DEFINE PLANTSIZE   100

#DEFINE beta        5.0

const float payoff[2][2] = {
    {1, -0.5},
    {0.5, -1}
};

typedef struct BeeAgent {
    int id;
    int * neighbors;
    float fitness;
} BeeAgent;

typedef struct PlantAgent {
    int id;
    int * neighbors;
    float fitness;
} PlantAgent;

typedef BeeAgent *   BeeSociety;
typedef PlantAgent * PlantSociety;
