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

std::string number2char(int number)
{
    switch (number)
    {
    case 0:
        return "A";
    case 1:
        return "C";
    case 2:
        return "G";
    case 3:
        return "T";
    default:
        return "";
    }
}

vector<vector<double> > get_pssm(vector<vector<int> > motif_list, vector<vector<int> > seq_seqs_transformed, int current_background_seq_index, vector<vector<double> > seq_gc)
{
    int alignment_length = motif_list[0].size();
    int sequence_number = motif_list.size();
    int frequency_matrix[alignment_length][4];
    float probability_matrix[alignment_length][4];
    vector<double> pssm_row;
    vector<vector<double> > pssm;
    int i, j;
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
            if (j == current_background_seq_index)
            {
                continue;
            }
            else
            {
                frequency_matrix[i][motif_list[j][i]]++;
            }
        }
        // calculate the probabilities
        for (j = 0; j < 4; j++)
        {
            probability_matrix[i][j] = (frequency_matrix[i][j] + 0.25) / (sequence_number + 1);
            if (current_background_seq_index == -1)
            {
                pssm_row.push_back(exp2(probability_matrix[i][j]));
                // cout << probability_matrix[i][j] << " ";
            }
            else
            {
                // pssm_row.push_back(exp2(probability_matrix[i][j]) - exp2(seq_gc[current_background_seq_index][j]));
                pssm_row.push_back((probability_matrix[i][j]) - exp2(seq_gc[current_background_seq_index][j]));
                // cout << probability_matrix[i][j] << " ";
            }
        }
        // cout << endl;
        pssm.push_back(pssm_row);
    }

    return pssm;
}

vector<double> get_score_list(vector<vector<double> > pssm, vector<int> current_seq)
{
    int seq_length = current_seq.size();
    int motifLength = pssm.size();
    vector<double> current_score_list;
    int i, j;
    for (i = 0; i < seq_length - motifLength + 1; i++)
    {
        double current_score = 0;
        for (j = 0; j < motifLength; j++)
        {
            current_score += pssm[j][current_seq[i + j]];
        }
        // cout << current_score << endl;
        if (current_score < 0) // in case it is negative
        {
            current_score = 0;
        }
        current_score_list.push_back(current_score);
    }
    return current_score_list;
}

double get_score_sum(vector<double> current_score_list)
{
    int seq_length = current_score_list.size();
    double current_score_sum = 0;
    int i;
    for (i = 0; i < seq_length; i++)
    {
        current_score_sum += current_score_list[i];
    }
    return current_score_sum;
}
int get_new_motif_position(vector<vector<int> > motif_list, vector<double> current_score_list, vector<vector<int> > seq_seqs_transformed, int current_background_seq_index)
{
    double R = drand48();
    double score_accumulation = 0;
    double score_sum = get_score_sum(current_score_list);
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
vector<int> update_motif_list(vector<vector<int> > motif_list, vector<double> current_score_list, vector<vector<int> > seq_seqs_transformed, int current_background_seq_index, int new_motif_position)
{

    int alignment_length = motif_list[0].size();
    int i = new_motif_position;
    vector<int> new_motif(alignment_length, 0);
    // substitute the motif
    for (int j = 0; j < alignment_length; j++)
    {
        new_motif[j] = seq_seqs_transformed[current_background_seq_index][i + j];
        // cout << seq_seqs_transformed[current_background_seq_index][i + j] << " ";
    }
    // cout << endl;
    return new_motif;
}

int main(int argc, char **argv)
{
    srand48(time(NULL));
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

    // read input files
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
    vector<int> motif_position;
    for (int i = 0; i < seq_seqs_transformed.size(); i++)
    {
        vector<int> motif_list_i;
        int R = round(drand48() * (seq_seqs_transformed[i].size() - motifLength + 1));
        for (int j = 0; j < motifLength; j++)
        {
            motif_list_i.push_back(seq_seqs_transformed[i][R + j]);
        }
        motif_list.push_back(motif_list_i);
        motif_position.push_back(R);
    }
    cout << "initial motif list generated" << endl;
    cerr << "Time after motif list generation: " << (clock() - Start) / (double)(CLOCKS_PER_SEC) << "seconds\n";

    // Gibbs sampling
    int plateau_count = 0;
    int plateau_count_max = 200;
    double score_max = 0;
    vector<vector<int> > motif_list_max;
    vector<int> motif_position_max;
    bool optimizing = true;
    int cycle_count = 0;
    while (optimizing)
    {
        cycle_count++;
        // cycle
        for (int current_background_seq_index = 0; current_background_seq_index < seq_seqs_transformed.size(); current_background_seq_index++)
        {
            // get pssm
            vector<vector<double> > pssm = get_pssm(motif_list, seq_seqs_transformed, current_background_seq_index, seq_gc);
            cout << "cycle_count: " << cycle_count << "pssm" << endl;
            // take care of the current sequence, calculate the score for all positions
            vector<double> current_score_list = get_score_list(pssm, seq_seqs_transformed[current_background_seq_index]);
            cout << "cycle_count: " << cycle_count << "score list" << endl;
            // get the new motif according to proportional probability
            motif_position[current_background_seq_index] = get_new_motif_position(motif_list, current_score_list, seq_seqs_transformed, current_background_seq_index);
            cout << "cycle_count: " << cycle_count << "get new motif" << endl;
            // cout << current_background_seq_index << ", " << motif_position[current_background_seq_index] << endl;
            motif_list[current_background_seq_index] = update_motif_list(motif_list, current_score_list, seq_seqs_transformed, current_background_seq_index, motif_position[current_background_seq_index]);
            cout << "cycle_count: " << cycle_count << "update motif" << endl;
        }
        cout << "cycle_count: " << cycle_count << endl;
        // objective function

        // after a whole round of substitution, calculate the pssm again to check the overall score improvement
        double score_sum = 0;
        vector<vector<double> >
            pssm = get_pssm(motif_list, seq_seqs_transformed, -1, seq_gc);
        for (int i = 0; i < seq_seqs_transformed.size(); i++)
        {
            vector<double> current_score_list = get_score_list(pssm, motif_list[i]);
            cout << current_score_list[0] << endl;
            score_sum += current_score_list[0];
        }

        if (score_sum > score_max)
        {
            score_max = score_sum;
            motif_list_max = motif_list;
            motif_position_max = motif_position;
            plateau_count = 0;
        }
        else
        {
            plateau_count++;
        }

        cout << ", " << score_max << ", " << score_sum << endl;
        if (plateau_count > plateau_count_max)
        {
            optimizing = false;
        }
    }
    cout << "Gibbs sampling finished" << endl;
    cout << "best score: " << score_max << endl;
    for (int i = 0; i < motif_list_max.size(); i++)
    {
        cout << seq_names[i] << "\t";
        cout << motif_position_max[i] << "-" << (motif_position_max[i] + motifLength) << "\t";
        for (int j = 0; j < motif_list_max[i].size(); j++)
        {
            cout << number2char(motif_list_max[i][j]);
        }
        cout << endl;
    }
    cout << "cycle_count: " << cycle_count << endl;

    cerr << "Time after scanning the whole sequence: " << (clock() - Start) / (double)(CLOCKS_PER_SEC) << "seconds\n";
    return 0;
}
