#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{    
    FILE* fd = fopen("log.txt", "w");
    if(fd == NULL)
	{
		printf("Cannot open the file\n");
		exit(1);
	}
    char *msg = "lsiadufnalsidufnasdf";
    fprintf(fd, "%s", msg);
    fclose(fd);
}