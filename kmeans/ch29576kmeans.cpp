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


using namespace std;

double getDistance(vector<double> a, vector<double> b)
{
    double sum = 0;
    for (int i = 0; i < a.size(); i++)
    {
        sum += pow(a[i] - b[i], 2);
    }
    return sqrt(sum);
}

void kMeansClustering(vector<vector<double> > data, int k, string fileName, map<int, string> label_map)
{
    ofstream fout;
    fout.open(fileName + ".chen_kmeans_output_" + std::to_string(k) + ".txt");
    fout << "Chen's Detailed output for k=" << k << ":" << endl;
    fout << "List of data points in each cluster preceded by distance to centroid:" << endl;
    int maxReps = 400;
    bool emptyCluster = true;
    double minError = 1000000;
    double bestMeanDistance = 0;
    int epochs = 100000;
    int M = data[0].size();
    int clusterSize = 0;
    vector<vector<double> > bestClusterPoints(k);
    vector<int> bestClusterAssignment(data.size());
    double distance2centroid = 0;

    for (int rep = 0; rep < maxReps; rep++)
    {
        // cout << "Repetition: " << rep << endl;

        vector<vector<double> > clusterPoints(k);
        vector<int> clusterAssignment(data.size());
        vector<int> previousRoundClusterAssignment(data.size());
        for (int i = 0; i < data.size(); i++)
        {
            previousRoundClusterAssignment.push_back(0);
        }
        int i, j;
        double minIndex;
        double minDistance;
        double distance;
        int count;

        double centroidIndex;
        int iteration;
        int randomPick;
        double meanDistance = 0;

        // pick centroids randomly
        for (i = 0; i < k; i++)
        {
            randomPick = rand() % data.size();
            clusterPoints[i] = data[randomPick];
        }

        for (iteration = 0; iteration < epochs; iteration++)
        {
            // calculate distance
            meanDistance = 0;
            for (i = 0; i < data.size(); i++)
            {
                minDistance = 1000000;
                minIndex = -1;
                // for k centroid
                for (j = 0; j < k; j++)
                {
                    distance = getDistance(data[i], clusterPoints[j]);
                    // cout << distance << "\t";
                    // if the distance is smaller than the min distance
                    if (distance < minDistance)
                    {
                        minDistance = distance;
                        minIndex = j;
                    }
                }

                // assign the data point to the cluster
                clusterAssignment[i] = minIndex;
                // cout << clusterAssignment[i] << "\t";
                meanDistance += minDistance / data.size();
            }

            for (i = 0; i < k; i++)
            {

                clusterPoints[i].clear();
                for (count = 0; count < M; count++) // for each dimension
                {
                    centroidIndex = 0;
                    clusterSize = 0;
                    for (j = 0; j < data.size(); j++) // for each data point
                    {
                        if (clusterAssignment[j] == i) // if any data point is in the cluster
                        {
                            clusterSize++;
                            emptyCluster = false;
                            centroidIndex += data[j][count];
                        }
                    }
                    centroidIndex /= clusterSize;
                    // cout << centroidIndex << "\t";
                    clusterPoints[i].push_back(centroidIndex);
                }
                if (emptyCluster)
                {
                    // cout << "Empty cluster" << endl;
                    randomPick = rand() % data.size();
                    clusterPoints[i] = data[randomPick];
                }
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
                cout << "epochs: " << iteration << endl;
            }
        }
        // measure the error, WCSS - within cluster sum of squares
        double error = 0;
        for (i = 0; i < data.size(); i++) // for each data point
        {
            error += pow(getDistance(data[i], clusterPoints[clusterAssignment[i]]), 2);
        }
        // cout << "WCSS = " << error << endl;
        if (error < minError)
        {
            minError = error;
            bestClusterPoints = clusterPoints;
            bestClusterAssignment = clusterAssignment;
            bestMeanDistance = 0;
            for (i = 0; i < data.size(); i++)
            {
                bestMeanDistance += (getDistance(data[i], bestClusterPoints[clusterAssignment[i]]) / data.size());
            }
        }
    }

    // print output
    cout << fixed << bestMeanDistance << "\t" << fixed << minError << "\t" << fixed << (minError + 2 * k * M) << "\t" << fixed << (minError + log(data.size()) * k * M) << endl;

    // write file

    // clustering result
    for (int k = 0; k < bestClusterPoints.size(); k++)
    {
        fout << "Cluster " << k << ": " << endl
             << endl;
        for (int i = 0; i < data.size(); i++)
        {
            if (bestClusterAssignment[i] == k)
            {
                distance2centroid = getDistance(data[i], bestClusterPoints[k]);
                fout << i << "\t";
                fout << distance2centroid << "\t";
                fout << label_map[i] << endl;
            }
        }

        fout << endl;
    }

    // centroid distance
    fout << "Mutual pairwise distances among centroids:" << endl
         << endl;
    for (int i = 0; i < bestClusterPoints.size(); i++)
    {
        for (int j = i + 1; j < bestClusterPoints.size(); j++)
        {
            fout << i << "\t" << j << "\t" << getDistance(bestClusterPoints[i], bestClusterPoints[j]) << endl;
        }
    }
    // cluster point coordinates
    fout << "Cluster point coordinates:" << endl;
    for (int i = 0; i < k; i++)
    {
        fout << "Cluster " << i << ":\t";
        for (int j = 0; j < M; j++)
        {
            fout << bestClusterPoints[i][j] << "\t";
        }
        fout << endl;
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
    cout << "input dataFrame size detecting (header included)" << endl;
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
    double data[rowSize - 1][colSize - 1];
    end = file_contents.find("\n", 0);
    start = end + 1;
    int lineEnd, lineStart;
    vector<vector<double> > dataPoints;
    map<int, string> label_map;
    for (int i = 0; i < rowSize - 1; i++)
    {
        dataPoints.push_back(vector<double>());
        end = file_contents.find("\n", start);
        std::string currentLine = file_contents.substr(start, end - start);

        lineEnd = currentLine.find("\t", 0);
        lineStart = 0;
        label_map[i] = currentLine.substr(lineStart, lineEnd - lineStart);
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
    cout << "data reading finished..." << endl;

    // calculate the mean and standard deviation
    vector<double> mean;
    vector<double> std;
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

    cout << "K-means starting" << endl
         << endl;
    cout << "K"
         << "\tMean_distance"
         << "\tminWCSS"
         << "\tAIC"
         << "\tBIC" << endl;
    for (int k = minimal_k; k <= maximal_k; k++)
    {
        cout << fixed << k << "\t";
        kMeansClustering(dataPoints, k, argv[1], label_map);
    }

    return 0;
}