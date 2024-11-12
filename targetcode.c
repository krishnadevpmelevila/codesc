#include <stdio.h>
#include <string.h>

void main() {
    char icode[10][30], str[20], opr[10];
    int i = 0, n, j = 0;

    printf("Enter no of codes: ");
    scanf("%d", &n);
    printf("Enter the set of intermediate code:\n");
    do {
        scanf("%s", icode[i]);
        i++;
    } while (i < n);

    printf("\nTarget code generation\n");
    printf("******************************\n");

    i = 0;
    do {
        strcpy(str, icode[i]);
        switch (str[3]) {
            case '+': strcpy(opr, "ADD"); break;
            case '-': strcpy(opr, "SUB"); break;
            case '*': strcpy(opr, "MUL"); break;
            case '/': strcpy(opr, "DIV"); break;
        }
        printf("\nMov %c, R%d", str[2], j);
        printf("\n%s %c, R%d", opr, str[4], j);
        printf("\nMov R%d, %c", j, str[0]);
        i++;
        j++;
    } while (i < n);
    printf("\n");
}
