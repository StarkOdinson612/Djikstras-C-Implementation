#include "../include/vector.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

static const int DEFAULT_CAPACITY = 4;

vector_t* vector_new() { return (vector_t*)malloc(sizeof(vector_t)); }

void vector_ctr(vector_t* obj) {
    obj->elements = calloc(DEFAULT_CAPACITY, sizeof(VertexNeighbor));
    obj->capacity = DEFAULT_CAPACITY;
    obj->size = 0;
}

void vector_dtr(vector_t* obj) {
    free(obj->elements);
    free(obj);
}

uint16_t vector_size(vector_t* obj) { return obj->size; }
uint16_t vector_capacity(vector_t* obj) { return obj->capacity; }

void vector_push_back(vector_t* obj, VertexNeighbor element) {
    if (obj->size > 0 && obj->size % obj->capacity == 0) {
        obj->capacity = (obj->size / DEFAULT_CAPACITY + 1) * DEFAULT_CAPACITY;
        obj->elements =
            realloc(obj->elements, obj->capacity * sizeof(VertexNeighbor));

        if (obj->elements == NULL) {
            printf("Reallocation failed. Returning.");
            exit(1);
        }

        // printf("New Allocation: %d\n", obj->capacity);
    }

    obj->elements[obj->size++] = element;
}

void vector_pop_back(vector_t* obj) {
    int last_ind = obj->size - 1;
    obj->elements[last_ind] = VertexNeighbor_init(0, UNDEF);
    obj->size--;
}

void vector_erase(vector_t* obj, uint16_t first_ind, uint16_t last_ind) {
    assert(first_ind <= last_ind);

    VertexNeighbor* first = &obj->elements[0] + first_ind;
    VertexNeighbor* last =
        &obj->elements[0] + (last_ind < obj->size ? last_ind : obj->size - 1);
    uint16_t last_element = last - &obj->elements[0];
    uint16_t first_element = first - &obj->elements[0];

    for (int i = first_element; i < last_element; i++) {
        obj->elements[i] = obj->elements[i + 1];
    }

    if (last_element < obj->size - 1) {
        for (int i = last_element; i < obj->size - 1; i++) {
            obj->elements[i] = obj->elements[i + 1];
        }
    }

    obj->size -= (last - first) == 0 ? 1 : (last - first);
}

void vector_pop(vector_t* obj, uint16_t ind) {
    assert(ind >= 0 ? ind < obj->size : ind >= (-obj->size));

    vector_erase(obj, ind, ind);
}

VertexNeighbor vector_at(vector_t* obj, int index) {
    assert(index >= 0 ? index < obj->size : index >= -obj->size);

    return index >= 0 ? obj->elements[index] : obj->elements[index + obj->size];
}

VertexNeighbor* vector_begin(vector_t* obj) { return &obj->elements[0]; }

VertexNeighbor* vector_end(vector_t* obj) { return &obj->elements[obj->size]; }

bool vector_contains(vector_t* obj, VertexNeighbor v) {
    for (int i = 0; i < obj->size; i++) {
        if (vector_at(obj, i).id == v.id) {
            return true;
        }
    }

    return false;
}

void vector_reverse(vector_t* obj) {
    VertexNeighbor* start = &obj->elements[0];
    VertexNeighbor* end = &obj->elements[obj->size - 1];

    while (start < end) {
        VertexNeighbor temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void vector_print(vector_t* obj) {
    for (int i = 0; i < obj->size; i++) {
        VertexNeighbor v = vector_at(obj, i);

        if (v.dist == UNDEF) {
            printf("ID: %d, DIST: UNDEFINED\n", vector_at(obj, i).id,
                   vector_at(obj, i).dist);
            return;
        }

        if (v.dist == INFINITY) {
            printf("ID: %d, DIST: UNDEFINED\n", vector_at(obj, i).id,
                   vector_at(obj, i).dist);
            return;
        }

        if (v.dist == SELF) {
            printf("ID: %d, DIST: SELF\n", vector_at(obj, i).id,
                   vector_at(obj, i).dist);
            return;
        }

        printf("ID: %d, DIST: %d\n", vector_at(obj, i).id,
               vector_at(obj, i).dist);
    }
}