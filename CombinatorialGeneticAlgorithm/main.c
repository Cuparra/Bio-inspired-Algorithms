#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "GeneticAlgorithm.h"

#define P_SIZE          100
#define S_MAX           50000

#define exchange(a,b) int c = a; a = b; b = c;

struct CITY{
    double x;
    double y;
};
typedef struct CITY City;

Population *P;
double **map;
int cities, travellers, s_cromossome;
int u_bound, l_bound;

void LoadFile(){

    int i,j,temp;
    FILE *Fptr = fopen("rat99.txt","r");

    fscanf(Fptr,"%d",&l_bound);
    fscanf(Fptr,"%d",&u_bound);
    fscanf(Fptr,"%d",&travellers);
    fscanf(Fptr,"%d",&cities);

    City m[cities];

    for(i=0;i<cities;i++)
        fscanf(Fptr,"%d %lf %lf",&temp,&m[i].x,&m[i].y);

    map = (double**)malloc(cities*sizeof(double*));

    for(i=0;i<cities;i++)
        map[i] = (double*)malloc(cities*sizeof(double));

    for(i=0;i<cities;i++){
        for(j=0;j<cities;j++)
            map[i][j] = sqrt( (m[i].x-m[j].x)*(m[i].x-m[j].x) + (m[i].y-m[j].y)*(m[i].y-m[j].y) );
    }

}

void FixErros(int *cromossome){

    int i,j = 0,k = 0;

    for(i=0;i<travellers-1;i++){

        while(j < s_cromossome - 1 && cromossome[j] < cities)
            ++j;

        if(j - k < l_bound+1){
            //int temp = ( l_bound + 1 - (j-k) );
            //printf("%d %d",( l_bound + 1 - (j-k) ),k);
            k = j + ( l_bound + 1 - (j-k) );
            //printf(" %d %d\n",j,temp);
            exchange(cromossome[j],cromossome[k]);

        }else if(j - k > u_bound+1){
            k = j + ( u_bound + 1 - (j-k) );
            exchange(cromossome[j],cromossome[k]);

        }else
            k = j;
    }
}

void EvaluateOrganism(Organism *O){

    int organism;

    for(organism = 0;   organism<P_SIZE     ;organism++){

        int *cromossome = O[organism].cromossome;
        double fitness  = 0.0;
        int count       = 0;
        int allel       = 0;

        FixErros(cromossome);

        while(count++ < travellers){

            int destCity;
            int sourceCity = 0;

            while(allel < s_cromossome -1 && cromossome[++allel] < cities){

                destCity = cromossome[allel];

                fitness += map[sourceCity][destCity];

                sourceCity = cromossome[allel];
            }

            sourceCity = cromossome[allel-1];

            fitness += map[sourceCity][0];
        }

        O[organism].fitness = -fitness;
    }

}

int TerminationCriteria(Population *P){

    int i;
    static int session = 0;

    printf("%d %lf\n",session,-P->CurrGeneration[0].fitness);

    if(session++ < S_MAX)
        return 1;

    //for(i=0;i<cities;i++)
      //  printf("%d ",P->CurrGeneration[0].cromossome[i]);

    return 0;

}

int main(){

    time_t t;
    srand((unsigned) time(&t));

    LoadFile();

    s_cromossome = cities + travellers - 1;

    P = InitializePopulation(P_SIZE,s_cromossome-1,S_MAX,s_cromossome,1,ExchangeMutation,OrderCrossover);

    GeneticAlgorithm(P,EvaluateOrganism,TerminationCriteria);

    return 0;
}
