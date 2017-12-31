#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>

#define TRUE    1
#define FALSE   0

#define DOUBLE  0
#define INT     1

typedef struct ORGANISM Organism;
typedef struct POPULATION Population;

struct ORGANISM{
    int *cromossome;
    double fitness;
};

struct POPULATION{
    Organism *CurrGeneration;
    Organism *NextGeneration;
    int SizeOfPopulation;             // size of population
    int SizeOfCromossome;             // size of cromossome
    int SizeOfSelection;
    int SizeOfBestOrganism;
    int LowestNumber;                   // lowest number in a variable range
    int HighestNumber;                  // highest number in a variable range
    int TotalIteraction;
    int Iteraction;
    void (*Mutation)(Population *);
    int  (*Crossover)(Population *, Organism *, Organism *, Organism *, Organism *);
};

// size of population, size of cromossome, Total of Iteraction, highest number in a variable range and its lowest number
Population *InitializePopulation(int , int , int, int, int, void (*)(Population *), int (*)(Population *, Organism *, Organism *, Organism *, Organism *));

// Population
void KillPopulation(Population *P);

#endif
