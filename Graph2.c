//  GRAPH: set of vertices and relationships between vertices
// graph of people and friendships
// for each person we want to store his/her name and age
// and list of friends


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct GRAPH_NODE {
    char* name;
    int age;
    struct GRAPH* neighbors;
    struct GRAPH_NODE* next;
}node;

typedef struct GRAPH {
    struct GRAPH* next;
    node* vertex_p;
    int num_vertices;
    int num_edges;
}graph;

node * newGraphNode(char* name, int age) {
    node* vertex;
    vertex->name = malloc(strlen(name) + 1);
    strcpy(vertex->name, name);
    vertex->age = age;
    vertex->neighbors = NULL;
    return vertex;
}

graph* createGraph() {
    graph* graph_p = malloc(sizeof(graph));
    graph_p->next = NULL;
    graph_p->vertex_p = NULL;
    graph_p->num_vertices = 0;
    graph_p->num_edges = 0;
    return graph_p;
}

void printVertex(node v) {
    printf("name: %s, age: %d\n", v.name, v.age);
}

void printGraph(node* g, int vertices) {
    if (g == NULL) return;
    int i;
    for (i = 0; i < vertices; i++) {
        printf("\n");
        printVertex(g[i]);
        printf("neighbors: ");
        graph* my_neighbors = g[i].neighbors;
        while (my_neighbors != NULL) {
            printf("; ");
            printVertex(*(my_neighbors->vertex_p));
            my_neighbors = my_neighbors->next;
        }
    }
}

void printVertexAndAllNeighborInfo(node vertex) {
    printVertex(vertex);
    graph* my_neighbors = vertex.neighbors;
    while (my_neighbors != NULL) {
        printf("; ");
        printVertex(*(my_neighbors->vertex_p));
        my_neighbors = my_neighbors->next;
    }
}

void printGraph2(node* g) {
    if (g == NULL) return;
    node* my_vertices = g;
    printVertexAndAllNeighborInfo(*my_vertices);
    printf("\n");
    printGraph2(my_vertices + 1);
}

void addNeighbor(node* v, node* neighbor) {
    if (v->neighbors == NULL) {
        v->neighbors = malloc(sizeof(graph));
        v->neighbors->vertex_p = neighbor;
        v->neighbors->num_vertices = 1;
        v->neighbors->num_edges = 0;
        v->neighbors->next = NULL;
    } else {
        graph* my_neighbors = v->neighbors;
        while (my_neighbors->next != NULL) {
            my_neighbors = my_neighbors->next;
        }
        my_neighbors->next = malloc(sizeof(graph));
        my_neighbors->next->vertex_p = neighbor;
        my_neighbors->next->num_vertices = 1;
        my_neighbors->next->num_edges = 0;
        my_neighbors->next->next = NULL;
    }
}
void addVertex2Graph(graph** g, node* v) {
    if (*g == NULL) {
        *g = malloc(sizeof(graph));
        (*g)->vertex_p = v;
        (*g)->num_vertices++;
        (*g)->num_edges = 0;
        (*g)->next = NULL;
    } else {
        graph* my_graph = *g;
        while (my_graph->next != NULL) {
            my_graph = my_graph->next;
        }
        my_graph->next = malloc(sizeof(graph));
        my_graph->next->vertex_p = v;
        my_graph->next->num_vertices++;
        my_graph->next->num_edges = 0;
        my_graph->next->next = NULL;
    }
}

node* getVertex(graph* g, char* name) {
    if (g == NULL) return NULL;
    node* my_vertices = g->vertex_p;
    while (my_vertices != NULL) {
        if (strcmp(my_vertices->name, name) == 0) {
            return my_vertices;
        }
        my_vertices = my_vertices->next;
    }
    return NULL;
}

int main() {
    struct GRAPH* g = createGraph();
    char str[100];
    int age;
    while (scanf("%s %d", str, &age) != EOF) {
        node* vertex = malloc(sizeof(node));
        vertex = newGraphNode(str, age);
        addVertex2Graph(&g, vertex);
    }

    addNeighbor(getVertex(g, "john"), getVertex(g, "jane"));
    addNeighbor(getVertex(g, "john"), getVertex(g, "jill"));
    addNeighbor(getVertex(g, "jane"), getVertex(g, "jill"));
    addNeighbor(getVertex(g, "bob"), getVertex(g, "mike"));

    printGraph2(g->vertex_p);
    return 0;
}
