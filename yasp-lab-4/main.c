#include <unistd.h>
#include "llist.h"

int main(int argc, char **argv) {
    int sum, num, err;
    size_t var;

    item *head = NULL;
    item const *node = NULL;

    printf("Type elements of list:\n");
    while (scanf("%d", &num) != 0) {
        llist_add_front(head, llist_create(num));
        sleep(1);
    }

    sum = llist_sum(head);
    printf("Sum of list elements is %d", sum);

    printf("Type variant: ");
    scanf("%zu", &var);

    node = llist_node_at(head, var);
    if (node != NULL) {
        printf("Node of llist #%zu is %d\n", var, node->n);
        printf("Type index: ");
    } else {
        printf("Out of llist index\n");
        printf("Type index: ");
    }

    scanf("%zu", &var);
    num = llist_get(head, var, &err);
    if (err != 1) {
        printf("llist[%lu]=%d\n", var, num);
    } else {
        printf("Out of index of linked list error!\n");
    }

    llist_free(head);
    printf("Allocated memory have been deallocated\n");

    return 0;
}

item const *llist_node_at(item const *head, size_t nth) {
    size_t size = 0;
    item const *cur = head;
    while (cur->next != NULL) {
        if (size == nth) {
            return cur;
        }
        cur = cur->next;
        size += 1;
    }
    if (size == nth) {
        return cur;
    }
    return NULL;
}

void llist_free(item *head) {
    item *cur = head;
    while ((cur = head) != NULL) {
        head = head->next;
        free(cur);
    }
}

int llist_sum(item const *head) {
    int s = 0;
    item const *cur = head;
    while (cur->next != NULL) {
        s += cur->n;
        cur = cur->next;
    }
    s += cur->n;
    return s;
}


// todo: rewrite code in such a way to make this method have a possibility add empty
void llist_add_back(item const *head, item *el) {
    item *cur = (void *) head;
    el->next = NULL;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = el;
}

void llist_add_front(item **head, item *el) {
    el->next = *head;
    *head = el;
}

item *llist_create(int n) {
    item *el = malloc(sizeof(item));
    el->n = n;
    el->next = NULL;
    return el;
}

int llist_get(item const *head, size_t index, int *err) {
    item const *cur = head;
    while (index--) {
        cur = cur->next;
        if (cur == NULL) {
            *err = 1;
            return 0;
        }
    }
    return cur->n;
}
