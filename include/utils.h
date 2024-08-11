#pragma once
#include <stdint.h>
#include <stdlib.h>

#define MAX_VERTICES 4
#define INFINITY INT16_MAX
#define UNDEFINED -1
#define SELF -3

typedef struct {
    uint16_t id;
    int16_t dist;
} VertexNeighbor;

typedef struct {
    uint16_t id;
    VertexNeighbor neighbors[MAX_VERTICES];
} WeightedGraphVertex;

typedef WeightedGraphVertex WeightedGraph[MAX_VERTICES];

VertexNeighbor VertexNeighbor_init(uint16_t id, int16_t dist);

WeightedGraphVertex WeightedGraphVertex_init(uint16_t id, VertexNeighbor neighbors[MAX_VERTICES]);
