#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char ** argv)
{
    pid_t child;
    int exitStatus;

    // at least, there should be 3 arguments
    // 2 for the first command, and the rest for the second command
    if (argc < 4) {
        fprintf(stderr, "Usage: %s cmd1 cmd1_arg cmd2 [cmd2_args ..]\n", argv[0]);
        return 1;
    }
    
    child = fork();
    //printf("Child: %d\n",child);
    if(child==0){
        char str1[69] = "/bin/";
        char *binPath = strcat(str1,argv[1]);
        //printf("COMMAND RUN: %s %s\n",binPath,argv[2]);
        execlp(binPath, binPath, argv[2], NULL);
    }
    else if(child<0) {
        perror("fork()");
    }
    else{
        if (waitpid(child, &exitStatus, 0) > 0) { 
            printf("exited=%d exitstatus=%d\n",WIFEXITED(exitStatus),WEXITSTATUS(exitStatus));
        if(WIFEXITED(exitStatus) && !WEXITSTATUS(exitStatus)){
            //printf("\nprogram execution successfull\n"); 
        }

        else if (WIFEXITED(exitStatus) && WEXITSTATUS(exitStatus)) { 
                if (WEXITSTATUS(exitStatus) == 127) { 
                    // execv failed 
                    printf("execv failed\n"); 
                } 
                else
                    printf("program terminated normally, but returned a non-zero status\n");                 
        } 
        else {
            printf("program didn't terminate normally\n");  
        }
        }else { 
            printf("waitpid() failed\n"); 
        }
    }

    //char * argv_list[] = {argv[3], NULL}; 
    int num_args = argc-2;
    //printf("NUMBER ARGS: %d", num_args);
    char * argv_list[num_args+1];
    for(int i=0;i<num_args;i++){
        argv_list[i] = argv[3+i];
    }
    argv_list[num_args] = NULL;

    child = fork();
    if(child==0){
        execvp(argv[3],argv_list);
    }
    else if(child<0) {
        perror("fork()");
    }
    else{
        if (waitpid(child, &exitStatus, 0) > 0) { 
            printf("exited=%d exitstatus=%d\n",WIFEXITED(exitStatus),WEXITSTATUS(exitStatus));
        }
    }


    return 0;
}