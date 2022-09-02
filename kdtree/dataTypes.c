struct node_s{
    int isLeaf; // TRUE or FALSE

    // used only in NON leafs
    struct node_s* leftSon;
    struct node_s* rightSon;
    float partitionValue;
    int discriminatorKey;

    // used only in leafs node
    float ** points;
    int nPoints;
};
typedef struct node_s node;