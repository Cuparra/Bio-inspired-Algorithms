#ifndef CROSSOVER_H
#define CROSSOVER_H

#include "math.h"
#include "Population.h"

// Population, Father, Mother, Child1 and Child2
inline int OrderCrossover(Population *, Organism *, Organism *, Organism *, Organism *);

inline int PMXCrossover(Population *, Organism *, Organism *, Organism *, Organism *);

inline int InverOverCrossover(Population *, Organism *, Organism *, Organism *, Organism *);

inline int MixCrossover(Population *, Organism *, Organism *, Organism *, Organism *);

#endif
