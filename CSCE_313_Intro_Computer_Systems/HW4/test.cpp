#include "iostream"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/wait.h"

using namespace std;

int main(int argc, char * argv[])
{
	int fd[2];
	
	if(pipe(fd) == -1)
	{
		fprintf(stderr, "%s\n", "pipe");
		exit(EXIT_FAILURE);
	}
	
	pid_t pid = fork();
	if(pid == -1)
	{
		fprintf(stderr, "%s\n", "fork");
		exit(EXIT_FAILURE);
	}
	else if(pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve("./toy", NULL, NULL);
		fprintf(stderr, "%s\n", "execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[1]);
		char f[4096];
		printf("Output: (%.*s)\n", read(fd[0], f, sizeof(f)), f);
		wait(NULL);
	}
	return 0;
}