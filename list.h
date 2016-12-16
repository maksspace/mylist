// The MIT License (MIT)

// Copyright (c) 2016 Maksim Smagin

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// ---------------------------------------------- //
// Doubly linked list implementation by maksspace //
// ---------------------------------------------- //

#ifndef maksspace_mylist_h
#define maksspace_mylist_h

// Common macros (Don't use it in your code)
#ifdef __GNUC__
    #define _ptr_to(t) typeof(t *)
#endif

// Entry point in node
#define LIST_LINK(type) struct type *prev, *next

typedef struct {
    void *prev,
         *next; 
} _node_link_t;

// List iterator
typedef struct {
    void* current;
} list_iter_t;

// This macros through the list starting from the head while maintaining the current node in current
#ifdef __GNUC__
    #define list_foreach(current, head) \
        for(_ptr_to(head) current = head; current != NULL; current = current->next)
#else
    #define list_foreach(type, current, head) \
        for(type * current = head; current != NULL; current = current->next)
#endif

// Node init
void list_node_init(void* node) {
    *(_node_link_t*)node = (_node_link_t){NULL, NULL};
}

// Iterator init
void list_iter_init(list_iter_t* iter, void* current) {
    iter->current = current;
}

// Return pointer to next and previous nodes respectively
void* list_iter_next(list_iter_t* iter) {
    if(iter->current != NULL)
        return iter->current = ((_node_link_t*)iter->current)->next;
    else return NULL;
}

void* list_iter_prev(list_iter_t* iter) {
    if(iter->current != NULL)
        return iter->current = ((_node_link_t*)iter->current)->prev;
    else return NULL;
}

// Insert node before head, and return pointer on new head of list
void* list_prepend(void* node, void* head) {
    *(_node_link_t*)node = (_node_link_t){NULL, head};
    return ((_node_link_t*)head)->prev = node;
}

// Insert node after tail, and return pointer on new tail of list
void* list_append(void* tail, void* node) {
    *(_node_link_t*)node = (_node_link_t){tail, NULL};
    return ((_node_link_t*)tail)->next = node;
}

// Insert new_node between prev and next, return pointer on new_node
void* list_insert(void* new_node, void* prev, void* next) {
    *(_node_link_t*)new_node = (_node_link_t){prev, next};
    return ((_node_link_t*)prev)->next = ((_node_link_t*)next)->prev = new_node;
}

// Delete nodes between `from` and `to`. return a pointer to deleted nodes, or NULL if  betwen `from` and `to` is empty
void* list_nodes_del(void* from, void* to) {
    if(((_node_link_t*)from)->next == to) return NULL;
    ((_node_link_t*)((_node_link_t*)to)->prev)->next = NULL;
    ((_node_link_t*)((_node_link_t*)from)->next)->prev = NULL;
    void* sub_list_ptr = ((_node_link_t*)from)->next;
    ((_node_link_t*)from)->next = to;
    ((_node_link_t*)to)->prev = from;
    return sub_list_ptr;
}

// Delete all nodes from list, starting from the 'head', using 'free_data' and 'free_node' function for free memory
#ifdef __GNUC__
    #define list_del(head, free_data, free_node) {     \
                _ptr_to(head) current = (head), *next;       \
                while(current != NULL) {                     \
                next = current->next;                        \
                free_data(current);                          \
                free_node(current);                          \
                current = next;                              \
            }                                                \
            };
#else
    #define list_del(type, head, free_data, free_node) {     \
                type * current = (head), *next;       \
                while(current != NULL) {                     \
                next = current->next;                        \
                free_data(current);                          \
                free_node(current);                          \
                current = next;                              \
            }                                                \
            };
#endif

// Same as list_del, but only data node will freed
#ifdef __GNUC__
    #define list_del_static(head, free_node) {     \
        _ptr_to(head) current = (head), *next;                   \
        while(current != NULL) {                         \
            next = current->next;                        \
            free_node(current);                          \
            current = next;                              \
        }                                                \
    };
#else
    #define list_del_static(type, head, free_node) {     \
        type* current = (head), *next;                   \
        while(current != NULL) {                         \
            next = current->next;                        \
            free_node(current);                          \
            current = next;                              \
        }                                                \
    };
#endif

#endif /* maksspace_mylist_h */

