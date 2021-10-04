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
using namespace std;

const int M = 20;

void kMeansClustering(vector<vector<float> > data, int k)
{
    int maxReps = 100;
    float minError = 1000000;
    int epochs = 100;
    vector<vector<float> > bestClusterPoints(k);
    for (int rep = 0; rep < maxReps; rep++)
    {
        cout << "Repetition: " << rep << endl;

        vector<vector<float> > clusterPoints(k);
        vector<int> centroids(k);
        vector<int> clusterAssignment(sizeof(data));
        vector<int> previousRoundClusterAssignment(sizeof(data));
        for (int i = 0; i < sizeof(data); i++)
        {
            previousRoundClusterAssignment.push_back(0);
        }
        int i, j;
        float minIndex;
        double minDistance;
        double distance;
        int count;
        int index;
        float centroidIndex;
        int iteration;
        // pick centroids randomly
        for (i = 0; i < k; i++)
        {
            centroids[i] = rand() % sizeof(data);
            for (count = 0; count < sizeof(data[i]); count++)
            {
                clusterPoints[i].push_back(data[centroids[i]][count]);
            }
        }

        // for (i = 0; i < k; i++)
        // {
        //     for (count = 0; count < sizeof(data[i]); count++)
        //     {
        //         cout << "clusterPoints[" << i << "," << count << ":" << clusterPoints[i][count] << endl;
        //     }
        // }

        centroids.clear();
        for (iteration = 0; iteration < epochs; iteration++)
        {
            // cout << "Iteration: " << iteration << endl;
            // calculate distance
            for (i = 0; i < sizeof(data); i++)
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
                    // if the distance is smaller than the min distance
                    if (distance < minDistance)
                    {
                        minDistance = distance;
                        minIndex = j;
                    }
                }
                // assign the data point to the cluster
                clusterAssignment[i] = minIndex;
            }
            // create new cluster points
            for (i = 0; i < k; i++)
            {
                // clusterPoints[i].clear();

                for (count = 0; count < M; count++) // for each dimension
                {
                    centroidIndex = 0;

                    for (j = 0; j < sizeof(data); j++) // for each data point
                    {

                        if (clusterAssignment[j] == i) // if the data point is in the cluster
                        {
                            centroidIndex += data[j][count];
                        }
                    }
                    // divide by the number of data points in the cluster
                    centroidIndex /= sizeof(data);
                    // cout << "k: " << i << " dimension " << count << "] = " << centroidIndex << endl;
                    // assign the new centroid
                    clusterPoints[i].push_back(centroidIndex);
                }
            }

            // convergence or not
            if (clusterAssignment == previousRoundClusterAssignment)
            {
                cout << "Convergence after " << iteration << " iterations" << endl;
                break;
            }
            else
            {
                // cout << "Not Convergence after " << iteration << " iterations" << endl;
                previousRoundClusterAssignment = clusterAssignment;
            }
            if (iteration == epochs - 1)
            {
                cout << "epochs: " << iteration << endl;
            }
        }
        // measure the error, WCSS - within cluster sum of squares
        double error = 0;
        for (i = 0; i < sizeof(data); i++) // for each data point
        {
            for (count = 0; count < M; count++) // for each dimension
            {
                error += pow(data[i][count] - clusterPoints[clusterAssignment[i]][count], 2);
            }
        }
        cout << "WCSS = " << error << endl;
        if (error < minError)
        {
            minError = error;
            bestClusterPoints = clusterPoints;
        }
    }
    cout << "WCSS = " << minError << endl;
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
            // data[i][j] = (data[i][j] - mean(dataPoints[i])) / standardDeviation(dataPoints[i]);
            mean[j] += data[i][j];
        }
    }
    for (int i = 0; i < colSize - 1; i++)
    {
        mean[i] /= rowSize - 1;
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
        std[i] /= rowSize - 1;
        std[i] = sqrt(std[i]);
    }

    // standardize the data
    for (int i = 0; i < rowSize - 1; i++)
    {
        for (int j = 0; j < colSize - 1; j++)
        {
            dataPoints[i][j] = (data[i][j] - mean[j]) / std[j];
            cout << dataPoints[i][j] << " ";
        }
        cout << endl;
    }

    // k-means clustering
    for (int k = minimal_k; k <= maximal_k; k++)
    {
        cout << "k = " << k << endl;
        kMeansClustering(dataPoints, k);
    }

    return 0;
}