#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

void die(char *s)
{
    fprintf(stderr, "Error: %s\n", s);
    if (errno)
        perror("errno");
    exit(EXIT_FAILURE);
} 

int main(int argc, char *argv[])
{
    char readbuffer[4096];
    int fd[5][2];
    for(int i = 0;i<5;i++){
        if(pipe(fd[i])<0){
            return 1;
        }
    }
    
    int pid1 = fork();
    if(pid1<0){
        return 2;
    }
    if(pid1 == 0){
        //child process 1
        dup2(fd[1][1], 1);
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);
        close(fd[3][0]);
        close(fd[3][1]);
        close(fd[4][0]);
        close(fd[4][1]);
        /*if(write(fd[1][1], string, strlen(string)+1) <0){
            return 4;
        }*/

        char * argv_list[] = {"cat", "pipe2.c", NULL};
        execvp("cat", argv_list); 

        close(fd[0][0]);
        close(fd[1][1]);
        return 0;
    }

    int pid2 = fork();
    if(pid2 <0) {
        return 5;
    }

    if(pid2 == 0){
        //child process 2
        dup2(fd[1][0],0);
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);
        //close(fd[2][1]);
        close(fd[3][0]);
        close(fd[3][1]);

        dup2(fd[2][1],1);
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[1][1]);
        close(fd[2][0]);
        close(fd[3][0]);
        close(fd[3][1]);
        close(fd[4][0]);
        close(fd[4][1]);

        char * argv_list[] = {"tr", "[a-z]", "[A-Z]", NULL};
        execvp("tr", argv_list);

        close(fd[1][0]);
        close(fd[2][1]);
        /*if(read(fd[1][0], readbuffer, sizeof(readbuffer)) <0){
            return 6;
        }*/
        //printf("Result is: %s\n\n",readbuffer);
        /*if(write(fd[2][1], newString, strlen(newString)+1) <0){
            return 7;
        }*/
        return 0;
    }

    int pid3 = fork();
    if(pid3 <0) {
        return 5;
    }

    if(pid3 == 0){
        //child process 3
        dup2(fd[2][0],0);
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);
        close(fd[3][0]);
        //close(fd[3][1]);
        close(fd[4][0]);
        close(fd[4][1]);

        dup2(fd[3][1],1);
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[1][1]);
        close(fd[2][1]);
        close(fd[3][0]);
        close(fd[4][0]);
        close(fd[4][1]);
    
    char * argv_list[] = {"tr", "[A-Z]", "[a-z]", NULL};
    execvp("tr", argv_list);

    close(fd[3][1]);
    close(fd[2][0]);
    }

int pid4 = fork();
    if(pid4 <0) {
        die("fork() failed");
        return 5;
    }

    if(pid4 == 0){
        //child process 4
        dup2(fd[3][0],0);
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);
        close(fd[3][0]);
        close(fd[3][1]);
        close(fd[4][0]);
        close(fd[4][1]);

        dup2(fd[4][1],1);
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[1][1]);
        close(fd[2][0]);
        close(fd[2][1]);
        close(fd[3][0]);
        close(fd[3][1]);
        close(fd[4][0]);
    char * argv_list[] = {"wc", "-l", NULL};
    execvp("wc", argv_list);

    close(fd[4][1]);
    close(fd[3][0]);
    }

//parent process
close(fd[0][0]);
close(fd[1][0]);
close(fd[1][1]);
close(fd[2][0]);
close(fd[2][1]);
close(fd[3][0]);
close(fd[3][1]);
close(fd[4][1]);
if(read(fd[4][0], readbuffer, sizeof(readbuffer))<0){
    return 9;
}
printf("Result is: %s\n",readbuffer);
close(fd[0][1]);
close(fd[4][0]);

int p1 = waitpid(pid1, NULL, 0);
int p2 = waitpid(pid2, NULL, 0);
int p3 = waitpid(pid3, NULL, 0);
int p4 = waitpid(pid4, NULL, 0);
printf("Process #1 return:  %i\nProcess #2 return:   %i\nProcess #3 return:    %i\nProcess #4 return:    %i\n",p1,p2,p3,p4);
printf("\n\n--FIN--\n");
return 0;
}