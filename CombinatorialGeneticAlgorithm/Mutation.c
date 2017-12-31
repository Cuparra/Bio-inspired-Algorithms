#include "Mutation.h"

void ExchangeMutation(Population *P){

    int organism, allel;
    double MutationRate;
    int SizeOfBestOrganism      = P->SizeOfBestOrganism;
    Organism *NextGeneration    = P->NextGeneration;
    int SizeOfCromossome        = P->SizeOfCromossome;
    int SizeOfPopulation        = P->SizeOfPopulation;

    MutationRate = 0.05;

    //Mutation
    for (organism=SizeOfBestOrganism;   organism<SizeOfPopulation      ;organism++){

        int *cromossome = NextGeneration[organism].cromossome;

        for (allel=0;   allel<SizeOfCromossome;     allel++){

            double probability = ( (double) rand() / RAND_MAX);

            if (probability < MutationRate){

                int position1 = rand()%(SizeOfCromossome);
                int position2 = rand()%(SizeOfCromossome);

                int tempAllel           = cromossome[position1];
                cromossome[position1]   = cromossome[position2];
                cromossome[position2]   = tempAllel;
            }

        }
    }

}

void StaticMutation(Population *P){

    int organism, allel;
    double MutationRate;
    int SizeOfBestOrganism      = P->SizeOfBestOrganism;
    Organism *NextGeneration    = P->NextGeneration;
    int HighestNumber           = P->HighestNumber;
    int LowestNumber            = P->LowestNumber;
    int SizeOfCromossome        = P->SizeOfCromossome;
    int SizeOfPopulation        = P->SizeOfPopulation;

    MutationRate = 0.05;

    //Mutation
    for (organism=SizeOfBestOrganism;   organism<SizeOfPopulation      ;organism++){

        int *cromossome = NextGeneration[organism].cromossome;

        for (allel=0;   allel<SizeOfCromossome;     allel++){

            double probability = ( (double) rand() / RAND_MAX);

            if (probability < MutationRate)
                cromossome[allel] = rand()%(HighestNumber-LowestNumber+1) + LowestNumber;

        }
    }
}
