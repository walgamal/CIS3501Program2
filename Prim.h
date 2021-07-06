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

//Prim's Algorithm

//Description: Finds minimum key index out of set
//Pre-condition: Number of vertices, key array, boolean set, graph
//Post-condition: minimum key index of the set
int minKey(int numV, float w[], bool mstSet[], Graph myGraph) {
	float min = INT_MAX;
	int min_index;

	for (int v = 0; v < numV; v++) {
		if (mstSet[v] == false && w[v] < min) {
			min = w[v];
			min_index = v;
		}
	}

	return min_index;
}

//Description: Prints the MST edges and weights and inserts to tree
//Pre-condition: Number of vertices, parent, graph, tree
//Post-condition: Prints tree
void printMST(int parent[], Graph myGraph, int numV, Node* tree) {
	treeNode data;
	cout << "\nEdge \t\tWeight\n";

	for (int i = 1; i < numV; i++) {
		cout << myGraph.vertexID[parent[i]] << " - " << myGraph.vertexID[i] << " \t\t" << myGraph.edgeMatrix[i][parent[i]].weight << " \n";
		data.parent = parent[i];
		data.vert = i;
		tree = insertNode(tree, myGraph, data);
	}

	cout << endl << "Pre-Order Traversal: ";
	printTree(tree, myGraph);
}

//Description: Follows Prim's Algo to find MST
//Pre-condition: Number of vertices, min heap, tree root, graph
//Post-condition: minimum key index of the set
void primMST(Graph myGraph, int numV, minHeap myMinHeap, Node* tree) {
	int parent[MAX_VERTS];
	float w[MAX_VERTS];
	bool mstSet[MAX_VERTS];
	
	for (int i = 0; i < numV; i++) {
		w[i] = INT_MAX, mstSet[i] = false;
	}

	w[0] = 0;
	parent[0] = -1;

	for (int count = 0; count < numV - 1; count++) {
		int u = minKey(numV, w, mstSet, myGraph);
		mstSet[u] = true;

		for (int v = 0; v < numV; v++) {
			if (myGraph.edgeMatrix[u][v].weight > 0 && mstSet[v] == false && myGraph.edgeMatrix[u][v].weight < w[v]) {
				parent[v] = u;
				myGraph.edgeMatrix[u][v].v2 = myGraph.edgeMatrix[v][u].v2 = u;
				myGraph.edgeMatrix[u][v].v1 = myGraph.edgeMatrix[v][u].v1 = v;
				w[v] = myGraph.edgeMatrix[u][v].weight;
			}
		}
	}

	printMST(parent, myGraph, numV, tree);
	cout << endl;
}