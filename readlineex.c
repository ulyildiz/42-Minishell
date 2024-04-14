#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>


int main() {
    char *input_line;

    // Loop to read commands until the user enters "exit"
    while (1) {
        // Read input from the user
        input_line = readline(getcwd());
		write(2, "qeq", 3);
        // Check if the user entered "exit"
        if (strcmp(input_line, "exit") == 0) {
            // Free the memory allocated for the input buffer
            free(input_line);
            break;  // Exit the loop
        }

        // Add the entered command to history
        add_history(input_line);

        // Free the memory allocated for the input buffer
        free(input_line);
    }

    return 0;
}
