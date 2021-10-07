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

## output

taking Archaea.txt as example

### standard output:

```
input dataFrame size detecting (header included)
rowSize: 40
colSize: 21
data reading finished...
K-means starting

K       Mean_distance   minWCSS AIC     BIC
1       4.292625        760.000000      800.000000      833.271233
2       3.301261        451.905288      531.905288      598.447754
3       2.674952        312.047179      432.047179      531.860877
4       2.408484        257.328914      417.328914      550.413845
5       2.206513        213.080831      413.080831      579.436996
6       1.976688        173.532476      413.532476      613.159873
7       1.821128        144.842776      424.842776      657.741406
8       1.674377        123.957047      443.957047      710.126910
9       1.579737        109.941774      469.941774      769.382870
10      1.471670        95.154788       495.154788      827.867117
11      1.464964        93.405903       533.405903      899.389465
12      1.303113        80.004923       560.004923      959.259718
13      1.225977        71.299331       591.299331      1023.825359
14      1.169156        68.906666       628.906666      1094.703927
15      1.186590        67.895294       667.895294      1166.963788
```

### for each K, a file with cluster results is generated:

```
Chen's Detailed output for k=2:
List of data points in each cluster preceded by distance to centroid:
Cluster 0: 

0	2.24571	Acidianus hospitalis W1|65|34.1
2	2.84852	Archaeoglobus fulgidus VC-16, DSM 4304|76|48.6
3	3.06676	Archaeoglobus profundus Av18, DSM 5631|82|42
4	3.50894	Caldisphaera lagunensis IC-154, DSM 15908|75|30
6	3.32258	Desulfurococcus kamchatkensis 1221n|85|45.34
7	2.30336	Fervidicoccus fontis Kam940|67.5|37.5
15	3.36478	Ignicoccus islandicus Kol8, DSM 13165|90|44.9
16	3.98103	Methanobacterium formicicum BRM9|35|41.3
17	3.85017	Methanobrevibacter olleyae DSM 16632|37|26.9
18	4.47906	Methanocaldococcus infernus ME|73|33.6
19	3.37773	Methanococcoides burtonii DSM 6242|23.4|40.8
20	3.24056	Methanococcus maripaludis S2|32.5|33.1
21	3.45214	Methanococcus vannielii SB|30|31.3
23	2.39652	Methanosarcina mazei Go1|35|41.5
24	2.36938	Methanosarcina thermophila TM-1|50|41.1
25	3.73688	Methanothermobacter thermautotrophicus Delta H|67.5|49.5
27	2.85805	Palaeococcus pacificus DY20341|80|43
28	5.12256	Picrophilus torridus DSM 9790|60|36
30	3.05258	Pyrococcus furiosus DSM 3638|86.5|40.8
31	4.02011	Pyrococcus yayanosii CH1|98|51.6
33	2.63801	Sulfolobus islandicus M.16.4|80|35
34	4.14818	Thermococcus sp. CL1|85|55.8
35	3.84251	Thermoplasma acidophilum DSM 1728|54|46
36	3.09536	Thermoplasma volcanium GSS1|50|39.9
38	3.87426	Vulcanisaeta distributa DSM 14429|90|45.4

Cluster 1: 

1	4.66106	Acidilobus saccharovorans 345-15|80|57.2
5	4.8628	Cenarchaeum symbiosum A|10|57.4
8	1.94042	Haloferax volcanii DS2|42|66.6
9	2.31504	Halogeometricum borinquense PR3, DSM 11551|40|61.1
10	2.50519	Halomicrobium mukohataei arg-2, DSM 12286|45|65.6
11	2.19421	Haloplanus natans DSM 17983|40|65
12	2.65739	Halorhabdus tiamatea SARL4B|45|62.6
13	2.68247	Halorubrum lacusprofundi ATCC 49239|34|66.7
14	2.53585	Halovivax ruber XH-70, DSM 18193|37|64.3
22	2.74286	Methanoculleus marisnigri JR1, DSM 1498|23|62.1
26	2.50771	Natronococcus occultus SP4|37|64.9
29	4.17275	Pyrobaculum islandicum DSM 4184|100|49.6
32	4.56628	Pyrolobus fumarii 1A, DSM 11204|106|54.9
37	4.20939	Thermoproteus tenax Kra1|86|55.1

Mutual pairwise distances among centroids:

0	1	5.85923
Cluster point coordinates:
Cluster 0:	-0.683359	-0.527366	0.548684	-0.450489	0.12963	-0.307295	-0.0293818	-0.591917	-0.444557	0.633564	0.134933	0.61606	0.436044	0.584284	-0.57772	0.220065	-0.473119	-0.319584	0.471626	-0.50347	
Cluster 1:	1.22028	0.941726	-0.979794	0.804444	-0.231483	0.54874	0.0524674	1.057	0.793852	-1.13136	-0.240951	-1.10011	-0.778649	-1.04336	1.03164	-0.392973	0.844856	0.570685	-0.84219	0.899054	
```
