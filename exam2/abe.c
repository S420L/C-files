//Test whether a word is a abecedarian word
//No need to check whether each character is an alphabetic character 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h> 
#include <fcntl.h>
#include <string.h> 
#include <sys/stat.h>

int abecedarian(const char *word)
{
	//TODO
	//fill in the code below
    int last = 0;
    int len = strlen(word);
    //printf("\nWORD: %s\n", word);
    for(int i=0;i<len;i++){
        //printf("%i ",word[i]);
        if((int)word[i]<last){
            return 0;
        }
        else{
            last = (int)word[i];
        }
    }
    return 1;
}

//redirect standard input to the specified file
void redirectStdin(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if(fd < 0)
    {
            perror("Error opening the file\n");
            exit(-1);
    }
	dup2(fd, 0);
    close(fd);

}

//redirect standad output to the specified file
void redirectStdout(const char *filename)
{
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if(fd < 0)
        {
                perror("Error opening the file\n");
                exit(-1);
        }
	dup2(fd, 1);
    close(fd);
}


/*int main()
{
    char* word = "abc";
    abecedarian(word);
}*/