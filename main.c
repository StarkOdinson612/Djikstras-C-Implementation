#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/priority_queue.h"
#include "include/utils.h"
#include "include/vector.h"

vector_t *shortest_path(WeightedGraph *graph, size_t num_vertices,
                        uint16_t start_index, uint16_t end_index) {
    if (start_index == end_index) {
        vector_t *temp = vector_new();
        vector_ctr(temp);
        vector_push_back(temp, VertexNeighbor_init(start_index, 0));

        return temp;
    }

    VertexNeighbor prev[NUM_VERTICES] = {};
    VertexNeighbor distances[NUM_VERTICES] = {};

    for (int i = 0; i < num_vertices; i++) {
        if (i == start_index - 1) {
            distances[i] = VertexNeighbor_init(i + 1, 0);
            prev[i] = VertexNeighbor_init(i + 1, 0);
            continue;
        }
        distances[i] = VertexNeighbor_init(i + 1, INFINITY);
        prev[i] = VertexNeighbor_init(i + 1, UNDEF);
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
        VertexNeighbor this_neighbors[NUM_VERTICES];
        memcpy(this_neighbors, graph[0][current.id - 1].neighbors,
               sizeof(this_neighbors));

        for (int i = 0; i < NUM_VERTICES; i++) {
            if (this_neighbors[i].dist == SELF ||
                this_neighbors[i].dist == UNDEF) {
                continue;
            }

            int16_t tentative_dist =
                distances[current.id - 1].dist + this_neighbors[i].dist;

            if (tentative_dist < distances[i].dist) {
                distances[i].dist = tentative_dist;
                prev[i] = VertexNeighbor_init(current.id, distances[i].dist);
                enqueue(&p_queue, VertexNeighbor_init(i + 1, distances[i].dist));
            }
        }
    }

    vector_dtr(visited);

    printf("Distances: \n");
    for (int i = 0; i < NUM_VERTICES; i++) {
        printf("ID: %d, DIST: %d\n", distances[i].id, distances[i].dist);
    }

    printf("\n");

    vector_t *ret = vector_new();
    vector_ctr(ret);

    uint16_t curr_ind = end_index - 1;

    if (distances[end_index - 1].dist == INFINITY) {
        vector_push_back(ret, VertexNeighbor_init(end_index, UNDEF));

        return ret;
    }

    if (prev[curr_ind].dist != UNDEF || curr_ind == start_index - 1) {
        while (prev[curr_ind].dist != 0) {
            vector_push_back(
                ret, VertexNeighbor_init(prev[curr_ind].id,
                                         distances[prev[curr_ind].id - 1].dist));
            curr_ind = prev[curr_ind].id - 1;
        }
    }

    vector_reverse(ret);

    vector_push_back(
        ret, VertexNeighbor_init(end_index, distances[end_index - 1].dist));

    return ret;
}

int main(void) {
    VertexNeighbor bits[NUM_VERTICES][NUM_VERTICES] = {
        {{1, SELF}, {2, 4}, {3, UNDEF}, {4, UNDEF}, {5, UNDEF}, {6, UNDEF}, {7, UNDEF}, {8, 8}, {9, UNDEF}},
        {{1, 4}, {2, SELF}, {3, 8}, {4, UNDEF}, {5, UNDEF}, {6, UNDEF}, {7, UNDEF}, {8, 11}, {9, UNDEF}},
        {{1, UNDEF}, {2, 8}, {3, SELF}, {4, 7}, {5, 4}, {6, UNDEF}, {7, UNDEF}, {8, UNDEF}, {9, 2}},
        {{1, UNDEF}, {2, UNDEF}, {3, UNDEF}, {4, SELF}, {5, UNDEF}, {6, UNDEF}, {7, UNDEF}, {8, UNDEF}, {9, UNDEF}},
        {{1, UNDEF}, {2, UNDEF}, {3, UNDEF}, {4, UNDEF}, {5, SELF}, {6, UNDEF}, {7, UNDEF}, {8, UNDEF}, {9, UNDEF}},
        {{1, UNDEF}, {2, UNDEF}, {3, UNDEF}, {4, UNDEF}, {5, UNDEF}, {6, SELF}, {7, UNDEF}, {8, UNDEF}, {9, UNDEF}},
        {{1, UNDEF}, {2, UNDEF}, {3, UNDEF}, {4, UNDEF}, {5, UNDEF}, {6, UNDEF}, {7, SELF}, {8, UNDEF}, {9, UNDEF}},
        {{1, UNDEF}, {2, UNDEF}, {3, UNDEF}, {4, UNDEF}, {5, UNDEF}, {6, UNDEF}, {7, UNDEF}, {8, SELF}, {9, UNDEF}},
        {{1, UNDEF}, {2, UNDEF}, {3, UNDEF}, {4, UNDEF}, {5, UNDEF}, {6, UNDEF}, {7, UNDEF}, {8, UNDEF}, {9, SELF}}};

    WeightedGraph graph = {
        WeightedGraphVertex_init(1, bits[0]), WeightedGraphVertex_init(2, bits[1]),
        WeightedGraphVertex_init(3, bits[2]), WeightedGraphVertex_init(4, bits[3]),
        WeightedGraphVertex_init(5, bits[4]), WeightedGraphVertex_init(6, bits[5])};

    vector_t *bob = shortest_path(&graph, NUM_VERTICES, 1, 6);

    vector_print(bob);

    vector_dtr(bob);

    return 0;
}
