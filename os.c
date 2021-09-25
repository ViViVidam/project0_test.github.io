#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
pid_t child1;
pid_t child2;
void fun()
{
	if(child1&&child2)
	{	
		kill(child1,SIGUSR1);
		kill(child2,SIGUSR2);
		wait(NULL);
		wait(NULL);
		printf("Parent Proccess is killed!\n");
		exit(0);
	}
}
void fun1()
{
	printf("child 1 proccess is Killed by Parents!\n");
	exit(0);
}
void fun2()
{
	printf("child 2 proccess is Killed by Parents!\n");
	exit(0);
}
void main()
{
	int fd1[2];
	int fd2[2];
	int ret1=pipe(fd1);
	int ret2=pipe(fd2);
	char buf[100];
	char buf_r1[100];
	char buf_r2[100];
	int i=0;
	signal(SIGINT,fun);//ctrl+c的程序中断
	signal(SIGUSR1,fun1);//ctrl+c的程序中断
	signal(SIGUSR2,fun2);
	if((child1=fork())==-1)
	{
		printf("fork child 1 error.\n");
		exit(0);
	}
	else if(child1==0)//子进程1执行
	{
		printf("子进程1:\n");
		close(fd1[1]);
		while(1)
		{
			read(fd1[0],buf_r1,25);
			printf("son1:%s\n",buf_r1);
		}
		printf("exit1\n");
		close(fd1[0]);
	}
	if((child2=fork())==-1)
		{
			printf("fork child 2 error.\n");
			exit(0);
		}
	else if(child2==0)//子进程2执行
	{
		printf("子进程2:\n");
			close(fd2[1]);
			while(1)
			{
				read(fd2[0],buf_r2,25);
				printf("son2:%s\n",buf_r2);
			}
			printf("exit2\n");
			close(fd2[0]);
	}
	close(fd1[0]);
	close(fd2[0]);
	while(1)
	{
			sleep(1);
			sprintf(buf,"i send you %d times\n",i);
			write(fd1[1],buf,strlen(buf));
			write(fd2[1],buf,strlen(buf));
			i+=1;	
	}
	close(fd1[1]);
	close(fd2[1]);
}
