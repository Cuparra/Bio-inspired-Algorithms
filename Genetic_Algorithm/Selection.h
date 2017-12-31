#ifndef SELECTION_H
#define SELECTION_H

#include <stdlib.h>
#include <stdio.h>
#include "Population.h"

// Population, sum of fitness
inline int RouletteWheel(Population *, double );

// Population
double Sumfitness(Population *);

inline int TournamentSelection(Population *);

#endif
