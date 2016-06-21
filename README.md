# mylist
Doubly linked list implementation in C

# features
- Simple
- Node type can be anything.
- Any memory allocator can be used

# author
- name &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: Smagin Maksim
- vkontakte : http://vk.com/maksspace
- email &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: maksspaceworld@yandex.ru
- facebook &nbsp;: https://www.facebook.com/maksspaceworld

# usage
Just include `list.h` into your project.
You can create any kind of data structures as nodes that should be as follows:
 ```C
 typedef struct your_node_name {
       LIST_LINK(your_node_name);
       // ... your fields
   } your_node_name_t;
 ```
 or
  ```C
 struct your_node_name {
     LIST_LINK(your_node_name);
     // ... your fields
 };
 ```
This library does not have a special function for creating new nodes. Just create a pointer to the new node and allocate memory for it using any memory allocator that you find suitable.

# example
Create list contains listeners of radio, and print it.
```C
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct listener {
    LIST_LINK(listener);
    int age;
} listener_t;

int main(int argc, char *argv[])
{
    listener_t* radio_listeners = malloc(sizeof(listener_t));
    radio_listeners->age = 0;
    list_node_init(radio_listeners);

    listener_t* cur;
    for(int i = 1; i < 10000; i++) {
        cur = malloc(sizeof(listener_t));
        cur->age = i;
        radio_listeners = list_prepend(cur, radio_listeners);
    }
    
    list_iter_t* it = malloc(sizeof(list_iter_t));
    list_iter_init(it, radio_listeners);
    
    while((cur = list_iter_next(it))) {
        printf("%d\n", cur->age);
    }
    
    free(it);
    list_del_static(listener_t, radio_listeners, free);
    
    return 0;
}

```

# data types
`list_iter_t` - iterator list


# api
 Insert `node` after `tail`, and return a pointer to the new tail of the list.
 ```C
 void* list_append(void* tail, void* node);
 ```
 Init s list iterator starting from `head`.
 ```C
 void list_iter_init(list_iter_t* iter, void* head);
 ```
 Return pointer to next and previous nodes respectively.
 ```C
 void* list_iter_next(list_iter_t* iter);

 void* list_iter_prev(list_iter_t* iter);
 ```
 Insert `node` before `head`, and return a pointer to the new head of the list.
  ```C
void* list_prepend(void* node, void* head);
 ```
 Insert `new` between `prev` and `next`, return a pointer to the `new`.
 ```C
void* list_insert(void* new, void* prev, void* next);
 ```
 Delete nodes between `from` and `to`. Return a pointer to deleted nodes, or NULL if betwen `from` and `to` is empty. 
 ```C
void list_nodes_del(void* from, void* to);
 ```
This macros through the list starting from the `head` while maintaining the current node in `current`
 ```C
list_foreach(head, current) { ... }
```
This macro delete all nodes `type` from list, starting from the `head`, using `free _ data` and `free_node` to free memory.
 ```C 
list_del(type, head, free_data, free_node);
list_del(head, free_data, free_node); // for GCC
```
Same as `list_del(...)`, but data of node is static and don't need to free.
 ```C 
list_del_static(type, head, free_node);
list_del_static(head, free_node); // for GCC
```
