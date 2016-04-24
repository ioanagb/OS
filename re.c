#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<time.h>
int fp[2],tc[2];

void f(int n, int *r1)
{	if (n>0) //cat timp n>0 cream procesele si legaturile recursiv
			//cand am ajuns la 0 procesam r1, conform cerintei
	{	close(fp[0]); close(fp[1]);   //inchid fp mostenit, pentru ca 
						//urmeaza sa facem fork si acest fp ar fi bunic pentru viitorul
						//copil => nu mai avem nevoie de el
			
		pipe(tc); //facem pipe pentru "to child", adica cream canalul de comunicare intre actualul parinte si viitorul lui copil
                           //iar in "from parent" o sa punem perechea de intregi de la "to child" pentru a putea citi in copil ce i-a
                           //scris parintele
		fp[0]=tc[0];
		fp[1]=tc[1];		
		if(fork()==0)   //cream copiii
                {       f(n-1,r1); printf("Pid: %d, Parent pid: %d",getpid(),getppid());
                        exit(0);

                } printf("Am creat copiii.");
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
{       srand(time(NULL));      //generez r1 conform cerintei
        int (*r1)=rand()%(10000+1-1000)+1000, n=5;
        printf("The generated number: %d",r1);
        pipe(fp);       //facem pipe "from parent"(va fi inchis pe else)
        f(n,r1);        //apelam functia
        printf("r1 modified: ",r1); //aceasta afisare ar trebui sa fie facuta
        return 0;                       //de ultimul copil, nu aici
}





                
                
                
                
                
                
                
                

	
	












