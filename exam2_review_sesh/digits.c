#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define PFD_READ     0
#define PFD_WRITE    1

// Write an integer value to the file descriptor fd
// Return 0 on success, -1 otherwise
int write_int(int fd, int* value) {
    if(write(fd, value, sizeof(int))){
        
    }
    return -1;
}

// Put an integer into value read from the file descriptor fd
// Return 0 on success, -1 otherwise
int read_int(int fd, int* value) {
    // TODO
    return -1;
}

// The program should receive integers over the command line
int main(int argc, char* argv[]) {
    // Make an array of integers and populate it with args
    int my_nums[argc];
    // Convert each value in argv from a string to an integer
 
    // TODO
    // Create pipes for the child and parent to use
    int PtoC[2], CtoP[2];

    int child_pid = fork();


    if(child_pid < 0) {
        exit(1);
    } else if(child_pid == 0) {
        // Child

        /*
         * TODO
         * Read a number from the parent
         * Count the digits in the number
         * Send the count back to the parent
         * Repeat until we hit EOF
         */

        close(PtoC[PFD_WRITE]);
        close(CtoP[PFD_READ]);

        int n;
        while(read_int(PtoC[PFD_READ],&n) ==0 ){
            int count = 0;
            while(n!=0){
                n/=10;
                count++;
            }
            write_int(CtoP[PFD_WRITE], count);
        }

        close(PtoC[PFD_READ]);
        close(CtoP[PFD_WRITE]);

        exit(0);
    }
    // Parent
    
    /*
     * TODO
     * Loop through each number in my_nums
     * Send it to the child
     * Receive a response from the child
     * Add the response to the total digit count
     * Close the pipe(s) when done
     */


    close(PtoC[PFD_READ]);
    close(CtoP[PFD_WRITE]);

    for(int i = 0;i<argc;i++){
    write_int(PtoC[PFD_WRITE],my_nums[i]);
    }

    close(PtoC[PFD_WRITE]);
    int total_digits = 0;
    int count = 0;
    for(int i = 0;i<argc;i++){
        read_int(CtoP[PFD_READ], &count);
        total_digits += count;
    }
    close(CtoP[PFD_READ]);

    waitpid(child_pid, NULL, 0);

    printf("\n\nThe total digit count is %d\n\n",total_digits);

    return 0;
}