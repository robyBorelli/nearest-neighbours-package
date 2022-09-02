#ifndef MAX_HEAP_H
#define MAX_HEAP_H

struct node_h{
    float *point;
    float distance;
};
typedef struct node_h heapNode;

/**
 * @return A new heapNode with set parameters
 */
heapNode *heapNodeCreate(float *point,float distance);

/**
 * @param size the maximum size of the heap
 * @param heapSize a pointer to a variable which handles the heapSize value.
 * @param heapLength a pointer to a variable which handles the heapLength value.
 * @return a new empty heap
 * @post 'heapLength' = 0
 * @post 'heapSize' = 'size'
 */
heapNode **heapCreate(int size,int *heapSize,int *heapLength);

/**
 * @param hn the heap to be destroyed
 * @param hl the current length of the heap.
 * @post The heap and all of the heapNodes contained are deallocated
 */
void heapDestroy(heapNode **hn,int hl);

/**
 * @param a The heap pointer
 * @return the heapNode containing the maximum value in the heap
 */
heapNode *heapMax(heapNode **a);

/**
 * @param a  the heap pointer
 * @param heapLength the current length of the heap
 * @return the heapNode containing the maximum value in the heap
 * @post the returned heapNode is no more in the heap
 * @post heapLength is decreased by 1
 */
heapNode *heapDequeue(heapNode **a,int *heapLength);

/**
 * @param a  the heap pointer
 * @param data the heapNode that we want to insert in the heap
 * @param heapLength the current length of the heap
 * @param heapSize the maximum length of the heap
 * @post on Success 'data' is inserted into the heap into the correct position.
 * if heapLength > heapSize, the function fails, no operation is performed in the heap,
 * an assertion is raised.
 */
void heapInsert(heapNode **a,heapNode *data,int *heapLength,int *heapSize);

/**
 * @param i a valid position of a HeapNode 'h'
 * @return the position of 'h.right'
 */
int heapRightChild(int i);

/**
 * @param i a valid position of a HeapNode 'h'
 * @return the position of 'h.left'
 */
int heapLeftChild(int i);

/**
 * @param i a valid position of a HeapNode 'h'
 * @return the position of 'h.parent'
 */
int heapParent(int i);
#endif