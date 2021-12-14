//
// Created by Ryan.Zurrin001 on 12/13/2021.
//
#include "Queue.h"

queue *create_queue() {
    queue *q = (queue *)malloc(sizeof(queue));
    q->size = 0;
    q->front = NULL;
    q->rear = NULL;
    return q;
}

bool empty_queue(queue *q) {
    return q->size == 0;
}

void enqueue(queue *q, int data) {
    queue_node *new_node = (queue_node *)malloc(sizeof(queue_node));
    new_node->data = data;
    new_node->next = NULL;
    if (empty_queue(q)) {
        q->front = new_node;
    } else {
        q->rear->next = new_node;
    }
    q->rear = new_node;
    q->size++;
}

int dequeue(queue *q) {
    if (empty_queue(q)) {
        printf("Queue is empty\n");
        return NIL;
    }
    int data = q->front->data;
    queue_node *temp = q->front;
    q->front = q->front->next;
    free(temp);
    q->size--;
    return data;
}

int peek(queue *q) {
    if (empty_queue(q)) {
        printf("Queue is empty\n");
        return NIL;
    }
    return q->front->data;
}

void print_queue(queue *q) {
    queue_node *temp = q->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void free_queue(queue *q) {
    queue_node *temp = q->front;
    while (temp != NULL) {
        q->front = q->front->next;
        free(temp);
        temp = q->front;
    }
    free(q);
}
