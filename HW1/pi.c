#include <stdio.h>
#include <stdlib.h>

int exponent(int base, int k){
	int sum = 1;
	for (int i=0; i<k; i++){
		sum = sum*base;
	}
    return sum;
}

int main() {
    int n;
    printf("n = ");
	scanf("%d", &n);
	double pi = 0;
	for (int i=0; i<=n; i++){
		double multiplier = 1/((double)exponent(16, i));
		double n1 = 4/((8*(double)i) + 1);
		double n2 = 2/((8*(double)i) + 4);
		double n3 = 1/((8*(double)i) + 5);
		double n4 = 1/((8*(double)i) + 6);
		pi += (n1-n2-n3-n4)*multiplier;
	}
    printf("PI = %.10f\n", pi);
    return 0;
}