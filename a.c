#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#define READ  0
#define WRITE 1

int main(){
    int myPipe[2];
    if (pipe(myPipe) < 0) {
        fprintf(stderr,"Pipe Error!");
        return -1;
    }
	printf("%d - %d\n", myPipe[0], myPipe[1]);
    pid_t pid = fork();
    if (pid < 0)
        perror("Error forking!");       
    else if(pid > 0){
    // Master
        char var[4];

/*         // Sends the first value.
        sprintf(var, "foo");
        close(myPipe[READ]);
        write(myPipe[WRITE], var, sizeof(var));

        // Sends the second value.
        sprintf(var, "bar");
        write(myPipe[WRITE], var, sizeof(var));
        close(myPipe[WRITE]);
 */
        wait(NULL);
       // return 0;
    }
    else if (pid == 0){ // Child
        char received[4];

        // Reads the first value.
		write(myPipe[WRITE], "kek", 3);

        // Reads the second value.
        read(myPipe[READ], received, sizeof(received));
        printf("I have received the following value: %s\n", received);
        exit(1);
    }
	pid = fork();
	if (pid > 0)
		wait(NULL);
	else if (pid == 0)
	{
		char received[4];
		read(myPipe[READ], received, sizeof(received));
		write(myPipe[WRITE], "kik", 3);
 		read(myPipe[READ], received, sizeof(received));
 		printf("I have received the following value: %s\n", received);
	}
  return 0;
}
