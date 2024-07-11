#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to recreate value based on quotes and whitespace
void recreate_value(char ***value) {
    int i, j = 0, token_len = 0, in_quotes = 0;
    int max_tokens = 10;  // Initial max number of tokens, will resize if needed
    char **new_value = malloc(sizeof(char*) * max_tokens);
    char *token = malloc(256);  // Arbitrary initial size, can be resized if needed

    // Process each string in the existing value array
    for (i = 0; (*value)[i] != NULL; i++) {
        const char *input = (*value)[i];
        int input_len = strlen(input);

        for (int k = 0; k < input_len; k++) {
            if (input[k] == '"') {
                in_quotes = !in_quotes;  // Toggle the quoted state
            } else if (isspace(input[k]) && !in_quotes) {
                if (token_len > 0) {  // End of a token
                    token[token_len] = '\0';
                    new_value[j++] = strdup(token);  // Store the token
                    token_len = 0;

                    // Resize new_value array if necessary
                    if (j >= max_tokens) {
                        max_tokens *= 2;
                        new_value = realloc(new_value, sizeof(char*) * max_tokens);
                    }
                }
            } else {
                token[token_len++] = input[k];
            }
        }

        if (token_len > 0) {
            token[token_len] = '\0';
            new_value[j++] = strdup(token);  // Store the last token
            token_len = 0;

            // Resize new_value array if necessary
            if (j >= max_tokens) {
                max_tokens *= 2;
                new_value = realloc(new_value, sizeof(char*) * max_tokens);
            }
        }
    }

    new_value[j] = NULL;  // Null-terminate the array

    // Free the original value array
    for (i = 0; (*value)[i] != NULL; i++) {
        free((*value)[i]);
    }
    free(*value);

    *value = new_value;

    free(token);
}

// Function to print value array
void print_value(char **value) {
    int i = 0;
    while (value[i]) {
        printf("value[%d]: %s\n", i, value[i]);
        i++;
    }
}

int main() {
    // Initial value array
    char *initial_value[] = {
        "ech\"o -n            s\"",
        NULL
    };

    // Copy the initial value array to **value
    char **value = malloc(sizeof(initial_value));
    for (int i = 0; initial_value[i] != NULL; i++) {
        value[i] = strdup(initial_value[i]);
    }
    value[sizeof(initial_value) / sizeof(char*) - 1] = NULL;

    // Recreate value array
    recreate_value(&value);
    print_value(value);

    // Free the value array
    for (int i = 0; value[i] != NULL; i++) {
        free(value[i]);
    }
    free(value);

    return 0;
}

