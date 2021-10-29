# PSSM

`ch29576PSSM.cpp` is the final submission for this assignment.

## compiling

```bash
g++ -std=c++11 -O3 -o ch29576PSSM -Wall ch29576PSSM.cpp
```

tested on M1 and intel mac

## usage and testing

```bash
# ./ch29576PSSM  AlignmentFile SequenceFile [ScoreCutoff]
time ./ch29576PSSM FruR.txt ecoK12-MG1655.fasta
```

## example output


```

Chen's PSSM implementation

read file complete
Time after reading input: 0.055512seconds
non regular bases: 0
GC content: 0.507907
Time after getting GC content: 0.102895seconds
12 sequences in the alignemnt file

Time after PSSM calculation: 0.103012seconds
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
1       0.250   0.173   0.558   0.019
2       0.019   0.635   0.250   0.096
3       0.019   0.019   0.019   0.942
4       0.019   0.019   0.865   0.096
5       0.942   0.019   0.019   0.019
6       0.942   0.019   0.019   0.019
7       0.327   0.019   0.096   0.558
8       0.019   0.865   0.019   0.096
9       0.019   0.096   0.865   0.019
10      0.404   0.173   0.096   0.327
11      0.019   0.019   0.019   0.942
12      0.096   0.096   0.019   0.788
13      0.250   0.558   0.019   0.173
14      0.712   0.019   0.019   0.250
15      0.250   0.173   0.481   0.096
16      0.019   0.481   0.173   0.327

PSSM:
pos.    A       C       G       T
1       0.023   -0.553  1.135   -3.677
2       -3.677  1.321   -0.023  -1.356
3       -3.677  -3.723  -3.723  1.937
4       -3.677  -3.723  1.769   -1.356
5       1.937   -3.723  -3.723  -3.677
6       1.937   -3.723  -3.723  -3.677
7       0.410   -3.723  -1.401  1.181
8       -3.677  1.769   -3.723  -1.356
9       -3.677  -1.401  1.769   -3.677
10      0.715   -0.553  -1.401  0.410
11      -3.677  -3.723  -3.723  1.937
12      -1.356  -1.401  -3.723  1.680
13      0.023   1.135   -3.723  -0.508
14      1.532   -3.723  -3.723  0.023
15      0.023   -0.553  0.921   -1.356
16      -3.677  0.921   -0.553  0.410

Training set motif scores:
Time after printing matrix: 0.103693seconds
CGTTAAGCGATTCAGC        14.858
ACTGAAACGTTTTTGC        18.257
CTTGAAACGTTTCAGC        18.155
GCTGAATCGTTTCAAT        21.882
GCTGAATCGCTTAACC        19.742
ACTGAAACGCTTCAGC        20.445
ACTGAATCGGTTAACT        17.271
GGTGAATCGATACTTT        14.920
GCTGAATTGATTCAGG        18.997
GGTGAATCGTTCAAGC        17.754
GCTGAATCGATTTTAT        19.036
GCTGAAACCATTCAAG        17.283

0: CGTTAAGCGATTCAGC were selected since the score is the least: 14.858

Time after determining threshold: 0.103913seconds
Matches with score 14.858 or higher found in ecoK12-MG1655.fasta (length 4641652bp):

4641652
Start   End     Strand  Sequence        Score
4528    4543    +       GGTGAAACGTTTTATT        16.747
121841  121856  +       AGTGAATCGGTTCAAT        17.615
212203  212218  -       GCAAAAACGCTTCACC        16.214
331872  331887  +       GCTGAATGGATTCAGT        17.593
331872  331887  -       GCTGAATGGATTCAGT        19.314
344627  344642  -       AGTTTATCGATTCAGT        16.351
497069  497084  -       CATTAACCGTTTCAGC        15.847
747259  747274  -       GGTTAACCGCTTCAGC        16.312
875057  875072  +       CCTGAAACGTTTTTAT        16.272
955387  955402  -       AAAGAATCGTTTCACG        15.497
1025883 1025898 -       GATTTACCGATTCAGC        15.056
1194877 1194892 +       GCTGAATCGCTTAACC        19.742
1194877 1194892 -       GCTGAATCGCTTAACC        16.546
1498941 1498956 +       ACTGAAACGATAAAAG        15.194
1667202 1667217 -       AAAGAAACGCTTCAGC        16.413
1678087 1678102 -       ATATTAACGATTCAGC        16.226
1755477 1755492 -       CTTGAATGGTTTCAGC        17.283
1787199 1787214 +       GGTGAATCGTTCAAGC        17.754
1862002 1862017 +       GCTGAATCGTTTTTTC        17.863
1885904 1885919 +       GGTGAAACGCTTCACG        17.265
1885904 1885919 -       GGTGAAACGCTTCACG        16.203
1934702 1934717 -       GCAAAAACGTTTCAGT        18.257
1936801 1936816 +       GGTGAATCGTTTCTGT        19.927
2099022 2099037 +       GTTTAATCGCTTCTGC        15.017
2131383 2131398 -       CCAGAATCGCTTCAGT        16.919
2146212 2146227 +       GCTGAAGCGATTTTAG        15.491
2150048 2150063 +       GCTGAAACGATACATT        17.002
2263515 2263530 +       ATTGAAACGATTCAGC        19.036
2263515 2263530 -       ATTGAAACGATTCAGC        21.882
2263582 2263597 +       GCTGAAACGTTTCAAG        20.149
2263582 2263597 -       GCTGAAACGTTTCAAG        18.155
2278144 2278159 +       GCGGAATCGGTTCAAC        14.921
2509545 2509560 -       ACTTTATCGTTTCAGC        18.167
2533545 2533560 +       GCTGAATCGATTTTAT        19.036
2736948 2736963 +       ACTGAAGCGATTTAGT        17.749
2736948 2736963 -       ACTGAAGCGATTTAGT        15.259
2856992 2857007 +       CCTGAAATGATTAACT        14.916
3011321 3011336 +       GGTGAAACGATTTTCT        16.345
3067197 3067212 -       GCTTAACCGTTTCAGT        18.485
3073813 3073828 +       ACTGAAACGCTTCAGC        20.445
3073813 3073828 -       ACTGAAACGCTTCAGC        20.198
3110695 3110710 -       GTTTAACCATTTCAGC        15.575
3247746 3247761 -       CGTTAACCGATTCACC        16.076
3439305 3439320 +       GCTGAATTGCTTCTCT        15.710
3532532 3532547 +       GGTGAATCGATACTTT        14.920
3613534 3613549 -       AATGGATCGATTCAGT        16.615
3687850 3687865 -       CGATAAACGCTTCAGC        15.140
3742172 3742187 -       AGTTAATGGTTTCACC        15.215
3772158 3772173 -       AGTTAACCGATTCAGT        17.271
3785196 3785211 -       ATTTTATCGATTCAGC        18.040
3866318 3866333 +       GCTGAATCGGTGAAGC        14.965
3947889 3947904 -       GATAGAGCGATTCAGC        15.328
4107431 4107446 +       CCTGAATCAATTCAGC        16.461
4107431 4107446 -       CCTGAATCAATTCAGC        18.997
4111653 4111668 +       GCTTAATCGGTTCAAC        17.458
4111653 4111668 -       GCTTAATCGGTTCAAC        14.903
4215228 4215243 +       CGTTAAGCGATTCAGC        14.858
4215228 4215243 -       CGTTAAGCGATTCAGC        18.268
4234751 4234766 +       ACTGAAGCGATTCTGC        18.393
4234751 4234766 -       ACTGAAGCGATTCTGC        16.202
4307706 4307721 -       AGTGTAGCGTTTCACC        15.193
4362676 4362691 -       GTAAAAGCGATTCAAC        15.602
4365792 4365807 -       CCTGAATCACTTCACC        15.072
4478623 4478638 +       GTTGAAGCGTTTAAAC        16.023
4478623 4478638 -       GTTGAAGCGTTTAAAC        14.858
4517845 4517860 -       GCAGAAACGCTTCACG        16.168
4558112 4558127 -       GGTTAAACAATTCAAC        14.904
4641134 4641149 +       GCTGAATCGTTACACG        17.307
Time after scanning the whole sequence: 2.65999seconds
```
