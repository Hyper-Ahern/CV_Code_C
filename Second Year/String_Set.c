#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
int prefix_strcmp(const char *key, const char *val) {
  return strncmp(key, val, strlen(key));
}
int main() {
  tree_t tree = make_tree((cmp_t) strcmp, (key_cmp_t) prefix_strcmp);
  if (!tree) {
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
	  tree_insert(tree, string);
	}
      }
    } else if (input[0] == 'd') {
      if (num_chars < 4 || input[1] != ' ') {
	printf("INVALID INPUT\n");
      } else {
	input[strlen(input) - 1] = 0;
	node_t node = tree_find(tree, input + 2);
	if (node) {
	  free(tree_delete(tree, node));
	} else {
	  printf("STRING NOT FOUND\n");
	}
      }
    } else if (input[0] == 'f') {
      if (num_chars < 4 || input[1] != ' ') {
	printf("INVALID INPUT\n");
      } else {
	input[strlen(input) - 1] = 0;
	node_t node = tree_find(tree, input + 2);
	if (node) {
	  printf("%s\n", (char *) node_value(node));
	} else {
	  printf("STRING NOT FOUND\n");
	}
      }
    } else if (input[0] == 'l') {
      iter_t iter = make_iterator(tree);
      if (iter) {
	char *string;
	while ((string = iter_next(iter))) {
	  printf("%s\n", string);
	}
	destroy_iterator(iter);
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
  iter_t iter = make_iterator(tree);
  if (iter) {
    void *string;
    while ((string = iter_next(iter))) {
      free(string);
    }
    destroy_iterator(iter);
  }
  destroy_tree(tree);
  return 0;
}
