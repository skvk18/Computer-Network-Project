#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	int val, fd[2], n, pr;
	char arr1[100], arr2[100];
	pipe(fd);
	val = open("abc.txt", O_RDONLY, 0666);
	n = read(val, arr1, 100);
	pr = fork();

	if (pr < 0)
		printf("\nError in fork, pr = %d", pr);
	else if (pr == 0)
	{
		printf("\nFor child process ,Value of pr is : %d", pr);
		printf("\nChild process: Child ID = %d, Parent ID = %d", getpid(), getppid());
		write(fd[1], arr1, n);
	}
	else
	{
		printf("\nFor parent process, Value of pr is : %d", pr);
		printf("\nParent process: Process ID = %d ", getpid());
		read(fd[0], arr2, 100);
		printf("\nString is : %s", arr2);
	}

	/*	printf("\nFile dscp :  %d ",val);
	printf("\nFile read dscp : %d ",fd[0]);
	printf("\nFile write dscp : %d",fd[1]);	
	printf("\nProcess status : %d",pr);
	printf("\nNo of bits : %d",n);*/

	printf("\n");
	close(fd[0]);
	close(fd[1]);
	close(val);
	return 0;
}
