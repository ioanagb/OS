#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<time.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{       int n=(*argv[1]);
	if(argc==2) // check if there is exactly 1 argument given(without the name)
        {       printf("Give just the number of processes!");
                exit(1);
        }
        if(n<=5 && n>15)
        {       printf("The number must be 5<n<=15");
                exit(2);
        }
        int counter=0,c2p[2],p2c[0],i,f;
	
	srand(time(NULL));
        int r1=rand()%(10000+1-1000)+1000;

	//pipe(c2p);
	pipe(p2c);
	//if(pipe(c2p)<0) //check if we encountered an error
        //{      perror("c2p error");
        //       exit(3);
        //}
        if(pipe(p2c)<0)
        {       perror("p2c error");
                exit(4);
        }
	int child=fork();
	if(child<0) //check if we encountered an error
        {       perror("fork error");
                exit(5);
        }
	else if(child>0)
	{	//close(c2p[1]); 
		close(p2c[0]);
		srand(time(NULL));
                int r2=rand()%(20+1-10)+10;
		r1=r1-r2;
		write(p2c[1],&r1,sizeof(int));
		//close(c2p[0]); 
		close(p2c[1]);
		if(n==counter)
		{	printf("r1=",r1);
			exit(0);
		}
	}
	else if(child==0)
	{
		close(p2c[0]);
		read(p2c[1],&r1,sizeof(int));
		close(p2c[1]);
		srand(time(NULL));
                int r2=rand()%(20+1-10)+10;
                r1=r1-r2;
		dup2(r1,0);
	}
	return 0;
}



