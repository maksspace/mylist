// ---------------------------------------------- //
// Doubly linked list implementation by maksspace //
// ---------------------------------------------- //

#ifndef maksspace_list_h
#define maksspace_list_h

#define LIST_NODE(type) \
    struct {            \
        type data;      \
        size_t next;    \
        size_t prev;    \
    }

#define LIST_NODE_TYPE_NEW(type, name) typedef LIST_NODE(type) name

#define LIST_NODE_LINK_INIT(name) ((name)->next = (name)->prev = 0)
#define LIST_NODE_NEXT(type, node_ptr) ((type*)((node_ptr)->next))
#define LIST_NODE_PREV(type, node_ptr) ((type*)((node_ptr)->prev))
#define LIST_NODE_GET(type, node_ptr) ((type*)(node_ptr))

#define LIST_INSERT(new_node, prev_node, next_node)         \
    if((next_node) == 0) {                                  \
        (prev_node)->next = (size_t)(new_node);             \
        (new_node)->prev = (size_t)(prev_node);             \
        (new_node)->next = 0;                               \
    }                                                       \
    else {                                                  \
        (next_node)->prev = (size_t)(new_node);             \
        (new_node)->next  = (size_t)(next_node);            \
        (new_node)->prev  = (size_t)(prev_node);            \
        (prev_node)->next = (size_t)(new_node);             \
    }

#define LIST_PREPEND(node, head)    \
    {(head)->prev = (size_t)(node); \
    (node)->next = (size_t)(head);  \
    (node)->prev = 0;               \
    (head) = (node);}

#define LIST_ITER(ptr) (size_t)(ptr)
#define LIST_ITER_DOWN(iter_name, type, head_ptr) iter_name = (size_t)LIST_NODE_NEXT(type, (type*)iter_name)
#define LIST_ITER_UP(iter_name, type, tail_ptr) iter_name = (size_t)LIST_NODE_PREV(type, (type*)iter_name)

#define LIST_NODE_DELETE(from, to) \
    {(from)->next = (size_t)(to);  \
    (to)->prev = (size_t)(foo);}

#define LIST_DELETE_STATIC(type, head, free_data)            \
    {size_t current_node = (size_t)(head);                   \
    size_t next_node = 0;                                    \
    while(current_node != 0) {                               \
        next_node = LIST_NODE_GET(type, current_node)->next; \
        free_data((void*)current_node);                      \
        current_node = next_node;                            \
    }}


#endif /* maksspace_list_h */
