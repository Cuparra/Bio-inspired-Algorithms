#include "Selection.h"

inline int TournamentSelection(Population *P){

    int i;
    int SizeOfPopulation        = P->SizeOfPopulation;
    int SizeOfSelection         = P->SizeOfSelection;
    Organism *CurrGeneration    = P->CurrGeneration;

    int best = rand()%SizeOfPopulation;

    for(i=0; i<SizeOfSelection; i++){

        int temp = rand()%SizeOfPopulation;

        if(CurrGeneration[temp].fitness > CurrGeneration[best].fitness)
            best = temp;

    }

    return best;
}

double Sumfitness(Population *P){

    int SizeOfPopulation        = P->SizeOfPopulation;
    double TotalFitness         = 0.0;
    Organism *CurrGeneration    = P->CurrGeneration;

    while(SizeOfPopulation--)
        TotalFitness += CurrGeneration[SizeOfPopulation].fitness;

    return TotalFitness;

}

inline int RouletteWheel(Population *P, double TotalFitness){

    int organism                = -1;
    double stopPoint            = 0.0;
    Organism *CurrGeneration    = P->CurrGeneration;
    double randomNumber         = ( (double) rand() / RAND_MAX);

    do{
        stopPoint += ( CurrGeneration[++organism].fitness/ TotalFitness );
    }while(stopPoint < randomNumber);

    return organism;
}
