#include "Population.h"

#define mod %

static double *GenerateCromossome(int HighestNumber, int LowestNumber, int SizeOfCromossome){

    int allel;
    double *cromossome = (double*)malloc( SizeOfCromossome*sizeof(double) );

    for(allel=0; allel<SizeOfCromossome ;allel++)
        cromossome[allel] = ( (double) rand() / RAND_MAX)*(HighestNumber-LowestNumber) + LowestNumber;

    return cromossome;
}

static void GenerateOrganism(Population *P){

    int organism;
    Organism *CurrGeneration    = P->CurrGeneration;
    Organism *NextGeneration    = P->NextGeneration;
    int  LowestNumber           = P->LowestNumber;
    int  HighestNumber          = P->HighestNumber;
    int SizeOfCromossome        = P->SizeOfCromossome;
    int SizeOfPopulation        = P->SizeOfPopulation;


    for(organism=0; organism<SizeOfPopulation ;organism++){

        CurrGeneration[organism].cromossome    = GenerateCromossome(HighestNumber,LowestNumber,SizeOfCromossome);
        NextGeneration[organism].cromossome    = GenerateCromossome(HighestNumber,LowestNumber,SizeOfCromossome);
        NextGeneration[organism].fitness       = 0;
        CurrGeneration[organism].fitness       = 0;

    }

}

Population *InitializePopulation(int SizeOfPopulation, int SizeOfCromossome, int TotalIteraction, int HighestNumber, int LowestNumber, void (*Mutation)(Population *), int (*Crossover)(Population *, Organism *, Organism *, Organism *, Organism *)){

    Population *P = (Population*)malloc(sizeof(Population));

    P->CurrGeneration     = (Organism*)malloc(SizeOfPopulation*sizeof(Organism));
    P->NextGeneration     = (Organism*)malloc(SizeOfPopulation*sizeof(Organism));
    P->SizeOfBestOrganism = SizeOfPopulation < 10 ? 1 : SizeOfPopulation*(0.1);
    P->SizeOfSelection    = SizeOfPopulation < 60 ? 3 : 0.05*SizeOfPopulation;
    P->SizeOfCromossome   = SizeOfCromossome;
    P->SizeOfPopulation   = SizeOfPopulation;
    P->TotalIteraction    = TotalIteraction;
    P->HighestNumber      = HighestNumber;
    P->LowestNumber       = LowestNumber;
    P->Mutation           = Mutation;
    P->Crossover          = Crossover;
    P->Iteraction         = 0;

    int result = SizeOfPopulation - P->SizeOfBestOrganism;

    if(result mod 2 != 0)
        --P->SizeOfBestOrganism;

    GenerateOrganism(P);

    return P;
}
/*
void KillPopulation(Population *P){

    int organism;
    int SizeOfPopulation    = P->SizeOfPopulation;
    int SizeOfBestOrganism  = P->SizeOfBestOrganism;

    for(organism=0; organism<SizeOfPopulation ;organism++){
        free(P->CurrGeneration[organism].cromossome);
        free(P->NextGeneration[organism].cromossome);
    }

    for(organism=0; organism<SizeOfBestOrganism ;organism++)
        free(P->BestOrganism[organism].cromossome);

    free(P->CurrGeneration);
    free(P->NextGeneration);
    free(P->BestOrganism);
    free(P);
}*/
