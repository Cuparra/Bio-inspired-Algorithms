#ifndef PARTICLESWARMOPT_H
#define PARTICLESWARMOPT_H

#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include "Topology.h"
#include "Population.h"

#define NOTCHANGED      -1

#define MINIMIZATION     1
#define MAXIMAZATION     0

/* -10<=V<=10 */
#define sigmoid(V,M)            M/(1.0 + exp(-V))

void ExecuteSwarm(Swarm *, void (*)(Swarm *), int (*)(Swarm *));

Particle *BestGlobalParticle(Swarm *);

//Population Size, Dimension Size, aceleration 1, aceleration 2, Highest Number, Lowerst Number, Number of Sessions
Swarm *InicializeSwarm(int , int, double , double , double , double ,  int );

//Swarm, type of distribution
void DefineDistribution(Swarm *, int );

#endif
