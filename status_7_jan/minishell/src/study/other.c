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
        //rl_replace_line("You entered: ", 0);
        //rl_redisplay();

        // Free the allocated memory for the input
        free(input);
    }

    // Clear history before exiting
    rl_clear_history();

    return 0;
}