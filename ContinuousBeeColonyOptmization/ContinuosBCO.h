#ifndef CONTINUOUSBCO_H
#define CONTINUOUSBCO_H

#include <stdlib.h>

typedef struct BEE      Bee;
typedef struct COLONY   Colony;

struct BEE{
    double Fitness;
    double *Flower;
    int Trial;
};

struct COLONY{
    Bee *BestBee;
    Bee *Employed;
    int Dimension;
    int TrialLimit;
    int SizeOfEmployed;
    int SizeOfOnlooker;
    double HighestNumber;
    double LowerstNumber;
};

/*Colony ,  EvaluateFlower, TerminationCriteria   */
void ContinuousBeeColonyOpt(Colony *, double (*)(Bee *), int (*)(Colony *));

/*SizeOfEmployed, SizeOfOnlooker, Dimension, HighestNumber, LowerstNumber*/
Colony *CreateColony(int , int , int , double , double );
#endif
