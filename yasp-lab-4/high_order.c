#include "llist.h"

void llist_foreach(void (*fun_ptr)(int), item const *head) {
    item *cur = (void *) head;
    while (cur->next != NULL) {
        fun_ptr(cur->n);
        cur = cur->next;
    }
}

item *llist_map(int (*map_fun)(int), item const *head) {
    item const *cur = head;
    item *new_head = llist_create(head->n);

    new_head->n = map_fun(head->n);

    while ((cur = cur->next)) {
        llist_add_front(&new_head, llist_create(map_fun(cur->n)));
    }

    return new_head;
}

item const *llist_map_mut(int (*fun_ptr)(int), item const *head) {
    item *cur = (void *) head;
    while (cur->next != NULL) {
        cur->n = fun_ptr(cur->n);
        cur = cur->next;
    }
    return head;
}

int llist_foldl(int acc, int (*fun_ptr)(int, int), item const *head) {
    if (head == NULL) {
        return acc;
    }

    item *cur = (void *) head;
    return llist_foldl(fun_ptr(acc, cur->n), fun_ptr, head->next);
}