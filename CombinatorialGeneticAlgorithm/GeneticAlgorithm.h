#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

#include <stdlib.h>
#include <math.h>
#include "Selection.h"
#include "Mutation.h"
#include "Crossover.h"


// void calculate_fitness(Population *), this function calculates fitness and the programmer must define it.
// int termination_criterion(Population *), this function is defined by the programmer and return true or false.

// Population, calculate_fitness(Population *), termination_criterion(Population *)
void GeneticAlgorithm(Population *, void (*)(Organism *), int (*)(Population *));

#endif
