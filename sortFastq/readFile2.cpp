#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// functions for quick sort
// hoare partition
int partition(vector<string> seqs, int left, int right)
{

    //declare variables
    int l = left, r = right;
    string temp;                                // for swap
    int pivotIndex = left + (right - left) / 2; // pick the middle one as pivot
    string pivotString = seqs[pivotIndex];      // get value

    // when still moving to the middle
    while (l <= r)
    {
        // move to the middle until meet someone tha should move to the other side
        while (seqs[l].compare(pivotString) < 0)
        {
            l++;
        }
        while (pivotString.compare(seqs[r]) < 0)
        {
            r--;
        }
        // check not ending case
        if (l <= r)
        {
            temp = seqs[l];
            seqs[l] = seqs[r];
            seqs[r] = temp;
            // offset to move on to next iteration
            l++;
            r--;
        }
    }
    return r;
}

void quicksort(vector<string> seqs, int left, int right)
{
    // when still have elements to sort
    if (left < right)
    {
        // partition, get the index of the pivot
        int pivotIndex = partition(seqs, left, right);

        // let the recursive functions to divide and conquor
        quicksort(seqs, left, pivotIndex);
        quicksort(seqs, pivotIndex + 1, right);
    }
}
int main(int argc, char *argv[])
{

    string line;
    ifstream myfile(argv[1]);
    ofstream resultfile;
    resultfile.open("out.fastq");

    int count = 0;
    int chunk_count = 0;
    vector<string> seqs;
    map<string, string> chunk_map;
    string chunk = "";
    // read file and store stuffs
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            chunk_count = count / 4;
            chunk += line;
            chunk += "\n";
            if (count % 4 == 1) // sequence line
            {
                seqs.push_back(line);
            }
            else if (count % 4 == 3) // quality line
            {
                chunk_map[seqs[chunk_count]] = chunk;
                chunk = "";
            }
            count++;
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
    }

    // let the quickSort kick in
    quicksort(seqs, 0, seqs.size() - 1);

    // recontruct the file for output
    for (int i = 0; i < seqs.size(); i++){
        resultfile << chunk_map[seqs[i]];
    }
    
    resultfile.close();

    return 0;
}
