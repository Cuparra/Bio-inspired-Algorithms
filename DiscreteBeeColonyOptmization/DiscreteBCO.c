#include "DiscreteBCO.h"

static void GenerateFlower(int *F, int Dimension, int HighestNumber, int LowerstNumber){

    int i;

    for(i=0;i<Dimension;i++)
        F[i] = rand()%(HighestNumber-LowerstNumber+1) + LowerstNumber;

}

Colony *CreateColony(int SizeOfEmployed, int SizeOfOnlooker, int Dimension, int HighestNumber, int LowerstNumber){

    int i;
    Colony *C = (Colony*)malloc(sizeof(Colony));

    C->SizeOfEmployed   = SizeOfEmployed;
    C->SizeOfOnlooker   = SizeOfOnlooker;
    C->HighestNumber    = HighestNumber;
    C->LowerstNumber    = LowerstNumber;
    C->Dimension        = Dimension;
    C->TrialLimit       = ( (SizeOfEmployed+SizeOfOnlooker)*Dimension )/4;

    C->BestBee          = (Bee*)calloc(1,sizeof(Bee));
    C->Employed         = (Bee*)calloc(SizeOfEmployed,sizeof(Bee));

    C->BestBee->Flower   = (int*)malloc(Dimension*sizeof(int));

    for(i=0;i<SizeOfEmployed;i++){
        C->Employed[i].Flower = (int *)malloc(Dimension*sizeof(int));
        GenerateFlower(C->Employed[i].Flower,Dimension,HighestNumber,LowerstNumber);
    }

    return C;
}

static void CopyFlower(int *s, int *v, int Dimension){

    while(Dimension--)
        s[Dimension] = v[Dimension];

}

static int RouletteWheel(Bee *Employed, double TotalFitness){

    int i                    = -1;
    int stopPoint            = 0.0;
    int randomNumber         = ( (double) rand() / RAND_MAX);

    do{
        stopPoint += ( Employed[++i].Fitness/ TotalFitness );
    }while(stopPoint < randomNumber);

    return i;
}

static inline int ChooseBee(int i, int SizeOfEmployed){

    int bee;

    do{
        bee = rand()%SizeOfEmployed;
    }while(bee == i);

    return bee;
}

static inline int RandInt(int a, int b){

    int min = (a>b) ? b : a;
    int max = (a>b) ? a : b;

    return rand()%(max-min+1) + min;
}

static inline void SearchFlowers(Bee *Employed, int i, int SizeOfEmployed, int Dimension, double (*EvaluateFlower)(Bee *)){

    int j = rand()%Dimension;
    int k = ChooseBee(i,SizeOfEmployed);

    int Xij      = Employed[i].Flower[j];
    int Xkj      = Employed[k].Flower[j];

    int newXij   = RandInt(Xij,Xkj);

    Employed[i].Flower[j]   = newXij;

    double newFitness       = EvaluateFlower(&Employed[i]);

    if( Employed[i].Fitness < newFitness ){

        Employed[i].Fitness = newFitness;
        Employed[i].Trial   = 0;

    }else{

        Employed[i].Flower[j] = Xij;
        ++Employed[i].Trial;
    }
}

void DiscreteBeeColonyOpt(Colony *C, double (*EvaluateFlower)(Bee *), int (*TerminationCriteria)(Colony *)){

    int LowerstNumber       = C->LowerstNumber;
    int HighestNumber       = C->HighestNumber;
    int SizeOfEmployed      = C->SizeOfEmployed;
    int SizeOfOnlooker      = C->SizeOfOnlooker;
    int Dimension           = C->Dimension;
    int TrialLimit          = C->TrialLimit;
    Bee *BestBee            = C->BestBee;
    int i;

    Bee *Employed           = C->Employed;

    while( TerminationCriteria(C) ){

        int bestIdBee       = -1;
        double totalFitness =  0;

        /*Employed Phase*/
        for(i=0;i<SizeOfEmployed;i++){

            SearchFlowers(Employed,i,SizeOfEmployed,Dimension,EvaluateFlower);
            totalFitness += Employed[i].Fitness;
        }

        /*Onlooker Phase*/
        for(i=0;i<SizeOfOnlooker;i++){

            int bee = RouletteWheel(Employed,totalFitness);
            SearchFlowers(Employed,bee,SizeOfEmployed,Dimension,EvaluateFlower);

        }

        /*Memorize Best Solution*/
        for(i=0;i<SizeOfEmployed;i++){

            if(BestBee->Fitness < Employed[i].Fitness){
                BestBee->Fitness = Employed[i].Fitness;
                bestIdBee        = i;
            }
        }

        if(bestIdBee != -1)
            CopyFlower(BestBee->Flower,Employed[bestIdBee].Flower,Dimension);

        /*Scout Phase*/
        for(i=0;i<SizeOfEmployed;i++){

            if(Employed[i].Trial >= TrialLimit){

                Employed[i].Trial   = 0;
                GenerateFlower(Employed[i].Flower,Dimension,HighestNumber,LowerstNumber);
                Employed[i].Fitness = EvaluateFlower(&Employed[i]);

            }
        }
    }

}
