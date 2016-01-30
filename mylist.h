//
// Created by maksspace on 30.01.16.
//

#include <stdint.h>

#ifndef MAKSSPACE_MYLIST_H
#define MAKSSPACE_MYLIST_H

//  Doubly linked list implementation by maksspace

#ifdef __cplusplus
extern "C" {
#endif

struct mylist {
    struct mylist* next;
    struct mylist* prev;
};
    
#define MYLIST_FREE free

#define MYLIST_GET_STRUCT(type, ptr) \
    ((type*)((size_t)(ptr) - ((size_t)(&((type*)0)->__list_link__))))

#define MYLIST_HEAD_NEW(name) \
    struct mylist name = {&(name), &(name)}

#define MYLIST_LINK_INIT(list) \
    ((list)->__list_link__.next = (list)->__list_link__.prev = NULL)

// ----------------------------------------------------------------------------
#define MYLIST_FOREACH(type, head, count)                                   \
    {                                                                       \
    struct mylist * __current_list_ptr__ = (head)->next;                    \
    type * __current_struct_ptr__ = NULL;                                   \
    for(size_t __i__ = 0; __i__ < (count); __i__++) {                       \
    __current_struct_ptr__ =  MYLIST_GET_STRUCT(type, __current_list_ptr__);

    /* do something */

#define MYLIST_FOREACH_END                     \
    __current_list_ptr__ = __current_list_ptr__->next; \
    }};
// ----------------------------------------------------------------------------

#define mylist_free(type, head, count)                              \
    {                                                               \
    struct mylist * __current_list_ptr__ = (head)->next;            \
    for(size_t __i__ = 0; __i__ < (count); __i__++) {               \
    struct mylist * __next_list_ptr__ = __current_list_ptr__->next; \
    MYLIST_FREE(MYLIST_GET_STRUCT(type, __current_list_ptr__));     \
    __current_list_ptr__ = __next_list_ptr__;                       \
    }};

void mylist_insert(struct mylist* new, struct mylist* prev, struct mylist* next) {
    next->prev = new;
    new->next  = next;
    new->prev  = prev;
    prev->next = new;
}

void mylist_delete(struct mylist* prev, struct mylist* next) {
    prev->next = next;
    next->prev = prev;
}

void mylist_prepend(struct mylist* new, struct mylist* head) {
    mylist_insert(new, head, head->next);
}

void mylist_append(struct mylist* new, struct mylist* tail) {
    tail->next = new;
    new->prev = tail;
    new->next = new;
}

void mylist_delete_node(struct mylist* node) {
    mylist_delete(node->prev, node->next);
    node->next = node->prev = NULL;
}
    
#ifdef __cplusplus
}
#endif
#endif // MYLIST_H
