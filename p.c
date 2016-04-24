#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<time.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{	int n=(*argv[1]);
	if(argc==2) // check if there is exactly 1 argument given(without the name)
	{	printf("Give just the number of processes!");
		exit(1);
	}
	if(n<=5 && n>15)
	{	printf("The number must be 5<n<=15");
		exit(2);
	}
	int counter=0,c2p[2],p2c[0],i,f;
	
	srand(time(NULL));
        int r1=rand()%(10000+1-1000)+1000;

	while(counter<n)//create n processes
	{
		
		if(pipe(c2p)<0) //check if we encountered an error
		{	perror("c2p error");
			exit(3);
		}
		if(pipe(p2c)<0)
		{	perror("p2c error");
			exit(4);
		}
		f=fork();
		if(f<0) //check if we encountered an error
		{	perror("fork error");
			exit(5);
		}counter=counter+1;
	}
	
	if(f>0)//in parent process
	{	close(c2p[1]); close(p2c[0]);
		if(read(c2p[0],&r1,sizeof(int))<0)
		{	perror("read c2p error");
			exit(6);
		}
		srand(time(NULL));
		int r2=rand()%(20+1-10)+10;
		r1=r1-r2;
		if(write(p2c[1],&r1,sizeof(int))<0)
		{	perror("write error");
			exit(7);
		}
		close(p2c[1]); close(c2p[0]);
	}
	else //in child process
	{	close(p2c[1]); close(c2p[0]);
		if(read(p2c[0],&r1,sizeof(int))<0)
		{	perror("read error");
			exit(8);
		}
		srand(time(NULL));
                int r2=rand()%(20+1-10)+10;
                r1=r1-r2;

		if(write(c2p[1],&r1,sizeof(int))<0)
		{	perror("write error");
			exit(9);
		}
	}
	for(i=1;i<=n;i++)
		wait(0);
	printf("Game reached the end: %d", r1);
	return 0;
}

