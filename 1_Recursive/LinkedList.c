#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node *next;
} node_t;

node_t *head = NULL;
node_t *tail = NULL;

void insert_node(int n)
{
    node_t *new_node = (node_t*) malloc(sizeof(node_t));

    new_node->key = n;
    new_node->next = NULL;

    if (head == NULL) {
        head = new_node;
        tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}

int delete_node(void)
{
    node_t *node;
    int r;

    if (head == NULL)
        return -1;

    node = head;
    head = head->next;
    if (head == NULL)
        tail = NULL;

    r = node->key;
    free(node);
    return r;
}

void print_list(node_t *from)
{
    node_t *node;

    node = from;
    while (node != NULL) {
        printf("%d ", node->key);
        node = node->next;
    }
}

void print_list2(node_t *from)
{
    if (from == NULL)
        return;
    printf("%d ", from->key);
    print_list2(from->next);
}

int main(void)
{
    int temp;
    while (1) {
        printf("input number: ");
        scanf("%d", &temp);
        if (temp == 0) {
            printf("[%d]\n", delete_node());
        } else if (temp == -1) {
            print_list2(head);
            break;
        } else
            insert_node(temp);
    }
    return 0;
}
