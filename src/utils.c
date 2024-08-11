//
// Created by Ishaan on 8/10/2024.
//
#include <memory.h>
#include "../include/utils.h"

VertexNeighbor VertexNeighbor_init(uint16_t id, int16_t dist) {
    VertexNeighbor v;
    v.id = id;
    v.dist = dist;

    return v;
}

WeightedGraphVertex WeightedGraphVertex_init(uint16_t id, VertexNeighbor neighbors[MAX_VERTICES]) {
    WeightedGraphVertex v;
    v.id = id;
    memcpy(v.neighbors, neighbors, sizeof (v.neighbors));

    return v;
}