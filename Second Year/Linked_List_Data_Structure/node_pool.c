#include <stdlib.h>
#include "node_pool.h"

#define CHUNK_SIZE 1024

struct _chunk_t {
    struct _chunk_t *next;
};

typedef struct _chunk_t chunk_t;

struct _node_pool_t {
    size_t slot_size;
    chunk_t *chunks;
    chunk_t *slots;
};

node_pool_t make_node_pool(size_t node_size) {
    node_pool_t node_pool = malloc(sizeof(struct _node_pool_t));
    if (node_pool) {
        node_pool->slot_size = node_size < sizeof(chunk_t *) ? sizeof(chunk_t *) : node_size;
        node_pool->chunks = NULL;
        node_pool->slots = NULL;
    }
    return node_pool;
}

void destroy_node_pool(node_pool_t node_pool) {
    chunk_t *chunk = node_pool->chunks, *next;
    while (chunk) {
        next = chunk->next;
        free(chunk);
        chunk = next;
    }
    free(node_pool);
}

void make_chunk(node_pool_t node_pool) {
    union {
        chunk_t *chunk;
        char *bytes;
    } ptr;
    ptr.chunk = malloc(CHUNK_SIZE * node_pool->slot_size);
    if (ptr.chunk) {
        ptr.chunk->next = node_pool->chunks;
        node_pool->chunks = ptr.chunk;
        ptr.bytes += node_pool->slot_size;
        chunk_t *next = node_pool->slots;
        for (int i = 0; i < CHUNK_SIZE - 1; ++i) {
            ptr.chunk->next = next;
            next = ptr.chunk;
            ptr.bytes += node_pool->slot_size;
        }
        node_pool->slots = next;
    }
}

void *request_node(node_pool_t node_pool) {
    if (!node_pool->slots) {
        make_chunk(node_pool);
    }
    if (!node_pool->slots) {
        return NULL;
    }
    chunk_t *slot = node_pool->slots;
    node_pool->slots = slot->next;
    return slot;
}

void release_node(node_pool_t node_pool, void *node) {
    chunk_t *slot = node;
    slot->next = node_pool->slots;
    node_pool->slots = slot;
}
