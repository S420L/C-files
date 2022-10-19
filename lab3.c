#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* print out an error message and exit */
void my_error(char *s)
{
    perror(s);
    exit(1);
}

/* Concatnate two strings.
 * Dynamically allocate space for the result.
 * Return the address of the result.
 */
char *my_strcat(char *s1, char *s2)
{
    int len = strlen(s1) + strlen(s2);
    char* s3 = (char*)malloc(len*sizeof(char));
    if(s3 == NULL){
        my_error("Failed to allocate bytes!");
    }
    for(int i=0;i<strlen(s1);i++){
        s3[i] = s1[i];
    }
    for(int i=0;i<strlen(s2);i++){
        s3[i+strlen(s1)] = s2[i];
    }
    return s3;
}

int main(int argc, char *argv[])
{
    char    *s;

    s = my_strcat("", argv[0]);

    for (int i = 1; i < argc; i ++) {
        s = my_strcat(s, argv[i]);
    }

    printf("%s\n", s);
    free(s);
    return 0;
}
