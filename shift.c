#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX], input[MAX];
int top = -1, i = 0;

// Push onto the stack
void push(char c) {
    stack[++top] = c;
    stack[top + 1] = '\0'; // Null terminate for easy printing
}

// Pop the last element from the stack
void pop() {
    if (top >= 0) {
        top--;
        stack[top + 1] = '\0';
    }
}

// Check if the top of the stack matches any grammar production
void reduce() {
    if (top >= 2 && stack[top] == 'E' && stack[top - 1] == '*' && stack[top - 2] == 'E') {
        printf("Reduce by E -> E * E\n");
        pop();
        pop();
    } else if (top >= 2 && stack[top] == 'E' && stack[top - 1] == '+' && stack[top - 2] == 'E') {
        printf("Reduce by E -> E + E\n");
        pop();
        pop();
    } else if (top >= 2 && stack[top] == ')' && stack[top - 1] == 'E' && stack[top - 2] == '(') {
        printf("Reduce by E -> ( E )\n");
        pop();
        pop();
    } else if (top >= 1 && stack[top] == 'd' && stack[top - 1] == 'i') {
        printf("Reduce by E -> id\n");
        pop();
        stack[top] = 'E'; // Replace "id" with "E"
    }
}

int main() {
    char action[MAX];
    printf("The grammar is:\n");
    printf("E -> E + E\n");
    printf("E -> E * E\n");
    printf("E -> ( E )\n");
    printf("E -> id\n\n");

    printf("Enter the input string: ");
    scanf("%s", input);

    // Add '$' to mark end of input
    strcat(input, "$");

    printf("\nStack\t\tInput\t\tAction\n");
    printf("-----\t\t-----\t\t------\n");

    while (1) {
        // Print the stack and remaining input
        printf("%-12s\t%-12s\t", stack, input + i);

        // Perform shift or reduce actions
        if (input[i] == 'i' && input[i + 1] == 'd') {
            strcpy(action, "Shift -> id");
            push(input[i++]);
            push(input[i++]);
        } else if (input[i] == '+' || input[i] == '*' || input[i] == '(' || input[i] == ')' || input[i] == '$') {
            sprintf(action, "Shift -> %c", input[i]);
            push(input[i++]);
        } else {
            strcpy(action, "Reduce");
            reduce();
        }

        printf("%s\n", action);

        // If we have reduced to just 'E' and end of input, parsing is complete
        if (strcmp(stack, "E") == 0 && input[i] == '$') {
            printf("\nAccepted\n");
            break;
        }

        // If the stack is empty and no further reduction is possible, the input is invalid
        if (top < 0) {
            printf("\nRejected\n");
            break;
        }
    }

    return 0;
}
