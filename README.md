# mylist
Doubly linked list implementation in C
# using
You can create any kind of data structure as nodes that should be as follows:
 ```C
 typedef struct your_node_name {
       struct your_node_name *prev, *next;
       int my_cool_int;
       float my_cool_float;
       ...
       strcut { ... } name;
   } some_node_name;
 ```
This library  not have a special function for creating new nodes. Just create pointer on new node and allocate memory for her as you want.

# api
 Insert $node after $tail, and return pointer on new tail of list
 ```C
 void* list_append(void* tail, void* node);
 ```
 Insert $node before $head, and return pointer on new head of list
  ```C
void* list_prepend(void* node, void* head);
 ```
 Insert $new between $prev and $next, return pointer on $new
 ```C
void* list_insert(void* new, void* prev, void* next);
 ```
 Delete nodes between $from and $to
 ```C
void list_nodes_del(void* from, void* to);
 ```
This macros through the list starting from the $head while maintaining the current node in $current
 ```C
list_foreach(head, current) { ... }
```
# features
- This's simple
- Type node can be anything.
- You can use any memory allocator

# author
maksspace, maksspaceworld@yandex.ru