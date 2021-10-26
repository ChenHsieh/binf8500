// binf8500 assignment 4 - PSSM
// Student: Chen Hsieh
// ID: ch29576, 811744663

// script for testing
// g++ -std=c++11 -o ch29576PSSM -Wall ch29576PSSM.cpp; time ./ch29576PSSM FruR.txt ecoK12-MG1655.fasta
// g++ -std=c++11 -O3 -o ch29576PSSM -Wall ch29576PSSM.cpp; time ./ch29576PSSM FruR.txt ecoK12-MG1655.fasta

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;

int main(int argc, char **argv)
{
    // check input arguments
    cout << endl
         << "Chen's PSSM implementation" << endl
         << endl;
    if (argc < 3)
    {
        cout << endl
             << endl
             << endl
             << "Usage: " << argv[0] << " <AlignmentFile> <SequenceFile> [ScoreCutoff]" << endl
             << "Example: " << argv[0] << " FruR.txt ecoK12-MG1655.fasta" << endl
             << endl
             << endl
             << endl;
        exit(1);
    }

    // init variables
    std::ifstream alignmentFile(argv[1]);
    std::ifstream sequenceFile(argv[2]);
    if (argc > 3)
    {
        int scoreCutoff = atoi(argv[3]);
    }

    // read file into a string like a lump sum
    std::stringstream buffer1;
    buffer1 << alignmentFile.rdbuf();
    std::string file_contents1(buffer1.str());
    std::stringstream buffer2;
    buffer2 << sequenceFile.rdbuf();
    std::string file_contents2(buffer2.str());
    cout << "read file complete" << endl;

    // get gc content
    std::string header;
    std::string sequence;
    int start = 0;
    int end = file_contents2.find("\n", 0);
    header = file_contents2.substr(start, end);
    start = end + 1;
    float whole_length = file_contents2.size();
    cout << whole_length << endl;
    sequence = file_contents2.substr(start, whole_length);

    float gc_count = 0;

    for (unsigned i = 0; i < whole_length; i++)
    {
        if (sequence[i] == 'G' || sequence[i] == 'C')
        {
            gc_count++;
        }
    }
    // TODO change the whole_length to the sum of (AGCT), since there might be ambiguous characters
    float gc_content = (gc_count / whole_length) / 2;
    float q[4];
    q[0] = 0.5 - gc_content;
    q[1] = gc_content;
    q[2] = gc_content;
    q[3] = 0.5 - gc_content;

    // get the alignment file content
    start = 0;
    end = file_contents1.find("\n", 0);

    unsigned lineNum = 0;
    vector<std::string> seqs;
    while (end != std::string::npos)
    {
        sequence = file_contents1.substr(start, end - start);
        seqs.push_back(sequence);
        start = end + 1;
        end = file_contents1.find("\n", start);
        lineNum++;
        // cout << sequence << endl;
    }
    cout << lineNum << " sequences in the alignemnt file" << endl
         << endl;

    const unsigned alignment_length = seqs[0].size();
    int frequency_matrix[alignment_length][4];
    float probability_matrix[alignment_length][4];
    float pssm[alignment_length][4];

    unsigned i, j, k;
    std::string current_base;

    for (i = 0; i < alignment_length; i++)
    {
        // init matrix current row
        for (j = 0; j < 4; j++)
        {
            frequency_matrix[i][j] = 0;
        }
        // fill in the count by going through each aligned sequence
        for (j = 0; j < lineNum; j++)
        {
            // current base
            current_base = toupper(seqs[j][i]);
            if (current_base == "A")
            {
                frequency_matrix[i][0]++;
            }
            else if (current_base == "C")
            {
                frequency_matrix[i][1]++;
            }
            else if (current_base == "G")
            {
                frequency_matrix[i][2]++;
            }
            else if (current_base == "T")
            {
                frequency_matrix[i][3]++;
            }
            else
            {
                cout << "something's wierd in the alignment file" << endl;
            }
        }
        for (j = 0; j < 4; j++)
        {
            probability_matrix[i][j] = (frequency_matrix[i][j] + 0.25) / (lineNum + 1);
            pssm[i][j] = log2f(probability_matrix[i][j]) - log2f(q[j]);
        }
    }

    // printint matrixs
    cout << "frequency matrix:" << endl
         << "pos.\tA\tC\tG\tT" << endl;
    for (i = 0; i < alignment_length; i++)
    {
        cout << i + 1 << "\t";
        for (j = 0; j < 4; j++)
        {
            cout << std::fixed << setprecision(3) << frequency_matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    cout << "probability matrix:" << endl
         << "pos.\tA\tC\tG\tT" << endl;
    for (i = 0; i < alignment_length; i++)
    {
        cout << i + 1 << "\t";
        for (j = 0; j < 4; j++)
        {
            cout << std::fixed << setprecision(3) << probability_matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    // still different
    // for (j = 0; j < 4; j++)
    // {
    //     cout << q[j] << endl;
    // }
    cout << "PSSM:" << endl
         << "pos.\tA\tC\tG\tT" << endl;
    for (i = 0; i < alignment_length; i++)
    {
        cout << i + 1 << "\t";
        for (j = 0; j < 4; j++)
        {
            // pssm[i][j] = pssm[i][j] - log2f(q[j]);
            cout
                // << std::fixed << setprecision(3)
                << pssm[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl
         << "Training set motif scores:"
         << "\n";
    float min_input_score = 10000;
    for (i = 0; i < lineNum; i++)
    {
        float input_score = 0;
        for (j = 0; j < alignment_length; j++)
        {
            // current base
            current_base = toupper(seqs[i][j]);
            if (current_base == "A")
            {
                input_score += pssm[j][0];
            }
            else if (current_base == "C")
            {
                input_score += pssm[j][1];
            }
            else if (current_base == "G")
            {
                input_score += pssm[j][2];
            }
            else if (current_base == "T")
            {
                input_score += pssm[j][3];
            }
            else
            {
                cout << "something's wierd in the alignment file" << endl;
            }
        }
        cout << seqs[i] << "\t" << input_score << "\n ";
        if (input_score < min_input_score)
        {
            min_input_score = input_score;
        }
    }
    cout << min_input_score << "\n";
}