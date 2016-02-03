// ---------------------------------------------- //
// Doubly linked list implementation by maksspace //
// ---------------------------------------------- //

#ifndef maksspace_list_h
#define maksspace_list_h

typedef struct { void *prev, *next; } node_link_t;

/* this macros through the list starting from the $head while maintaining the current node in $current */
#define list_foreach(head, current) \
    for(typeof(head) current = head; current != NULL; current = current->next)

/* insert $node before $head, and return pointer on new head of list */
void* list_prepend(void* node, void* head) {
    *(node_link_t*)node = (node_link_t){NULL, head};
    return ((node_link_t*)head)->prev = node;
}

/* insert $node after $tail, and return pointer on new tail of list */
void* list_append(void* tail, void* node) {
    *(node_link_t*)node = (node_link_t){tail, NULL};
    return ((node_link_t*)tail)->next = node;
}

/* insert $new_node between $prev and $next, return pointer on $new_node */
void* list_insert(void* new_node, void* prev, void* next) {
    *(node_link_t*)new_node = (node_link_t){prev, next};
    return ((node_link_t*)prev)->next = ((node_link_t*)next)->prev = new_node;
}

/* delete nodes between $from and $to */
void list_nodes_del(void* from, void* to) {
    ((node_link_t*)from)->next = to;
    ((node_link_t*)to)->prev = from;
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
