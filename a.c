
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 25
#define WRITE_END 1
#define READ_END 0

int main() {
    char write_msg[BUFFER_SIZE] = "Merhaba, dünya!";
    int fd[2]; // file descriptors

    // Create the pipe
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) { // Error occurred
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (pid > 0) { // Parent process
        // Close the unused end of the pipe
        close(fd[READ_END]);

        // Write to the pipe
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);

        // Close the write end of the pipe
        close(fd[WRITE_END]);
    } else { // Child process
        // Close both ends of the pipe in the child process
        close(fd[READ_END]);
        close(fd[WRITE_END]);
    }

    return 0;
}
