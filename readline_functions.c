#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    while (1) {
        // Display prompt and read input
        input = readline("Enter command (type 'exit' to quit): ");

        // Check for EOF (Ctrl+D) or 'exit' command
        if (!input || strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        // Add input to history (if it's not empty)
        if (*input) {
            add_history(input);
        }

        // Example usage of rl_replace_line and rl_redisplay
        rl_replace_line("You entered: ", 0);
        rl_redisplay();

        // Free the allocated memory for the input
        free(input);
    }

    // Clear history before exiting
    rl_clear_history();

    return 0;
}


/*
These are just some of the readline finctions we will need to get familiar with; code and explanation is from ChatGPT
Explanation of the code:

Readline Loop: The program enters an infinite loop where it displays a prompt and waits for the user to enter a command.

Reading Input: readline("Enter command (type 'exit' to quit): ") displays the prompt and reads a line from the terminal.
If the user presses Ctrl+D (EOF) or types 'exit', the loop breaks, and the program exits.

Adding to History: add_history(input) adds the non-empty input to readline's internal history list.
This allows the user to navigate through previous inputs using the arrow keys.

Editing and Redisplaying: rl_replace_line and rl_redisplay are used to replace the current line in the readline buffer and immediately redisplay it.
This is just an example of how these functions can be used.
In this code, it replaces the user's input with "You entered: " and then redisplays the line. This does not affect the actual history.

Freeing Input: After processing, the memory allocated for input is freed.

Clearing History: Before exiting the program, rl_clear_history() clears the readline history list.

To compile this program, you'll need to link it with the readline library:

bash
Copy code
gcc -o myprogram myprogram.c -lreadline
Run the compiled program, and you should be able to enter commands, see them replaced with "You entered: ", and navigate through the history with the arrow keys.
Remember, this is a basic demonstration, and the readline library offers a lot more functionality that can be explored for more complex applications.
*/