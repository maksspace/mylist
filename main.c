#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"

LIST_NODE_TYPE_NEW(int, node_int);

int main(int argc, char *argv[])
{
    
    node_int* my_numbers = list_node_new(sizeof(node_int), malloc);
    my_numbers->data = 0;
    
    unsigned long t = clock();
    for(int i = 1; i < 1000; i++) {
        node_int* tmp = malloc(sizeof(node_int));
        tmp->data = i;
        my_numbers = list_prepend(tmp, my_numbers);
    }
    printf("prepend: %fs\n", (float)(clock() - t)/CLOCKS_PER_SEC);
    
    for(size_t current = LIST_ITER(my_numbers); current != 0;  current = list_iter_down(current))
        printf("%d\n", LIST_NODE_VAL(node_int, current)->data);
    
    list_delete_static(my_numbers, free);
    return 0;
}
