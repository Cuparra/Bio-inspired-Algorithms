#include "Population.h"

#define mod %

int *GenerateCommoArray(int SizeOfCromossome, int HighestNumber, int LowestNumber){

    int allel = 0;
    int *CommomArray = (int*)malloc(SizeOfCromossome*sizeof(int));

    while(LowestNumber <= HighestNumber)
        CommomArray[allel++] = LowestNumber++;

    return CommomArray;
}

static int *GenerateCromossome(int *CommomArray, int SizeOfCromossome){

    int allel;

    int *cromossome = (int*)malloc(SizeOfCromossome*sizeof(int));

    for(allel=0; allel<SizeOfCromossome ;allel++)
        cromossome[allel] = CommomArray[allel];

    int position1 = rand()%(SizeOfCromossome);
    int position2 = rand()%(SizeOfCromossome);

    int tempAllel           = cromossome[position1];
    cromossome[position1]   = cromossome[position2];
    cromossome[position2]   = tempAllel;

    CommomArray[position1]  = cromossome[position1];
    CommomArray[position2]  = cromossome[position2];

    return cromossome;
}


static void GenerateOrganism(Population *P){

    int organism;
    Organism *CurrGeneration    = P->CurrGeneration;
    Organism *NextGeneration    = P->NextGeneration;
    int SizeOfCromossome        = P->SizeOfCromossome;
    int SizeOfPopulation        = P->SizeOfPopulation;

    int *CommomArray = GenerateCommoArray(SizeOfCromossome,P->HighestNumber,P->LowestNumber);

    for(organism=0; organism<SizeOfPopulation ;organism++){

        CurrGeneration[organism].cromossome    = GenerateCromossome(CommomArray, SizeOfCromossome);
        NextGeneration[organism].cromossome    = GenerateCromossome(CommomArray, SizeOfCromossome);
        NextGeneration[organism].fitness       = 0;
        CurrGeneration[organism].fitness       = 0;

    }

    free(CommomArray);
}

Population *InitializePopulation(int SizeOfPopulation, int SizeOfCromossome, int TotalIteraction, int HighestNumber, int LowestNumber, void (*Mutation)(Population *), int (*Crossover)(Population *, Organism *, Organism *, Organism *, Organism *)){

    Population *P         = (Population*)malloc(sizeof(Population));

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

    GenerateOrganism(P);

    int result = SizeOfPopulation - P->SizeOfBestOrganism;

    if(result mod 2 != 0)
        --P->SizeOfBestOrganism;

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
