// binf8500 assignment 3 - NW
// Student: Chen Hsieh
// ID: ch29576, 811744663

// g++ -std=c++11 -o ch29576NW -Wall ch29576NW.cpp;time ./ch29576NW Test01.fasta Test02.fasta 1 -1 -1

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    // check input arguments
    if (argc != 6)
    {
        cout << endl
             << endl
             << endl;
        cout << "Usage: " << argv[0] << " <input1.fasta> <input2.fasta> <match> <mismatch> <gap>" << endl;
        cout << "Example: " << argv[0] << " Test01.fasta Test02.fasta 1 -1 -1" << endl;
        cout << endl
             << endl
             << endl;
        exit(1);
    }

    // init variables
    std::ifstream myFile1(argv[1]);
    std::ifstream myFile2(argv[2]);
    int match = atoi(argv[3]);
    int mismatch = atoi(argv[4]);
    int gap = atoi(argv[5]);

    // read file into a string like a lump sum
    std::stringstream buffer;
    buffer << myFile1.rdbuf();
    std::string file_contents1(buffer.str());
    buffer << myFile2.rdbuf();
    std::string file_contents2(buffer.str());
    
    // get the column size and then row size
    int start = 0;
    int end = file_contents.find("\n", 0);
    std::string firstLine = file_contents.substr(start, end - start);
}