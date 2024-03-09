#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    char buffer[100];
    char *msg = "Hello from parent!";
	//printf("%lu\n%lu\n", sizeof(msg), strlen(msg));

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }
	printf("%d\n%d\n", fd[0], fd[1]);
    int pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        // Child process
        close(fd[1]); // Close unused write end
        read(fd[0], buffer, sizeof(buffer));
        printf("%s\n", buffer);
        close(fd[0]);
    } else {
        // Parent process
        close(fd[0]); // Close unused read end
        write(fd[1], msg, strlen(msg)+1);
        close(fd[1]);
        wait(NULL); // Wait for child to finish
    }

    return 0;
}
