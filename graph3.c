//  GRAPH: set of vertices and relationships between vertices
// graph of people and friendships
// for each person we want to store his/her name and age
// and list of friends

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct GRAPHNODE {
    char* name; // store the name of the node (person)
    int age;
    struct LISTNODE* neighbors;
    struct GRAPHNODE* next; // next vertex in the linked list representing the graph
};


struct LISTNODE {
    struct LISTNODE* next;
    struct GRAPHNODE *vertex_p; // address of the corresponding graph vertex
};




struct GRAPHNODE newGraphNode(char* _name, int _age) {
    struct GRAPHNODE vertex;
    vertex.name = malloc(strlen(_name)+1);
    strcpy(vertex.name, _name);
    vertex.age = _age;
    vertex.neighbors =NULL;

    return vertex;
}


void printVertex(struct GRAPHNODE vertex) {
    // print name and age of this vertex
    printf("name: %s, age: %d", vertex.name, vertex.age);
}

void printGraph(struct GRAPHNODE *g, int n_vertices) {
    // print  the inforamtion for every vertex in a given graph
    // g: address of the array of vertices
    // n_vertices: num of vertices in this graph
    int i;
    for (i=0; i<n_vertices;i++) {
        //g[i]: vertex i
        printf("\n");
        printVertex(g[i]);
        // print all neighbors' info
        printf("\nNeighbors: ");
        struct LISTNODE* my_neighbor = g[i].neighbors;
        while (my_neighbor != NULL) {
            printf(";");
            printVertex(*(my_neighbor->vertex_p));
            my_neighbor = my_neighbor->next;
        }

    }
}

void PrintVertexAndAllNeighborIfo(struct GRAPHNODE vertex) {
    printVertex(vertex);
    // print all neighbors' info
    struct LISTNODE* neighbor_p = vertex.neighbors;
    while(neighbor_p!=NULL) {
        printVertex(*(neighbor_p->vertex_p));
        neighbor_p = neighbor_p->next; // go to next neighbor in my neighbor list
    }
}

void printGraph2(struct GRAPHNODE* g) {
    // g: the pointer to first vertex in graph linked list

    if (g==NULL) return;

    struct GRAPHNODE *vertex_p;
    vertex_p = g;
    PrintVertexAndAllNeighborIfo(*vertex_p); // print this vertex and all of its neighbors
    printf("\n");

    // print the remaining vertices
    printGraph2(vertex_p->next); // printing graph consisting of all the remaining vertice
}

void addVertex2Graph(struct GRAPHNODE** address_of_graph, struct GRAPHNODE *vertex_p) {
    // address_of_graph: address of the graph I want to add to
    // vertex_p: poiner (address) of the vertex I want to add

    if (vertex_p == NULL) return;

    struct GRAPHNODE* first_vertex_p;
    first_vertex_p = *address_of_graph;

    // add vertex_p to the front of the graph linked list
    vertex_p->next = first_vertex_p;
    *address_of_graph = vertex_p;
}

void addNeighbor(struct GRAPHNODE* vertexA_p, struct GRAPHNODE *vertexB_p) {
    // make vertexB a neighbor of vertex A
    // vertexA_p: address (pointer) of vertexA
    // vertexB_p: address of vertex B
    if (vertexB_p == NULL || vertexA_p == NULL) return;
    struct LISTNODE* neighbor_of_A = vertexA_p->neighbors;
    struct LISTNODE* neighbor_node_p = malloc(sizeof(struct LISTNODE));
    neighbor_node_p->vertex_p =vertexB_p;
    neighbor_node_p->next = neighbor_of_A;

}

struct GRAPHNODE* getVertex(struct GRAPHNODE* first_vertex_p, char* name) {
    // return the address of the vertex with "name"
    if (first_vertex_p==NULL) return NULL;
    if (strcmp(first_vertex_p->name, name) == 0) {
        // equal, name matching
        return first_vertex_p;
    }
    return getVertex(first_vertex_p->next, name);
}


int main() {
    /* stdin:
    John 20
    Jane 21
     Joe 18
     Jenny 25
     */

    struct GRAPHNODE* first_vertex_p = NULL; // pointer to first vertex in graph linked list

    while(1) {
        char str[100];
        int age;
        if (scanf("%s %d", str, &age) == EOF) break;

        struct GRAPHNODE* vertex_p;
        vertex_p = malloc(sizeof(struct GRAPHNODE));
        *vertex_p = newGraphNode(str, age);

        addVertex2Graph(&first_vertex_p, vertex_p);
    }

    addNeighbor(getVertex(first_vertex_p, "john"), getVertex(first_vertex_p, "jane"));


    // print all information about this graph
    printGraph2(first_vertex_p);
    return 0;
}






