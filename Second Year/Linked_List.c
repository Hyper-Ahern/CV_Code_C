#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node {
char value[100];
struct node *next;
} ;
struct node *head = NULL;
struct node *tail = NULL;

void make_list() {

  // Allocating memory
  struct node *newStruct = (struct node *) malloc(sizeof(struct node));
  (*newStruct).next = NULL;
  printf("?");
  scanf("%s", &(newStruct)->value);
  head = tail = newStruct;
  }

struct node node_succ(node){

  //return node->next;
}

struct node list_head(){

  return *head;
}

void inputData(){

  //If head is null, make a new list. Otherwise a list exists.
  if(head == NULL){
    make_list();
  } else {
    struct node *newStruct = (struct node *) malloc(sizeof(struct node));
    printf("?");
    scanf("%s", &(newStruct)->value);

    // Second node
    if(head == tail){
      (*head).next = newStruct;
      tail = newStruct;
      (*newStruct).next = NULL;

    //Any Other Scenario, add the node to the end of the list
    } else {
      (*tail).next = newStruct;
      (*newStruct).next = NULL;
      tail = newStruct;
    }
  }
}

void destroy_list(){

   head->next = NULL;
}

// Used for printing while testing my code
void printTest(){
  struct node *allNodes = head;

  //Once the pointer is at null, we have hit the last node
  while(allNodes != NULL){
    printf("%s\n", allNodes->value);
    allNodes  = allNodes->next;
  }
}

void list_add(){

}

void list_delete(){

}

void node_value(){

}

int main(){

  //Need to put this in a loop to gather data until user stops...
  inputData();
  printTest();
  return 0;
}


// Although I never had time to finish due to finals, I wanted to be safe and
// say that the Code was influenced by https://www.youtube.com/watch?v=PYzqi0eOxIg&t=11s
// which helped me understand how to start this.
