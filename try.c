#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<time.h>

int main ()
{	int n=5,i, p[17][2];
	for(i=0;i<=n;i++)
		pipe(p[i]);
	for(i=1;i<=n;i++)
	{
		if(fork()==0)
		{
			printf("%d %d\n", getpid(), getppid());
			if(i==n)
			{	int r1;
				close(p[0][0]);
				write(p[0][1],"ok",3);
				close(p[0][1]);
				close(p[i][1]);
				read(p[i][0],&r1,sizeof(int)); close(p[i][0]);
				printf("r1 after subtraction: %d", r1);
				exit(0);	
			}
			int r1;
			close(p[i][1]);
			read(p[i][0],&r1,sizeof(int)); close(p[i][0]);
			srand(i);
			int r2=rand()%11+10;
			r1=r1-r2; close(p[i+1][0]);
			write(p[i+1][1],&r1,sizeof(int)); close(p[i+1][1]);
		}
		else 
		{
			wait(0);
			if(i==1)
			{	char var[3];
				close(p[0][1]);
				read(p[0][0],&var,3); close(p[0][0]);
				srand(0);//setam seed-ul functiei rand ca fiind i pentru ca sa genereze alt numar in fiecare proces 
				int r1=rand()%9001+1000; close(p[1][0]);
				write(p[1][1],&r1,sizeof(int)); close(p[1][1]);
			}	
			exit(0);
		}
	}
	return 0;
}
