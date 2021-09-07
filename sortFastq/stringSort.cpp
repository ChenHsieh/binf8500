#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// functions for quick sort
// hoare partition
int partition(vector<string> &seqs, int left, int right)
{
    //declare variables
    int l = left, r = right;
    string temp;                                // for swap
    int pivotIndex = left + (right - left) / 2; // pick the middle one as pivot
    string pivotString = seqs[pivotIndex];      // get value
    // when still moving to the middle
    while (l < r)
    {

        // move boundaries to the middle
        // until meet someone tha should move to the other side
        while (seqs[l].compare(pivotString) < 0) // if the left one is smaller than pivot
        {
            l++;
        }
        while (pivotString.compare(seqs[r]) < 0)
        {
            r--;
        }
        // check not ending case
        if (l < r)
        {
            temp =seqs[l];
            seqs[l] = seqs[r];
            seqs[r] = temp;
            // offset to move on to next iteration
            l++;
            r--;
        }
    }
    return l;
}

void quicksort(vector<string> &seqs, int left, int right)
{
    // when still have elements to sort
    if (left < right)
    {
        // partition, get the index of the pivot
        int pivotIndex = partition(seqs, left, right);
        cout << "pivotIndex: " << pivotIndex << endl;
        cout << "left: " << left << endl;
        cout << "right: " << right << endl;
        for (int i = 0; i < seqs.size(); i++)
        {
            cout << seqs[i] << endl;
        }
        // let the recursive functions to divide and conquor
        quicksort(seqs, left, pivotIndex);
        quicksort(seqs, pivotIndex + 1, right);
    }
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
    cout << seqs[0].compare(seqs[1]) << endl;
    cout << seqs[1].compare(seqs[0]) << endl;
    int count = 0;
    cout << "file reading finished" << endl;
    // let the quickSort kick in
    quicksort(seqs, 0, seqs.size() - 1);
    cout << "quick sort finished" << endl;
    // print out the sorted sequence
    for (int i = 0; i < seqs.size(); i++)
    {
        cout << seqs[i] << endl;
    }
    return 0;
}
