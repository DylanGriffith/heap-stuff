#include<stdlib.h>
#include<stdio.h>
#include "heap.h"

#define TRUE 1
#define FALSE 0

void maxHeapify(Heap heap, int node);
int leftChild(int node);
int rightChild(int node);
int parent(int node);
Node nodeAtIndex(Heap heap, int i);
void swap(Heap heap, int a, int b);
void setNodeAt(Heap heap, int i, Node node);
int largestChild(Heap heap, int i);
int compareNodesAt(Heap heap, int i, int j);

void maxHeapify(Heap heap, int node) {
    int biggestBiggerChild = findLargestChild(heap, node);
    if(biggestBiggerChild != NONE) {
        swap(heap, node, biggestBiggerChild);
        maxHeapify(heap, biggestBiggerChild);
    }
}

int findLargestChild(Heap heap, int i) {
    int left = leftChild(i);
    int right = rightChild(i);
    int biggestBiggerChild = NONE;
    if(left <= heap->numNodes) {
        if(compareNodesAt(heap, i, left) < 0) {
            biggestBiggerChild = left;
        }
    }
    if(right <= heap->numNodes) {
        if(compareNodesAt(heap, i, right) < 0) {
            if(biggestBiggerChild == NONE) {
                biggestBiggerChild = right;
            }else {
                if(compareNodesAt(heap, left, right) < 0) {
                    biggestBiggerChild = right;
                }
            }
        }
    }
    return biggestBiggerChild;
}

void swap(Heap heap, int a, int b) {
    Node nodeA = nodeAtIndex(heap, a);
    Node nodeB = nodeAtIndex(heap, b);
    setNodeAt(heap, a, nodeB);
    setNodeAt(heap, b, nodeA);
}

Node nodeAtIndex(Heap heap, int i) {
    return *(heap->nodes + i);
}

void setNodeAt(Heap heap, int i, Node node) {
    *(heap->nodes + i) = node;
}

int compareNodesAt(Heap heap, int i, int j) {
    return nodeComp(nodeAtIndex(heap, i), nodeAtIndex(heap, j));
}

int parent(int node) {
    return node/2;
}

int leftChild(int node) {
    return node << 1;
}

int rightChild(int node) {
    return (node << 1) + 1;
}

void makeMaxHeap(Heap heap) {
    for(int i = heap->numNodes/2; i>0; i--) {
        maxHeapify(heap, i);
    }
}

Node *heapSort(Heap heap) {
    makeMaxHeap(heap);
    while(heap->numNodes > 0) {
        swap(heap, 1, heap->numNodes);
        heap->numNodes--;
        maxHeapify(heap, 1);
    }
    return (heap->nodes + 1);
}

void deleteFromHeap(Heap heap, int i) {
    swap(heap, i, heap->numNodes);
    heap->numNodes--;
    maxHeapify(heap, i);
}

void insertIntoHeap(Heap heap, Node node) {
    heap->numNodes++;
    int i = heap->numNodes;
    setNodeAt(heap, i, node);
    while(i > 1 && compareNodesAt(heap, i, parent(i)) > 0) {
        swap(heap, i, parent(i));
        i = parent(i);
    }
}

int isLargerThanChildren(Heap heap, int i) {
    return findLargestChild(heap, i) == NONE;
}

int isMaxHeap(Heap heap) {
    for(int i=1; i<=heap->numNodes; i++) {
        if(!isLargerThanChildren(heap, i)) {
            return FALSE;
        }
    }
    return TRUE;
}

Node *getNodes(Heap heap) {
    return (heap->nodes + 1);
}

Heap newHeap(int numNodes, Node nodes[]) {
    Heap heap = malloc(sizeof(struct heap));
    heap->numNodes = numNodes;
    heap->nodes = malloc((numNodes + 1)*(sizeof(Node)));
    *(heap->nodes) = NULL;
    for(int i=0; i<numNodes; i++) {
        *(heap->nodes + i + 1) = nodes[i];
    }
    return heap;
}
