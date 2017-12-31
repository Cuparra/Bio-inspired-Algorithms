#include "Crossover.h"

#define NOTFOUND        -1

#define SELECTED        1
#define NOTSELECTED     0

#define exch(x,y)       {int z = x; x = y; y = z;}

static inline int SearchAllel(int allel, int r1, int r2, int *cromossome){

    int count;

    for(count = r1 ;count<=r2; count++){

        if(allel == cromossome[count])
            return SELECTED;

    }

    return NOTSELECTED;
}

static void AuxiliaryCrossoverFunction(int *Cromossome, int *CromossomeChild, int SizeOfCromossome, int r1, int r2 ){

    int allel, count = 0;

    for(allel = 0;  count < r1  ;allel++){

        int tempAllel = Cromossome[allel];

        if ( SearchAllel(tempAllel,r1,r2,CromossomeChild) == NOTSELECTED )
                CromossomeChild[count++] = tempAllel;
    }

    count = r2+1;

    for(allel = allel; allel<SizeOfCromossome  ;allel++){

        int tempAllel = Cromossome[allel];

        if ( SearchAllel(tempAllel,r1,count-1,CromossomeChild) == NOTSELECTED )
                CromossomeChild[count++] = tempAllel;
    }

}

inline int OrderCrossover(Population *P, Organism *Father, Organism *Mather, Organism *Child1, Organism *Child2){

    int allel;
    int *Cromossome1                    = Father->cromossome;
    int *Cromossome2                    = Mather->cromossome;
    int *CromossomeChild1               = Child1->cromossome;
    int *CromossomeChild2               = Child2->cromossome;
    int SizeOfCromossome                = P->SizeOfCromossome;

    double probability = ( (double) rand() / RAND_MAX);

    if (probability > 0.7)
        return 0;

    /*Select a swath*/
    int r1 = rand()%SizeOfCromossome;
    int r2 = rand()%(SizeOfCromossome-r1) + r1;

    /* Copy the swath to the cromossome of the childs*/
    for(allel = r1; allel<=r2 ;allel++){

        CromossomeChild1[allel] = Cromossome1[allel];
        CromossomeChild2[allel] = Cromossome2[allel];

    }

    AuxiliaryCrossoverFunction(Cromossome2,CromossomeChild1,SizeOfCromossome,r1,r2);

    AuxiliaryCrossoverFunction(Cromossome1,CromossomeChild2,SizeOfCromossome,r1,r2);

    return 2;
}

static inline int FindAllel(int *cromossome, int allel, int start, int finish){

    int i;

    for(i=start;i<=finish;i++){

        if (cromossome[i] == allel)
            return i;

    }

    return NOTFOUND;
}

//PMX
inline int PMXCrossover(Population *P, Organism *Father, Organism *Mather, Organism *Child1, Organism *Child2){

    int allel;
    int *Cromossome1                    = Father->cromossome;
    int *Cromossome2                    = Mather->cromossome;
    int *CromossomeChild1               = Child1->cromossome;
    int *CromossomeChild2               = Child2->cromossome;
    int SizeOfCromossome                = P->SizeOfCromossome;

    double probability = ( (double) rand() / RAND_MAX);

    if (probability > 0.7)
        return 0;

    /*Select a swath*/
    int r1 = rand()%SizeOfCromossome;
    int r2 = rand()%(SizeOfCromossome-r1) + r1;
    int flag[r2-r1+1];

    /* Copy the swath to the cromossome of the childs */
    for(allel = r1; allel<=r2 ;allel++){

        CromossomeChild1[allel] = Cromossome2[allel];
        CromossomeChild2[allel] = Cromossome1[allel];

    }

    /*Copy the left side of the parents cromossomes*/
    for(allel = 0; allel<r1 ; allel++){

        CromossomeChild1[allel] = Cromossome1[allel];
        CromossomeChild2[allel] = Cromossome2[allel];

    }

    /*Copy the right side of the parent's cromossomes*/
    for(allel = r2+1; allel<SizeOfCromossome ; allel++){

        CromossomeChild1[allel] = Cromossome1[allel];
        CromossomeChild2[allel] = Cromossome2[allel];

    }

    for(allel = r1; allel<=r2; ++allel)
        flag[allel - r1] = TRUE;

    for(allel = r1; allel<=r2 ; allel++){

        if(flag[allel-r1] == TRUE){

            int idx         = NOTFOUND;
            int newIdx      = NOTFOUND;
            int startIdx    = allel - r1;
            int allel1      = CromossomeChild1[allel];
            int allel2      = CromossomeChild2[allel];

            flag[startIdx]  = FALSE;

            while( ( newIdx = FindAllel(CromossomeChild1,allel2,r1,r2) ) != NOTFOUND && newIdx != startIdx && flag[newIdx-r1]){

                idx             = newIdx;
                allel2          = CromossomeChild2[idx];
                flag[idx-r1]    = FALSE;

            }

            if ( idx != startIdx ){

                if  ( ( idx = FindAllel(CromossomeChild2,allel2,0,r1-1) ) != NOTFOUND  )
                    CromossomeChild2[idx] = allel1;

                else if ( (idx = FindAllel(CromossomeChild2,allel2,r2+1,SizeOfCromossome-1)) != NOTFOUND )
                    CromossomeChild2[idx] = allel1;
            }
        }
    }


    for(allel = r1; allel<=r2; ++allel)
        flag[allel - r1] = TRUE;

    for(allel = r1; allel<=r2 ; allel++){

        if(flag[allel-r1] == TRUE){

            int idx         = NOTFOUND;
            int newIdx      = NOTFOUND;
            int startIdx    = allel - r1;
            int allel1      = CromossomeChild1[allel];
            int allel2      = CromossomeChild2[allel];

            flag[startIdx]  = FALSE;

            while( ( newIdx = FindAllel(CromossomeChild2,allel1,r1,r2) ) != NOTFOUND && newIdx != startIdx && flag[newIdx-r1]){

                idx             = newIdx;
                allel1          = CromossomeChild1[idx];
                flag[idx-r1]    = FALSE;

            }

            if ( idx != startIdx ){

                if  ( ( idx = FindAllel(CromossomeChild1,allel1,0,r1-1) ) != NOTFOUND  )
                    CromossomeChild1[idx] = allel2;

                else if ( (idx = FindAllel(CromossomeChild1,allel1,r2+1,SizeOfCromossome-1)) != NOTFOUND )
                    CromossomeChild1[idx] = allel2;
            }
        }
    }

    return 2;
}

inline int InverOverCrossover(Population *P, Organism *Father, Organism *Mather, Organism *Child1, Organism *Child2){

    int allel;
    int *Cromossome1                    = Father->cromossome;
    int *Cromossome2                    = Mather->cromossome;
    int *CromossomeChild1               = Child1->cromossome;
    int *CromossomeChild2               = Child2->cromossome;
    int SizeOfCromossome                = P->SizeOfCromossome;

    double probability = ( (double) rand() / RAND_MAX);

    if (probability > 0.7)
        return 0;

    for(allel = 0; allel < SizeOfCromossome ;++allel){

        CromossomeChild1[allel] = Cromossome1[allel];
        CromossomeChild2[allel] = Cromossome2[allel];

    }

    int s           = rand()%(SizeOfCromossome-1);
    int allelS      = Cromossome1[s];
    int k           = FindAllel(Cromossome2,allelS,0,SizeOfCromossome-1);

    k               = (k + 1 < SizeOfCromossome ) ? k + 1: SizeOfCromossome - 1;
    int allelK      = Cromossome2[k];

    k               = FindAllel(Cromossome1,allelK,0,SizeOfCromossome-1);
    allelK          = Cromossome1[k];
    allelS          = Cromossome1[++s];

    int min     = (s > k) ? k : s;
    int max     = (s > k) ? s : k;

    int lenght  = (max - min + 1)/2;

    for(allel = 0; allel<lenght ;++allel)
        exch(CromossomeChild1[min+allel],CromossomeChild1[max-allel]);

    s               = rand()%(SizeOfCromossome-1);
    allelS          = Cromossome2[s];
    k               = FindAllel(Cromossome1,allelS,0,SizeOfCromossome-1);

    k               = (k + 1 < SizeOfCromossome ) ? k + 1: SizeOfCromossome - 1;
    allelK          = Cromossome1[k];

    k               = FindAllel(Cromossome2,allelK,0,SizeOfCromossome-1);
    allelK          = Cromossome2[k];
    allelS          = Cromossome2[++s];

    min     = (s > k) ? k : s;
    max     = (s > k) ? s : k;

    lenght  = (max - min + 1)/2;

    for(allel = 0; allel<lenght ;++allel)
        exch(CromossomeChild2[min+allel],CromossomeChild2[max-allel]);

    return 2;
}

inline int MixCrossover(Population *P, Organism *Father, Organism *Mather, Organism *Child1, Organism *Child2){

    double probability = ( (double) rand() / RAND_MAX);

    if (probability > 0.7)
        return 0;

    if(probability < 0.23)
        return PMXCrossover(P,Father,Mather,Child1,Child2);
    else if(probability < 0.46)
        return InverOverCrossover(P,Father,Mather,Child1,Child2);
    else
        return OrderCrossover(P,Father,Mather,Child1,Child2);

}

/*
void printCromossome(int *S, int SizeOfCromossome){

    int i,j;

    for(i=0;i<SizeOfCromossome;i++)
        printf("%d ",S[i]);

    for(i=0;i<SizeOfCromossome;i++){
        int flag = 0;

        for(j=0;j<SizeOfCromossome;j++){
            if(S[j] == i)
                flag = 1;
        }

        if(flag == 0){
            printf("No\n");
            return;
        }

    }

    printf("YES\n");
}*/
