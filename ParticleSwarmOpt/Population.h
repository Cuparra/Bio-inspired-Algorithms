
#ifndef POPULATION_H
#define POPULATION_H

#define UNIFORM 1

typedef struct PARTICLE{
    int *Neighbor;
    double *Velocity;

    double CurrentFitness;
    double LocalBestFitness;
    double ParticleBestFitness;

    double *CurrentPosition;
    double *LocalBestPosition;
    double *ParticleBestPosition;
}Particle;

typedef struct SWARM{
    Particle *Particles;
    Particle *BestParticle;
    int SizeOfNeighbor;
    int Topology;
    int SizeOfDimention;
    int SizeOfSwarm;
    double accelaration1;
    double accelaration2;
    int MaxInteraction;
    double weight;
    double Range;
    double HighestNumber;
    double LowestNumber;
    int Cycle;
}Swarm;

#endif
