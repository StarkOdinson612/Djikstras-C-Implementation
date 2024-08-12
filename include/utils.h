#pragma once
#include <stdint.h>
#include <stdlib.h>

#define NUM_VERTICES 6
#define INFINITY INT16_MAX
#define UNDEFINED -1
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
