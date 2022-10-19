#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int n;
	printf("n = ");
	scanf("%d", &n);
    int m = n;
    
    while(n!=4 && n!=1){
        int sum = 0;
        char buf[BUFSIZ];
        sprintf(buf, "%d", n);
        int len = strlen(buf);
        for(int i=0; i<len; i++){
            int addition = (buf[i]-'0')*(buf[i]-'0');
            sum += addition;
            }
        n = sum;
        printf("%i\n",n);
        }
        if(n==1) printf("%d is a happy number.\n", m);
        else printf("%d is NOT a happy number.\n", m);
    return 0;	
}
