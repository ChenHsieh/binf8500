// binf8500 assignment 3 - NW
// Student: Chen Hsieh
// ID: ch29576, 811744663

// script for testing
// g++ -std=c++11 -o ch29576NW -Wall ch29576NW.cpp;time ./ch29576NW News1.fasta News2.fasta 1 -1 -1
// g++ -std=c++11 -o ch29576NW -Wall ch29576NW.cpp;time ./ch29576NW RpoB-E.coli.fasta RpoB-B.subtilis.fasta 1 -1 -1
// g++ -std=c++11 -o ch29576NW -Wall ch29576NW.cpp;time ./ch29576NW HIV1a.fasta HIV1b.fasta 1 -1 -1
// g++ -std=c++11 -o ch29576NW -Wall ch29576NW.cpp;time ./ch29576NW M.genitaliumM2321.fasta M.genitaliumG37.fasta 1 -1 -1

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// helper functions
std::string cleanStr(std::string str)
{
    // for(unsigned int i = 0; i <= str.length(); i++) // buggy, end of file not handled
    // {
    //     if(str[i] == '\n' || str[i] == '\r')
    //     {
    //         str.erase(i, 1);
    //     }
    // }
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    return str;
}

int getAlignmentNumber(std::string str)
{
    int nonGapNum = 0;
    int N = str.length();
    for (unsigned i = 0; i < N; i++)
    {
        // cout << str[i];
        // cout << (str[i] == '-') << endl;

        if (str[i] == '-')
        {
            continue;
        }
        else
        {
            nonGapNum++;
        }
    }
    return nonGapNum;
}

int main(int argc, char **argv)
{
    // check input arguments
    cout << endl
         << "Chen's Needleman-Wunsch global alignment implementation" << endl
         << endl;
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
    cout << "\theader from file 1:\t" << firstLine1 << endl;
    content1 = cleanStr(content1);
    cout << "\tcontent from file 1:\t" << content1 << endl;
    cout << "\tsize of file 1:\t" << content1.size() << endl;
    cout << endl;

    // get the second file content
    start = 0;
    end = file_contents2.find("\n", 0);
    std::string firstLine2 = file_contents2.substr(start, end - start);
    start = end + 1;
    std::string content2 = file_contents2.substr(start, file_contents2.size());
    cout << "File 2: " << argv[2] << endl;
    cout << "\theader from file 2:\t" << firstLine2 << endl;
    content2 = cleanStr(content2);
    cout << "\tcontent from file 2:\t" << content2 << endl;
    // print size of content2
    cout << "\tsize of file 2:\t" << content2.size() << endl
         << endl
         << endl;

    cout << "Scores:" << endl
         << "Match: " << match << ",  Mismatch: " << mismatch << ",  Gap: " << gap << endl
         << endl;

    // init the matrix
    cout << "Initializing matrix..." << endl;
    // int matrix[content1.size() + 1][content2.size() + 1];
    // vector<vector<int> > matrix(content1.size() + 1, vector<int>(content2.size() + 1, 0));
    int row = content2.size() + 1;
    int col = content1.size() + 1;
    int *matrix = (int *)malloc((row * col) * sizeof(int));
    // T = (int *)malloc(12*sizeof(int));
    cout << "Initializing matrix...done" << endl
         << endl;
    for (unsigned i = 0; i < content1.size() + 1; i++)
    {
        // cout << "Initializing row " << i << "..." << endl;
        // cout << "\t\t";
        // if (i == 0) // fill up the first row
        // {

        //     for (int j = 0; j < content2.size() + 1; j++)
        //     {
        //         cout << content2[j] << "\t";
        //     }
        // }
        // cout << endl;
        for (unsigned j = 0; j < content2.size() + 1; j++)
        {
            // cout << "Initializing col " << j << "..." << endl;
            if (i == 0) // fill up the first row
            {

                matrix[j] = j * gap;
                // if (j == 0)
                // {
                //     cout << "\t";
                // }
            }
            else if (j == 0) // fill up the first column
            {
                // cout << content1[i - 1] << "\t";
                matrix[i * row] = i * gap;
            }
            else // actual content
            {
                // if the character is the same, beware of the offset
                if (content1[i - 1] == content2[j - 1])
                {
                    matrix[i * row + j] = matrix[(i - 1) * row + (j - 1)] + match;
                }
                else
                {
                    matrix[i * row + j] = std::max(
                        matrix[(i - 1) * row + j] + gap,
                        std::max(
                            matrix[i * row + j - 1] + gap,
                            matrix[(i - 1) * row + (j - 1)] + mismatch));
                }
            }
            // cout << matrix[i * row + j] << "\t";
        }
        // cout << endl;
    }
    cout << "matrix calc done" << endl;
    cout << endl
         << "Alignment score: " << matrix[content1.size() * row + content2.size()] << endl
         << endl;
    // traverse the matrix to find the alignment

    bool found = false;
    int i = content1.size();
    int j = content2.size();
    std::string alignment1 = "";
    std::string alignment2 = "";
    std::string matching = "";
    //  backtracing
    while (!found)
    {
        if (matrix[(i)*row + (j)] == matrix[(i - 1) * row + (j)] + gap)
        {
            alignment1 = content1[i - 1] + alignment1;
            alignment2 = "-" + alignment2;
            matching = " " + matching;
            i--;
        }
        else if (matrix[(i)*row + (j)] == matrix[(i)*row + (j - 1)] + gap)
        {
            alignment1 = "-" + alignment1;
            alignment2 = content2[j - 1] + alignment2;
            matching = " " + matching;
            j--;
        }
        else if (matrix[(i)*row + (j)] == matrix[(i - 1) * row + (j - 1)] + mismatch)
        {
            alignment1 = content1[i - 1] + alignment1;
            alignment2 = content2[j - 1] + alignment2;
            matching = " " + matching;
            i--;
            j--;
        }
        else if (matrix[(i)*row + (j)] == matrix[(i - 1) * row + (j - 1)] + match)
        {
            alignment1 = content1[i - 1] + alignment1;
            alignment2 = content2[j - 1] + alignment2;
            matching = "*" + matching;
            i--;
            j--;
        }
        else
        {
            // debug
            cout << i << ":" << j << endl;
            cout << "Error: " << matrix[(i)*row + (j)] << endl;
            break;
        }
        if (i == 0 && j == 0)
        {
            found = true;
        }
    }

    // fancy output formatting
    int alignment_length = alignment1.length();
    int count1 = 1;
    int count2 = 1;
    for (unsigned i = 0; i < alignment_length / 60; i++)
    {

        cout
            << "\t\t" << count1 << "\t" << alignment1.substr(i * 60, 60) << endl;
        cout << "\t\t"
             << "\t" << matching.substr(i * 60, 60) << endl;
        cout << "\t\t" << count2 << "\t" << alignment2.substr(i * 60, 60) << endl
             << endl;
        count1 += getAlignmentNumber(alignment1.substr(i * 60, 60));
        count2 += getAlignmentNumber(alignment2.substr(i * 60, 60));
        // if (i % 60 == 0)
        // {
        //     cout << endl;
        // }
        // cout << alignment1[i] << "\t" << alignment2[i] << "\t" << matching[i] << endl;
    }
    cout << "\t\t" << count1 << "\t" << alignment1.substr((alignment_length / 60) * 60, alignment_length) << endl;
    cout << "\t\t"
         << "\t" << matching.substr((alignment_length / 60) * 60, alignment_length) << endl;
    cout << "\t\t" << count2 << "\t" << alignment2.substr((alignment_length / 60) * 60, alignment_length) << endl
         << endl;
}