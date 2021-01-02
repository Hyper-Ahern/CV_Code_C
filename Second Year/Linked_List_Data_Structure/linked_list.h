#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct _list_t *list_t;
typedef struct _node_t *node_t;

list_t make_list();
void destroy_list(list_t);

node_t list_add(list_t, void *);
void *list_delete(list_t, node_t);

node_t list_head(list_t);

void *node_value(node_t);

node_t node_succ(node_t);

#endif // LINKED_LIST_H
