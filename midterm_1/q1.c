#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

//TODO
int palindrome(unsigned long n)
{
	char forward[BUFSIZ];
    sprintf(forward, "%lu", n);
	int len = strlen(forward);
	char backward[len-1];
	for(int i=0; i<len; i++){
		backward[i] = forward[len-(i+1)];
	}
	for(int i=0; i<len; i++){
		if(backward[i]!=forward[i]){
			return 0;
		}
	}
	return 1;
}

//TODO
unsigned long pCube()
{
	unsigned long p = 0;
	while(1){
		unsigned long p3 = p*p*p;
		if(palindrome(p)==0 && palindrome(p3)==1){
			return p;
		}
		else{
			p++;
		}
	}
}
//Do not change the main function
int main()
{
	printf("%lu\n", pCube());
	return 0;
}