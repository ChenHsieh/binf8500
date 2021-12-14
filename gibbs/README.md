# Gibbs

`ch29576gibbs.cpp` is the final submission for this assignment.

## compiling

```bash
g++ -std=c++11 -O3 -o ch29576gibbs -Wall ch29576gibbs.cpp
```

tested on M1 and intel mac

## usage and testing

```bash
# ./ch29576gibbs InputFile MotifLength
time ./ch29576gibbs E.coliRpoN-sequences-6-300nt.fasta 30
```

## example output


```
Simple Gibbs motif sampler output:

     Input file: E.coliRpoN-sequences-6-300nt.fasta
     Initial motif length: 30
     Final motif length:   31
     Final score:          106.646372


Motif sequences and locations:

TAAAAGTTGGCACAGATTTCGCTTTATCTTT 195-225 glnA
GCAAAACTGGCACGATTTTTTCATATATGTG 224-254 glnH
TAAAATGTGGCATAAAAGATGCATACTGTAG 227-257 fdhF
TAAAAGTTGGCACAAAAAATGCTTAAAGCTG 242-272 hyc
TCAACACTGGCACAATTATTGCTTGTAGCTG 248-278 hyp
GGCAAAGCGAGAAAAAATACCCATAATGTTG 111-141 pspF
```

glnA    210-240 TTTCGCTTTATCTTTTTTACGGCGACACGG
glnH    60-90   TACATAAAGATTGTTTTTTCATCAGGTTTT
fdhF    121-151 GCTGTCACGCGGTATTTCGTTTCGTCACGT
hyc     11-41   TACGCGTTTTGCGCCGTGTTTTGCGGCCTG
hyp     123-153 TAAGCATTTTTTGTGCCAACTTTTAATTTA
pspF    133-163 TAATGTTGTCCTCTTGATTTCTGCGTTCAG