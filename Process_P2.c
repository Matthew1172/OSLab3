#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#define DEBUG 0
#define NUMBEROFBYTES 50


int checkFile(char* filepath);

int main(int argc, char* argv[]){

	if(argc != 4){
		printf("\nUsage: ./a.out <file-to-copy> <destination>\n");
		return 1;
	}


	//SOURCE.TXT FILEPATH
	char* filepath1 = argv[1];
	//DESTINATION1.TXT FILEPATH
	char* filepath2 = argv[2];
	//DESTINATION2.TXT FILEPATH
	char* filepath3 = argv[3];
	//GET FILE SIZE OF SOURCE.TXT USING STAT
	struct stat stbuf;
	stat(filepath1, &stbuf);
	const unsigned long filesize = stbuf.st_size;
	//CREATE BUFFER TO READ FROM
	char* bf = (char*) calloc(NUMBEROFBYTES, 1);
	//GET LEFTOVER
	int lps = filesize % NUMBEROFBYTES;
	//FLAG FOR WRITE TO D1.TXT OR WRITE TO D2.TXT
	int flag = 0;

	int fd1, fd2, fd3, returnval;
	int i = 0;

	
	if(checkFile(filepath1)) printf("There was an error!");
	else if(DEBUG) printf("%s is good.\n", filepath1);
	if(checkFile(filepath2)) printf("There was an error!");
	else if(DEBUG) printf("%s is good.\n", filepath2);
	if(checkFile(filepath3)) printf("There was an error!");
	else if(DEBUG) printf("%s is good.\n", filepath3);


	fd1 = open(filepath1, O_RDONLY);
	if(fd1 == -1){
		printf("\nopen() failed with error [%s]\n", strerror(errno));	
		return 1;	
	}		
	if(DEBUG) printf("\nOpen() successful\n");

	fd2 = open(filepath2, O_RDWR);
	if(fd2 == -1){
		printf("\nopen() failed with error [%s]\n", strerror(errno));	
		return 1;	
	}		
	if(DEBUG) printf("\nOpen() successful\n");

	fd3 = open(filepath3, O_RDWR);
	if(fd3 == -1){
		printf("\nopen() failed with error [%s]\n", strerror(errno));	
		return 1;	
	}		
	if(DEBUG) printf("\nOpen() successful\n");




	while(i < filesize-lps){
		returnval = read(fd1, bf, NUMBEROFBYTES);
		if(!flag){
			flag = 1;
			//WRITE TO D1
			returnval = write(fd2, bf, NUMBEROFBYTES);
			i+=NUMBEROFBYTES;
		}else{
			flag = 0;
			//CHECK IF WE CAN READ EXTRA 50 BYTES
			if(i+(NUMBEROFBYTES*2) > filesize-lps){
				//WRITE TO D2
				returnval = write(fd3, bf, NUMBEROFBYTES);
				i+=NUMBEROFBYTES;
			}else{
				returnval = read(fd1, bf, NUMBEROFBYTES);
				returnval = write(fd3, bf, NUMBEROFBYTES);
				i+=NUMBEROFBYTES*2;
			}
		}		
	}
	
	if(lps > 0){
		returnval = read(fd1, bf, NUMBEROFBYTES);
		if(!flag) returnval = write(fd2, bf, NUMBEROFBYTES);
		else returnval = write(fd3, bf, NUMBEROFBYTES);
	}



	if(close(fd1) != 0){
		strerror(errno);
		return 1;
	}

	if(close(fd2) != 0){
		strerror(errno);
		return 1;
	}

	if(close(fd3) != 0){
		strerror(errno);
		return 1;
	}


	//done
	return 0;
}

int checkFile(char* filepath){
	int returnval;

	// Check file existence
	returnval = access(filepath, F_OK);
	if (returnval == 0){
		if(DEBUG) printf ("%s exists\n", filepath);
	}else{
		if (errno == ENOENT){
			printf ("%s does not exist\n", filepath);
			return -1;
		}
		else if (errno == EACCES){
			printf ("%s is not accessible\n", filepath);
			return -2;
		}
	}
	/* Check read access. */
	returnval = access (filepath, R_OK);
	if (returnval == 0){
		if(DEBUG) printf("%s is readable\n", filepath);
	}else{
		printf ("%s is not readable (access denied)\n", filepath);
		return -3;
	}
	/* Check write access. */
	returnval = access (filepath, W_OK);
	if (returnval == 0){
		if(DEBUG) printf("%s is writable\n", filepath);
	}else if (errno == EACCES){
		printf ("%s is not writable (access denied)\n", filepath);
		return -4;
	}else if (errno == EROFS){
		printf ("%s is not writable (read-only filesystem)\n", filepath);
		return -5;
	}
	return 0;
}
