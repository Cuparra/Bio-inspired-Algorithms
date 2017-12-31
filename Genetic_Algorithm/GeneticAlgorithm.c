#include "GeneticAlgorithm.h"

#define  OFFSET   sizeof(Organism)

#define Offspring(i)  &NextGeneration[i]
#define Father(i)     &CurrGeneration[i]
#define Mother(i)     &CurrGeneration[i]

#define UpdateIteraction(P) ++P->Iteraction

static void exch(Organism *O1, Organism *O2){

    double temp_fitness;
    double *temp_cromossome;

    temp_cromossome     = O1->cromossome;
    O1->cromossome      = O2->cromossome;
    O2->cromossome      = temp_cromossome;

    temp_fitness        = O1->fitness;
    O1->fitness         = O2->fitness;
    O2->fitness         = temp_fitness;

}

/* Tem quer ser modificado!!! Só pra incluir os index*/
static void ElitistStrategy(Population *P){

    int i,j;
    Organism *CurrGeneration    = P->CurrGeneration;
    int SizeOfPopulation        = P->SizeOfPopulation;
    int SizeOfBestOrganism      = P->SizeOfBestOrganism;

    for (i=0;  i<SizeOfBestOrganism;   i++){

        int temp = i;

        for (j=i+1;     j<SizeOfPopulation      ;j++){

            if (CurrGeneration[temp].fitness<CurrGeneration[j].fitness )
                temp = j;
        }

        if (i!=temp)
            exch( &CurrGeneration[i] ,&CurrGeneration[temp]);
    }

}

static void UpdateGeneration(Population *P){

    int organism;
    Organism *NextGeneration    = P->NextGeneration;
    Organism *CurrGeneration    = P->CurrGeneration;
    int SizeOfBestOrganism      = P->SizeOfBestOrganism;

    /*Não precisa fazer esta parafernalha toda... usar ponteiro*/
    for(organism=0;    organism<SizeOfBestOrganism    ;organism++)
        exch(&NextGeneration[organism],&CurrGeneration[organism]);

    Organism *temp      = P->CurrGeneration;
    P->CurrGeneration   = P->NextGeneration;
    P->NextGeneration   = temp;
}

static inline void ProduceNextGeneration(Population *P){

    int organism;
    int jump                    = 0;
    Organism *CurrGeneration    = P->CurrGeneration;
    Organism *NextGeneration    = P->NextGeneration;
    int SizeOfPopulation        = P->SizeOfPopulation;

    for (organism=P->SizeOfBestOrganism;  organism<SizeOfPopulation;  organism+=jump){

        int x = TournamentSelection(P);
        int y = TournamentSelection(P);

        jump = P->Crossover(P,Father(x),Mother(y),Offspring(organism),Offspring(organism+1));
    }

    P->Mutation( P );
}

// void EvaluateOrganism(Organism *), this function calculates fitness and the programmer must define it.
// int termination_criterion(Population *), this function is defined by the programmer and return true or false.

void GeneticAlgorithm(Population *P, void (*EvaluateOrganism)(Organism *), int (*TerminationCriteria)(Population *)){

    EvaluateOrganism(P->CurrGeneration);
    ElitistStrategy(P);

    while(TerminationCriteria(P)){

        ProduceNextGeneration(P);
        UpdateGeneration(P);
        EvaluateOrganism(P->CurrGeneration);
        ElitistStrategy(P);
        UpdateIteraction(P);
    }

}
