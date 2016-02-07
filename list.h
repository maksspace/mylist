// The MIT License (MIT)

// Copyright (c) 2016 Maks

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

#ifndef maksspace_list_h
#define maksspace_list_h

/* entry point in node */
#define LIST_LINK(type) struct type *prev, *next

typedef struct { void *prev, *next; } _node_link_t;

/* this macros through the list starting from the head while maintaining the current node in current */
#define list_foreach(type, current, head) \
for(type* current = head; current != NULL; current = current->next)

/* node init */
void list_node_init(void* node) {
    *(_node_link_t*)node = (_node_link_t){NULL, NULL};
}

/* insert node before head, and return pointer on new head of list */
void* list_prepend(void* node, void* head) {
    *(_node_link_t*)node = (_node_link_t){NULL, head};
    return ((_node_link_t*)head)->prev = node;
}

/* insert node after tail, and return pointer on new tail of list */
void* list_append(void* tail, void* node) {
    *(_node_link_t*)node = (_node_link_t){tail, NULL};
    return ((_node_link_t*)tail)->next = node;
}

/* insert new_node between prev and next, return pointer on new_node */
void* list_insert(void* new_node, void* prev, void* next) {
    *(_node_link_t*)new_node = (_node_link_t){prev, next};
    return ((_node_link_t*)prev)->next = ((_node_link_t*)next)->prev = new_node;
}

/* delete nodes between `from` and `to`. return a pointer to deleted nodes, or NULL if  betwen `from` and `to` is empty */
void* list_nodes_del(void* from, void* to) {
    if(((_node_link_t*)from)->next == to) return NULL;
    ((_node_link_t*)((_node_link_t*)to)->prev)->next = NULL;
    ((_node_link_t*)((_node_link_t*)from)->next)->prev = NULL;
    void* sub_list_ptr = ((_node_link_t*)from)->next;
    ((_node_link_t*)from)->next = to;
    ((_node_link_t*)to)->prev = from;
    return sub_list_ptr;
}

/* -----------------------------------
 * Each node of the list must contain:
 * struct node_name *prev, *next;
 * at the beginning.
 * -----------------------------------
 * Example:
 
 typedef struct your_node_name {
 struct your_node_name *prev, *next;
 int my_cool_int;
 float my_cool_float;
 ...
 strcut { ... } name;
 } some_node_name;
 */

#endif /* maksspace_list_h */

