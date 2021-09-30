// binf8500 assignment 2 - kmeans
// Student: Chen Hsieh
// ID: ch29576, 811744663

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>

using namespace std;

void kMeansClustering(map<string, vector<float> > dataPointsMap, int k)
{
    vector<int> clusterAssignment(dataPointsMap.size());
    vector<vector<int> > clusterPoints(k);
    vector<int> centroids(k);
    int i, j;
    int minIndex;
    double minDistance;
    double distance;
    int count;
    int index;
    int centroidIndex;
    int iteration;
    int maxIteration;
    int maxIterationCount;
    int maxIterationIndex;
    int maxIterationDistance;
    int maxIterationCentroidIndex;
    // random selestion

    for (i = 0; i < k; i++)
    {
        centroids[i] = rand() % dataPointsMap.size();
        cout << "centroids[" << i << "] = " << centroids[i] << endl;
    }

    // calculate distance to centroid
    // for each data point
    for (i = 0; i < dataPointsMap.size(); i++)
    {
        minDistance = 1000000;
        minIndex = -1;
        // for k centroid
        for (j = 0; j < k; j++)
        {
            distance = 0;
            // foreach dimension of the data point
            for (count = 0; count < dataPointsMap[dataPointsMap.begin()->first].size(); count++)
            {
                // sum of square of difference
                distance += pow(dataPointsMap[dataPointsMap.begin()->first][count] - dataPointsMap[dataPointsMap.begin()->first][centroids[j]], 2);

                // assign to centroidIndex
            }
        }
    }
}

// with_separator() function accepts
// two  arguments i.e., a vector and
// a separator string
// void with_separator(const vector<S> &vec,
//                     string sep = " ")
// {
//     // Iterating over all elements of vector
//     for (auto elem : vec)
//     {
//         cout << elem << sep;
//     }

//     cout << endl;
// }
int main(int argc, char **argv)
{
    // check input arguments
    if (argc != 4)
    {
        cout << "Usage: " << argv[0] << " <input_file> <minimal k> <maximal k>" << endl;
        exit(1);
    }
    // assign values from cmd line input
    std::ifstream myFile(argv[1]);
    int minimal_k = atoi(argv[2]);
    int maximal_k = atoi(argv[3]);
    // read data from file
    std::string line;
    map<string, vector<float> > dataPointsMap;
    int start = 0;
    int end = 0;
    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            vector<float> dataPoints;

            start = 0;
            end = line.find("\t", 0);
            string label = line.substr(start, end - start);
            cout << "label: " << label << endl;
            while (end != std::string::npos)
            {
                start = end + 1;
                end = line.find("\t", start);
                float dataPoint = atof(line.substr(start, end - start).c_str());
                dataPoints.push_back(dataPoint);
            }
            // with_separator(dataPoints, ", ");
            dataPointsMap[label] = dataPoints;
        }
    }
    myFile.close();
    cout << "dataPointsMap.size(): " << dataPointsMap.size() << endl;
    cout << "dataPointsMap[dataPointsMap.begin()->first].size(): " << dataPointsMap[dataPointsMap.begin()->first].size() << endl;

    int dataPointsArray[dataPointsMap.size()][dataPointsMap[dataPointsMap.begin()->first].size()];
    

    // kMeansClustering(dataPointsMap, 3);

    return 0;
}
