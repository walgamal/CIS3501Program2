//Program Name: Graph to MST
//Programmer Name: Wasim Algamal
//Description: Input an undirected graph with weighted edges, 
//             compute an initial MST for the graph, then as changes occur 
//             in the graph structure, the MST is to be updated. These 
//             changes include the insertion and deletion of vertices, 
//             insertion, and deletion of edges, and changing the weights of 
//             edges.
//Date Created: 03/23/2021

#pragma once
using namespace std;

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

const int MAX_VERTS = 100;

//Description: Warns if file is empty
//Pre-condition: file being used
//Post-condition: boolean to indicate if empty
bool isEmpty(fstream& fileInUse) {
    return fileInUse.peek() == fstream::traits_type::eof();
}

//Description: Tests file validity
//Pre-condition: file being used, fileName
//Post-condition: Returns message if file is invalid and lets you re-input file name
void fileTest(fstream& fileInUse, string& fileName) {			//ENSURE OF VALID INPUT, ELSE USE WHILE LOOP!!  
    while (fileInUse.fail()) {
        cout << "ERROR: CANNOT FIND FILE! TRY ENTERING AGAIN: ";
        cin >> fileName;
        fileInUse.open(fileName);
        fileTest(fileInUse, fileName);
    }

    if (isEmpty(fileInUse)) {
        cout << "WARNING: FILE IS EMPTY!\n";
        fileInUse.seekg(0, ios::beg);
    }
}

//Description: Asks user if they want to continue
//Pre-condition: sentinel
//Post-condition: returns new sentinel [y/n]
void cont(char& loop) {
    cout << "\nWould you like to enter another directive? [y/n]";
    cin >> loop;
}

//<----------------------------------------------------------------------------------------------------------------------------------------------------->

//Description: Finds vertex index 
//Pre-condition: vertex ID and vertex vector
//Post-condition: returns vertex index
int findVertIndex(string ID, vector<string> VIDs) {
    for (int i = 0; i < VIDs.size(); i++) {
        if (ID == VIDs[i]) {
            return i;
        }
    }
}

//<----------------------------------------------------------------------------------------------------------------------------------------------------->

//Description: Structs to help create needed objects
struct edge{
    int v1 = 0;
    int v2 = 0;
    float weight = 0;
};

struct treeNode {
    int parent = -1;
    int vert = 0;
};

struct heapVert {
    int vert;
    float key = 0;
    int parent;
};

//<----------------------------------------------------------------------------------------------------------------------------------------------------->
//Dijkstra's Algorithm

//Description: Prints Dijkstra table
//Pre-condition: Number of vertices, distance array, boolean set, Vertex vector
//Post-condition: Dijkstras Table
void printDijkstra(int numV, float distance[], bool set[], vector<string> vertexID){
    cout << "\nVertex \t\tKnown\t\tDistance from Source\n";

    for (int i = 0; i < numV; i++) {
        cout << vertexID[i] << "\t\t";
        if (set[i]) {
            cout << "True ";
        }
        else {
            cout << "False ";
        }
            cout  << "\t\t" << distance[i] << endl;
    }
}

//Description: Finds Distance from root using Dijkstras Algorithm
//Pre-condition: Number of vertices, distance array, boolean set
//Post-condition: minimum distance from vert to root
int minDistance(int numVertices, float distance[], bool sptSet[]) {
    float min = INT_MAX;
    int minIndex;

    for (int i = 0; i < numVertices; i++) {
        if (sptSet[i] == false && distance[i] <= min) {
            min = distance[i];
            minIndex = i;
        }
    }

    return minIndex;
}

//Description: Follows Dijkstras Algorithm to create table
//Pre-condition: Graph, Number of vertices, source index, distance array, boolean set
//Post-condition: Sets data up for printing Dijkstra Table
void dijkstra(vector<vector<edge>> graph, int numVertices, int source, float distance[], bool known[]) {
    for (int i = 0; i < MAX_VERTS; i++) {
        distance[i] = INT_MAX;
        known[i] = false;
    }


    distance[source] = 0;

    for (int i = 0; i < numVertices - 1; i++) {
        int x = minDistance(numVertices, distance, known);

        known[x] = true;

        for (int j = 0; j < numVertices; j++) {
            if (!known[j] && graph[x][j].weight && distance[x] != INT_MAX && distance[x] + graph[x][j].weight < distance[j]) {
                distance[j] = distance[x] + graph[x][j].weight;
            }
        }
    }
}

//<----------------------------------------------------------------------------------------------------------------------------------------------------->