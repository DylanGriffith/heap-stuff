#include <stdio.h>
#include "heap.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void printFailed(char *toPrint);
void printPassed(void);
void testSort(void);
void testNewHeap(void);
void runTests(void);
void testFindLargestChild(void);
Heap setupUnorderedHeap();
Node nodeAt(Node *nodes, int i);
void testDelete(void);
void testInsert(void);

int main(void) {
    runTests();
    return 0;
}

void runTests(void) {
    testNewHeap();
    testFindLargestChild();
    testDelete();
    testInsert();
    testSort();
}

void testDelete(void) {
    printf("Running delete test\n");
    Heap heap = setupUnorderedHeap();
    makeMaxHeap(heap);
    deleteFromHeap(heap, 4);
    if (!isMaxHeap(heap) || heap->numNodes != 9) {
        printFailed("Not a max heap after deleting 4");
    }
    printPassed();
}

void testInsert(void) {
    printf("Running insert test\n");
    Heap heap = setupUnorderedHeap();
    makeMaxHeap(heap);
    deleteFromHeap(heap, 4);
    insertIntoHeap(heap, newNode(14));
    if (!isMaxHeap(heap) || heap->numNodes != 10) {
        printFailed("Not a max heap after deleting 4 and inserting 14");
        return;
    }

    deleteFromHeap(heap, 1);
    insertIntoHeap(heap, newNode(5));
    if (!isMaxHeap(heap) || heap->numNodes != 10) {
        printFailed("Not a max heap after reinserting 4");
        return;
    }
    printPassed();
}

void testSort(void) {
    printf("Running heapSort test\n");
    Node nodes[10] = { newNode(10), newNode(1), newNode(7), newNode(4), newNode(3), newNode(6), newNode(9), newNode(2), newNode(5), newNode(8) };
    Heap heap = newHeap(10, nodes);
    Node *sortedNodes = heapSort(heap);
    for(int i = 0; i<10; i++) {
        int expected = i + 1;
        if(nodeAt(sortedNodes, i)->data != expected) {
            char message[50];
            sprintf(message, "expected data=%d, got data=%d", expected, (*(sortedNodes + i))->data);
            printFailed(message);
            return;
        }
    }
    printPassed();
}

void testNewHeap(void) {
    printf("Running newHeap test\n");
    Node nodes[10] = { newNode(1), newNode(2), newNode(3), newNode(4), newNode(5), newNode(6), newNode(7), newNode(8), newNode(9), newNode(10) };
    Heap heap = newHeap(10, nodes);
    Node *sortedNodes = getNodes(heap);
    for(int i = 0; i<10; i++) {
        int expected = i + 1;
        if(nodeAt(sortedNodes, i)->data != expected) {
            char message[50];
            sprintf(message, "expected data=%d, got data=%d", expected, (*(sortedNodes + i))->data);
            printFailed(message);
            return;
        }
    }
    printPassed();
}

void testFindLargestChild() {
    printf("Running test: Find largest child\n");
    Heap heap = setupUnorderedHeap();
    int node;
    int expected;
    int actual;
    char buffer[59];

    // Test value 10
    node = 1;
    expected = NONE;
    actual = findLargestChild(heap,node);
    if (actual != expected) {
        sprintf(buffer, "findLargestChild: expected=%d, got=%d for node=%d",expected, actual, node);
        printFailed(buffer);
        return;
    }

    // Test value 7
    node = 3;
    expected = 7;
    actual = findLargestChild(heap,node);
    if (actual != expected) {
        sprintf(buffer, "findLargestChild: expected=%d, got=%d for node=%d",expected, actual, node);
        printFailed(buffer);
        return;
    }

    // Test value 9
    node = 7;
    expected = NONE;
    actual = findLargestChild(heap,node);
    if (actual != expected) {
        sprintf(buffer, "findLargestChild: expected=%d, got=%d for node=%d",expected, actual, node);
        printFailed(buffer);
        return;
    }

    // Test value 1
    node = 2;
    expected = 4;
    actual = findLargestChild(heap,node);
    if (actual != expected) {
        sprintf(buffer, "findLargestChild: expected=%d, got=%d for node=%d",expected, actual, node);
        printFailed(buffer);
        return;
    }

    // Test value 8
    node = 10;
    expected = NONE;
    actual = findLargestChild(heap,node);
    if (actual != expected) {
        sprintf(buffer, "findLargestChild: expected=%d, got=%d for node=%d",expected, actual, node);
        printFailed(buffer);
        return;
    }

    // Test value 8
    node = 9;
    expected = NONE;
    actual = findLargestChild(heap,node);
    if (actual != expected) {
        sprintf(buffer, "findLargestChild: expected=%d, got=%d for node=%d",expected, actual, node);
        printFailed(buffer);
        return;
    }

    // Test value 8
    node = 6;
    expected = NONE;
    actual = findLargestChild(heap,node);
    if (actual != expected) {
        sprintf(buffer, "findLargestChild: expected=%d, got=%d for node=%d",expected, actual, node);
        printFailed(buffer);
        return;
    }
    printPassed();
}


Node nodeAt(Node *nodes, int i) {
    return *(nodes + i);
}

void printFailed(char *message) {
    printf(ANSI_COLOR_RED "FAILED: " ANSI_COLOR_RESET);
    printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, message);
    printf("\n");
}

void printPassed() {
    printf(ANSI_COLOR_GREEN "PASSED\n" ANSI_COLOR_RESET);
}

Heap setupUnorderedHeap() {
    Node nodes[10] = {
        /*1*/ newNode(10),
        /*2*/ newNode(1),
        /*3*/ newNode(7),
        /*4*/ newNode(4),
        /*5*/ newNode(3),
        /*6*/ newNode(6),
        /*7*/ newNode(9),
        /*8*/ newNode(2),
        /*9*/ newNode(5),
        /*10*/ newNode(8)
    };
    return newHeap(10, nodes);
}
