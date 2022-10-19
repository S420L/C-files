#include <stdio.h>
#include <stdlib.h>

double two_d_random(int n)
{
    int x = 0, y = 0, count = 0, flag = 0, subtotal = 0;
    int total_points = ((n*2)-1)*((n*2)-1);
    int arr1[total_points];
    int arr2[total_points];
    for(int i=0; i<total_points; i++){
        arr1[i] = 69;
        arr2[i] = 69;
    }
    while(x<n && y<n) {
        flag = 0;
        for(int i=0; i<total_points; i++){
            if(arr1[i]==x & arr2[i]==y){
                flag = 1;
            }
        }
        if(flag!=1){
            arr1[count] = x;
            arr2[count] = y;
            count++;
        }
        int r = rand() % 4;
        if(r==0) y+=1;
        else if(r==1) x+=1;
        else if(r==2) y-=1;
        else if(r==3) x-=1;
        else printf("Breh u F'd up");
    }
    for(int i=0; i<total_points; i++){
        if(arr1[i]!=69) subtotal++;
    }
    return (double)subtotal/(double)total_points;

	//TODO
	//Fill in code below
	//When deciding which way to go for the next step, generate a random number as follows.
	//r = rand() % 4;
	//Treat r = 0, 1, 2, 3$ as up, right, down and left respectively.

	//The random walk should stop once the x coordinate or y coordinate reaches $-n$ or $n$. 
	//The function should return the fraction of the visited $(x, y)$ coordinates inside (not including) the square.
}

//Do not change the code below
int main()
{
	int trials = 1000;

	srand(12345);
	for(int n=1; n<=64; n*=2)
	{	
		double sum = 0.;
		for(int i=0; i < trials; i++)
		{
			double p = two_d_random(n);
			sum += p;
		}
		printf("%d %.3lf\n", n, sum/trials);
	}
	return 0;
}

