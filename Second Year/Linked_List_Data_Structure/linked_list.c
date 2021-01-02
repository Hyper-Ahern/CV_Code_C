#include <stdlib.h>
#include "linked_list.h"
#include "node_pool.h"

struct _list_t {
    node_t head;
    node_pool_t pool;
};

struct _node_t {
    void *item;
    node_t next;
};

list_t make_list() {
    list_t list = malloc(sizeof(struct _list_t));
    if (list) {
        list->head = NULL;
        list->pool = make_node_pool(sizeof(struct _node_t));
        if (!list->pool) {
            free(list);
            return NULL;
        }
    }
    return list;
}

void destroy_list(list_t list) {
    destroy_node_pool(list->pool);
    free(list);
}

node_t list_add(list_t list, void *item) {
    node_t node = request_node(list->pool);
    if (node) {
        node->item = item;
        node->next = list->head;
        list->head = node;
    }
    return node;
}

void *list_delete(list_t list, node_t node) {
    node_t prev = NULL, curr = list->head;
    void *item = node->item;
    while (curr != node) {
        prev = curr;
        curr = curr->next;
    }
    if (prev) {
        prev->next = node->next;
    } else {
        list->head = node->next;
    }
    release_node(list->pool, node);
    return item;
}

node_t list_head(list_t list) {
    return list->head;
}

void *node_value(node_t node) {
    return node->item;
}

node_t node_succ(node_t node) {
    return node->next;
}
