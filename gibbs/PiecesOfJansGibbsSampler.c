/*  Simple version of Gibbs sampler for BINF8500

by Jan Mrazek (mrazek@uga.edu)

Input: 
- DNA sequences in FASTA format
- expected size of the motif

sampling probabilities are scores in the form of ratio of target and background probabilities without the log (that is, the exp of the normal PSSM scores)

*/




#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAXNSEQ 1000        // maximum number of sequences analyzed
#define MAXMOTLEN 100       // maximum length of the motif
#define NSEEDS 200           // number of different seeds (initial motif locations) to be used
#define ADJCYCLES 5         // perform adjustment every ADJCYCLES cycles
#define MAXADJ 3            // maximum number of nucleotides the motif start/end can move during the adjustment step
#define PLATEAUCYCLES 200    // program stops when the maximum is not improved for this many cycles
#define MAXCYCLES 5000      // maximujm number of iteration cycles for each seed
#define PSEUDO 0.25         // the pseudocount value

//structure to store information about each input seqeunce. Only MotPos will change once the Gibbs sampler starts
typedef struct SequenceStruct    {
  char *Seq;         // pointer to the start of the sequence
  char *Desc;        // pointer to the start of the sequence description without the '>'
  long Len;          // length of the sequence less one
  long MotPos;       // Current position of the motif start in the sequence
  double BProb[4];      // background probabilities
}    SequenceStruct;

//Structure to store the results. Note that MotPos is present in both structures, which is principally unnecessary but I found it easier to do it this way.
typedef struct ResultStruct    {
  double Score;               // sum of PSSM scores for all motif sequences
  int MotLen;                 // motif length
  long MotPos[MAXNSEQ];       // current position of the motif start in the sequence
}    ResultStruct;







/********************************************************************
GetScore fills the structure Results based on info from Sq[], Buffer, and MotLen.
The Score is calculated as a sum of scores of all motif occurrences (one in each sequence)
using PSSM derived from all motif sequences except the one being scored
********************************************************************/


void GetScore (Sq,Buffer,NSeq,MotLen,Result)
SequenceStruct Sq[];
char *Buffer;
int NSeq;
long MotLen;
ResultStruct *Result;
{
	
//This part is censored

}




/********************************************************************
GetScoreAdj is the same as GetScore except for an extra parameter that 
shifts all motif locations left or right
********************************************************************/

//Note that there is no need to have both GetScore and GetScoreAdj (I could use GetScoreAdj with Adj=0 instead of GetScore)
//This is one of those situations where I did not plan sufficiently ahead, wrote GetScore, and later realized that having
//an option to shift all motif starting positions when calling the function would make writing the program much easier. 


void GetScoreAdj (Sq,Buffer,NSeq,MotLen,Adj,Result)
SequenceStruct Sq[];
char *Buffer;
int NSeq;
long MotLen;
int Adj;
ResultStruct *Result;
{
	
//This part is censored

}





/********************************************************************
Adjust runs the adjustment step. It compares scores for both motif boundaries 
(start and end) shifted by up to MAXADJ nucleotides left or right and picks 
the one that give the best overall score.
Options that would shrink the motif below minimum length or which do not have
a required extra nucleotide on left or right to expand the motif in some 
sequence(s) are excluded.
Returns new motif length.
********************************************************************/


long Adjust (Sq,Buffer,NSeq,MotLen,MinMotLen)
SequenceStruct Sq[];
char *Buffer;
int NSeq;
long MotLen;
long MinMotLen;
{
	
//This part is censored

}






/********************************************************************
Cycle runs one cycle of iterations getting new motif locations for each sequence
********************************************************************/


void Cycle (Sq,Buffer,NSeq,MotLen,MaxSLen)
SequenceStruct Sq[];
char *Buffer;
int NSeq;
long MotLen;
long MaxSLen;
{
  long II,I,J;
  double S,R;
  double *Score;
  Score=(double *)malloc(sizeof(double)*MaxSLen);  // this is equivalent of Score=new double[MaxSLen]; MaxSLen is the length of the longest sequence in the input fileno
	
//This part is censored

/*
The following part is how I pick the new location for the motif in seqeunce II:
Sq[II].Len ... length of the sequence II less 1
MotLen ... length of the motif less 1
Score[I] ... at the beginning, this is the PSSM score of a substring of length (MotLen+1) starting at possition I in the seqeunce
exp2(x) ... math function that returns 2 to the power of x (the same as pow(2,x) but faster
*/
    for (I=0;I<=Sq[II].Len-MotLen+1;++I)    {
      Score[I]=exp2(Score[I]);           // switching to ratio of target to background probabilities instead of the log-ratio used in the PSSM.
    };
    for (I=1;I<=Sq[II].Len-MotLen+1;++I)    {
      Score[I]+=Score[I-1]; 
    };  // at this point, Score[I] is not the score at position I but sum of all scores between 0 and I
    R=Score[Sq[II].Len-MotLen+1];  // the last elemnt of the Score aray, that is, some of all scores in sequences II
    for (I=0;I<=Sq[II].Len-MotLen+1;++I)    {
      Score[I]/=R;
    }; // now the values Score[I] were scaled to be between 0 and 1
    R=drand48();  // random number between 0 and 1
    I=0;
    while (R>=Score[I] && I<Sq[II].Len-MotLen+1)    ++I;  // choosing the new location of the motif, I
    Sq[II].MotPos=I;  // store I as the new location of the motif in sequence II

//This part is censored

  free(Score); // since I created Score[] dynamically and I will be calling this function repeatedly, I have to free the allocated memory, otherwise I would create a memory leak
               // if you used 'new' instead of 'malloc" (in Java or C++), you replace it with delete(Score).

}






/********************************************************************
RunGibbs is the actual Gibbs Sampler for single initial (seed) motif locations
********************************************************************/


void RunGibbs (Sq,Buffer,NSeq,MotLen,MinMotLen,MinSLen,MaxSLen,Result0)
SequenceStruct Sq[];
char *Buffer;
int NSeq;
long MotLen;
long MinMotLen;
long MinSLen;
long MaxSLen;
ResultStruct *Result0;
{
  int NCyc,NAdj,NPlat;         // iteration counters
  int I;
  ResultStruct Result;


// seed the algorithm with initial motif positions

  
	
//This part is censored



// set initial score value
  GetScore (Sq,Buffer,NSeq,MotLen,Result0);


// run the Gibbs sampler with adjustment until plateau is reached

  NCyc=0;
  NAdj=0;
  NPlat=0;
  while (NCyc<MAXCYCLES && NPlat<PLATEAUCYCLES)    {
    if (NAdj>=ADJCYCLES)    {
      MotLen=Adjust(Sq,Buffer,NSeq,MotLen,MinMotLen);
//GetScore(Sq,Buffer,NSeq,MotLen,&Result);
//printf ("%li %f\n",MotLen,Result.Score);
      NAdj=0;
    };
    Cycle(Sq,Buffer,NSeq,MotLen,MaxSLen);
    GetScore(Sq,Buffer,NSeq,MotLen,&Result);
//printf ("%i: %li %f %f\n",NCyc,MotLen,Result.Score,Result0->Score);
    if (Result.Score>Result0->Score)    {
      *Result0=Result;
      NPlat=0;
    };
    ++NCyc;
    ++NPlat;
    ++NAdj;
  };

}



/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


int main (argc, argv)
int argc;
char *argv[];
{
  FILE *IFi;
  char *Buffer;                  // a place to store all sequence names and sequences
  SequenceStruct Sq[MAXNSEQ];    // info about each sequence (see the typedef above)
  int NSeq;                      // number of sequences in the input less one
  long MinSLen,MaxSLen;          // length of the shortest and longest sequence in the input
  long MotLen,MotLen0,MinMotLen;         // motif length, the orifginal (estimated) motif length, and minimum motif length
  char NT[5];                    // will be used to convert codes 0, 1, 2, and 3 to characters A, C, G, and T, respectively, for output
  ResultStruct Result,Result0;   // to store sampling results
  char Z;
  long BNT[4];                   // will be used to count nucleotides for background probabilities
  long I,J,L;


  if (argc!=3)    {
    printf ("\n\n\nUsage:  Gibbs InputFile MotifLength\n\n");
    printf ("InputFile: sequences in FASTA format.\n");
    printf ("MotifLength: estimated length of the motif.\n\n\n");
    exit(1);
  };

	
//This part is censored

}








