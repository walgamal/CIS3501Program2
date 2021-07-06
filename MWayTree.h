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
#include "AdjMatrix.h"
#include "BinaryHeap.h"

struct Node {
    treeNode data;
    Node *sibling, *child;
};

//Description: Creates a new node
//Pre-condition: Node's data
//Post-condition: New node is returned
Node* newNode(treeNode data) {
    Node* newNode = new Node;
    newNode->sibling = newNode->child = NULL;
    newNode->data = data;
    return newNode;
}

//Description: Inserts a new node
//Pre-condition: Root node, graph, and node's data
//Post-condition: New node is inserted to tree and root is returned
Node* insertNode(Node* root, Graph myGraph, treeNode data) {
    if (root == NULL) {
        root->data = data;
    }
    else if (root->data.parent == data.parent) {
        Node* temp = root;
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }

        Node* newSib = newNode(data);
        temp->sibling = newSib;

    }
    else if (root->sibling != NULL) {
        Node* temp = root;

        while (temp->sibling != NULL) {           
            temp = temp->sibling;
            if (temp->data.vert == root->data.parent) {
                insertNode(temp->sibling, myGraph, data);
            }
        }
    }
    else {
        Node* temp = root;

        while (temp->child != NULL) {
            temp = temp->child;
        }

        Node* newChild = newNode(data);

        temp->child = newChild;
    }

    return root;
}

//Description: Prints tree
//Pre-condition: Tree root and graph
//Post-condition: Tree contents in pre-order
void printTree(Node* root, Graph myGraph){
    if (root == NULL) {
        return;
    }

    cout << myGraph.findVertID(root->data.vert, myGraph) << " ";

    printTree(root->child, myGraph);
  
    printTree(root->sibling, myGraph);
}
