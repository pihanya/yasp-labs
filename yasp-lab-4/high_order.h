#ifndef YASP_LAB_4_HIGH_ORDER_H
#define YASP_LAB_4_HIGH_ORDER_H

#include "llist.h"

void llist_foreach(void (*fun_ptr)(int), item const *head);

item *llist_map(int (*map_fun)(int), item const *head);

item *llist_map_mut(int (*fun_ptr)(int), item const *head);

int llist_foldl(int acc, int (*fun_ptr)(int, int), item const *head);

#endif //YASP_LAB_4_HIGH_ORDER_H