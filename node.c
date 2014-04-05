#include<stdlib.h>
#include "node.h"

int nodeEquals(Node node, Node other) {
    return (node->data == other->data);
}

int nodeHashKey(Node node) {
    return node->data;
}

Node newNode(int data) {
    Node node = malloc(sizeof(struct node));
    node->data = data;
    return node;
}

int nodeComp(Node node, Node other) {
    return (node->data - other->data);
}
