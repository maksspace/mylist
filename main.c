#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"


LIST_NODE_TYPE_NEW(int, node_int);

int main(int argc, char *argv[])
{

    node_int* my_numbers = malloc(sizeof(node_int));
    LIST_NODE_LINK_INIT(my_numbers);
    my_numbers->data = 0;
    
    for(int i = 1; i < 1000; i++) {
        node_int* tmp = malloc(sizeof(node_int));
        tmp->data = i;
        LIST_PREPEND(tmp, my_numbers);
    }
    
    for(size_t current = LIST_ITER(my_numbers); current != 0; LIST_ITER_DOWN(current, node_int, my_numbers))
        printf("%d\n", LIST_NODE_GET(node_int, current)->data);
    
    LIST_DELETE_STATIC(node_int, my_numbers, free);

    return 0;
}
