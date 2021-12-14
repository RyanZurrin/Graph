//
// Created by Ryan.Zurrin001 on 12/13/2021.
//

#include "Heap.h"

edge create_edge(int vertex, int weight) {
    edge e;
    e.vertex = vertex;
    e.weight = weight;
    return e;
}

heap* create_heap(int size) {
    heap *h = (heap *)malloc(sizeof(heap));
    h->arr = (edge *)malloc(sizeof(edge) * size);
    h->size = 0;
    for (int i = 0; i < size; ++i) {
        h->arr[i].vertex = 0;
        h->arr[i].weight = 0;
    }
    return h;
}

bool empty_heap(heap *h) {
    return h->size == 0;
}

void swap(edge *a, edge *b) {
    edge temp = *a;
    *a = *b;
    *b = temp;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void insert_max_heap(heap *h, edge *e) {
    h->size++;
    int i = h->size - 1;
    while (i > 0 && h->arr[(i - 1) / 2].weight < e->weight) {
        swap(h->arr + i, h->arr + (i - 1) / 2);
        i = (i - 1) / 2;
    }
    h->arr[i] = *e;
}

void insert_min_heap(heap *h, edge *e) {
    h->size++;
    int i = h->size - 1;
    while (i > 0 && h->arr[(i - 1) / 2].weight > e->weight) {
        swap(h->arr + i, h->arr + (i - 1) / 2);
        i = (i - 1) / 2;
    }
    h->arr[i] = *e;
}

edge remove_max_heap(heap *h) {
    if (empty_heap(h)) {
        printf("Heap is empty\n");
        return create_edge(0, 0);
    }
    edge e = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    int i = 0;
    while (i < h->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int max_index = i;
        if (left < h->size && h->arr[left].weight > h->arr[max_index].weight) {
            max_index = left;
        }
        if (right < h->size && h->arr[right].weight > h->arr[max_index].weight) {
            max_index = right;
        }
        if (max_index != i) {
            swap(h->arr + i, h->arr + max_index);
            i = max_index;
        } else {
            break;
        }
    }
    return e;
}

edge remove_min_heap(heap* h) {
    if (empty_heap(h)) {
        printf("Heap is empty\n");
        return create_edge(0, 0);
    }
    edge e = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    int i = 0;
    while (i < h->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int min_index = i;
        if (left < h->size && h->arr[left].weight < h->arr[min_index].weight) {
            min_index = left;
        }
        if (right < h->size && h->arr[right].weight < h->arr[min_index].weight) {
            min_index = right;
        }
        if (min_index != i) {
            swap(h->arr + i, h->arr + min_index);
            i = min_index;
        } else {
            break;
        }
    }
    return e;
}

void decrease_key(heap* h, int e, int new_weight) {
    int i = 0;
    while (i < h->size) {
        if (h->arr[i].vertex == e) {
            break;
        }
        i++;
    }
    h->arr[i].weight = new_weight;
    while (i > 0 && h->arr[(i - 1) / 2].weight > h->arr[i].weight) {
        swap(h->arr + i, h->arr + (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void increase_key(heap* h, int e, int new_weight) {
    int i = 0;
    while (i < h->size) {
        if (h->arr[i].vertex == e) {
            break;
        }
        i++;
    }
    h->arr[i].weight = new_weight;
    while (i > 0 && h->arr[(i - 1) / 2].weight < h->arr[i].weight) {
        swap(h->arr + i, h->arr + (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void print_heap(heap *h) {
    for (int i = 0; i < h->size; ++i) {
        printf("%d ", h->arr[i].weight);
    }
    printf("\n");
}

void free_heap(heap *h) {
    free(h->arr);
    free(h);
}
