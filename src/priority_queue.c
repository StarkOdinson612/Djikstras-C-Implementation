//
// Created by Ishaan on 8/11/2024.
//

#include "../include/priority_queue.h"

#include <assert.h>
#include <stdio.h>

void swap(VertexNeighbor *a, VertexNeighbor *b) {
    VertexNeighbor temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue *pq, uint16_t index) {
    uint16_t prev = pq->items[(index - 1) / 2].dist;
    uint16_t curr = pq->items[index].dist;

    //    if (prev > curr) {
    //        int y = 0;
    //    } else {
    //        int y = 2;
    //    }

    if (index != 0 && prev > curr) {
        swap(&pq->items[(index - 1) / 2], &pq->items[index]);
        heapifyUp(pq, (index - 1) / 2);
    }
}

void heapifyDown(PriorityQueue *pq, uint16_t index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->items[left].dist < pq->items[smallest].dist) {
        smallest = left;
    }

    if (right < pq->size && pq->items[right].dist < pq->items[smallest].dist) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&pq->items[index], &pq->items[smallest]);
        heapifyDown(pq, smallest);
    }
}

void print_queue(PriorityQueue *pq) {
    for (int i = 0; i < pq->size; i++) {
        printf("Index %d, Id %d, Dist %d\n", i, pq->items[i].id,
               pq->items[i].dist);
    }
}

void enqueue(PriorityQueue *pq, VertexNeighbor value) {
    if (pq->size == MAX_CAPACITY) {
        printf("Priority queue is full\n");
        return;
    }

    pq->items[pq->size++] = value;
    heapifyUp(pq, pq->size - 1);
}

VertexNeighbor dequeue(PriorityQueue *pq) {
    assert(pq->size > 0);

    VertexNeighbor item = pq->items[0];
    pq->items[0] = pq->items[--pq->size];
    heapifyDown(pq, 0);
    return item;
}

VertexNeighbor peek(PriorityQueue *pq) {
    assert(pq->size > 0);

    return pq->items[0];
}
