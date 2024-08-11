#pragma once
#include <stdlib.h>
#include "utils.h"

typedef struct vector_t {
    VertexNeighbor* elements;
    uint16_t capacity;
    uint16_t size;
} vector_t;

vector_t* vector_new();
void vector_ctr(vector_t* obj);
void vector_dtr(vector_t* obj);

uint16_t vector_size(vector_t* obj);
uint16_t vector_capacity(vector_t* obj);

void vector_push_back(vector_t* obj, VertexNeighbor element);
void vector_pop_back(vector_t* obj);
void vector_erase(vector_t* obj, uint16_t first_ind, uint16_t last_ind);
void vector_pop(vector_t* obj, uint16_t ind);

VertexNeighbor vector_at(vector_t* obj, int index);
VertexNeighbor* vector_begin(vector_t* obj);
VertexNeighbor* vector_end(vector_t* obj);

bool vector_contains(vector_t* obj, VertexNeighbor v);