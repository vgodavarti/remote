#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Function to perform Floyd-Warshall algorithm
void floyd(int inputGraphArray[100][100], int n, int num, ofstream& output) {
    int distances[100][100]; // 
    memcpy(distances, inputGraphArray, sizeof(distances)); 

    int predecessors[100][100]; // Array to store predecessors for shortest paths
    memset(predecessors, 0, sizeof(predecessors)); // Initialize predecessors array with zeros

    // Floyd-Warshall algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (distances[i][k] + distances[k][j] < distances[i][j]) {
                    distances[i][j] = distances[i][k] + distances[k][j]; // Update distance
                    predecessors[i][j] = k; // Update predecessor
                }
            }
        }
    }

    
    output << "Problem " << num << ": n = " << n << endl; // Output problem number and size
    output << "Pmatrix:" << endl; 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            output << predecessors[i][j] << " "; 
        }
        output << endl;
    }
    // Output shortest paths and lengths
    for (int i = 0; i < n; i++) {
        output << "V" << (i + 1) << "-Vj: shortest path and length" << endl; 
        for (int j = 0; j < n; j++) {
            output << "V" << (i + 1) << " "; 
            for (int k = 0; k < n; k++) {
                if (k != i && k != j && distances[i][j] == distances[i][k] + distances[k][j]) {
                    output << "V" << (k + 1) << " "; 
                }
            }
            output << "V" << (j + 1) << ":" << distances[i][j] << endl; 
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "<graph.txt>" << endl; 
        return 1;
    }

    ifstream inputFile(argv[1]); // Open input file
    ofstream outputFile("output.txt"); // Create output file

    int num = 1; // Initialize problem number
    string currLine;
    while (getline(inputFile, currLine)) { 
        if (currLine.find("n = ") != string::npos) { 
            int n = stoi(currLine.substr(currLine.find("n = ") + 4)); 
            int inputGraphArray[100][100] = {0}; // Initialize array to store input graph

            // Read graph from input file
            for (int i = 0; i < n; i++) {
                int column = 0;
                getline(inputFile, currLine); // Read a line from input file
                stringstream ss(currLine); 
                string value;
                while (ss >> value) { 
                    if (!value.empty() && value[0] != ' ') {
                        inputGraphArray[i][column] = stoi(value); 
                        column++;
                    }
                }
            }
            
            cout << "PRINTED MATRIX\n";
            for (int xx = 0; xx < n; xx++) {
                cout << "\n";
                for (int xxx = 0; xxx < n; xxx++) {
                    cout << inputGraphArray[xx][xxx] << " ";
                }
            }

            // Perform Floyd-Warshall algorithm 
            floyd(inputGraphArray, n, num, outputFile);
            num++; // Increment problem number
        }
    }
                      
                     //Close output file and input file
    inputFile.close(); 
    outputFile.close(); 

    return 0; 
}
