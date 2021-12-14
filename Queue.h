//
// Created by Ryan.Zurrin001 on 12/13/2021.
//

#ifndef GRAPH_QUEUE_H
#define GRAPH_QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INT_MAX 2147483647
#define NIL (-1)
// Queue node
typedef struct queue_node {
    int data;
    struct queue_node *next;
} queue_node;
// Queue structure
typedef struct queue {
    int size;
    queue_node *front;
    queue_node *rear;
} queue;
// create a new queue
queue *create_queue();
// true if queue isempty else false
bool empty_queue(queue*);
// enqueue an element
void enqueue(queue*, int);
// dequeue an element
int dequeue(queue*);
// peek the front element
int peek(queue*);
// print the queue
void print_queue(queue*);
// free the queue
void free_queue(queue*);
#endif //GRAPH_QUEUE_H