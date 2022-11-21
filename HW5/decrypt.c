#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>

#define MAX 10240
#define MAX_WORD_COUNT 60000                //we have less than 60000 words
#define MAX_WORD_LENGTH 80                //each word is less than 80 letters

//Using these two global variables can be justified :)
char words[MAX_WORD_COUNT][MAX_WORD_LENGTH];        //2-d array to hold all the words
int word_count = 0;                    //number of words, initilized to 0

typedef struct Word{
    char* word;
} Word;

//Note the words in the dictionary file are sorted
//This fact could be useful
void read_file_to_array(char *filename)
{
    FILE *fp;

    //open the file for reading
    fp = fopen(filename, "r");
    if(fp==NULL)
    {
        printf("Cannot open file %s.\n", filename);
        exit(-1);
    }
    //make sure when each word is saved in the array words,
    //it does not ends with a '\n'
    //see how this is done using fscanf 
    while(!feof(fp))
        fscanf(fp, "%s\n", words[word_count++]);
    fclose(fp);
}

//TODO
//Test wether a string word is in the dictionary
//Return 1 if word is in the dictionary
//Return 0 otherwise
//Be efficient in implementing this function
//Efficiency is needed to pass test cases in limited time
int in_dict(char *word)
{
    int start = 0;
    int end = 58022;
    int c = 6689;
    int e = 15957;
    int g = 21102;
    int j = 27637;
    int n = 33245;
    int q = 40115;
    int t = 50709;
    

    if(word[0]>=97 && word[0]<99){
        end = 6689;
    }else if(word[0]>=99 && word[0]<101){
        start = 6689;
        end = 15957;
    }else if(word[0]>=101 && word[0]<103){
        start = 15957;
        end = 21102;
    }else if(word[0]>=103 && word[0]<106){
        start = 21102;
        end = 27637;
    }else if(word[0]>=106 && word[0]<110){
        start = 27637;
        end = 33245;
    }else if(word[0]>=110 && word[0]<113){
        start = 33245;
        end = 40115;
    }else if(word[0]>=113 && word[0]<116){
        start = 40115;
        end = 50709;
    }
    else if(word[0]>=116){
        start = 50709;
    }
    
    
    
    for(int i=start;i<end;i++){
        if(!strcmp(words[i],word)){
            //printf("WORDS[i]: %s\n",words[i]);
            return 1;
        }
    }

return 0;
}

//TODO
//Use key and shift to decrypt the encrypted message
//len is the length of the encrypted message
//Note the encrypted message is stored as an array of integers (not chars)
//The result is in decrypted

void decryption(unsigned char key, unsigned char shift, const int *encrypted, int len, char *decrypted)
{
    for(int i = 0; i<len; i++){
		decrypted[i] = (key^encrypted[i]) >> shift;
    }

}

//TODO
//calculate a score for a message msg
//the score is used to determine whether msg is the original message
int message_score(const char *msg)
{
    //printf("\nDECRYPTED:___________\n");
    //printf("%s\n",msg);
    int score = 0;
    int letter = 0;
    char temp[MAX_WORD_LENGTH];
    for(int i=0;i<strlen(msg);i++){
        if(msg[i]==32){
            temp[letter]='\0';
            letter = 0;
            if(in_dict(temp)){
                score++;
            }
        }else if(i==strlen(msg)-1){
            temp[letter] = msg[i];
            temp[letter+1]='\0';
            if(in_dict(temp)){
                score++;
            }
        }else{
            temp[letter] = msg[i];
            letter++;
        }
        if(letter>=MAX_WORD_LENGTH){
            //if(score>0)printf("TEMP: %s",temp);//printf("SCORE: %i\n",score);
            //printf("TEMP: %s",temp);
            return score;
        }
    }
    //if(score>0)printf("SCORE: %i\n",score);
return score;
}

//search using all the (key, shift) combinations
//to find the original message
//result is saved in message
void search(const int *encrypted, int len, char *message)
{
	char decrypted[MAX];

    int max_score = 0;
    strcpy(message, "");
    for(unsigned char k = 0; k < 255; k++)
    {
        for(unsigned char shift = 0; shift <= 24; shift++)
        {
            decryption(k, shift, encrypted, len, decrypted);
			int score = message_score(decrypted);
			if(score > max_score)
			{	//printf("MAX SCORE INCREASED! %i",score);
				max_score = score;
				strcpy(message, decrypted);
			}
        }
    }
}

//TODO
//read the encrypted message from the file to encrypted
//return number of bytes read
int read_encrypted(char *filename, int *encrypted)
{
    //printf("Filename: %s\n",filename);

    int fp = open(filename, O_RDONLY);
    if(fp < 0)
    {
        printf("Cannot open file %s\n", filename);
        return -1;
    }
    int len = read(fp, encrypted, MAX);
    
    return len;
}

//Do not change the main() function
int main(int argc, char *argv[])
{

    /*read_file_to_array("dict.txt");
    for(int i=97;i<123;i++){
        for(int j=0;j<word_count;j++){
            if(i==words[j][0]){
                printf("%c: %i\n",i,j);
                break;
            }
        }
    }
    exit(0);*/
    //printf("IN DICT: %i\n", in_dict("aardvark"));
    //printf("HASH: %lu\n", hash("aardvark"));
    /*char *mm = "r";
    printf("%i\n",mm[0]);
    exit(0);*/
	if(argc != 2)
	{
		printf("%s encrypted-message\n", argv[0]);
		return 0;
	}

	read_file_to_array("dict.txt");
    /*for(int i=0;i<10;i++){
        printf("%s\n",words[i]);
    }
    printf("\n");*/

	int encrypted[MAX];
	int len = read_encrypted(argv[1], encrypted);
    /*printf("Encrypted:  ");
    for(int i=0;i<18;i++){
        printf("%i ",encrypted[i]);
    }
    printf("\nLEN: %i\n",len);*/
	
	char message[MAX];
	strcpy(message, "");
	search(encrypted, len, message);
	printf("%s\n", message);
	return 0;
}