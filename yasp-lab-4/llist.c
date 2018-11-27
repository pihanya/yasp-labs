#include "llist.h"

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
    item *cur;
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
    item *list = malloc(sizeof(item));
    if (list) {
        list->n = n;
        list->next = NULL;
        return list;
    } else {
        return NULL;
    }
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