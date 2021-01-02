#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

int prefix_strcmp(const char *key, const char *val) {
    return strncmp(key, val, strlen(key));
}

int main() {
    list_t list = make_list();
    if (!list) {
        printf("ERROR ALLOCATING TREE\n");
        return 1;
    }
    int quit = 0;
    size_t line_cap = 0;
    char *input = NULL;
    while (!quit) {
        printf("? ");
        int num_chars = getline(&input, &line_cap, stdin);
        if (num_chars < 0) {
            quit = 1;
        } else if (num_chars < 2) {
            printf("INVALID INPUT\n");
        } else if (input[0] == 'a') {
            if (num_chars < 4 || input[1] != ' ') {
                printf("INVALID INPUT\n");
            } else {
                size_t len = strlen(input);
                char *string = malloc(len - 2);
                input[len - 1] = 0;
                if (string) {
                    strcpy(string, input + 2);
                    list_add(list, string);
                }
            }
        } else if (input[0] == 'd') {
            if (num_chars < 4 || input[1] != ' ') {
                printf("INVALID INPUT\n");
            } else {
                input[strlen(input) - 1] = 0;
                size_t n = strlen(input + 2);
                node_t node = list_head(list);
                while (node) {
                    char *item = node_value(node);
                    if (strncmp(item, input + 2, n) == 0) {
                        break;
                    }
                    node = node_succ(node);
                }
                if (node) {
                    free(list_delete(list, node));
                } else {
                    printf("STRING NOT FOUND\n");
                }
            }
        } else if (input[0] == 'f') {
            if (num_chars < 4 || input[1] != ' ') {
                printf("INVALID INPUT\n");
            } else {
                input[strlen(input) - 1] = 0;
                size_t n = strlen(input + 2);
                node_t node = list_head(list);
                while (node) {
                    char *item = node_value(node);
                    if (strncmp(item, input + 2, n) == 0) {
                        break;
                    }
                    node = node_succ(node);
                }
                if (node) {
                    printf("%s\n", (char *) node_value(node));
                } else {
                    printf("STRING NOT FOUND\n");
                }
            }
        } else if (input[0] == 'l') {
            node_t node = list_head(list);
            while (node) {
                char *item = node_value(node);
                printf("%s\n", item);
                node = node_succ(node);
            }
        } else if (input[0] == 'q') {
            quit = 1;
        } else {
            printf("INVALID INPUT\n");
        }
    }
    if (input) {
        free(input);
    }
    node_t node = list_head(list);
    while (node) {
        free(node_value(node));
        node = node_succ(node);
    }
    destroy_list(list);
    return 0;
}
