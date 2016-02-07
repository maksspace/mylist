# mylist
Doubly linked list implementation in C
# usage
You can create any kind of data structures as nodes that should be as follows:
 ```C
 typedef struct your_node_name {
       struct your_node_name *prev, *next;
       int my_cool_int;
       float my_cool_float;
       ...
       strcut { ... } name;
   } some_node_name;
 ```
This library does not have a special function for creating new nodes. Just create a pointer to the new node and allocate memory for it using any memory allocator that you find suitable.

# api
 Insert `$node` after `$tail`, and return a pointer to the new tail of the list.
 ```C
 void* list_append(void* tail, void* node);
 ```
 Insert `$node` before `$head`, and return a pointer to the new head of the list.
  ```C
void* list_prepend(void* node, void* head);
 ```
 Insert `$new` between `$prev` and `$next`, return a pointer to the `$new`.
 ```C
void* list_insert(void* new, void* prev, void* next);
 ```
 Delete nodes between `$from` and `$to`
 ```C
void list_nodes_del(void* from, void* to);
 ```
This macros through the list starting from the `$head` while maintaining the current node in `$current`
 ```C
list_foreach(head, current) { ... }
```
# features
- Simple
- Node type can be anything.
- Any memory allocator can be used

# author
maksspace, maksspaceworld@yandex.ru
