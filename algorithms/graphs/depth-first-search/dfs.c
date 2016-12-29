/*
 * Depth-first Search graph traversal
 * ----------------------------------
 * Uses adjacency matrix for storing graph
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

/* Node structure */
typedef struct Node
{
    unsigned data;
    struct Node* next;
} Node;

/* Node helpers */
Node* createNode(void)
{
    Node* new = (Node* )malloc(sizeof(Node));
    new->data = 0;
    new->next = NULL;
    return new;
}

/* Stack structure */
typedef struct Stack
{
    Node* top;
} Stack;

/* Stack helper methods */

Stack* createStack(void)
{
    Stack* s = (Stack* )malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

// push operation
void push(Stack* s, unsigned data)
{
    if (s == NULL)
    {
        fprintf(stderr, "[ ERROR ] Invalid stack");
        return;
    }

    Node* new = createNode();
    if (!new)
    {
        fprintf(stderr, "[ ERROR ] Memory error");
    }
    new->data = data;

    // first push
    if (s->top == NULL)
        s->top = new;

    // subsequent pushes
    else
    {
        new->next = s->top;
        s->top = new;
    }
}

// pop operation
unsigned pop(Stack* s)
{
    if (s == NULL)
    {
        fprintf(stderr, "[ ERROR ] Invalid stack");
        return UINT_MAX;
    }

    if (s->top == NULL)
    {
        fprintf(stderr, "[ ERROR ] Stack underflow");
        return UINT_MAX;
    }

    unsigned data = s->top->data;
    Node* temp = s->top;
    s->top = s->top->next;
    free(temp);

    return data;
}

// destroy stack
void destroyStack(Stack* s)
{
    Node* i = s->top;
    Node* temp;

    while (i != NULL)
    {
        temp = i;
        i = i->next;
        free(temp);
    }
    free(s);
}

// display stack
void displayStack(Stack* s)
{
    Node* i = s->top;

    while (i != NULL)
    {
        printf("%u ", i->data);
        i = i->next;
    }
}

/* Graph structure */
typedef struct Graph
{
    unsigned** adj; // adjacency matrix
    size_t size;    // |V|
} Graph;

/* Graph helper methods */

// create new graph
Graph* createGraph(void)
{
    Graph* g = (Graph* )malloc(sizeof(Graph));
    g->adj = NULL;
    g->size = 0;
    return g;
}

// destroy graph
void destroyGraph(Graph* g)
{
    size_t i = 0;
    while (i < g->size)
        free(g->adj[i++]);
    free(g->adj);
    free(g);
}

// fill the graph
//  => g    - graph to be populated
//  => adj  - the input adjacency matrix
//  => size - size of adjacency matrix
void fillGraph(Graph* g, unsigned** adj, size_t size)
{
    size_t i = 0, j;
    
    g->size = size;
    g->adj = (unsigned** )malloc(size * sizeof(unsigned* ));    
    while (i < size)
        g->adj[i++] = (unsigned* )malloc(size * sizeof(unsigned));

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            g->adj[i][j] = adj[i][j];
            ++j;
        }
        ++i;
    }
}

// display the graph
void displayGraph(Graph* g)
{
    size_t i = 0, j;
    int maxWidth = (log10(g->size) + 1) + 1;

    printf("%*c ", maxWidth, ' ');

    while (i < g->size)
        printf("%*c ", maxWidth - 1, 'A' + i++);
    printf("\n");
    
    i = 0;
    while (i < g->size)
    {
        printf("%*c", maxWidth, 'A' + i);
        j = 0;
        while (j < g->size)
            printf("%*u", maxWidth, g->adj[i][j++]);
        printf("\n");
        i++;
    }
}

/* Depth-first Search traversal */
void DFS(Graph* g, unsigned src)
{
    unsigned v, w;
    Stack* s = createStack();
    unsigned* visited = (unsigned* )calloc(g->size, sizeof(unsigned));
    for (v = 0; v < g->size; ++v)
        visited[v] = 0;

    push(s, src);
    visited[src] = 1;

    while (s->top != NULL)
    {
        // the popped node from stack
        v = pop(s);
        //visited[v] = 1;
        printf("Current Vertex : %c\n", 'A' + v);

        for (w = 0; w < g->size; ++w)
        {
            // for each neighbor w of v and w not visited,
            // push it to traversal stack
            if (!visited[w] && g->adj[v][w])
            {
                push(s, w);
                visited[w] = 1;
            }
        }
    }

    free(visited);
}

/* utility methods */

// create adjacency matrix
unsigned** createAdjMatrix(size_t size)
{
    size_t i = 0;
    unsigned** adj = (unsigned** )malloc(size * sizeof(unsigned));
    while (i < size)
        adj[i++] = (unsigned* )malloc(size * sizeof(unsigned));
    return adj;
}

// destroy adjacency matrix
void destroyAdjMatrix(unsigned** adj, size_t size)
{
    size_t i = 0;
    while (i < size)    
        free(adj[i++]);
    free(adj);
}

/* test 1 : test DFS traversal on a graph */
void test1()
{
    size_t n = 8;
    unsigned** adj = createAdjMatrix(n);
    
    adj[0][0] = 0;
    adj[0][1] = 1;
    adj[0][2] = 0;
    adj[0][3] = 0;
    adj[0][4] = 0;
    adj[0][5] = 0;
    adj[0][6] = 0;
    adj[0][7] = 0;


    adj[1][0] = 1;
    adj[1][1] = 0;
    adj[1][2] = 1;
    adj[1][3] = 0;
    adj[1][4] = 0;
    adj[1][5] = 0;
    adj[1][6] = 0;
    adj[1][7] = 1;

    adj[2][0] = 0;
    adj[2][1] = 1;
    adj[2][2] = 0;
    adj[2][3] = 1;
    adj[2][4] = 1;
    adj[2][5] = 0;
    adj[2][6] = 0;
    adj[2][7] = 0;

    adj[3][0] = 0;
    adj[3][1] = 0;
    adj[3][2] = 1;
    adj[3][3] = 0;
    adj[3][4] = 0;
    adj[3][5] = 0;
    adj[3][6] = 0;
    adj[3][7] = 0;

    adj[4][0] = 0;
    adj[4][1] = 0;
    adj[4][2] = 1;
    adj[4][3] = 0;
    adj[4][4] = 0;
    adj[4][5] = 1;
    adj[4][6] = 1;
    adj[4][7] = 1;

    adj[5][0] = 0;
    adj[5][1] = 0;
    adj[5][2] = 0;
    adj[5][3] = 0;
    adj[5][4] = 1;
    adj[5][5] = 0;
    adj[5][6] = 0;
    adj[5][7] = 0;

    adj[6][0] = 0;
    adj[6][1] = 0;
    adj[6][2] = 0;
    adj[6][3] = 0;
    adj[6][4] = 1;
    adj[6][5] = 0;
    adj[6][6] = 0;
    adj[6][7] = 0;

    adj[7][0] = 0;
    adj[7][1] = 1;
    adj[7][2] = 0;
    adj[7][3] = 0;
    adj[7][4] = 1;
    adj[7][5] = 0;
    adj[7][6] = 0;
    adj[7][7] = 0;
    
    Graph* g = createGraph();
    
    fillGraph(g, adj, n);
    destroyAdjMatrix(adj, n);
    displayGraph(g);
    DFS(g, 0);

    destroyGraph(g);
}

int main()
{   
    /*size_t i, j, n = 5;

    unsigned** adj = createAdjMatrix(n);

    // create a complete graph of size 5
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            adj[i][j] = i == j ? 0 : 1;*/

    /*Graph* g = createGraph();
    fillGraph(g, adj, n);
    displayGraph(g);
    destroyGraph(g);*/
    test1();

    return EXIT_SUCCESS;
}
