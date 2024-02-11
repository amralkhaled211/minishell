#include <stdio.h>
#include <stdlib.h>

int main() {
    // Get the value of the PATH environment variable
    char* path = getenv("USER");

    // Check if the PATH variable was found
    if (path != NULL) {
        printf("The PATH environment variable is: %s\n", path);
    } else {
        printf("The PATH environment variable could not be found.\n");
    }

    return 0;
}
