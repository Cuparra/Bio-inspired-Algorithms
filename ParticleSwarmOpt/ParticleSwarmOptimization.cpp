#include "ParticleSwarmOptimization.h"

#define  ALFA       0.975

#define MINIMUM     0.4
#define MAXIMUM     0.9

#define AND         &&
#define OR          ||

#define SWAP(a,b)   int temp = a; a = b; b = temp

static void UniformGeneration(Swarm *S){

    int i,j;
    int SizeOfDimention = S->SizeOfDimention;
    int HighestNumber   = S->HighestNumber;
    int LowestNumber    = S->LowestNumber;
    int SizeOfSwarm     = S->SizeOfSwarm;

    Particle *Particles = S->Particles;

    for(i=0;i<SizeOfSwarm;i++){

        double *Position = (double*)calloc(SizeOfDimention, sizeof(double));

        for(j=0;j<SizeOfDimention;j++)
                Position[j] = ((double) rand() / RAND_MAX)*(HighestNumber-LowestNumber) + LowestNumber;

        Particles[i].CurrentPosition = Position;
    }

}

void DefineDistribution(Swarm *S, int Distribution){

   if(Distribution == UNIFORM)
        UniformGeneration(S);
   else
        UniformGeneration(S);
}

Swarm *InicializeSwarm(int SizeOfSwarm, int SizeOfDimention, double accelaration1, double accelaration2, double HighestNumber, double LowestNumber,  int MaxInteraction){

    int i;
    Swarm *S                = (Swarm*)malloc(sizeof(Swarm));
    S->SizeOfSwarm          = SizeOfSwarm;
    S->MaxInteraction       = MaxInteraction;
    S->SizeOfDimention      = SizeOfDimention;
    S->accelaration1        = accelaration1;
    S->accelaration2        = accelaration2;
    S->weight               = MAXIMUM;
    S->Cycle                = 0;

    S->HighestNumber        = HighestNumber;
    S->LowestNumber         = LowestNumber;

    S->Particles            = (Particle*)calloc(SizeOfSwarm,sizeof(Particle));

    Particle *Particles     = S->Particles;

    for(i=0;i<SizeOfSwarm;i++){

        Particles[i].ParticleBestFitness     =  INT_MAX;
        Particles[i].CurrentFitness          =  INT_MAX;
        Particles[i].LocalBestFitness        =  INT_MAX;
        Particles[i].Velocity                = (double*)calloc(SizeOfDimention, sizeof(double));
        Particles[i].ParticleBestPosition    = (double*)calloc(SizeOfDimention, sizeof(double));
        Particles[i].LocalBestPosition       = Particles[i].ParticleBestPosition;
    }

    return S;
}

static inline void CopyPosition(double *Pos1, double *Pos2, int Size){

    while(Size--)
        Pos1[Size] = Pos2[Size];

}

/* Update the velocity and position*/
static void UpdateParticles(Swarm *S){

    int i,j;

    double w                = S->weight;
    Particle *particle      = S->Particles;
    double c1               = S->accelaration1;
    double c2               = S->accelaration2;
    double HighestNumber    = S->HighestNumber;
    double LowestNumber     = S->LowestNumber;
    int SizeOfDimention     = S->SizeOfDimention;
    int SizeOfSwarm         = S->SizeOfSwarm;

    for(i=0;i<SizeOfSwarm;i++){

        double *velocity    = particle[i].Velocity;
        double *x           = particle[i].CurrentPosition;
        double *lb          = particle[i].LocalBestPosition;
        double *b           = particle[i].ParticleBestPosition;

        for(j=0;j<SizeOfDimention;j++){

            double r1      = ( (double) rand()/RAND_MAX );
            double r2      = ( (double) rand()/RAND_MAX );

            velocity[j]    = w*velocity[j] + c1*r1*(b[j] - x[j]) + c2*r2*(lb[j] - x[j]);
            x[j]           = x[j] + velocity[j];

        }
    }

}

static void SetParticleBestPosition(Swarm *S){

    int i;
    Particle *particle              = S->Particles;
    int SizeOfDimention             = S->SizeOfDimention;
    int SizeOfSwarm                 = S->SizeOfSwarm;

    for(i=0;i<SizeOfSwarm;i++){

        if( particle[i].CurrentFitness < particle[i].ParticleBestFitness ){

            particle[i].ParticleBestFitness = particle[i].CurrentFitness;
            CopyPosition(particle[i].ParticleBestPosition, particle[i].CurrentPosition,SizeOfDimention);

        }
   }

}

static void SetNeighborhoodBestPosition(Swarm *S){

    int i,j;
    Particle *particle              = S->Particles;
    int SizeOfNeighbor              = S->SizeOfNeighbor;
    int SizeOfSwarm                 = S->SizeOfSwarm;

    for(i=0;i<SizeOfSwarm;i++){

        int bestIdxNeighbor = NOTCHANGED;

        for(j=0;j<SizeOfNeighbor;j++){

            int idx = particle[i].Neighbor[j];

            if( particle[i].LocalBestFitness > particle[idx].ParticleBestFitness ){

                bestIdxNeighbor                = idx;
                particle[i].LocalBestFitness   = particle[idx].ParticleBestFitness;
            }
        }

        if(bestIdxNeighbor != NOTCHANGED)
            particle[i].LocalBestPosition = particle[bestIdxNeighbor].ParticleBestPosition;
    }

}

static void SetBestGlobalPosition(Swarm *S){

    int i;
    int idx = 0;
    Particle *Particles             = S->Particles;
    int SizeOfSwarm                 = S->SizeOfSwarm;

    for(i=1;i<SizeOfSwarm;i++){

        if( Particles[i].ParticleBestFitness < Particles[idx].ParticleBestFitness )
            idx = i;

    }

    S->BestParticle = &Particles[idx];

}

void ExecuteSwarm(Swarm *S, void (*EvaluateParticles)(Swarm *), int (*TerminationCriteria)(Swarm *)){

    int MaxInteraction              = S->MaxInteraction;

    do{

        /*Set the fitness of all particles*/
        EvaluateParticles(S);

        /*Set particle best position*/
        SetParticleBestPosition(S);

        /*Set the neighborhood(local) best position */
        SetNeighborhoodBestPosition(S);

        /*Set Best Global Position*/
        SetBestGlobalPosition(S);

        /* Update the velocity and position*/
        UpdateParticles(S);

        /*Update weight and sigma*/
        ++S->Cycle;
        S->weight = (MAXIMUM - MINIMUM)*( 1.0*(MaxInteraction - S->Cycle)/MaxInteraction ) + MINIMUM;

    }while(TerminationCriteria(S));

}
