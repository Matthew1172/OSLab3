#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define P1 "/home/student/Desktop/csc332/pecko_lab_3/Process_P1.o"
#define P2 "/home/student/Desktop/csc332/pecko_lab_3/Process_P2.o"

int main(int argc, char** argv){
	int child, child2, status, status2, mypid;
	char* const myargs[] = {"Process_P1.o", "source.txt", "destination1.txt", "destination2.txt", NULL};

	child = fork();
	if(child < 0) return -555;
	if(child == 0){
		//child 1 process
		mypid = getpid();
		printf("I am the first child, my pid is: %d\n", mypid);
		execv(P2, myargs); printf("Error. execl() failed.\n");
	} else {
		child2 = fork();
		if(child2 < 0) return -555;
		if(child2 == 0){
			//child 2 process will finish before child1 without sleep()
			//sleep(1);
			mypid = getpid();
			printf("I am the second child, my pid is: %d\n", mypid);
			execv(P1, argv); printf("Error. execl() failed.\n");
		}
	}
	//wait for first and second child process to finish
	waitpid(child, &status, 0);
	waitpid(child2, &status2, 0);
	return 0;
}
