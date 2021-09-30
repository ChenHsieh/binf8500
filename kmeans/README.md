# kmeans (WIP)

`ch29576kmeans.cpp` is the final submission for this assignment.

## compiling

```bash
g++ -std=c++11 -o ch29576kmeans easy_ch29576kmeans.cpp
```

works on Intel mac, M1 mac, sapelo2 interactive mode. not in login node of sapelo2.

## usage and testing

```bash
# clustering
# ./ch29576kmeans <file.tsv> <minimal k> <maximal k>
time ./ch29576kmeans Archaea.txt 1 15
```

g++ -std=c++11 -o ch29576kmeans ch29576kmeans.cpp; time ./ch29576kmeans Archaea.txt 1 15