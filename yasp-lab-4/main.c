#include "high_order.h"

void print_number(int num) {
    printf("%d\n", num);
}

int main(int argc, char **argv) {
    int num;
    size_t index;

    item *head = NULL;
    item const *node = NULL;

    printf("Type elements of list:\n");
    while (scanf("%d", &num)) {
        llist_add_front(&head, llist_create(num));
    }

    printf("[Sum of list elements is %d]\n", llist_sum(head));

    printf("[Printing result of execution foreach higher order function]\n");
    llist_foreach( print_number, head );

    printf("Element selection. Please, type index of list element to get:\n");
    scanf("%zu", &index);

    printf("[Index of element to get: %zu]\n", index);
    node = llist_node_at(head, index);
    if (node != NULL) {
        printf("Element at index %zu is %d]\n", index, node->n);
    } else {
        printf("[Out of llist index]\n");
    }

    llist_free(head);
    printf("[Allocated memory has been deallocated]\n");

    return 0;
}