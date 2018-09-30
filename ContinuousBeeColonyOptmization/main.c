#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "ContinuosBCO.h"

#define E_SIZE      50
#define O_SIZE      50
#define D_SIZE      10

Colony *C;

double EvaluateFlower(Bee *B){

}

int TerminationCriteria(Colony *C){



}

int main(){

    time_t t;
    srand((unsigned) time(&t));

    C = CreateColony(E_SIZE,O_SIZE,D_SIZE,1048576,-1048576);

    ContinuousBeeColonyOpt(C,EvaluateFlower,TerminationCriteria);

    return 0;
}
