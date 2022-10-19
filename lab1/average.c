#include <stdio.h>

int main()
{
    double x;
    double total;
    double average;
    double count;
    while (scanf("%lf", &x) == 1) { 
        count++;
        total+=x;
        average = total/count;
        printf("Total=%f Average=%f\n", total, average); 
    };
}