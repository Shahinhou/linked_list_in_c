#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {

    struct Node *next;
    struct Node *prev;
    int val;
};

typedef struct Node Node;

void add(Node *node, int n){

    if (node->next == NULL){
        Node *tmp = (Node*)malloc(1*sizeof(Node));
        tmp->val = n;
        tmp->next = NULL;

        tmp->prev = node;
        node->next = tmp;
        return;
    }

    add(node->next, n);
}

void pop(Node *node){

    if (node->prev != NULL){
        node->prev->next = node->next;
    }
    if (node->next != NULL){
        node->next->prev = node->prev;
    }
    free(node);
}

void free_nodes(Node *node){

    if (node->next != NULL){
        free_nodes(node->next);
    }
    free(node);
}

void print_nodes(Node *node){

    printf("%d\n", node->val);
    if (node->next != NULL){
        print_nodes(node->next);
    }
}

Node* linked_list_from_argv(char **str, int size){
    // this is calibrated for an argv string.
    Node* head = (Node*)malloc(1*sizeof(Node));
    head->val = atoi(*(str+1));
    head->next = NULL;
    head->prev = NULL;

    for (int i = 2; i < size; i++){
        add(head, atoi(*(str+i)));
    }

    return head;
}

void linked_list_from_nums(int *nums, int size, Node *head){

    head = (Node*)malloc(1*sizeof(Node));
    head->val = *(nums+0);
    head->next = NULL;
    head->prev = NULL;

    for (int i = 1; i < size; i++){
        add(head, *(nums+i));
    }
}

Node* search(Node *node, int target){

    if (node == NULL){
        return NULL;
    }

    if (node->val == target){
        return node;
    }

    return search(node->next, target);
}

// This is just main down here. REMOVE WHEN IMPORTING USING :r

int main(int argc, char *argv[]){

    Node *head = linked_list_from_argv(argv, argc);
    int n;

    printf("search list for:\n");
    //print_nodes(head);
    scanf("%d", &n);

    Node *tmp = search(head, n);
    if (tmp != NULL){
        printf("%d\n", tmp->val);
    }
    else {
        printf("Not found\n");
    }

    free_nodes(head);
    return 0;
}

