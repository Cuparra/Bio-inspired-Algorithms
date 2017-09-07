
#include "Topology.h"

static void ConstructRing(Swarm *S){

    int i;
    int SizeOfNeighbor  = 2;
    Particle *Particles = S->Particles;
    int SizeOfSwarm     = S->SizeOfSwarm;
    S->SizeOfNeighbor   = SizeOfNeighbor;


    for(i=0; i<SizeOfSwarm;i++)
        Particles[i].Neighbor = (int*)malloc(SizeOfNeighbor*sizeof(int));

    for(i=1; i<SizeOfSwarm - 1; i++){

        Particles[i].Neighbor[0] = i - 1;
        Particles[i].Neighbor[1] = i + 1;

    }

    Particles[0].Neighbor[0] = SizeOfSwarm - 1;
    Particles[0].Neighbor[1] = 1;

    Particles[SizeOfSwarm - 1].Neighbor[0] = 0;
    Particles[SizeOfSwarm - 1].Neighbor[1] = SizeOfSwarm - 2;

}

static void ConstructMesh(Swarm *S){

    int i,j;
    Particle *Particles = S->Particles;
    int SizeOfSwarm     = S->SizeOfSwarm;

    int SizeOfNeighbor  = sqrt(SizeOfSwarm);

    if(SizeOfNeighbor*SizeOfNeighbor != SizeOfSwarm){
        ConstructRing(S);
        return;
    }

    S->SizeOfNeighbor = 4;

    for(i=0; i<SizeOfSwarm;i++)
        Particles[i].Neighbor = (int*)malloc(4*sizeof(int));

    for(i=0; i<SizeOfNeighbor; i++){

        for(j=0; j<SizeOfNeighbor; j++){

            int pos = i*SizeOfNeighbor + j;

            Particles[pos].Neighbor[0] = (i-1)*SizeOfNeighbor + j;
            Particles[pos].Neighbor[1] = (i+1)*SizeOfNeighbor + j;
            Particles[pos].Neighbor[2] = pos - 1;
            Particles[pos].Neighbor[3] = pos + 1;

            if(i - 1 < 0)
               Particles[pos].Neighbor[0] = (SizeOfNeighbor - 1)*SizeOfNeighbor + j;

            if(i + 1 > SizeOfNeighbor - 1)
               Particles[pos].Neighbor[1] = j;

            if(pos - 1 < i*SizeOfNeighbor)
                Particles[pos].Neighbor[2] = (i+1)*SizeOfNeighbor - 1;

            if(pos + 1 > (i+1)*SizeOfNeighbor - 1)
                Particles[pos].Neighbor[3] = i*SizeOfNeighbor;

        }
    }

}

static void ConstructTree(Swarm *S){

    int i;
    int SizeOfNeighbor  = 3;
    Particle *Particles = S->Particles;
    int SizeOfSwarm     = S->SizeOfSwarm;
    S->SizeOfNeighbor   = SizeOfNeighbor;


    for(i=0; i<SizeOfSwarm;i++)
        Particles[i].Neighbor = (int*)malloc(SizeOfNeighbor*sizeof(int));

    for(i=1; i<SizeOfSwarm; i++){

        Particles[i].Neighbor[0] = (i-1)/2;
        Particles[i].Neighbor[1] = 2*i + 1;
        Particles[i].Neighbor[2] = 2*i + 2;

        if(2*i+1 > SizeOfSwarm){

            Particles[i].Neighbor[1] = i;
            Particles[i].Neighbor[2] = i;

        }
    }

    Particles[0].Neighbor[0] = 0;
    Particles[0].Neighbor[1] = 1;
    Particles[0].Neighbor[2] = 2;

}

void DefineTopology(Swarm *S, int Topology){

    if(Topology == RING)
        ConstructRing(S);
    else if(Topology == TREE)
        ConstructTree(S);
    else
        ConstructMesh(S);

}
