#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define rows 41
#define cols 2

int main(){
    int list[] = {420,69,42069420};
    char list1[] = "Hello";
    //printf("MY SWIGGA 420: %i\n", list[0]);
    printf("Rows: %c\n",rows);
    printf("Cols: %d\n",cols);
    printf("List1: %s\n",list1);
    printf("Strlen: %lu\n",strlen(list1));
    printf("Size: %lu\n",sizeof(list1));
    printf("List[-2]: %c\n",list1[4]);
    printf("List[-1]: %c\n",list1[5]);
    printf("Pointer to pointer to list: %p\n",&list);
    printf("Pointer to list: %p\n",list1);
    printf("Value at pointer to list: %c\n",*list1);
    printf("ASCII at first element: %d\n",*list1);
    int swiggaz = 420;
    printf("SWiggaz: %p",swiggaz);
}

//CC := gcc-12

