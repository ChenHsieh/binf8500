#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// functions for quick sort
// hoare partition
void swap(vector<string> seqs)
{
string temp;
            temp = seqs[0];
            seqs[0] = seqs[1];
            seqs[1] = temp;
        }


int main(int argc, char **argv)
{
    vector<string> seqs;
    // seqs.push_back("AAT");
    // seqs.push_back("ATG");
    seqs.push_back("zelda");
    seqs.push_back("peggy");
    seqs.push_back("betty");
    // seqs.push_back("becky");
    swap(seqs);
    // print out the sorted sequence
    for (int i = 0; i < seqs.size(); i++)
    {
        cout << seqs[i] << endl;
    }
    return 0;
}
