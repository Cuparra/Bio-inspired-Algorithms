#include "CombinatorialCBO.h"

void ReverseInsertion(int *Flower,int j, int k){

    int i;
    int min = (j > k) ? k : j;
    int max = (j > k) ? j : k;

    int temp = Flower[max];

    for(i = max;i > min; i--)
        Flower[i] = Flower[i-1];

    Flower[i] = temp;

}

void InsertionOperation(int *Flower,int j, int k){

    int i;
    int min = (j > k) ? k : j;
    int max = (j > k) ? j : k;

    int temp = Flower[min];

    for(i = min;i < max; i++)
        Flower[i] = Flower[i+1];

    Flower[i] = temp;
}

void InvertionOperation(int *Flower,int j, int k){

    int i;
    int min = (j > k) ? k : j;
    int max = (j > k) ? j : k;

    int lenght = (max - min + 1)/2;

    for(i = 0;i < lenght; i++)
        exch(Flower[min+i],Flower[max-i]);
}

static void ReverseInvertion(int *Flower,int j, int k){

    InvertionOperation(Flower,j,k);
}

static int *GenerateSample(int Dimension, int LowerstNumber){

    int i;
    int *Sample = (int*)malloc(Dimension*sizeof(int));

    for(i=0;i<Dimension;i++)
        Sample[i] = LowerstNumber++;

    return Sample;
}

static void GenerateFlower(int *Flower, int *Sample, int Dimension){

    int i;
    int op = rand()%3;
    int j  = rand()%Dimension;
    int k  = rand()%Dimension;

    if (op == SWAP_OP){
        exch(Sample[j],Sample[k]);
    }else if(op == INSERTION_OP){
        InsertionOperation(Sample,j,k);
    }else
        InvertionOperation(Sample,j,k);

    for(i=0;i<Dimension;i++)
        Flower[i] = Sample[i];
}

Colony *CreateColony(int SizeOfEmployed, int SizeOfOnlooker, int Dimension, int HighestNumber, int LowerstNumber, void (*SearchFlowers)(Bee *, int, double (*)(Bee*)) ){

    int i;
    Colony *C   = (Colony*)malloc(sizeof(Colony));
    C->Sample   = GenerateSample(Dimension,LowerstNumber);

    C->SearchFlowers    = SearchFlowers;
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
        GenerateFlower(C->Employed[i].Flower,C->Sample,Dimension);
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

inline void SearchFlowers(Bee *Employed, int Dimension, double (*EvaluateFlower)(Bee *)){

    int j;
    int k;
    int op      = rand()%3;
    int *Flower = Employed->Flower;

    do{
        j  = rand()%Dimension;
        k  = rand()%Dimension;
    }while(j == k);

    if (op == SWAP_OP){
        exch(Flower[j],Flower[k]);
    }else if (op == INSERTION_OP){
        InsertionOperation(Flower,j,k);
    }else
        InvertionOperation(Flower,j,k);

    double newFitness = EvaluateFlower(Employed);

    if( Employed->Fitness < newFitness ){

        Employed->Fitness = newFitness;
        Employed->Trial   = 0;

    }else{

        if (op == SWAP_OP){
            exch(Flower[j],Flower[k]);
        }else if(op == INSERTION_OP){
            ReverseInsertion(Flower,j,k);
        }else
            ReverseInvertion(Flower,j,k);

        ++Employed->Trial;
    }
}

void CombinatorialBeeColonyOpt(Colony *C, double (*EvaluateFlower)(Bee *), int (*TerminationCriteria)(Colony *)){

    void (*SearchFlowers)(Bee *, int, double (*)(Bee*)) = C->SearchFlowers;
    int SizeOfEmployed                                  = C->SizeOfEmployed;
    int SizeOfOnlooker                                  = C->SizeOfOnlooker;
    int Dimension                                       = C->Dimension;
    int TrialLimit                                      = C->TrialLimit;
    Bee *BestBee                                        = C->BestBee;
    int i;

    Bee *Employed                                       = C->Employed;

    while( TerminationCriteria(C) ){

        int bestIdBee       = -1;
        double totalFitness =  0;

        /*Employed Phase*/
        for(i=0;i<SizeOfEmployed;i++){

            SearchFlowers(&Employed[i],Dimension,EvaluateFlower);
            totalFitness += Employed[i].Fitness;
        }

        /*Onlooker Phase*/
        for(i=0;i<SizeOfOnlooker;i++){

            int bee = RouletteWheel(Employed,totalFitness);
            SearchFlowers(&Employed[bee],Dimension,EvaluateFlower);

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
                GenerateFlower(Employed[i].Flower,C->Sample,Dimension);
                Employed[i].Fitness = EvaluateFlower(&Employed[i]);

            }
        }
    }

}
