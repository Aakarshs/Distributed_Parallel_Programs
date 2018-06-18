/*
Assignment 1
Aakarsh Sinha

As someone new to C and even bash, this was a challenge for me as i had to extensively look for books or tutorials online, however since i already know python i first made and ran the program there and then started researching the internet for how to write c programs. i have tried my best to list the resources i used as a part of completing this assignment.

www.stackoverflow.com/questions/40346871/comment-in-bash-script-processed-by-slurm
www.garron.me/en/articles/bash-for-loop-examples.html
www.stackoverflow.com/questions/5627179/syntax-of-for-loop-in-linux-shell-scripting
www.learn-c.org/en/Hello%2C_World%21
www.youtube.com/watch?v=z8evnLrYm9I
www.youtube.com/watch?v=9P5J5-IYspQ
www.youtube.com/watch?v=W9CV1IxIsmw
www.youtube.com/watch?v=UQqnGfQc-xY
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, const char* argv[])
{
int N=atoi(argv[1]);
    
int count = 0;
int j,c,d,k,i,r;
double t;
 
//Initializing arrays.
int array1[N][N];     //creating the first array.
int array2[N][N];     //creating the second array.
int mul[N][N];        //creating the third array.
int sum=0;
//filling first matrix.
    for(i=0;i<N;i++)
    {
    for(j=0;j<N;j++)
	{
	r=rand()%10;     //using rand to generate random numbers from 0-9.
	array1[i][j]=r;  //putting the generated values into arrays.
	}
    }
//filling second matrix.
    for(i=0;i<N;i++)
    {
    for(j=0;j<N;j++)
	{
	r=rand()%10;     //using rand to generate random numbers from 0-9.
	array2[i][j]=r;  //putting the generated values into arrays.
	}
    }
    
//caculating time.
    clock_t start=clock();
    
//multiplying matrix.
    for(i=0;i<N;i++)  {
    for(j=0;j<N;j++)  {
    sum=0;
    for(k=0;k<N;k++)  {
    sum=sum+array1[i][k]*array2[k][j];
    }
    mul[i][j]=sum;
    }
    }

    clock_t end=clock();
    t=(double)(end-start)/CLOCKS_PER_SEC;
    
printf("No of elements:%d", N*N);
printf("|");
printf("Time taken: %fs \n",t );

}


