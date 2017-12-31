#ifndef DISCRETEBCO_H
#define DISCRETEBCO_H

#include <stdlib.h>

typedef struct BEE      Bee;
typedef struct COLONY   Colony;

struct BEE{
    double Fitness;
    int *Flower;
    int Trial;
};

struct COLONY{
    Bee *BestBee;
    Bee *Employed;
    int Dimension;
    int TrialLimit;
    int Modifications;
    int HighestNumber;
    int LowerstNumber;
    int SizeOfEmployed;
    int SizeOfOnlooker;
};

/*Colony ,  EvaluateFlower, TerminationCriteria   */
void DiscreteBeeColonyOpt(Colony *, double (*)(Bee *), int (*)(Colony *));

/*SizeOfEmployed, SizeOfOnlooker, Dimension, HighestNumber, LowerstNumber*/
Colony *CreateColony(int , int , int , int,  int );
#endif
