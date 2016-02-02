// ---------------------------------------------- //
// Doubly linked list implementation by maksspace //
// ---------------------------------------------- //

#include <stdint.h>

#ifndef maksspace_list_h
#define maksspace_list_h

#define LIST_NODE(type) \
    struct {            \
        size_t next;    \
        size_t prev;    \
        type data;      \
    }

#define NEXT_NODE_PTR(size_t_name)               *((size_t*)(size_t_name))                                             // return pointer to next node
#define PREV_NODE_PTR(size_t_name)               *(((size_t*)(size_t_name)) + 1)                                       // return pointer to previous node
#define LIST_NODE_TYPE_NEW(type, name)           typedef LIST_NODE(type) name                                          // creates a node type "name" with the type data field == "type"
#define NODE_LINK_INIT(name, next_val, prev_val) {NEXT_NODE_PTR(name) = (next_val); PREV_NODE_PTR(name) = (prev_val);} // initializes node's link
#define LIST_NODE_VAL(type, node_ptr)            ((type*)(node_ptr))                                                   // return pointer to node type == "type"
#define LIST_ITER(ptr)                           (size_t)(ptr)                                                         // create list iterator

// allocate new node and return pointer on him
void* list_node_new(size_t sizeof_node, void*(node_allocator)(size_t))
{
    void* new_node = node_allocator(sizeof_node);
    if(new_node != NULL)
        NODE_LINK_INIT(new_node, 0, 0);
    return new_node;
}

// insert new_node betwin prev_node and next_node
void list_insert(size_t new_node, size_t prev_node, size_t next_node)
{
    if(next_node == 0) {
        NEXT_NODE_PTR(prev_node) = new_node;
        PREV_NODE_PTR(new_node) = prev_node;
        NEXT_NODE_PTR(new_node) = 0;
    }
    else {
        PREV_NODE_PTR(next_node) = new_node;
        NEXT_NODE_PTR(new_node)  = next_node;
        PREV_NODE_PTR(new_node)  = prev_node;
        NEXT_NODE_PTR(prev_node) = new_node;
    }
}

// insert new_node before head node and return pointer to new head
size_t list_prepend(size_t new_node_ptr, size_t head_ptr) {
    PREV_NODE_PTR(head_ptr) = new_node_ptr;
    NODE_LINK_INIT(new_node_ptr, head_ptr, 0);
    return new_node_ptr;
}

// return next node by pointer
size_t list_iter_down(size_t node) {
    return NEXT_NODE_PTR(node);
}

// return previous node by pointer
size_t list_iter_up(size_t node) {
    return PREV_NODE_PTR(node);
}

// delete nodes betven $from_node and $to_node
void list_node_delete(size_t from_node, size_t to_node) {
    NEXT_NODE_PTR(from_node) = to_node;
    PREV_NODE_PTR(to_node) = from_node;
}

// delete list, in nodes field "data" was not dynamicly allocated
void list_delete_static(size_t head, void(*free_data)(void*))
{
    size_t current_node = head;
    size_t next_node = 0;
    while(current_node != 0) {
        next_node = NEXT_NODE_PTR(current_node);
        free_data((void*)current_node);
        current_node = next_node;
    }
}

#endif /* maksspace_list_h */
