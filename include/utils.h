#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define NUM_VERTICES 9
#define INFINITY INT16_MAX
#define UNDEF -1
#define SELF -3

typedef struct {
    uint16_t id;
    int16_t dist;
} VertexNeighbor;

typedef struct {
    uint16_t id;
    VertexNeighbor neighbors[NUM_VERTICES];
} WeightedGraphVertex;

typedef WeightedGraphVertex WeightedGraph[NUM_VERTICES];

VertexNeighbor VertexNeighbor_init(uint16_t id, int16_t dist);

WeightedGraphVertex WeightedGraphVertex_init(
    uint16_t id, VertexNeighbor neighbors[NUM_VERTICES]);

bool is_number(char* str);