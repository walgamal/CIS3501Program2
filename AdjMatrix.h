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
#include "Main.h"
#include "MWayTree.h"
#include "BinaryHeap.h"


class Graph {
private:
    // number of vertices
    int n;
public:
    // constructor
    Graph() {}

    // adjacency matrix
    vector<vector<edge>> edgeMatrix;

    //list of vertices
    vector<string> vertexID;

    //<----------------------------------------------------------------------------------------------------------------------------------------------------->
    //Description: Utility function finds ID of vertex
    //Pre-condition: graph and vertex index
    //Post-condition: ID of Vertex
    string findVertID(int index, Graph myGraph) {
        if (index < myGraph.vertexID.size()) {
            return myGraph.vertexID[index];
        }
    }
    
    //Description: Directive to add an edge
    //Pre-condition: 2 vetices of the edge and weight
    //Post-condition: Edge is added to graph
    void addEdge(string ID1, string ID2, float w){
        int x = findVertIndex(ID1, vertexID);
        int y = findVertIndex(ID2, vertexID);

        // checks if the vertex exists in the graph
        if ((x >= n) || (y > n)) {
            cout << "Vertex does not exists!\n";
        }

        //check if edge already exists in graph
        if (edgeMatrix[x][y].weight > 0) {
            cout << "Edge already exists!";
            return;
        }

        // checks if the vertex is connecting to itself
        if (x == y) {
            cout << "Same Vertex!\n";
        }
        else {
            edgeMatrix[x][y].v1 = x;
            edgeMatrix[x][y].v2 = y;

            edgeMatrix[x][y].weight = edgeMatrix[y][x].weight = w;
        }
    }

    //Description: Directive to remove an edge
    //Pre-condition: 2 vetices of the edge
    //Post-condition: Edge is removed to graph
    void removeEdge(string ID1, string ID2) {
        int x = findVertIndex(ID1, vertexID);
        int y = findVertIndex(ID2, vertexID);
        
        if ((x >= n) || (y > n)) {
            cout << "Vertex does not exists!\n";
        }

        // checks if the vertex is connecting to itself
        if (x == y) {
            cout << "Same Vertex!\n";
        }

        if (edgeMatrix[x][y].weight == 0) {
            cout << "Edge does not exist!\n";
        }
        else {
            // delete existing edge
            edgeMatrix[y][x].weight = edgeMatrix[x][y].weight = 0;
        }
    }

    //Description: Directive to add a vertex
    //Pre-condition: ID of vertex
    //Post-condition: Vertex is added to graph
    void addVertex(string ID) {
        //make sure vertex is not a duplicate
        bool isDupe = NULL;
       
        for (int i = 0; i < vertexID.size(); i++) {
            if (ID == vertexID[i]) {
                isDupe = true;
                break;
            }
            else {
                isDupe = false;
            }
        }

        //add new vertex to vector if not duplicate
        if (isDupe == true) {
            cout << "Vertex already exists!\n";
        }
        else {
            // increasing the number of vertices
            n++;

            // initializing the new elements to 0
            edgeMatrix.resize(n);
            for (int i = 0; i < n; i++) {
                edgeMatrix[i].resize(n);
            }
            
            //add to vertex vector
            vertexID.push_back(ID);
        }
    }

    //Description: Directive to remove a vertex
    //Pre-condition: ID of vertex
    //Post-condition: Vertex is removed to graph
    void removeVertex(string ID) {
        int x = findVertIndex(ID, vertexID);

        // checking if the vertex is present
        if (x > n) {
            cout << "Vertex not present!\n";
            return;
        }
        else {
            //Erase ID from vertice vector
            vertexID.erase(vertexID.begin() + x);

            // removing the vertex
            int i;
            while (x < n-1) {
                // shifting the rows to left side
                for (i = 0; i < n; ++i) {
                    edgeMatrix[i][x] = edgeMatrix[i][x + 1];
                }

                // shifting the columns upwards
                for (i = 0; i < n; ++i) {
                    edgeMatrix[x][i] = edgeMatrix[x + 1][i];
                }
                x++;
            }

            // decreasing the number of vertices
            n--;
        }
    }

    //Description: Directive to increase the weight of an edge
    //Pre-condition: 2 vetices of the edge and weight to add
    //Post-condition: Edge has new weight
    void IncreaseWeight(string ID1, string ID2, float w) {
        int x = findVertIndex(ID1, vertexID);
        int y = findVertIndex(ID2, vertexID);

       edgeMatrix[x][y].weight += w;
       edgeMatrix[y][x].weight += w;
    }

    //Description: Directive to decrease the weight of an edge
    //Pre-condition: 2 vetices of the edge and weight to decrease
    //Post-condition: Edge has new weight
    void DecreaseWeight(string ID1, string ID2, float w) {
        int x = findVertIndex(ID1, vertexID);
        int y = findVertIndex(ID2, vertexID);

        while (edgeMatrix[x][y].weight - w < 0) {
            cout << "Weight is now too low! Enter another number: ";
            cin >> w;
        }

        edgeMatrix[x][y].weight -= w;
        edgeMatrix[y][x].weight -= w;
    }

    //Description: Directive to find the path between 2 vertices
    //Pre-condition: 2 vetices
    //Post-condition: Path is given
    void path(string ID1, string ID2) {

    }

    //Description: Directive to print graph
    //Pre-condition: N/A
    //Post-condition: Graph is printed
    void displayMatrix() {
        cout << "\nAdjacency Matrix:";

        // displaying the 2D array
        for (int i = 0; i < n; ++i) {
            cout << endl;
            for (int j = 0; j < n; ++j) {
                cout << "\t" << edgeMatrix[i][j].weight;
            }
        }
        cout << endl << endl;
    }
};