//
// Created by Ryan.Zurrin001 on 12/13/2021.
// heap for a graph
//

#ifndef GRAPH_HEAP_H
#define GRAPH_HEAP_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// heap node which represents an edge
typedef struct edge {
    int vertex;
    int weight;
} edge;
// heap structure
typedef struct heap {
    edge *arr;
    int size;
} heap;

edge create_edge(int, int);

heap* create_heap(int);

bool empty_heap(heap*);

void swap(edge*, edge*);

int max(int, int);

int min(int, int);

void insert_max_heap(heap*, edge*);

void insert_min_heap(heap*, edge*);

edge remove_max_heap(heap*);

edge remove_min_heap(heap*);

void decrease_key(heap*, int, int);

void increase_key(heap*, int, int);

void print_heap(heap*);
// free heap
void free_heap(heap*);
#endif //GRAPH_HEAP_H
