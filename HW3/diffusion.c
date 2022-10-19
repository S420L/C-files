#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Point {
    int x, y, z, count;
};
//TODO
//Implement the below function
//Simulate one particle moving n steps in random directions
//Use a random number generator to decide which way to go at every step
//When the particle stops at a final location, use the memory pointed to by grid to 
//record the number of particles that stop at this final location
//Feel free to declare, implement and use other functions when needed

void one_particle(struct Point *grid, int n)
{
    struct Point one_point = {0,0,0};
        for(int i = 1; i<=n; i++){
            int r = rand() % 6;
            if(r==0) one_point.x+=1;
            else if(r==1) one_point.x-=1;
            else if(r==2) one_point.y+=1;
            else if(r==3) one_point.y-=1;
            else if(r==4) one_point.z+=1;
            else if(r==5) one_point.z-=1;
            else printf("Breh u F'd up");
        }
    printf("Point: (%d,%d,%d)", one_point.x, one_point.y, one_point.z);
    int count = 0;
    for(int x=0; x<=n; x++){
        for(int y=0; y<=n; y++){
            for(int z=0; z<=n; z++){
                if(one_point.x==x & one_point.y==y & one_point.z==z){
                    grid[count].count = grid[count].count + 1;
                }
                count++;
            }
        }
    }
}

//TODO
//Implement the following function
//This function returns the fraction of particles that lie within the distance
//r*n from the origin (including particles exactly r*n away)
//The distance used here is Euclidean distance
//Note: you will not have access to math.h when submitting on Mimir
double density(struct Point *grid, int n, double r)
{
    printf("Count: %d\n", grid[1].count);
    printf("Count: %d\n", grid[2].count);
    printf("Count: %d\n", grid[3].count);


    
}

//use this function to print results
void print_result(struct Point *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++)
    {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}

//TODO
//Finish the following function
//See the assignment decription on Piazza for more details
void diffusion(int n, int m)
{
	//fill in a few line of code below
    int total_points = (n+1)*(n+1)*(n+1);
    int count = 0;
    //int *grid = (int*) malloc(total_points*sizeof(Point));
    struct Point grid[total_points];
    for(int x=0; x<=n; x++){
        for(int y=0; y<=n; y++){
            for(int z=0; z<=n; z++){
                grid[count].x = x;
                grid[count].y = y;
                grid[count].z = z;
                grid[count].count = 0;
                count++;
            }
        }
    }
	for(int i = 1; i<=m; i++) one_particle(grid, n);

	print_result(grid, n);
	//fill in some code below


}

int main(int argc, char *argv[])
{
	
	if(argc != 3)
	{
		printf("Usage: %s n m\n", argv[0]);
		return 0; 
	}
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	assert(n >= 1 && n <=50);
	assert(m >= 1 && m <= 1000000);
	srand(12345);
	diffusion(n, m);
	return 0;
}
