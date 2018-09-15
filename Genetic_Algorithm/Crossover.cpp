#include "Crossover.h"

// Uniform Crossover
int UniformCrossover(Population *P, Organism *Father, Organism *Mather, Organism *Child1, Organism *Child2){

    int allel;
    double *Cromossome1         = Father->cromossome;
    double *Cromossome2         = Mather->cromossome;
    double *CromossomeChild1    = Child1->cromossome;
    double *CromossomeChild2    = Child2->cromossome;
    int SizeOfCromossome        = P->SizeOfCromossome;
    double HighestNumber        = P->HighestNumber;
    double LowestNumber         = P->LowestNumber;

    double probability = ( (double) rand() / RAND_MAX);

    if (probability > 0.7)
        return 0;

    for (allel=0 ;      allel<SizeOfCromossome        ;allel++){

        double r = 2*( (double) rand()/RAND_MAX ) - 1;
        double allel1   = r*Cromossome1[allel] + (1-r)*Cromossome2[allel];
        double allel2   = r*Cromossome2[allel] +  (1-r)*Cromossome1[allel];

        if(allel1 > HighestNumber)
            allel1 = HighestNumber;
        if(allel2 > HighestNumber)
            allel2 = HighestNumber;

        if(allel1 < LowestNumber)
            allel1 = LowestNumber;
        if(allel2 < LowestNumber)
            allel2 = LowestNumber;

        if ( rand()%10 < 5){
            CromossomeChild1[allel] = allel1;
            CromossomeChild2[allel] = allel2;
        }
        else{
            CromossomeChild1[allel] = allel2;
            CromossomeChild2[allel] = allel1;
        }
    }

    return 2;

}
