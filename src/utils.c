//
// Created by Ishaan on 8/10/2024.
//
#include "../include/utils.h"

#include <ctype.h>
#include <memory.h>

VertexNeighbor VertexNeighbor_init(uint16_t id, int16_t dist) {
    VertexNeighbor v;
    v.id = id;
    v.dist = dist;

    return v;
}

WeightedGraphVertex WeightedGraphVertex_init(
    uint16_t id, VertexNeighbor neighbors[NUM_VERTICES]) {
    WeightedGraphVertex v;
    v.id = id;
    memcpy(v.neighbors, neighbors, sizeof(v.neighbors));

    return v;
}

bool is_number(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }

    return true;
}