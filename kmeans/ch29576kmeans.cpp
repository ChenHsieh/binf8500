// binf8500 assignment 2 - kmeans
// Student: Chen Hsieh
// ID: ch29576, 811744663

// g++ -std=c++11 -o ch29576kmeans -Wall ch29576kmeans.cpp; time ./ch29576kmeans Archaea.txt 5 5

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void kMeansClustering(vector<vector<float> > data, int k)
{
    for (int i = 0; i < data.size(); i++)
    {
        cout << data[i][0] << " " << data[i][1] << endl;
    }
    int maxReps = 50;
    float minError = 1000000;
    float bestMeanDistance = 0;
    int epochs = 1000;
    int M = data[0].size();
    vector<vector<float> > bestClusterPoints(k);
    for (int rep = 0; rep < maxReps; rep++)
    {
        // cout << "Repetition: " << rep << endl;

        vector<vector<float> > clusterPoints(k);
        vector<int> clusterAssignment(data.size());
        vector<int> previousRoundClusterAssignment(data.size());
        for (int i = 0; i < data.size(); i++)
        {
            previousRoundClusterAssignment.push_back(0);
        }
        int i, j;
        float minIndex;
        double minDistance;
        double distance;
        int count;

        float centroidIndex;
        int iteration;
        int randomPick;
        float meanDistance = 0;

        // pick centroids randomly
        srand(time(NULL) / rand());
        cout << time(NULL) / rand() << " ";
        for (i = 0; i < k; i++)
        {
            randomPick = rand() % data.size();
            clusterPoints[i] = data[randomPick];
        }
        for (iteration = 0; iteration < epochs; iteration++)
        {
            // calculate distance
            for (i = 0; i < data.size(); i++)
            {
                minDistance = 1000000;
                minIndex = -1;
                // for k centroid
                for (j = 0; j < k; j++)
                {
                    distance = 0;
                    // foreach dimension of the data point
                    for (count = 0; count < M; count++)
                    {
                        // sum of square of difference
                        distance += pow(data[i][count] - clusterPoints[j][count], 2);
                    }
                    distance = sqrt(distance);
                    // cout << distance << "\t";
                    // if the distance is smaller than the min distance
                    if (distance < minDistance)
                    {
                        minDistance = distance;
                        minIndex = j;
                    }
                }
                // cout << i << ":" << minDistance << endl;
                // assign the data point to the cluster
                clusterAssignment[i] = minIndex;
                // cout << clusterAssignment[i] << "\t";
                meanDistance += minDistance / data.size();
            }

            // create new cluster points
            for (i = 0; i < k; i++)
            {
                cout << endl
                     << "Cluster " << i << ": ";
                clusterPoints[i].clear();
                centroidIndex = 0;
                bool emptyCluster = true;
                for (count = 0; count < M; count++) // for each dimension
                {
                    for (j = 0; j < data.size(); j++) // for each data point
                    {
                        if (clusterAssignment[j] == i) // if any data point is in the cluster
                        {
                            emptyCluster = false;

                            centroidIndex += (data[j][count] / data.size());
                        }
                    }
                    cout << centroidIndex << "\t";
                    clusterPoints[i].push_back(centroidIndex);
                }
                if (emptyCluster)
                {
                    cout << "Empty cluster" << endl;
                    randomPick = rand() % data.size();
                    clusterPoints[i] = data[randomPick];
                }
                // divide by the number of data points in the cluster

                
                // assign the new centroid
            }
            for (i = 0; i < data.size(); i++)
            {

                cout << clusterAssignment[i] << ";" << previousRoundClusterAssignment[i] << " ";
            }
            // convergence or not
            if (clusterAssignment == previousRoundClusterAssignment)
            {
                // cout << "Convergence after " << iteration << " iterations" << endl;
                // cout << iteration << "\t";
                break;
            }
            else
            {
                // cout << "Not Convergence after " << iteration << " iterations" << endl;
                previousRoundClusterAssignment = clusterAssignment;
            }
            if (iteration == epochs - 1)
            {
                // cout << "epochs: " << iteration << endl;
            }
        }
        // measure the error, WCSS - within cluster sum of squares
        double error = 0;
        for (i = 0; i < data.size(); i++) // for each data point
        {
            for (count = 0; count < M; count++) // for each dimension
            {
                error += pow(data[i][count] - clusterPoints[clusterAssignment[i]][count], 2);
            }
        }
        // cout << "WCSS = " << error << endl;
        if (error < minError)
        {
            minError = error;
            bestClusterPoints = clusterPoints;
            bestMeanDistance = meanDistance;
        }
    }
    cout << "Mean distance " << bestMeanDistance << " minWCSS = " << minError << endl;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << bestClusterPoints[i][j] << " ";
        }
        cout << endl;
    }
}

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
    // float data[][colSize - 1];
    // float **points = new float*[rowSize];

    end = file_contents.find("\n", 0);
    start = end + 1;
    int lineEnd, lineStart;
    vector<vector<float> > dataPoints;

    for (int i = 0; i < rowSize - 1; i++)
    {
        dataPoints.push_back(vector<float>());
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
            dataPoints[i].push_back(data[i][j]);
            lineStart = lineEnd + 1;
        }
        start = end + 1;
    }
    cout << "read data finished..." << endl;

    // calculate the mean and standard deviation
    vector<float> mean;
    vector<float> std;
    for (int i = 0; i < colSize - 1; i++)
    {
        mean.push_back(0);
        std.push_back(0);
    }
    for (int i = 0; i < rowSize - 1; i++)
    {
        for (int j = 0; j < colSize - 1; j++)
        {
            mean[j] += (data[i][j] / (rowSize - 1));
        }
    }
    for (int i = 0; i < rowSize - 1; i++)
    {
        for (int j = 0; j < colSize - 1; j++)
        {
            std[j] += pow(data[i][j] - mean[j], 2);
        }
    }
    for (int i = 0; i < colSize - 1; i++)
    {
        std[i] /= (rowSize - 2); //sample deviation
        std[i] = sqrt(std[i]);
    }

    // standardize the data
    for (int i = 0; i < rowSize - 1; i++)
    {
        for (int j = 0; j < colSize - 1; j++)
        {
            dataPoints[i][j] = (data[i][j] - mean[j]) / std[j];
            // cout << dataPoints[i][j] << " ";
        }
        // cout << endl;
    }
    // for (int j = 0; j < colSize - 1; j++)
    // {

    //     cout << mean[j] << " ";

    // }

    // k-means clustering
    for (int k = minimal_k; k <= maximal_k; k++)
    {
        cout << "k = " << k << "\t";
        kMeansClustering(dataPoints, k);
    }

    return 0;
}