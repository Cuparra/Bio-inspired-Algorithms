#ifndef COMBINATORIALCBO_H
#define COMBINATORIALCBO_H

#include <stdlib.h>

#define SWAP_OP         0
#define INSERTION_OP    1
#define INVERTION_OP    2

#define exch(x, y)       {int z = x; x = y; y = z;}

typedef struct BEE      Bee;
typedef struct COLONY   Colony;

struct BEE{
    double Fitness;
    int *Flower;
    int Trial;
};

struct COLONY{
    int *Sample;
    Bee *BestBee;
    Bee *Employed;
    int Dimension;
    int TrialLimit;
    int SizeOfEmployed;
    int SizeOfOnlooker;
    int HighestNumber;
    int LowerstNumber;
    void (*SearchFlowers)(Bee *, int, double (*)(Bee*));
};

/*Colony ,  EvaluateFlower, TerminationCriteria   */
void CombinatorialBeeColonyOpt(Colony *, double (*)(Bee *), int (*)(Colony *));

/*SizeOfEmployed, SizeOfOnlooker, Dimension, HighestNumber, LowerstNumber, SearchFlowers*/
Colony *CreateColony( int , int , int , int , int , void (*)(Bee *, int, double (*)(Bee*)) );


inline void SearchFlowers(Bee *, int , double (*)(Bee *));
#endif
