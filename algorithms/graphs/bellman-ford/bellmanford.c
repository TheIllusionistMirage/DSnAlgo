/*
 * Bellman-Ford shortest path algorithm
 * -------------------------------------
 *  Uses adjacency matrix for storing the graph
 *  If u and v are connected, then the adjacency matrix
 *  will have adj-matrix[u,v] := weight. If u and v are
 *  not connected, then adj-matrix[u,v] := infinity.
 *
 *  INT_MAX defined in limits.h is used to denote
 *  infinity.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>


/* Weighted graph structure */
typedef struct WtGraph
{
    size_t size; // |V|
    int**  adj;  // adjacency matrix
} WtGraph;

/* Graph helpers */

// Create a new graph
WtGraph* createGraph(void);

// Destroy an existing graph
void destroyGraph(WtGraph* wg);

// Display an exising graph
void displayGraph(WtGraph* wg);


/* Node structure */
typedef struct Node
{
    unsigned     data; // node data
    struct Node* next; // next Node
} Node;

/* Node helpers */

// Create new node
Node* createNode(void);


/* List structure */
typedef struct List
{
    Node* head; // head node
} List;

/* List helpers */

// Create new list
List* createList(void);

// Insert in front of an existing list
void insertFront(List* l, unsigned data);

// Delete existing list
void destroyList(List* l);

// Display existing list
void displayList(List* l);


/* Distance & Path pair structure */

typedef struct DistPath
{
    int*   distance; // stores distance from source to all targets
    List** paths;    // stores the path from source to all targets
} DistPath;


/* Bellman-Ford algorithm */

// Find the shortest paths from source to all other target vertices
DistPath* bellmanFord(WtGraph* wg, unsigned src);

// Reconstruct the path from source to
// `target` by using a shortest path table
List* reconstructPath(unsigned* previous, unsigned target);


// test 1 : test the implementation
// of Bellman-Ford algorithm
void test1();

int main()
{
    test1();
    return EXIT_SUCCESS;
}

/* Implementation */

WtGraph* createGraph(void)
{
    WtGraph* wg = (WtGraph* )malloc(sizeof(WtGraph));
    if (!wg)
    {
        fprintf(stderr, "[ERROR] Memory error\n");
        return NULL;
    }
    wg->size = 0;
    wg->adj = NULL;
    return wg;
}

// destroy graph
void destroyGraph(WtGraph* wg)
{
    if (wg == NULL)
    {
        fprintf(stderr, "[ERROR] Invalid graph\n");
        return;
    }
    size_t i = 0;
    while (i < wg->size)
        free(wg->adj[i++]);
    free(wg->adj);
    free(wg);
}

// display graph
void displayGraph(WtGraph* wg)
{
    if (wg == NULL)
    {
        fprintf(stderr, "[ERROR] Invalid graph\n");
        return;
    }

    // Since vertices are denoted by 0..size-1, the
    // maximum width of the largest vertex, i.e.,
    // `size - 1` is the log of size base 10 plus one.
    // The extra one is added to prepend an extra space
    // before printing the vertices.
    int maxWidth = (log10(wg->size) + 1) + 1;

    size_t i, j;

    // print the column vertices first
    printf("%*c ", maxWidth, ' ');
    //printf("\n\n%u\n\n", wg->size);
    for (i = 0; i < wg->size; ++i)
        printf("%*c ", maxWidth, 'A' + i);
    printf("\n");

    // now print the row vertex,
    // followed by the weights 
    for (i = 0; i < wg->size; ++i)
    {
        printf("%*c ", maxWidth, 'A' + i);
        for (j = 0; j < wg->size; ++j)
        {
            if (i == j || wg->adj[i][j] == INT_MAX)
                printf("%*c ", maxWidth, 'X');
            else
                printf("%*d ", maxWidth, wg->adj[i][j]);
        }
        printf("\n");
    }
}

Node* createNode(void)
{
    Node* n = (Node* )malloc(sizeof(Node));
    if (!n)
    {
        fprintf(stderr, "[ERROR] Memory error\n");
        return NULL;
    }
    n->data = UINT_MAX;
    n->next = NULL;
    return n;
}


List* createList(void)
{
    List* l = (List* )malloc(sizeof(List));
    if (!l)
    {
        fprintf(stderr, "[ERROR] Memory error\n");
        return NULL;
    }
    l->head = NULL;
    return l;
}

void insertFront(List* l, unsigned data)
{
    if (l == NULL)
    {
        fprintf(stderr, "[ERROR] Invalid list\n");
        return;
    }

    Node* new = createNode();
    new->data = data;

    // first insertion
    if (l->head == NULL)
        l->head = new;
    else
    {
        new->next = l->head;
        l->head = new;
    }
}

void destroyList(List* l)
{
    if (l == NULL)
    {
        fprintf(stderr, "[ERROR] Invalid list\n");
        return;
    }

    Node* n = l->head;
    Node* temp;
    while (n != NULL)
    {
        temp = n;
        n = n->next;
        free(temp);
    }
    free(l);
}

void displayList(List* l)
{
    if (l == NULL)
    {
        fprintf(stderr, "[ERROR] Invalid list\n");
        return;
    }
    
    Node* i = l->head;
    while (i != NULL)
    {
        printf("%d ", i->data);
        i = i->next;
    }
}

DistPath* bellmanFord(WtGraph* wg, unsigned src)
{
    DistPath* dp = (DistPath* )malloc(sizeof(DistPath));
    dp->distance = (int* )calloc(wg->size, sizeof(int));
    dp->paths = (List** )malloc(wg->size * sizeof(List));
    
    // This array stores the shortest path tree
    // previous[v] returns the parent of v in
    // the shortest path tree
    unsigned* previous = (unsigned* )calloc(wg->size, sizeof(unsigned));

    size_t i, u, v;
    
    // Step 1 : Initialize distance to all other vertices as INFINITY
    for (u = 0; u < wg->size; ++u)
    {
        dp->distance[u] = INT_MAX;
        previous[u] = INT_MAX;
    }

    // the weight from source to source is 0
    dp->distance[src] = 0;

    // Step 2 : Relax all edges v in G(V) |V| - 1 times
    // Since adjacency matrix is used, the complexity
    // to traverse the matrix is O(V^2)
    for (i = 0; i < wg->size - 1; ++i)
    {
        for (u = 0; u < wg->size; ++u)
        {
            for (v = 0; v < wg->size; ++v)
            {
                if (wg->adj[u][v] != INT_MAX &&
                    (dp->distance[u] + wg->adj[u][v] < dp->distance[v]))
                {
                    dp->distance[v] = dp->distance[u] + wg->adj[u][v];
                    previous[v] = u;
                }
            }
        }
    }

    // Step 3 : Check for negative-weight cycles
    for (u = 0; u < wg->size; ++u)
        for (v = 0; v < wg->size; ++v)
            if (wg->adj[u][v] != INT_MAX &&
                (dp->distance[u] + wg->adj[u][v] < dp->distance[v]))
                fprintf(stderr, "[ERROR] Graph contains negative weight cycle\n");

    // Reconstruct the shortest paths from source to all targets
    for (u = 0; u < wg->size; ++u)
        if (dp->distance[u] != INT_MAX)
        {
            List* path = reconstructPath(previous, u);
            dp->paths[u] = path;
        }

    free(previous);
    return dp;
}

// reconstruct path
List* reconstructPath(unsigned* previous, unsigned target)
{
    List* path = createList();
    unsigned u = target;

    while (previous[u] != INT_MAX)
    {
        insertFront(path, u);
        u = previous[u];
    }
    insertFront(path, u);

    return path;
}

void test1()
{
    // test graph of size 5, having
    // negative edge weights
    size_t n = 5, i;

    // Create the graph & initialize it
    WtGraph* wg = createGraph();
    wg->size = n;
    wg->adj = (int** )malloc(wg->size * sizeof(int* ));
    for (i = 0; i < wg->size; ++i)
        wg->adj[i] = (int* )malloc(wg->size * sizeof(int));

    // populate the adjacency matrix
    wg->adj[0][0] = INT_MAX;
    wg->adj[0][1] = -1;
    wg->adj[0][2] = 4;
    wg->adj[0][3] = INT_MAX;
    wg->adj[0][4] = INT_MAX;

    wg->adj[1][0] = INT_MAX;
    wg->adj[1][1] = INT_MAX;
    wg->adj[1][2] = 3;
    wg->adj[1][3] = 1;
    wg->adj[1][4] = 2;
   
    wg->adj[2][0] = INT_MAX;
    wg->adj[2][1] = INT_MAX;
    wg->adj[2][2] = INT_MAX;
    wg->adj[2][3] = INT_MAX;
    wg->adj[2][4] = INT_MAX;

    wg->adj[3][0] = INT_MAX;
    wg->adj[3][1] = 1;
    wg->adj[3][2] = 5;
    wg->adj[3][3] = INT_MAX;
    wg->adj[3][4] = INT_MAX;

    wg->adj[4][0] = INT_MAX;
    wg->adj[4][1] = INT_MAX;
    wg->adj[4][2] = INT_MAX;
    wg->adj[4][3] = -3;
    wg->adj[4][4] = INT_MAX;

    // Display the test graph
    printf("Test graph :-\n");
    displayGraph(wg);

    // Use Bellman-Ford algorithm on the test
    // graph taking vertex `0` as the source
    DistPath* dp = bellmanFord(wg, 0);

    printf("\nDistances & paths :-\n");
    for (i = 0; i < wg->size; ++i)
    {
        printf("Target : %u,\tDistance : %d\t,Path : ", i, dp->distance[i]);
        Node* j = dp->paths[i]->head;

        while (j != NULL)
        {
            printf("%d ", j->data);
            j = j->next;
        }
        printf("\n");
    }

    // Free resources
    free(dp->distance);
    for (i = 0; i < wg->size; ++i)
        free(dp->paths[i]);
    free(dp->paths);
    free(dp);

    destroyGraph(wg);
}
