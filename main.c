//
// Created by maksspace on 30.01.16.
//


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mylist.h"

struct Coord {
    int x, y;
    struct mylist __list_link__;
};

int main()
{
    
    MYLIST_HEAD_NEW(coords);
    
    for (int i = 0; i < 100; i++) {
        struct Coord* temp = malloc(sizeof(struct Coord));
        temp->x = i;
        temp->y = i + 1;
        MYLIST_LINK_INIT(temp);
        mylist_prepend(&temp->__list_link__, &coords);
    }
    
    MYLIST_FOREACH(struct Coord, &coords, 100)
        printf("(%d, %d)\n", __current_struct_ptr__->x, __current_struct_ptr__->y);
    MYLIST_FOREACH_END
    
    mylist_free(struct Coord, &coords, 100);
    
    return 0;
}
