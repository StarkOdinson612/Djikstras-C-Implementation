//
// Created by Ishaan on 8/11/2024.
//

#include <stdlib.h>
#include <stdint.h>

#include "utils.h"

#define MAX_CAPACITY 100

#pragma once

typedef struct {
    VertexNeighbor items[MAX_CAPACITY];
    uint16_t size;
} PriorityQueue;

void queue_swap(VertexNeighbor *a, VertexNeighbor *b);

void heapifyUp(PriorityQueue *pq, uint16_t index);

void heapifyDown(PriorityQueue *pq, uint16_t index);

void enqueue(PriorityQueue *pq, VertexNeighbor value);

VertexNeighbor dequeue(PriorityQueue *pq);

VertexNeighbor queue_peek(PriorityQueue *pq);

void queue_print(PriorityQueue* pq);



