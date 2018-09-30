#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#include "ParticleSwarmOptimization.h"

#define P_SIZE          100
#define SESSION         100
#define D_SIZE          2

Swarm *S;

/* exemple of a function to be avaluated. */
void EvaluateParticles(Swarm *S){

    int i,j;
    Particle *P = S->Particles;

    for(i=0;i<P_SIZE;i++){

        double arg1 = 0;
        double arg2 = 0;
        double *x = P[i].CurrentPosition;

        for(j=0;j<D_SIZE;j++){

            arg1 += x[j]*x[j];
            arg2 += cos(2*M_PI*x[j]);

        }

        P[i].CurrentFitness = -20*exp(-0.2*sqrt( (1/D_SIZE)*(arg1) ) ) - exp( (1/D_SIZE)*( arg2) ) + M_E + 20;

    }
}

int TerminationCriteria(Swarm *S){

    int i;
    static int session          = 0;
    double fitness              = S->BestParticle->ParticleBestFitness;

    printf("%d %lf\n",session,fitness);

    if( ++session < SESSION )
        return 1;

    for(i=0;i<S->SizeOfDimention;i++)
        printf("%lf ",S->BestParticle->ParticleBestPosition[i]);

    return 0;
}


int main(){

    time_t t;
    srand((unsigned) time(&t));

    Swarm *S = InicializeSwarm(P_SIZE,D_SIZE,2,2,1,-1,SESSION);
    DefineDistribution(S,UNIFORM);
    DefineTopology(S,MESH);

    ExecuteSwarm(S,EvaluateParticles,TerminationCriteria);

    return 0;
}
