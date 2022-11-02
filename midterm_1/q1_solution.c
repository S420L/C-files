#include <stdio.h>

//TODO
int palindrome(unsigned long n)
{
	//fill in your code
	unsigned long m = 0, nn = n;
	while(n > 0)
	{
		m = m*10 + n % 10;
		n /= 10;
	}
	return m == nn;
}

//TODO
unsigned long pCube()
{
	//fill in your code
	unsigned long p = 1;
	while(palindrome(p) || !palindrome(p*p*p)) p++;
	return p;
}
//Do not change the main function
int main()
{
	printf("%lu\n", pCube());
	return 0;
}