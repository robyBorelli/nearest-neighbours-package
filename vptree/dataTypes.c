struct node_s{
    int isLeaf; // TRUE or FALSE

    // used only in NON leafs
    struct node_s* leftSon;
    struct node_s* rightSon;
    float* vantagePoint;
    float radius;

    // used only in leafs node
    float ** points;
    int nPoints;
};
typedef struct node_s node;

/*
struct node_h{
    float *point;
    float distance;
};
typedef struct node_h heapNode;*/
