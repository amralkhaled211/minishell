/*
execve is a system call in Unix-like operating systems used to execute a new program within the context of the current process.
When execve is called, the current process image is replaced with a new process image specified by the pathname of a program file.
The current process's PID remains the same, but almost all other aspects are replaced by the new program - including code, data, heap, and stack segments.

Here's a basic example in C that demonstrates the use of execve:
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *const program = "/bin/ls";
    char *const arguments[] = { "ls", "-l", NULL };
    char *const environment[] = { NULL };

    printf("Before execve\n");

    // Execute the /bin/ls program with the specified arguments and environment
    if (execve(program, arguments, environment) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }

    // This line will not be executed if execve is successful
    printf("After execve\n");

    return 0;
}


/*
In this example:

Program and Arguments: The program variable specifies the path to the executable (/bin/ls in this case).
The arguments array contains the arguments passed to the program, where the first argument should be the name of the program (ls). 
The array must be NULL-terminated.

Environment: The environment array is used to set the environment variables for the new program.
Here, it's set to NULL, which means the new program will inherit the current process's environment.

Calling execve: execve(program, arguments, environment) replaces the current process image with the new one specified by program.
If successful, the "After execve" line will never be executed, as the current program's code is completely replaced by /bin/ls.

Error Handling: If execve fails (which might happen if the specified file doesn't exist or isn't executable), an error message is printed, and the program exits.

When you run this program, it will execute /bin/ls -l, listing the contents of the current directory in long format.
After execve is called, the remainder of the original program is effectively replaced, so nothing after the execve call in the original program gets executed.
*/