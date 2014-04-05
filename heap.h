#include "node.h"
#define NONE 0

typedef struct heap {
    Node *nodes;
    int numNodes;
}*Heap;

Heap newHeap(int numNodes, Node nodes[]);

// Sorts the heap and returns nodes as a pointer
// to the start of an array of nodes the length
// of numNodes when you called newHeap
Node *heapSort(Heap heap);
void makeMaxHeap(Heap heap);
Node *getNodes(Heap heap);
int findLargestChild(Heap heap, int partent);
