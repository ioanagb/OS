#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<time.h>


int fp[2],tc[2];

void f(int n,int *r1)
{
	if(n==0)
	{	
		close(fp[0]); close (fp[1]);
		fp[0]=tc[0];
		fp[1]=tc[1];//ce atribui?
		//close ..???
		
		//printf("r1=%d", *r1);
		//return;
	}
	else
	{	
		if(fork()==0)
		{	f(n-1,r1); printf("Pid: %d, Parent pid: %d",getpid(),getppid());
			exit(0);
			
		}
		read(fp[0],r1,sizeof(int));
		srand(time(NULL));
        	int r2=rand()%(10000+1-1000)+1000;
		printf("r2=%d\n",r2);
		*r1=*r1-r2;
		write(tc[1],r1,sizeof(int));
		wait(0);
		exit(0);
	}
}	

int main()
{
	srand(time(NULL));
        int r1=rand()%(10000+1-1000)+1000;
	printf("r1=%d\n",r1);
	int n=5;
	//printf("Number of processes: ");
	//scanf(&n);
	pipe(fp); pipe(tc);
	f(n,&r1);
	printf("r1 dupa apel: %d\n",r1);
	return 0;
}






