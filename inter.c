#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char stackA[MAX]; // Stack for operators
char stackB[MAX][MAX]; // Stack for operands
char stackC[MAX][MAX]; // Stack for storing intermediate code
int topA = -1, topB = -1, topC = -1;
int tempVarCount = 1; // Temporary variable counter

void pushA(char ch) {
    stackA[++topA] = ch;
}

char popA() {
    if (topA >= 0)
        return stackA[topA--];
    return '\0';
}

void pushB(char *str) {
    strcpy(stackB[++topB], str);
}

void popB(char *str) {
    if (topB >= 0)
        strcpy(str, stackB[topB--]);
}

void pushC(char *str) {
    strcpy(stackC[++topC], str);
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void generateIntermediateCode(char *expr) {
    char temp[2] = "t";
    char operand1[MAX], operand2[MAX], result[MAX];
    char intermediate[MAX];
    int i = 0;

    while (expr[i] != '\0') {
        if (isalnum(expr[i])) { // If it's an operand
            char operand[2] = {expr[i], '\0'};
            pushB(operand);
        } else if (expr[i] == '(') {
            pushA(expr[i]);
        } else if (expr[i] == ')') {
            while (stackA[topA] != '(') {
                char op = popA();
                popB(operand2);
                popB(operand1);
                sprintf(result, "t%d", tempVarCount++);
                sprintf(intermediate, "%s = %s %c %s", result, operand1, op, operand2);
                pushC(intermediate);
                pushB(result);
            }
            popA(); // Remove '(' from stackA
        } else { // It's an operator
            while (topA != -1 && precedence(stackA[topA]) >= precedence(expr[i])) {
                char op = popA();
                popB(operand2);
                popB(operand1);
                sprintf(result, "t%d", tempVarCount++);
                sprintf(intermediate, "%s = %s %c %s", result, operand1, op, operand2);
                pushC(intermediate);
                pushB(result);
            }
            pushA(expr[i]);
        }
        i++;
    }

    while (topA != -1) {
        char op = popA();
        popB(operand2);
        popB(operand1);
        sprintf(result, "t%d", tempVarCount++);
        sprintf(intermediate, "%s = %s %c %s", result, operand1, op, operand2);
        pushC(intermediate);
        pushB(result);
    }
}

void printIntermediateCode() {
    printf("Intermediate Code:\n");
    for (int i = 0; i <= topC; i++) {
        printf("%s\n", stackC[i]);
    }
}

int main() {
    char expression[MAX];
    printf("Enter an expression: ");
    scanf("%s", expression);

    generateIntermediateCode(expression);
    printIntermediateCode();

    return 0;
}
