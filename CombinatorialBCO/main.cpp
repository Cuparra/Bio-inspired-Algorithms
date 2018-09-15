#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "CombinatorialCBO.h"

#define E_SIZE 100
#define O_SIZE 200

#define SESSION 10000

int n;
int *arr;
Colony *C;
int sizeDef;
int *defPos;
int *defNum;
int *auxArr;
int **graph;
double  maximum;
int session = 0;

void LoadFile(){

    FILE *fptr;
    int Total;
    int i;

    fptr = fopen("SodokuExpert.txt","r");

    fscanf(fptr,"%d",&n);
    Total   = n*n;
    sizeDef = 0;

    defPos = NULL;
    defNum = NULL;

    defPos = (int*)malloc(Total*sizeof(int));
    defNum = (int*)malloc(Total*sizeof(int));
    auxArr = (int*)malloc(Total*sizeof(int));

    for(i=0;i<Total;i++){

        fscanf(fptr,"%d",&defNum[sizeDef]);

        if(defNum[sizeDef] != 0){

            defPos[sizeDef]   = i;
            defNum[sizeDef]  -= 1;
            ++sizeDef;

        }
    }

}

void CreateGraph(){

    int i,j;
    int m       = sqrt(n);
    int Total   = n*n;
    int N       = m*m + 2*n - 2*m - 1;

    graph = (int**)malloc(Total*sizeof(int*));

    for(i=0;i<Total;i++)
        graph[i] = (int*)calloc(N,sizeof(int));

    for(i=0;i<Total;i++){

        int k = -1;
        int x = i/n;
        int y = i%n;

        int quadrant = m*(x/m)+y/m;

        for(j=0;j<Total;j++){

            int tempX = j/n;
            int tempY = j%n;
            int tempQ = m*(tempX/m)+tempY/m;

            if(i != j && (x == tempX || y == tempY) )
                graph[i][++k] = j;
            else if (i != j && quadrant == tempQ)
                graph[i][++k] = j;

        }
    }

    for(i=0;i<Total;i++){
        printf("%d: ",i);
        for(j=0;j<N;j++)
            printf("%d ",graph[i][j]);
        printf("\n");
    }

}

double EvaluateFlower(Bee *B){

    int m           = sqrt(n);
    int N           = m*m + 2*n - 2*m - 1;
    int Total       = n*n;
    double fitness  = 0.0;
    double  maximum = 5*n*n*n;
    int i,j;

	int *F = B->Flower;

    for(i=0;i<sizeDef;i++){
        auxArr[i]    = F[defPos[i]];
        F[defPos[i]] = defNum[i];
    }

     for(i=0;i<Total;i++){

        int num = F[i] % n;

        for(j=0;j<N;j++){

            int position    = graph[i][j];
            int temp        = F[position] % n;
            fitness         += ( (num == temp) ? 5 : 0 );

          }
      }

    for(i=0;i<sizeDef;i++)
        F[defPos[i]] = auxArr[i];

     return maximum - fitness;
}

int TerminationCriteria(Colony *C){

    printf("%d %lf\n",session,C->BestBee->Fitness);

    if(++session < SESSION)
        return 1;

    return 0;
}

void printSolution(int *F){

    int i,j;
    int m      = sqrt(n);

    printf("\n\n");

    for(i=0;i<sizeDef;i++)
        F[defPos[i]] = defNum[i];

    for(i=0;i<n;i++){

        for(j=0;j<n;j++)
            printf("%d ",F[i*n+j] % n + 1);
        printf("\n");
    }
}

int main(){

    time_t T;
    srand((unsigned) time(&T));

    LoadFile();
    CreateGraph();
    maximum = 5*n*n*n;

    C = CreateColony(E_SIZE,O_SIZE,n*n,n*n-1,0,SearchFlowers);

    CombinatorialBeeColonyOpt(C,EvaluateFlower,TerminationCriteria);

    printSolution(C->BestBee->Flower);

    return 0;
}
