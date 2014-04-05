typedef struct node {
    int data;
}* Node;

Node newNode(int data);
int nodeEquals(Node node, Node other);
int nodeHashKey(Node node);

// Returns negative number if node comes
// before other, 0 if they are the same
// and positive if other comes before node
int nodeComp(Node node, Node other);

