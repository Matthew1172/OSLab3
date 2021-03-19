#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	
	int fd, fd2;

	//create destination1.txt and give 777 permission
	fd = open("destination1.txt", 
			O_CREAT | O_RDWR, 
			S_IRWXU | S_IRWXG | S_IRWXO);
	//check for error
	if (fd == -1) 
	{ 
		// print which type of error have in a code 
		printf("Error creating file. Error#:  %d\n", errno);  
		// print program error details 
		perror("Program");
		return -555;
	}
	//close file, print if there is an error
	if(close(fd) < 0)  
	{ 
		perror("c1"); 
		return -555; 
	}

	//create destination2.txt and give 777 permission
	fd2 = open("destination2.txt", 
			O_CREAT | O_RDWR, 
			S_IRWXU | S_IRWXG | S_IRWXO);
	//check for error
	if (fd2 == -1) 
	{ 
		// print which type of error have in a code 
		printf("Error creating file. Error#:  %d\n", errno);  
		// print program error details 
		perror("Program");
		return -555;
	}
	//close file, print if there is an error
	if(close(fd2) < 0)  
	{ 
		perror("c1"); 
		return -555; 
	}

	//done
	return 0;
}
