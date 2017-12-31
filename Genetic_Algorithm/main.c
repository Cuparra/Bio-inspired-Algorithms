#include <stdio.h>
#include <time.h>
#include <math.h>

#include "GeneticAlgorithm.h"

#define SESSION         10000
#define CONNECTED       1
#define NOT_CONNECTED   0
#define P_SIZE          100

#define NUMCOLOR        7

int **graph;
int maxColor;
int numVertices;
int numOfEdges;

Population *P;

void LoadFile(){

    FILE *fptr;
    int i,num1,num2;

    if ( ( fptr = fopen("queen6.txt","r") ) == NULL)
        return;

    fscanf(fptr,"%d %d",&numVertices,&numOfEdges);

    graph = (int**)calloc(numVertices,sizeof(int*));

    for(i=0;i<numVertices;i++)
        graph[i]  = (int*)calloc(numVertices,sizeof(int));

    for(i=0;i<numOfEdges;i++){

            fscanf(fptr,"%d %d\n",&num1,&num2);
            graph[num1-1][num2-1] = graph[num2-1][num1-1] = CONNECTED;
    }

    fclose(fptr);
}

void EvaluateOrganism(Organism *O){

    int organism    = 0;

    while(++organism<P_SIZE){

        int i,j;
        int hit             = 0;
        double *cromossome  = O[organism].cromossome;

        for(i=0;i<numVertices;i++){

            int color1 = floor(sigmoid( cromossome[i] , NUMCOLOR));

            for(j=0;j<numVertices;j++){

                int color2 = floor(sigmoid( cromossome[j] , NUMCOLOR));

                if(graph[i][j] == CONNECTED && color1 == color2)
                            hit += 1;
            }
        }

        O[organism].fitness = ( (double) (2*numOfEdges)/(hit+1) );

    }

}

int TerminationCriteria(Population *P){

    int i;
    static int session          = 0;
    double fitness              = P->CurrGeneration[0].fitness;

    printf("%d %lf\n",session,fitness);

    if( ++session < SESSION)
        return 1;

    for(i=0;i<P->SizeOfCromossome;i++){

        int colour = floor( sigmoid( P->CurrGeneration[0].cromossome[i] , NUMCOLOR) );
        printf("%d ", colour );

    }

    return 0;
}

int main(){

    time_t T;
    srand((unsigned) time(&T));

    LoadFile();

    P = InitializePopulation(P_SIZE,numVertices,SESSION,3,-3,StaticMutation,UniformCrossover);

    GeneticAlgorithm(P,EvaluateOrganism,TerminationCriteria);

    return 0;
}

