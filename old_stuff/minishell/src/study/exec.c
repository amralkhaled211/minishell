#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    char *const program = "/bin/ls";
    char *const arguments[] = { "ls", "-l", NULL};
    char *const environment[] = { NULL };
    int *status;

    printf("Before execve\n");

    int child_pid = fork();
    // Execute the /bin/ls program with the specified arguments and environment
    if (child_pid == 0)
    {
        if (execve(program, arguments, environment) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    waitpid(-1, status, 0);
  //  printf("status: %i\n", *status);

    // This line will not be executed if execve is successful
    printf("After execve\n");

    return 0;
}