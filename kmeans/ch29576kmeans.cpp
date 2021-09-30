// binf8500 assignment 2 - kmeans
// Student: Chen Hsieh
// ID: ch29576, 811744663

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// void kMeansClustering(array<>* points, int epochs, int k);

int main(int argc, char **argv)
{
    // check input arguments
    if (argc != 4)
    {
        cout << "Usage: " << argv[0] << " <input_file> <minimal k> <maximal k>" << endl;
        exit(1);
    }

    std::ifstream myFile(argv[1]);
    int minimal_k = atoi(argv[2]);
    int maximal_k = atoi(argv[3]);

    // read file into a string like a lump sum
    std::stringstream buffer;
    buffer << myFile.rdbuf();
    std::string file_contents(buffer.str());

    // get the column size and then row size
    int start = 0;
    int end = file_contents.find("\n", 0);
    std::string firstLine = file_contents.substr(start, end - start);

    // get row size
    start = 0;
    end = file_contents.find("\n", 0);
    int rowSize = 0;
    while (end != std::string::npos)
    {
        start = end + 1;
        end = file_contents.find("\n", start);
        rowSize++;
    }
    cout << "rowSize: " << rowSize << endl;

    // split lines into words according to \t, store values into vector or array
    start = 0;
    end = firstLine.find("\t", 0);
    int colSize = 0;
    while (end != std::string::npos)
    {
        // cout << firstLine.substr(start, end - start) << endl;
        start = end + 1;
        end = firstLine.find("\t", start);
        colSize++;
    }
    colSize++;
    cout << "colSize: " << colSize << endl;

    // create a 2D array to store the data
    float data[rowSize - 1][colSize - 1];
    // float **points = new float*[rowSize];

    end = file_contents.find("\n", 0);
    start = end + 1;
    int lineEnd, lineStart;

    for (int i = 0; i < rowSize - 1; i++)
    {
        end = file_contents.find("\n", start);
        std::string currentLine = file_contents.substr(start, end - start);

        lineEnd = currentLine.find("\t", 0);
        lineStart = lineEnd + 1;
        // cout << "currentLine: " << currentLine << endl;
        for (int j = 0; j < colSize - 1; j++)
        {
            lineEnd = currentLine.find("\t", lineStart);
            // cout << "currentnumber: " << currentLine.substr(lineStart, lineEnd - lineStart) << endl;
            data[i][j] = atof(currentLine.substr(lineStart, lineEnd - lineStart).c_str());

            lineStart = lineEnd + 1;
        }
        start = end + 1;

        cout << i << endl;
    }
    cout << "data[0][0]: " << data[0][0] << endl;

    return 0;
}