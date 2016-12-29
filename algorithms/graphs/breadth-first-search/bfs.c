#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Linked list structure */

typedef struct Node
{
    unsigned data;
    struct Node* next;
} Node;

/* Queue structure */
typedef struct Queue
{
    Node* head;
    Node* tail;
} Queue;

/* Queue helpers */

// create and initialize
Node* newNode()
{
    Node* n = (Node* )malloc(sizeof(Node));
    n->data = 0;
    n->next = NULL;
    return n;
}

// create and initialize
Queue* newQueue()
{
    Queue* q = (Queue* )malloc(sizeof(Queue));
    q->head = q->tail = NULL; 
    return q;
}

// enqueue operation
void enqueue(Queue* q, unsigned data)
{
    if (q->head == NULL)
    {
        q->head = newNode();
        q->head->data = data;
        q->tail = q->head;
        //q->head->next = q->tail;
    }
    else
    {
        q->tail->next = newNode();
        q->tail = q->tail->next;
        q->tail->data = data;
    }
}

// dequeue operation
unsigned dequeue(Queue* q)
{
    unsigned data;
    Node* temp = NULL;

    if (q->head == NULL)
        return UINT_MAX;

    data = q->head->data;
    temp = q->head;
    q->head = q->head->next;
    free(temp);

    if (q->head == NULL)
        q->tail = NULL;

    return data;
}

// destroy queue
void destroyQueue(Queue* q)
{
    while (q->head != NULL)
        dequeue(q);
    free(q);
}

// print queue
void displayQueue(Queue* q)
{
    Node* i = q->head;

    while (i != NULL)
    {
        printf("%u ", i->data);
        i = i->next;
    }
    printf("\n");
}

/* Graph structure */
typedef struct Graph
{
    int** adjMat;
    unsigned V;
} Graph;

/* Graph helpers */

// create and initialize
Graph* newGraph()
{
    Graph* g = (Graph* )malloc(sizeof(Graph));
    g->adjMat = NULL;
    g->V = 0;
    return g;
}

// destroy graph
void destroyGraph(Graph* g)
{
    size_t i;
    for (i = 0; i < g->V; ++i)
        free(g->adjMat[i]);
    free(g->adjMat);
    free(g);
}

// print graph
void displayGraph(Graph* g)
{
    size_t i, j;
    for (i = 0; i < g->V; ++i)
    {
        for (j = 0; j < g->V; ++j)
            printf("%d ", g->adjMat[i][j]);
        printf("\n");
    }
}

/* Breadth First Search algorithm implementation */
void BFS(Graph* g, size_t src)
{
    // denotes whether node u in G(V) has been visited or not
    //  => 0 : not visited
    //  => 1 : visited
    int* visited = (int* )malloc(g->V * sizeof(int));
    Queue* vertexQ = newQueue();
    unsigned u, v;

    // Initialize visited array to all unvisited
    for (v = 0; v < g->V; ++v)
        visited[v] = 0;

    // initialize vertex queue with source vertex
    enqueue(vertexQ, src);
    visited[src] = 1;

    while (vertexQ->head != NULL)
    {
        u = dequeue(vertexQ);
        printf("Vertex : %d\n", u);

        for (v = 0; v < g->V; ++v)
            if (!visited[v] && g->adjMat[u][v])
            {
                enqueue(vertexQ, v);
                visited[v] = 1;
            }
    }

    // release auxiliary resources
    free(visited);
    destroyQueue(vertexQ);
}

/* Unit tests */

// test 1 : Test queue implementation
void test1()
{
    Queue* q = newQueue();
    
    enqueue(q, 3);
    enqueue(q, 1);
    enqueue(q, 2);
    
    displayQueue(q);
    
    dequeue(q);
    enqueue(q, 4);;
    
    displayQueue(q);

    destroyQueue(q);
}

// test 2 : Test graph implementation
void test2()
{
    Graph* g = newGraph();
    size_t i, j;
    
    printf("Setting the no. of vertices as 5...\n");
    
    g->V = 5;
    g->adjMat = (int** )malloc(sizeof(int) * g->V);

    for (i = 0; i < g->V; ++i)        
        g->adjMat[i] = (int* )malloc(sizeof(int) * g->V);

    printf("Creating a complete graph...\n");
    for (i = 0; i < g->V; ++i)
        for (j = 0; j < g->V; ++j)
            g->adjMat[i][j] = i == j ? 0 : 1;

    printf("Displaying graph :-\n");
    displayGraph(g);

    destroyGraph(g);
}

// test 3 : Test BFS traversal implementation
void test3()
{
    Graph* g = newGraph();

    size_t i;
    
    printf("Unit test : Test Breadth-First Search Implementation\n\n");
    
    printf("Setting the no. of vertices as 8...\n");
    
    g->V = 8;
    g->adjMat = (int** )malloc(sizeof(int* ) * g->V);

    for (i = 0; i < g->V; ++i)        
        g->adjMat[i] = (int* )malloc(sizeof(int) * g->V);

    printf("Creating graph...\n");

    g->adjMat[0][0] = 0;
    g->adjMat[0][1] = 1;
    g->adjMat[0][2] = 0;
    g->adjMat[0][3] = 0;
    g->adjMat[0][4] = 0;
    g->adjMat[0][5] = 0;
    g->adjMat[0][6] = 0;
    g->adjMat[0][7] = 0;


    g->adjMat[1][0] = 1;
    g->adjMat[1][1] = 0;
    g->adjMat[1][2] = 1;
    g->adjMat[1][3] = 0;
    g->adjMat[1][4] = 0;
    g->adjMat[1][5] = 0;
    g->adjMat[1][6] = 0;
    g->adjMat[1][7] = 1;

    g->adjMat[2][0] = 0;
    g->adjMat[2][1] = 1;
    g->adjMat[2][2] = 0;
    g->adjMat[2][3] = 1;
    g->adjMat[2][4] = 1;
    g->adjMat[2][5] = 0;
    g->adjMat[2][6] = 0;
    g->adjMat[2][7] = 0;

    g->adjMat[3][0] = 0;
    g->adjMat[3][1] = 0;
    g->adjMat[3][2] = 1;
    g->adjMat[3][3] = 0;
    g->adjMat[3][4] = 0;
    g->adjMat[3][5] = 0;
    g->adjMat[3][6] = 0;
    g->adjMat[3][7] = 0;

    g->adjMat[4][0] = 0;
    g->adjMat[4][1] = 0;
    g->adjMat[4][2] = 1;
    g->adjMat[4][3] = 0;
    g->adjMat[4][4] = 0;
    g->adjMat[4][5] = 1;
    g->adjMat[4][6] = 1;
    g->adjMat[4][7] = 1;

    g->adjMat[5][0] = 0;
    g->adjMat[5][1] = 0;
    g->adjMat[5][2] = 0;
    g->adjMat[5][3] = 0;
    g->adjMat[5][4] = 1;
    g->adjMat[5][5] = 0;
    g->adjMat[5][6] = 0;
    g->adjMat[5][7] = 0;

    g->adjMat[6][0] = 0;
    g->adjMat[6][1] = 0;
    g->adjMat[6][2] = 0;
    g->adjMat[6][3] = 0;
    g->adjMat[6][4] = 1;
    g->adjMat[6][5] = 0;
    g->adjMat[6][6] = 0;
    g->adjMat[6][7] = 0;

    g->adjMat[7][0] = 0;
    g->adjMat[7][1] = 1;
    g->adjMat[7][2] = 0;
    g->adjMat[7][3] = 0;
    g->adjMat[7][4] = 1;
    g->adjMat[7][5] = 0;
    g->adjMat[7][6] = 0;
    g->adjMat[7][7] = 0;

    printf("\nDisplaying graph :-\n");
    displayGraph(g);

    // Use BFS traversal
    printf("\nUsing Breadth-First Search to traverse the graph :-\n");
    BFS(g, 0);

    destroyGraph(g);
}

int main()
{
    // UNIT TESTS
    // Uncomment these lines to see them
    
    // Test 1 : Test queue implementation
    // test1();    
    
    // Test 2 : Test graph implementation
    // test2();
        
    // Test 3 : Test BFS traversal implementation
    test3();
        
    return EXIT_SUCCESS;
}
