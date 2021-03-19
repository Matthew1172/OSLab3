#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int child, child2, status, status2, mypid;

	child = fork();
	if(child < 0) return -555;
	if(child == 0){
		//child 1 process
		mypid = getpid();
		printf("I am the child process, my pid is: %d\n", mypid);
		//execl("/bin/echo", "myEchoProcess", "process 1\n", NULL); printf("Error. execl() failed.\n");
		execl("/bin/date", "myDateProcess", NULL); printf("Error. execl() failed.\n");
	}
	waitpid(child, &status, 0);
	return 0;
}
