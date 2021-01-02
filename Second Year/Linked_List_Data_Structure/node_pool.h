#ifndef NODE_POOL_H
#define NODE_POOL_H

typedef struct _node_pool_t *node_pool_t;

node_pool_t make_node_pool(size_t);
void destroy_node_pool(node_pool_t);

void *request_node(node_pool_t);
void release_node(node_pool_t, void *);

#endif
