#include <malloc.h>
#include <memory.h>
#include <stdio.h>

#include "include/utils.h"
#include "include/priority_queue.h"
#include "include/vector.h"

uint16_t *shortest_path(WeightedGraph *graph, size_t num_vertices,
                        uint16_t start_index, uint16_t end_index) {
    if (start_index == end_index) {
        uint16_t *arr = (uint16_t *)malloc(sizeof(uint16_t));
        arr[0] = start_index;

        return arr;
    }

    VertexNeighbor distances[MAX_VERTICES] = {};

    for (int i = 0; i < num_vertices; i++) {
        if (i == start_index - 1) {
            distances[i] = VertexNeighbor_init(i + 1, 0);
            continue;
        }
        distances[i] = VertexNeighbor_init(i + 1, INFINITY);
    }

    vector_t *visited = vector_new();
    vector_ctr(visited);

    PriorityQueue p_queue = {{}, 0};
    enqueue(&p_queue, VertexNeighbor_init(start_index, 0));

    while (p_queue.size > 0) {
        VertexNeighbor current = dequeue(&p_queue);

        if (vector_contains(visited, current)) {
            continue;
        }

        vector_push_back(visited, current);
        VertexNeighbor this_neighbors[MAX_VERTICES];
        memcpy(this_neighbors, graph[0][current.id - 1].neighbors,
               sizeof(this_neighbors));

        for (int i = 0; i < MAX_VERTICES; i++) {
            if (this_neighbors[i].dist == SELF ||
                this_neighbors[i].dist == UNDEFINED) {
                continue;
            }

            int16_t tentative_dist =
                distances[current.id - 1].dist + this_neighbors[i].dist;

            if (tentative_dist < distances[i].dist) {
                distances[i].dist = tentative_dist;
                enqueue(&p_queue, VertexNeighbor_init(i + 1, distances[i].dist));
            }
        }
    }

    vector_dtr(not_queue);
    vector_dtr(visited);

    uint16_t *arr = (uint16_t *)malloc(sizeof(uint16_t) * MAX_VERTICES);

    for (int i = 0; i < MAX_VERTICES; i++) {
        arr[i] = distances[i].dist;
    }

    return arr;
}

int main(void) {
    VertexNeighbor one[MAX_VERTICES] = {
        {1, SELF}, {2, 1}, {3, UNDEFINED}, {4, 2}};

    VertexNeighbor two[MAX_VERTICES] = {
        {1, 1}, {2, SELF}, {3, 5}, {4, UNDEFINED}};

    VertexNeighbor three[MAX_VERTICES] = {{1, 3}, {2, 1}, {3, SELF}, {4, 3}};

    VertexNeighbor four[MAX_VERTICES] = {
        {1, UNDEFINED}, {2, 5}, {3, 5}, {4, SELF}};

    WeightedGraph graph = {
        WeightedGraphVertex_init(1, one), WeightedGraphVertex_init(2, two),
        WeightedGraphVertex_init(3, three), WeightedGraphVertex_init(4, four)};

    uint16_t *bob = shortest_path(&graph, 4, 1, 4);

    for (int i = 0; i < MAX_VERTICES; i++) {
        printf("%d - Distance: %d\n", i + 1, bob[i]);
    }

    free(bob);

    return 0;
}
