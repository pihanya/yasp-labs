#ifndef YASP_LAB_4_LLIST_H
#define YASP_LAB_4_LLIST_H

#include <stdio.h>
#include <malloc.h>

struct llist_t {
    int n;
    struct llist_t *next;
};

typedef struct llist_t item;

item *llist_create(int);

void llist_add_front(item **, item *);

void llist_add_back(item const *, item *);

void llist_free(item *);

int llist_get(item const *, size_t, int *);

item const *llist_node_at(item const *, size_t);

int llist_sum(item const *);

#endif //YASP_LAB_4_LLIST_H
