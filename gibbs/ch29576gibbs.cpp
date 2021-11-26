// binf8500 assignment 5 - Gibbs Sampler
// Student: Chen Hsieh
// ID: ch29576, 811744663

// script for testing the Gibbs sampler
// g++ -std=c++11 -O3 -o ch29576gibbs -Wall ch29576gibbs.cpp; time ./ch29576gibbs E.coliRpoN-sequences-6-300nt.fasta 30

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <vector>
#include <map>

using namespace std;

int main(int argc, char **argv)
{
    // timer
    clock_t Start = 0;

    cout << std::fixed << setprecision(3) << endl
         << "Chen's Simple Gibbs motif sampler output:" << endl
         << endl;
    // check input arguments

    // Usage:
    //     Gibbs InputFile MotifLength

    if (argc < 3)
    {
        cout << endl
             << endl
             << endl
             << "Usage: " << argv[0] << " <InputFile> <MotifLength>" << endl
             << "Example: " << argv[0] << " E.coliRpoN-sequences-6-300nt.fasta 30" << endl
             << "InputFile : sequences in FASTA format." << endl
             << "MotifLength : estimated length of the motif." << endl
             << endl
             << endl
             << endl;
        exit(1);
    }
    // read input and init variables
    cout << "Input File: " << argv[1] << endl;
    cout << "Initial Motif Length: " << argv[2] << endl;
    std::ifstream sequenceFile(argv[1]);
    int motifLength = atoi(argv[2]);

    // read file into a string like a lump sum
    std::stringstream buffer;
    buffer << sequenceFile.rdbuf();
    std::string file_contents(buffer.str());
    cout << "read file complete" << endl;
    cerr << "Time after reading input: " << (clock() - Start) / (double)(CLOCKS_PER_SEC) << "seconds\n";

    // get each input sequence and calculate  gc content
    unsigned rowSize = 0;
    std::string header = "";
    std::string sequence = "";
    map<string, string> input_seqs;
    // map<string, double> gc_content;
    double gc_content = 0;

    vector<string> seq_names;
    vector<string> seq_seqs;
    vector<vector<int> > seq_seqs_transformed;
    vector<vector<double> > seq_gc;
    int start = 1;
    int end = 0;

    while (end != std::string::npos)
    {
        end = file_contents.find("\n", start);
        header = file_contents.substr(start, end - start);
        start = end + 1;
        end = file_contents.find(">", start);

        sequence = file_contents.substr(start, end - start);
        start = end + 1;
        sequence.erase(std::remove(sequence.begin(), sequence.end(), '\n'),
                       sequence.end());
        rowSize++;
        // cout << rowSize << endl;
        // cout << header << endl;
        // cout << sequence << endl;
        input_seqs[header] = sequence;
        seq_names.push_back(header);
        seq_seqs.push_back(sequence);

        // calculate gc content and transform into number
        int gc_count = 0;

        // "pos.\tA\tC\tG\tT"
        // 0 A
        // 1 C
        // 2 G
        // 3 T
        // 4 others
        int seq_length = sequence.length();
        vector<int> seq_transformed(seq_length, 0);
        for (int i = 0; i < sequence.length(); i++)
        {
            if (sequence[i] == 'G')
            {
                seq_transformed[i] = 2;
                gc_count++;
            }
            else if (sequence[i] == 'C')
            {
                seq_transformed[i] = 1;
                gc_count++;
            }
            else if (sequence[i] == 'A')
            {
                seq_transformed[i] = 0;
            }
            else if (sequence[i] == 'T')
            {
                seq_transformed[i] = 3;
            }
            else
            {
                seq_transformed[i] = 4;
            }
        }
        gc_content = ((double)gc_count / (double)seq_length) / 2;
        vector<double> q{(0.5 - gc_content), gc_content, gc_content, (0.5 - gc_content)};
        seq_gc.push_back(q);

        // gc_content[header] = (double)gc_count / sequence.length();
        seq_seqs_transformed.push_back(seq_transformed);
    }

    // get initial motif list according to motif length
    vector<vector<int> > motif_list;
    for (int i = 0; i < seq_seqs_transformed.size(); i++)
    {
        vector<int> motif_list_i;
        int R = round(drand48() * (seq_seqs_transformed[i].size() - motifLength + 1));
        for (int j = 0; j < motifLength; j++)
        {
            motif_list_i.push_back(seq_seqs_transformed[i][R + j]);
        }
        motif_list.push_back(motif_list_i);
    }
    cout << "motif list generated" << endl;
    cerr << "Time after motif list generation: " << (clock() - Start) / (double)(CLOCKS_PER_SEC) << "seconds\n";

    // calculate pssm
    int current_background_seq_index = 0;
    unsigned int sequence_number = rowSize - 1;
    const unsigned alignment_length = motifLength;
    int frequency_matrix[alignment_length][4];
    float probability_matrix[alignment_length][4];
    float pssm[alignment_length][4];
    unsigned i, j;
    int current_base;
    // get the probabilities
    for (i = 0; i < alignment_length; i++)
    {
        // init matrix current row
        for (j = 0; j < 4; j++)
        {
            frequency_matrix[i][j] = 0;
        }
        // fill in the count by going through each aligned sequence
        for (j = 0; j < sequence_number; j++)
        {
            // current base
            frequency_matrix[i][seq_seqs_transformed[j][i]]++;
        }
        // calculate the probabilities
        for (j = 0; j < 4; j++)
        {
            probability_matrix[i][j] = (frequency_matrix[i][j] + 0.25) / (sequence_number + 1);
            pssm[i][j] = log2f(probability_matrix[i][j]) - log2f(seq_gc[current_background_seq_index][j]);
        }
    }
    // we do not need the complementary matrix this time
    cout << "PSSM:" << endl
         << "pos.\tA\tC\tG\tT" << endl;
    for (i = 0; i < alignment_length; i++)
    {
        cout << i + 1 << "\t";
        for (j = 0; j < 4; j++)
        {
            // complementary_pssm[alignment_length - 1 - i][3 - j] = pssm[i][j];
            cout << pssm[i][j] << "\t";
        }
        cout << endl;
    }
    cerr << "Time after PSSM calculation: " << (clock() - Start) / (double)(CLOCKS_PER_SEC) << "seconds\n";

    // take care of the current sequence, calculate the score for all positions
    vector<double> current_score_list;
    int seq_length = seq_seqs_transformed[0].size();
    double score_sum = 0;
    cout << "seq_length: " << seq_length << endl;
    for (i = 0; i < seq_length - motifLength + 1; i++)
    {
        double current_score = 0;
        for (j = 0; j < motifLength; j++)
        {
            cout << seq_seqs_transformed[current_background_seq_index][i + j];
            current_base = seq_seqs_transformed[current_background_seq_index][i + j];

            current_score += pssm[j][current_base];
        }
        if (current_score < 0) // in case it is negative
        {
            current_score = 0;
        }
        current_score_list.push_back(current_score);
        score_sum += current_score;
        cout << endl;
    }

    // get the new motif according to proportional probability
    double R = drand48();
    double score_accumulation = 0;
    R *= score_sum;
    i = 0;
    while (R > score_accumulation)
    {
        score_accumulation += current_score_list[i];
        i++;
    }
    i--; //offset
    // substitute the motif
    for  (j = 0; j < motifLength; j++)
    {
        motif_list[current_background_seq_index][j] = seq_seqs_transformed[current_background_seq_index][i + j];
    }


    
// // generate random start positions
// vector<int> start_positions;
// for (int i = 0; i < rowSize; i++)
// {
//     int start = round(drand48() * (input_seqs.size() - 1));
//     start_positions.push_back(start);
// }
// cout << "start positions generated" << endl;
// cerr << "Time after start positions generation: " << (clock() - Start) / (double)(CLOCKS_PER_SEC) << "seconds\n";

// // generate random motifs
// vector<string> motifs;
// for (int i = 0; i < rowSize; i++)
// {
//     int index = round(drand48() * (motif_list.size() - 1));
//     motifs.push_back(motif_list[index]);
// }
// cout << "motifs generated" << endl;
// cerr << "Time after motifs generation: " << (clock() - Start) / (double)(CLOCKS_PER_SEC) << "seconds\n";

// // calculate motif count
// vector<int> motif_count;
// for (int i = 0; i < rowSize; i++)
// {
//     int count = 0;
//     for (int j = 0; j < motifLength; j++)

cerr << "Time after scanning the whole sequence: " << (clock() - Start) / (double)(CLOCKS_PER_SEC) << "seconds\n";
return 0;
}
