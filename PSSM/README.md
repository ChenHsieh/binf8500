# PSSM (WIP)

`ch29576PSSM.cpp` is the final submission for this assignment.

## compiling

```bash
g++ -std=c++11 -o ch29576PSSM -Wall ch29576PSSM.cpp
```

tested on M1 and intel mac

## usage and testing

```bash
# ./ch29576PSSM  AlignmentFile SequenceFile [ScoreCutoff]
time ./ch29576PSSM FruR.txt FruR.fasta 
```

## example output


```
frequency matrix:
pos.    A       C       G       T
1       3       2       7       0
2       0       8       3       1
3       0       0       0       12
4       0       0       11      1
5       12      0       0       0
6       12      0       0       0
7       4       0       1       7
8       0       11      0       1
9       0       1       11      0
10      5       2       1       4
11      0       0       0       12
12      1       1       0       10
13      3       7       0       2
14      9       0       0       3
15      3       2       6       1
16      0       6       2       4

probability matrix:
pos.    A       C       G       T
1        0.250   0.173   0.558   0.019
2        0.019   0.635   0.250   0.096
3        0.019   0.019   0.019   0.942
4        0.019   0.019   0.865   0.096
5        0.942   0.019   0.019   0.019
6        0.942   0.019   0.019   0.019
7        0.327   0.019   0.096   0.558
8        0.019   0.865   0.019   0.096
9        0.019   0.096   0.865   0.019
10       0.404   0.173   0.096   0.327
11       0.019   0.019   0.019   0.942
12       0.096   0.096   0.019   0.788
13       0.250   0.558   0.019   0.173
14       0.712   0.019   0.019   0.250
15       0.250   0.173   0.481   0.096
16       0.019   0.481   0.173   0.327

PSSM:
pos.    A       C       G       T
1       -0.196  -0.303   1.385  -3.897
2       -3.897   1.571   0.227  -1.575
3       -3.897  -3.473  -3.473   1.718
4       -3.897  -3.473   2.019  -1.575
5        1.718  -3.473  -3.473  -3.897
6        1.718  -3.473  -3.473  -3.897
7        0.191  -3.473  -1.151   0.961
8       -3.897   2.019  -3.473  -1.575
9       -3.897  -1.151   2.019  -3.897
10       0.495  -0.303  -1.151   0.191
11      -3.897  -3.473  -3.473   1.718
12      -1.575  -1.151  -3.473   1.461
13      -0.196   1.385  -3.473  -0.727
14       1.313  -3.473  -3.473  -0.196
15      -0.196  -0.303   1.171  -1.575
16      -3.897   1.171  -0.303   0.191

Training set motif scores:
CGTTAAGCGATTCAGC         15.103
ACTGAAACGTTTTTGC         17.563
CTTGAAACGTTTCAGC         17.931
GCTGAATCGTTTCAAT         21.189
GCTGAATCGCTTAACC         19.987
ACTGAAACGCTTCAGC         20.690
ACTGAATCGGTTAACT         16.577
GGTGAATCGATACTTT         14.226
GCTGAATTGATTCAGG         18.773
GGTGAATCGTTCAAGC         17.999
GCTGAATCGATTTTAT         17.873
GCTGAAACCATTCAAG         17.059

Matches with score  14.226 or higher found in FruR.fasta (length 203 bp):

Start   End     Strand  Sequence        Score
1       16      +       CGTTAAGCGATTCAGC         15.103
1       16      -       GCTGAATCGCTTAACG         18.513
18      33      +       ACTGAAACGTTTTTGC         17.563
35      50      +       CTTGAAACGTTTCAGC         17.931
35      50      -       GCTGAAACGTTTCAAG         19.924
52      67      +       GCTGAATCGTTTCAAT         21.189
52      67      -       ATTGAAACGATTCAGC         18.343
69      84      +       GCTGAATCGCTTAACC         19.987
69      84      -       GGTTAAGCGATTCAGC         16.791
86      101     +       ACTGAAACGCTTCAGC         20.690
86      101     -       GCTGAAGCGTTTCAGT         20.444
103     118     +       ACTGAATCGGTTAACT         16.577
120     135     +       GGTGAATCGATACTTT         14.226
137     152     +       GCTGAATTGATTCAGG         18.773
137     152     -       CCTGAATCAATTCAGC         16.237
154     169     +       GGTGAATCGTTCAAGC         17.999
171     186     +       GCTGAATCGATTTTAT         17.873
188     203     +       GCTGAAACCATTCAAG         17.059
```