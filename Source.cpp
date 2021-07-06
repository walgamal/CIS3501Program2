//Program Name: Graph to MST
//Programmer Name: Wasim Algamal
//Description: Input an undirected graph with weighted edges, 
//             compute an initial MST for the graph, then as changes occur 
//             in the graph structure, the MST is to be updated. These 
//             changes include the insertion and deletion of vertices, 
//             insertion, and deletion of edges, and changing the weights of 
//             edges.
//Date Created: 03/23/2021

#include "Main.h"
#include "MWayTree.h"
#include "AdjMatrix.h"
#include "BinaryHeap.h"
#include "Prim.h"

//Description: Driver
//Pre-condition: N/A
//Post-condition: Graph will become an MST with directives

int main(){
    //Creating Instance of Graph
    Graph myGraph;

    //Read Vertices From File
    int numVertices, numEdges;
    
    fstream inFile, outFile;
    string fileName, fileReader;

    //ASK USER FOR INPUT/OUTPUT FILE NAMES
    cout << "\nPlease enter input file name: ";		//Initial inserts
    cin >> fileName;
    inFile.open(fileName);
    fileTest(inFile, fileName);

    cout << "\n\nPlease enter output file name: ";	
    cin >> fileName;
    outFile.open(fileName);
    fileTest(outFile, fileName);

    //Insert Initial Read Vertices
    cout << "Number of Vertices in Graph: ";
    inFile >> numVertices;
    cout << numVertices;

    getline(inFile, fileReader);

    for (int i = 0; i < numVertices; i++) {
        getline(inFile, fileReader);
        myGraph.addVertex(fileReader);
    }

    //Insert Initial Read Edges
    cout << "\nNumber of Edges in Graph: ";
    getline(inFile, fileReader);
    numEdges = stoi(fileReader);
    cout << numEdges;

    string v1, v2;
    float weight;

    for (int i = 0; i < numEdges; i++) {
        inFile >> v1 >> v2 >> weight;
        myGraph.addEdge(v1, v2, weight);
    }

    //Create minHeap
    minHeap myMinHeap(numEdges);

    //Create Root Node for Tree
    treeNode init;
    Node* tree = newNode(init);

    //Print Matrix
    myGraph.displayMatrix();
   
    //Print Init Graph MST
    primMST(myGraph, numVertices, myMinHeap, tree);

    int userChoice;
    char sentinel = 'y';
    
    while (sentinel == 'y' || sentinel == 'Y') {
    
        cout << "Would you like to enter your directives via file, keyboard or both?\n" <<
        "1. File\n2. Keyboard\n3. Both\n4. Quit\n";
        cout << "Your Selection: ";
        cin >> userChoice;
        cout << endl;

        int command;
        string temp;
        string temp2;
        float tempw;
        char loop = 'y';

        switch (userChoice) {
            case 1:
                cout << "You have selected file ... processing file\n";
                getline(inFile, fileReader);
                getline(inFile, fileReader);
                while (!inFile.eof()) {
                    inFile >> command;

                    switch (command) {
                    case 1:
                        myGraph.displayMatrix();
                        break;
                    case 2:
                        //print MST (Prim)
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        break;
                    case 3:
                        //Path (Dijkstra)
                        float dist[MAX_VERTS];
                        bool known[MAX_VERTS];
                        dijkstra(myGraph.edgeMatrix, numVertices, 0, dist, known);
                        printDijkstra(numVertices, dist, known, myGraph.vertexID);
                        break;
                    case 4:
                        cout << "\nEnter Vertex ID to Add: ";
                        cin >> temp;
                        myGraph.addVertex(temp);
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        break;
                    case 5:
                        cout << "\nEnter Vertex ID 1 of Edge to Add: ";
                        cin >> temp;
                        cout << "\nEnter Vertex ID 2 of Edge to Add: ";
                        cin >> temp2;
                        cout << "\nEnter Weight of Edge to Add: ";
                        cin >> tempw;
                        myGraph.addEdge(temp, temp2, tempw);
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        break;
                    case 6:
                        cout << "\nEnter Vertex ID to Remove: ";
                        cin >> temp;
                        myGraph.removeVertex(temp);
                        printTree(tree, myGraph);
                        break;
                    case 7:
                        cout << "\nEnter Vertex ID 1 of Edge to Remove: ";
                        cin >> temp;
                        cout << "\nEnter Vertex ID 2 of Edge to Remove: ";
                        cin >> temp2;
                        myGraph.removeEdge(temp, temp2);
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        break;
                    case 8:
                        cout << "\nEnter Vertex ID 1 of Edge to Add Weight: ";
                        cin >> temp;
                        cout << "\nEnter Vertex ID 2 of Edge to Add Weight: ";
                        cin >> temp2;
                        cout << "\nEnter Weight to Add: ";
                        cin >> tempw;
                        myGraph.IncreaseWeight(temp, temp2, tempw);
                        myGraph.displayMatrix();
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        break;
                    case 9:
                        cout << "\nEnter Vertex ID 1 of Edge to Remove Weight: ";
                        cin >> temp;
                        cout << "\nEnter Vertex ID 2 of Edge to Remove Weight: ";
                        cin >> temp2;
                        cout << "\nEnter Weight to Remove: ";
                        cin >> tempw;
                        myGraph.DecreaseWeight(temp, temp2, tempw);
                        myGraph.displayMatrix();
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        break;
                    case 10:
                        "\nGoodbye!\n";
                        exit(0);
                        break;
                    default:
                        "\nYou have made an invalid selection! Try Again!";
                        break;
                    }
                }
                cout << "\nFile Processed! Now, Make a selection from menu!\n";
                break;
                sentinel = 'n';
            case 2:
                int choice;
               
                while (loop == 'y' || loop == 'Y') {
                    cout << "You have selected keyboard ... please make a selection\n";
                    cout << "\n Directives Menu\n";
                    cout << "1. Print Graph\n" <<
                        "2. Print MST\n" <<
                        "3. Path \n" <<
                        "4. Add Vertex\n" <<
                        "5. Add Edge\n" <<
                        "6. Remove Vertex\n" <<
                        "7. Remove Edge\n" <<
                        "8. Increase Weight\n" <<
                        "9. Decrease Weight\n" <<
                        "10. Quit\n\n" <<
                        "Your Selection: ";
                    cin >> choice;
                    cout << endl;

                    switch (choice) {
                    case 1:
                        myGraph.displayMatrix();
                        cont(loop);
                        break;
                    case 2:
                        //print MST (Prim)
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        cont(loop);
                        break;
                    case 3:
                        //Path (Dijkstra)
                        float dist[MAX_VERTS];
                        bool known[MAX_VERTS];
                        dijkstra(myGraph.edgeMatrix, numVertices, 0, dist, known);
                        printDijkstra(numVertices, dist, known, myGraph.vertexID);
                        cont(loop);
                        break;
                    case 4:
                        cout << "\nEnter Vertex ID to Add: ";
                        cin >> temp;
                        myGraph.addVertex(temp);
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        cont(loop);
                        break;
                    case 5:
                        cout << "\nEnter Vertex ID 1 of Edge to Add: ";
                        cin >> temp;
                        cout << "\nEnter Vertex ID 2 of Edge to Add: ";
                        cin >> temp2;
                        cout << "\nEnter Weight of Edge to Add: ";
                        cin >> tempw;
                        myGraph.addEdge(temp, temp2, tempw);
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        cont(loop);
                        break;
                    case 6:
                        cout << "\nEnter Vertex ID to Remove: ";
                        cin >> temp;
                        myGraph.removeVertex(temp);
                        myGraph.displayMatrix();
                        printTree(tree, myGraph);
                        cont(loop);
                        break;
                    case 7:
                        cout << "\nEnter Vertex ID 1 of Edge to Remove: ";
                        cin >> temp;
                        cout << "\nEnter Vertex ID 2 of Edge to Remove: ";
                        cin >> temp2;
                        myGraph.removeEdge(temp, temp2);
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        cont(loop);
                        break;
                    case 8:
                        cout << "\nEnter Vertex ID 1 of Edge to Add Weight: ";
                        cin >> temp;
                        cout << "\nEnter Vertex ID 2 of Edge to Add Weight: ";
                        cin >> temp2;
                        cout << "\nEnter Weight to Add: ";
                        cin >> tempw;
                        myGraph.IncreaseWeight(temp, temp2, tempw);
                        myGraph.displayMatrix();
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        cont(loop);
                        break;
                    case 9:
                        cout << "\nEnter Vertex ID 1 of Edge to Remove Weight: ";
                        cin >> temp;
                        cout << "\nEnter Vertex ID 2 of Edge to Remove Weight: ";
                        cin >> temp2;
                        cout << "\nEnter Weight to Remove: ";
                        cin >> tempw;
                        myGraph.DecreaseWeight(temp, temp2, tempw);
                        myGraph.displayMatrix();
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        cont(loop);
                        break;
                    case 10:
                        "\nGoodbye!\n";
                        exit(0);
                        break;
                    default:
                        "\nYou have made an invalid selection! Try Again!";
                        cont(loop);
                        break;
                    }
                }
                
                sentinel = 'n';
                break;
            case 3:                       
                cout << "You have selected Both .. processing file\n";
                getline(inFile, fileReader);
                getline(inFile, fileReader);
                while (!inFile.eof()) {
                    inFile >> command;

                    switch (command) {
                    case 1:
                        myGraph.displayMatrix();
                        break;
                    case 2:
                        //print MST (Prim)
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        break;
                    case 3:
                        //Path (Dijkstra)
                        float dist[MAX_VERTS];
                        bool known[MAX_VERTS];
                        dijkstra(myGraph.edgeMatrix, numVertices, 0, dist, known);
                        printDijkstra(numVertices, dist, known, myGraph.vertexID);
                        break;
                    case 4:
                        cout << "\nEnter Vertex ID to Add: ";
                        cin >> temp;
                        myGraph.addVertex(temp);
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        break;
                    case 5:
                        cout << "\nEnter Vertex ID 1 of Edge to Add: ";
                        cin >> temp;
                        cout << "\nEnter Vertex ID 2 of Edge to Add: ";
                        cin >> temp2;
                        cout << "\nEnter Weight of Edge to Add: ";
                        cin >> tempw;
                        myGraph.addEdge(temp, temp2, tempw);
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        break;
                    case 6:
                        cout << "\nEnter Vertex ID to Remove: ";
                        cin >> temp;
                        myGraph.removeVertex(temp);
                        printTree(tree, myGraph);
                        break;
                    case 7:
                        cout << "\nEnter Vertex ID 1 of Edge to Remove: ";
                        cin >> temp;
                        cout << "\nEnter Vertex ID 2 of Edge to Remove: ";
                        cin >> temp2;
                        myGraph.removeEdge(temp, temp2);
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        break;
                    case 8:
                        cout << "\nEnter Vertex ID 1 of Edge to Add Weight: ";
                        cin >> temp;
                        cout << "\nEnter Vertex ID 2 of Edge to Add Weight: ";
                        cin >> temp2;
                        cout << "\nEnter Weight to Add: ";
                        cin >> tempw;
                        myGraph.IncreaseWeight(temp, temp2, tempw);
                        myGraph.displayMatrix();
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        break;
                    case 9:
                        cout << "\nEnter Vertex ID 1 of Edge to Remove Weight: ";
                        cin >> temp;
                        cout << "\nEnter Vertex ID 2 of Edge to Remove Weight: ";
                        cin >> temp2;
                        cout << "\nEnter Weight to Remove: ";
                        cin >> tempw;
                        myGraph.DecreaseWeight(temp, temp2, tempw);
                        myGraph.displayMatrix();
                        cout << endl << "\nPre-Order Traversal: ";
                        printTree(tree, myGraph);
                        break;
                    case 10:
                        "\nGoodbye!\n";
                        exit(0);
                        break;
                    default:
                        "\nYou have made an invalid selection! Try Again!";
                        break;
                    }
                }
                cout << "File Processed! Now, Make a selection from menu!\n";

                while (loop == 'y' || loop == 'Y') {
                    cout << "\n Directives Menu\n";
                    cout << "1. Print Graph\n" <<
                        "2. Print MST\n" <<
                        "3. Path \n" <<
                        "4. Add Vertex\n" <<
                        "5. Add Edge\n" <<
                        "6. Remove Vertex\n" <<
                        "7. Remove Edge\n" <<
                        "8. Increase Weight\n" <<
                        "9. Decrease Weight\n" <<
                        "10. Quit\n\n" <<
                        "Your Selection: ";
                    cin >> choice;
                    cout << endl;

                    switch (choice) {
                    case 1:
                        myGraph.displayMatrix();
                        cont(loop);
                        break;
                    case 2:
                        //print MST (Prim)
                        primMST(myGraph, numVertices, myMinHeap, tree);
                        cont(loop);
                        break;
                    case 3:
                        //Path (Dijkstra)
                        float dist[MAX_VERTS];
                        bool known[MAX_VERTS];
                        dijkstra(myGraph.edgeMatrix, numVertices, 0, dist, known);
                        printDijkstra(numVertices, dist, known, myGraph.vertexID);
                        cont(loop);
                        break;
                    case 4:
                        cout << "\nEnter Vertex ID to Add: ";
                        cin >> temp;
                        myGraph.addVertex(temp);
                        //PrintMST
                        cont(loop);
                        break;
                    case 5:
                        cout << "\nEnter Vertex ID 1 of Edge to Add: ";
                        cin >> temp;
                        cout << "\nEnter Vertex ID 2 of Edge to Add: ";
                        cin >> temp2;
                        cout << "\nEnter Weight of Edge to Add: ";
                        cin >> tempw;
                        myGraph.addEdge(temp, temp2, tempw);
                        //PrintMST
                        cont(loop);
                        break;
                    case 6:
                        cout << "\nEnter Vertex ID to Remove: ";
                        cin >> temp;
                        myGraph.removeVertex(temp);
                        //PrintMST
                        cont(loop);
                        break;
                    case 7:
                        cout << "\nEnter Vertex ID 1 of Edge to Remove: ";
                        cin >> temp;
                        cout << "\nEnter Vertex ID 2 of Edge to Remove: ";
                        cin >> temp2;
                        myGraph.removeEdge(temp, temp2);
                        //PrintMST
                        cont(loop);
                        break;
                    case 8:
                        cout << "\nEnter Vertex ID 1 of Edge to Add Weight: ";
                        cin >> temp;
                        cout << "\nEnter Vertex ID 2 of Edge to Add Weight: ";
                        cin >> temp2;
                        cout << "\nEnter Weight to Add: ";
                        cin >> tempw;
                        myGraph.IncreaseWeight(temp, temp2, tempw);
                        //Print Graph
                        //Print MST
                        cont(loop);
                        break;
                    case 9:
                        cout << "\nEnter Vertex ID 1 of Edge to Remove Weight: ";
                        cin >> temp;
                        cout << "\nEnter Vertex ID 2 of Edge to Remove Weight: ";
                        cin >> temp2;
                        cout << "\nEnter Weight to Remove: ";
                        cin >> tempw;
                        myGraph.DecreaseWeight(temp, temp2, tempw);
                        //Print Graph
                        //Print MST
                        cont(loop);
                        break;
                    case 10:
                        "\nGoodbye!\n";
                        exit(0);
                        break;
                    default:
                        "\nYou have made an invalid selection! Try Again!";
                        cont(loop);
                        break;
                    }
                }
                break;
                sentinel = 'n';
            case 4:
                "\nGoodbye!\n";
                exit(0);
            default:
                cout << "\nYou have not made a valid selection! Try again. \n\n";
                break;
        }
    }    
    return 0;
}

// {X} READ FILEa
        // {X} GET NUM VERTICES
        // {X} CREATE GRAPH
        // {X} ADD EACH VERTEX TO GRAPH (USE AddVertex func)
        // {X} GET NUM EDGES
        // {X} ADD EACH EDGE TO GRAPH (USE AddEdge func)
        //********INIT GRAPH COMPLETED********
                   // {X} CREATE MINHEAP
                   // {/} USE MINHEAP TO CREATE TREE (PRIMS ALGO)
                   // { } HANDLE A SPLIT GRAPH
   // {X} PAUSE READING FILE TO ASK USER DIRECTIVE INPUT METHOD
   // {X} SWITCH STATEMENT 
       // {/} READ USER'S DATA BASED ON INPUT METHOD -- UPDATE/RECONSTRUCT MST AFTER DIRECTIVES
               // {X} TEST PrintGraph func
               // {X} TEST PrintMST func
               // {/} TEST Path(string vert1, string vert2) func -- (DIJKSTRAS ALGO)
               // {X} TEST AddVertex(string v) func
               // {X} TEST AddEdge(string vert1, string vert2) func
               // {X} TEST IncreaseWeight(float w) func
               // {X} TEST DecreaseWeight(float w) func
               // {X} TEST RemoveVertex(string v) func
               // {X} TEST RemoveEdge(string vert1, string vert2) func
               // {X} TEST Quit func


