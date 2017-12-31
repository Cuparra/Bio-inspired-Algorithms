#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>

#define TRUE    1
#define FALSE   0

typedef struct ORGANISM Organism;
typedef struct POPULATION Population;

struct ORGANISM{
    double *cromossome;
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
typedef struct POPULATION Population;

// size of population, size of cromossome, Total Iteraction, highest number in a variable range and its lowest number
Population *InitializePopulation(int , int , int, int, int, void (*)(Population *), int (*)(Population *, Organism *, Organism *, Organism *, Organism *));


// Population
void KillPopulation(Population *P);

#endif
