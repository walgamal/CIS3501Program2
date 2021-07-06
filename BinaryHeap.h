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

// A utility function to swap two elements
void swap(heapVert* x, heapVert* y) {
	heapVert temp = *x;
	*x = *y;
	*y = temp;
}

struct minHeap {
	heapVert* heaparray; // pointer to array of elements in heap
	int capacity;   // maximum possible size of min heap
	int heap_size;  // Current number of elements in min heap

	//<----------------------------------------------------------------------------------------------------------------------------------------------------->

	minHeap(int cap) {
		heap_size = 0;
		capacity = cap;
		heaparray = new heapVert[cap];
	}

	//<----------------------------------------------------------------------------------------------------------------------------------------------------->

	int left(int i) { return 2 * i + 1; }
	int right(int i) { return 2 * i + 2; }
	int parent(int i) { return (i - 1) / 2; }

	//<----------------------------------------------------------------------------------------------------------------------------------------------------->

	// Inserts a new key 'k' 
	void insertKey(heapVert k) {
		if (heap_size == capacity)		{
			cout << "\nOverflow: Could not insertKey\n";
			return;
		}
		heap_size++;
		int i = heap_size - 1;
		heaparray[i] = k;

		// Fix the min heap property if it is violated
		while (i != 0 && heaparray[parent(i)].key > heaparray[i].key)
		{
			swap(&heaparray[i], &heaparray[parent(i)]);
			i = parent(i);
		}
	}

	//<----------------------------------------------------------------------------------------------------------------------------------------------------->

	// Method to remove minimum element (or root) from min heap 
	heapVert extractMin() {
		if (heap_size <= 0) {
			return heaparray[-1];
		}

		if (heap_size == 1)
		{
			heap_size--;
			return heaparray[0];
		}

		// Store the minimum value, and remove it from heap 
		heapVert root = heaparray[0];
		heaparray[0] = heaparray[heap_size - 1];
		heap_size--;
		MinHeapify(0);

		return root;
	}

	//<----------------------------------------------------------------------------------------------------------------------------------------------------->

	// A recursive method to heapify a subtree with the root at given index 
	// This method assumes that the subtrees are already heapified 
	void MinHeapify(int i) {
		int l = left(i);
		int r = right(i);
		int smallest = i;

		if (l < heap_size && heaparray[l].key < heaparray[i].key)
			smallest = l;

		if (r < heap_size && heaparray[r].key < heaparray[smallest].key)
			smallest = r;

		if (smallest != i)
		{
			swap(&heaparray[i], &heaparray[smallest]);
			MinHeapify(smallest);
		}
	}

	//<----------------------------------------------------------------------------------------------------------------------------------------------------->

	void printArr(int x) {
		for (int i = 0; i < x; i++) {
			cout << heaparray[i].vert << " ";
		}
		cout << endl;
	}

};