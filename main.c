#include <assert.h>
#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/priority_queue.h"
#include "include/utils.h"
#include "include/vector.h"

vector_t *shortest_path_djikstra(WeightedGraph *graph, size_t num_vertices,
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
        distances[i] = VertexNeighbor_init(i + 1, F_INFINITY);
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

            float tentative_dist =
                distances[current.id - 1].dist + this_neighbors[i].dist;

            if (tentative_dist < distances[i].dist) {
                distances[i].dist = tentative_dist;
                distances[i].r_dist = tentative_dist;
                prev[i] = VertexNeighbor_init(current.id, distances[i].dist);
                enqueue(&p_queue, VertexNeighbor_init(i + 1, distances[i].dist));
            }
        }
    }

    vector_dtr(visited);

    printf("Distances: \n");
    for (int i = 0; i < NUM_VERTICES; i++) {
        printf("ID: %d, DIST: %.2f\n", distances[i].id, distances[i].r_dist);
    }

    printf("\n");

    vector_t *ret = vector_new();
    vector_ctr(ret);

    uint16_t curr_ind = end_index - 1;

    if (distances[end_index - 1].dist == F_INFINITY) {
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

int main(int argc, char *argv[]) {
    assert(argc == 3);
    assert(is_number(argv[1]));
    assert(is_number(argv[2]));

    int start_index = atoi(argv[1]);
    int end_index = atoi(argv[2]);

    assert(start_index >= 1 && end_index <= NUM_VERTICES);

    VertexNeighbor v = VertexNeighbor_init(1, 1);

    VertexNeighbor bits[NUM_VERTICES][NUM_VERTICES] = {
        {{1, SELF}, {2, 4}, {3, UNDEF}, {4, UNDEF}, {5, UNDEF}, {6, UNDEF}, {7, UNDEF}, {8, 8}, {9, UNDEF}},
        {{1, 4}, {2, SELF}, {3, 8}, {4, UNDEF}, {5, UNDEF}, {6, UNDEF}, {7, UNDEF}, {8, 11}, {9, UNDEF}},
        {{1, UNDEF}, {2, 8}, {3, SELF}, {4, 7}, {5, 4}, {6, UNDEF}, {7, UNDEF}, {8, UNDEF}, {9, 2}},
        {{1, UNDEF}, {2, UNDEF}, {3, 7}, {4, SELF}, {5, 9}, {6, 14}, {7, UNDEF}, {8, UNDEF}, {9, UNDEF}},
        {{1, UNDEF}, {2, UNDEF}, {3, UNDEF}, {4, 9}, {5, SELF}, {6, 10}, {7, UNDEF}, {8, UNDEF}, {9, UNDEF}},
        {{1, UNDEF}, {2, UNDEF}, {3, 4}, {4, 14}, {5, 10}, {6, SELF}, {7, 2}, {8, UNDEF}, {9, UNDEF}},
        {{1, UNDEF}, {2, UNDEF}, {3, UNDEF}, {4, UNDEF}, {5, UNDEF}, {6, 2}, {7, SELF}, {8, 1}, {9, 6}},
        {{1, 8}, {2, 11}, {3, UNDEF}, {4, UNDEF}, {5, UNDEF}, {6, UNDEF}, {7, 1}, {8, SELF}, {9, 7}},
        {{1, UNDEF}, {2, UNDEF}, {3, 2}, {4, UNDEF}, {5, UNDEF}, {6, UNDEF}, {7, 6}, {8, 7}, {9, SELF}}};

    WeightedGraph graph = {
        WeightedGraphVertex_init(1, bits[0]), WeightedGraphVertex_init(2, bits[1]),
        WeightedGraphVertex_init(3, bits[2]), WeightedGraphVertex_init(4, bits[3]),
        WeightedGraphVertex_init(5, bits[4]), WeightedGraphVertex_init(6, bits[5]),
        WeightedGraphVertex_init(7, bits[6]), WeightedGraphVertex_init(8, bits[7]),
        WeightedGraphVertex_init(9, bits[8])};

    vector_t *bob = shortest_path_djikstra(&graph, NUM_VERTICES, start_index, end_index);

    vector_print(bob);

    vector_dtr(bob);

    return 0;
}
