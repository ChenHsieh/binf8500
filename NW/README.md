# Needleman-Wunsch global alignment implementation

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

Chen's Needleman-Wunsch global alignment implementation

File 1: Test01.fasta
        header from file 1:     >test01
        content from file 1:    ACGCGATCGCGCAAATCAGACCTAGCATCGCACTTTCGACAGCATCAGCGACATCGATCGATCGTACGATCGTAC
        size of file 1: 75

File 2: Test02.fasta
        header from file 2:     >test01
        content from file 2:    ACGCGAttgCGCAAATCAGACCgCATCGCACTaTCGACAgtGCATCAGCGttctacgGATCGATCGccTACGATCGTAC
        size of file 2: 79


Scores:
Match: 1,  Mismatch: -1,  Gap: -1

Initializing matrix...
Initializing matrix...done

matrix calc done

Alignment score: 45

                1       ACGCGATCGCGCAAATCAGACCTAGCATCGCACTTTCGACA--GCATCAGCGACATC--G
                        ******   *************   ********* ******  *********       *
                1       ACGCGAttgCGCAAATCAGACCg--CATCGCACTaTCGACAgtGCATCAGCGttctacgG

                57      ATCGATCG--TACGATCGTAC
                        ********  ***********
                59      ATCGATCGccTACGATCGTAC

```