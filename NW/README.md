# NW (WIP)

`ch29576NW.cpp` is the final submission for this assignment.

## compiling

```bash
g++ -std=c++11 -o ch29576NW -Wall ch29576NW.cpp
```

tested on M1 mac

## usage and testing

```bash
# ./ch29576NW <input1.fasta> <input2.fasta> <match> <mismatch> <gap>
time ./ch29576NW Test01.fasta Test02.fasta 1 -1 -1
```

## example output


```
Needleman-Wunsch global alignment


Sequence 1 (Test01.fasta):

ACGCGATCGCGCAAATCAGACCTAGCATCGCACTTTCGACAGCATCAGCGACATCGATCG
ATCGTACGATCGTAC

Length:  75


Sequence 2 (Test02.fasta):

ACGCGATTGCGCAAATCAGACCGCATCGCACTATCGACAGTGCATCAGCGTTCTACGGAT
CGATCGCCTACGATCGTAC

Length:  79


Scores:
  Match: 1,  Mismatch: 0,  Gap: -1


Alignment score: 60
Alignment:

       1: ACGCGATCGCGCAAATCAGACCTAGCATCGCACTTTCGACA--GCATCAGCG-AC-ATCG
          ******* **************  ********** ******  *********  * *  *
       1: ACGCGATTGCGCAAATCAGACC--GCATCGCACTATCGACAGTGCATCAGCGTTCTACGG

      57: ATCGATCG--TACGATCGTAC
          ********  ***********
      59: ATCGATCGCCTACGATCGTAC
```