# kmeans

`ch29576kmeans.cpp` is the final submission for this assignment.

## compiling

```bash
g++ -std=c++11 -o ch29576kmeans -Wall ch29576kmeans.cpp
```

tested on M1 mac

## usage and testing

```bash
# clustering
# ./ch29576kmeans <file.tsv> <minimal k> <maximal k>
time ./ch29576kmeans Archaea.txt 1 15
```