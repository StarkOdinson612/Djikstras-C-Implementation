#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define NUM_VERTICES 9
#define F_INFINITY INT16_MAX
#define UNDEF -1
#define SELF -3

typedef struct {
    int32_t x;
    int32_t y;
} Point;

typedef struct {
    uint16_t id;
    float dist;
    float r_dist;
} VertexNeighbor;

typedef struct {
    uint16_t id;
    VertexNeighbor neighbors[NUM_VERTICES];
} WeightedGraphVertex;

typedef WeightedGraphVertex WeightedGraph[NUM_VERTICES];

VertexNeighbor VertexNeighbor_init(uint16_t id, float dist);
VertexNeighbor VertexNeighbor_alt_init(uint16_t id, float dist, float r_dist);

WeightedGraphVertex WeightedGraphVertex_init(
    uint16_t id, VertexNeighbor neighbors[NUM_VERTICES]);

bool is_number(char* str);

float get_distance(Point a, Point b);