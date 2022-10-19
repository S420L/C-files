#include <stdio.h>

/* This function calculates n-th Catalan number.
 * n is assumed to be non-negative.
 * Do not worry about overflow.
 * Do not print anything in this function.
 * Do not use floating-point numbers (or operations).
 */

int numerator = 1, denominator = 1;

long catalan_number(int n)
{
    if (n < 0)
        return 0;
    if (n==0){
        int result = numerator/denominator;
        numerator = 1, denominator = 1; 
        return result;
    }
    else{
        numerator*=(4*n-2);
        denominator*=(n + 1);
        return catalan_number(n-1);
    }
}

/* do not change main function */
int main(void)
{
    int n;
    while (scanf("%d", &n) == 1) {
        if (n < 0) 
            printf("C(%2d) is not defined.\n", n);
        else 
            printf("C(%2d)=%18ld\n", n, catalan_number(n));
    }
    return 0;
}
