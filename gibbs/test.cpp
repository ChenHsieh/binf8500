
// g++ -std=c++11 -O3 -o test -Wall test.cpp; time ./test

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <vector>
#include <map>

using namespace std;

int get_new_motif_position(vector<vector<int> > motif_list, vector<double> current_score_list, vector<vector<int> > seq_seqs_transformed, int current_background_seq_index)
{
    double R = drand48();
    double score_accumulation = 0;
    double score_sum = 100;
    R *= score_sum;
    int i = 0;
    while (R > score_accumulation)
    {
        score_accumulation += current_score_list[i];
        i++;
    }
    i--; // offset
    return i;
}

int main(int argc, char **argv)
{
    cout << exp2(3) << endl;
    cout << exp2(3) - exp2(2) << endl;
    return 0;
}
