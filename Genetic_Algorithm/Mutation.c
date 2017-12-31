
#include "Crossover.h"

void StaticMutation(Population *P){

    int organism, allel;
    double MutationRate;
    int SizeOfBestOrganism      = P->SizeOfBestOrganism;
    Organism *NextGeneration    = P->NextGeneration;
    int HighestNumber           = P->HighestNumber;
    int LowestNumber            = P->LowestNumber;
    int SizeOfCromossome        = P->SizeOfCromossome;
    int SizeOfPopulation        = P->SizeOfPopulation;

    MutationRate = 0.02;

    //Mutation
    for (organism=SizeOfBestOrganism;   organism<SizeOfPopulation      ;organism++){

        double *cromossome = NextGeneration[organism].cromossome;

        for (allel=0;   allel<SizeOfCromossome;     allel++){

            double probability = ( (double) rand() / RAND_MAX);

            if (probability < MutationRate)
                cromossome[allel] = ( (double) rand() / RAND_MAX)*(HighestNumber-LowestNumber) + LowestNumber;

        }
    }

}

void SchutzMutation(Population *P){

    int organism, allel;
    int SizeOfBestOrganism      = P->SizeOfBestOrganism;
    Organism *NextGeneration    = P->NextGeneration;
    int HighestNumber           = P->HighestNumber;
    int LowestNumber            = P->LowestNumber;
    int SizeOfCromossome        = P->SizeOfCromossome;
    int SizeOfPopulation        = P->SizeOfPopulation;
    int TotalIteraction         = P->TotalIteraction;
    int Iteraction              = P->Iteraction;

    double MutationRate = 0.10*((TotalIteraction - Iteraction)/TotalIteraction) + 0.05;

    //Mutation
    for (organism=SizeOfBestOrganism;   organism<SizeOfPopulation      ;organism++){

        double *cromossome = NextGeneration[organism].cromossome;

        for (allel=0;   allel<SizeOfCromossome;     allel++){

            double probability = ( (double) rand() / RAND_MAX);

            if (probability < MutationRate)
                cromossome[allel] = ( (double) rand() / RAND_MAX)*(HighestNumber-LowestNumber) + LowestNumber;

        }
    }

}
