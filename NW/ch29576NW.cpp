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
#include <algorithm>

using namespace std;

// helper functions
std::string cleanStr(std::string str)
{
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    return str;
}

int main(int argc, char **argv)
{
    // check input arguments
    if (argc != 6)
    {
        cout << endl
             << endl
             << endl;
        cout << "Usage: " << argv[0] << " <input1.fasta> <input2.fasta> <match> <mismatch> <gap>" << endl;
        cout << "Example: " << argv[0] << " Test01.fasta Test02.fasta 1 0 -1" << endl;
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
    std::stringstream buffer1;
    buffer1 << myFile1.rdbuf();
    std::string file_contents1(buffer1.str());
    std::stringstream buffer2;
    buffer2 << myFile2.rdbuf();
    std::string file_contents2(buffer2.str());

    // get the first file content
    int start = 0;
    int end = file_contents1.find("\n", 0);
    std::string firstLine1 = file_contents1.substr(start, end - start);
    start = end + 1;
    std::string content1 = file_contents1.substr(start, file_contents1.size());
    cout << "File 1: " << argv[1] << endl;
    cout << "\tfirstLine1: " << firstLine1 << endl;
    content1 = cleanStr(content1);
    cout << "\tcontent1: " << content1 << endl;
    cout << "\tcontent1 size: " << content1.size() << endl;
    cout << endl;

    // get the second file content
    start = 0;
    end = file_contents2.find("\n", 0);
    std::string firstLine2 = file_contents2.substr(start, end - start);
    start = end + 1;
    std::string content2 = file_contents2.substr(start, file_contents2.size());
    cout << "File 2: " << argv[2] << endl;
    cout << "\tfirstLine2: " << firstLine2 << endl;
    content2 = cleanStr(content2);
    cout << "\tcontent2: " << content2 << endl;
    // print size of content2
    cout << "\tcontent2 size: " << content2.size() << endl
         << endl
         << endl;

    // init the matrix
    int matrix[content1.size() + 1][content2.size() + 1];
    for (int i = 0; i < content1.size() + 1; i++)
    {
        cout << "\t\t";
        if (i == 0) // fill up the first row
        {

            for (int j = 0; j < content2.size() + 1; j++)
            {
                cout << content1[j] << "\t";
            }
        }
        cout << endl;
        for (int j = 0; j < content2.size() + 1; j++)
        {
            if (i == 0) // fill up the first row
            {

                matrix[i][j] = j * gap;
                if (j == 0)
                {
                    cout << "\t";
                }
            }
            else if (j == 0) // fill up the first column
            {
                cout << content2[i - 1] << "\t";
                matrix[i][j] = i * gap;
            }
            else // actual content
            {
                // if the character is the same, beware of the offset
                if (content1[i - 1] == content2[j - 1])
                {
                    matrix[i][j] = matrix[i - 1][j - 1] + match;
                }
                else
                {
                    matrix[i][j] = std::max(
                        matrix[i - 1][j] + gap,
                        std::max(
                            matrix[i][j - 1] + gap,
                            matrix[i - 1][j - 1] + mismatch));
                }
            }
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "Alignment score: " << matrix[content1.size()][content2.size()] << endl;
    // traverse the matrix to find the alignment

    bool found = false;
    int i = content1.size();
    int j = content2.size();
    std::string alignment1 = "";
    std::string alignment2 = "";
    std::string matching = "";
    // std::string alignment1(1, content1.at(i - 1));
    // std::string alignment2(1, content2.at(j - 1));
    // std::string matching = "*";
    // cout << "Alignment 1: " << alignment1 << endl;
    // cout << "Alignment 2: " << alignment2 << endl;
    // cout << matrix[i][j] << endl;
    // i--;
    // j--;
    cout << i << ":" << j<<endl;

    while (!found)
    {
        cout << matrix[i][j] << endl;
        cout << matrix[i][j-1] << endl;
        cout << matrix[i-1][j] << endl;
        cout << matrix[i-1][j-1] << endl;
        cout << match << endl;
        cout << (matrix[i][j] == matrix[i - 1][j - 1] + match) << endl;
        if (matrix[i][j] == matrix[i - 1][j] + gap)
        {

            alignment1 = content1[i - 1] + alignment1;
            alignment2 = "-" + alignment2;
            matching = " " + matching;
            i--;
        }
        else if (matrix[i][j] == matrix[i][j - 1] + gap)
        {

            alignment1 = "-" + alignment1;
            alignment2 = content2[j - 1] + alignment2;
            matching = " " + matching;
            j--;
        }
        else if (matrix[i][j] == matrix[i - 1][j - 1] + mismatch)
        {

            alignment1 = content1[i - 1] + alignment1;
            alignment2 = content2[j - 1] + alignment2;
            matching = " " + matching;
            i--;
            j--;
        }
        else if (matrix[i][j] == matrix[i - 1][j - 1] + match)
        {

            alignment1 = content1[i - 1] + alignment1;
            alignment2 = content2[j - 1] + alignment2;
            matching = "*" + matching;
            i--;
            j--;
        }
        else
        {
            cout << i << ":" << j<<endl;
            cout << "Error: " << matrix[i][j] << endl;
            cout << "wrong!!!" << endl;
            break;
        }
        if (i == 0 && j == 0)
        {
            found = true;
        }
        cout << alignment1 << " ";
        cout << matching << " ";
        cout << alignment2 << " ";
        cout << endl;
    }
    cout << "Alignment 1:\t" << alignment1 << endl;
    cout << "Matching:\t" << matching << endl;
    cout << "Alignment 2:\t" << alignment2 << endl;
}