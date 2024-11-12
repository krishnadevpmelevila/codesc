#include <stdio.h>
#include <string.h>

struct {
    int a, b, f, flag;
    char name[20];
} a[10];

int n, m, x, k, l, m1, c, ch;

void replace(int x, int y) {
    int i;
    for (i = 0; i < n; i++) {
        if (a[i].flag == 1) {
            if (a[i].a == x) a[i].a = y;
            if (a[i].b == x) a[i].b = y;
        }
    }
}

void minimize() {
    do {
        ch = 0;
        for (int i = 0; i < n - 1; i++) {
            if (a[i].flag == 1) {
                for (int j = i + 1; j < n; j++) {
                    if (a[j].flag == 1) {
                        if (a[i].a == a[j].a && a[i].b == a[j].b && a[i].f == a[j].f) {
                            printf("Merging %s and %s\n", a[i].name, a[j].name);
                            a[j].flag = 0;
                            replace(a[j].f, a[i].f);
                            ch = 1;
                        }
                    }
                }
            }
        }
    } while (ch == 1);
}

void unreachable() {
    do {
        ch = 0;
        for (int i = 0; i < n; i++) {
            if (a[i].flag == 1) {
                c = 0;
                for (int j = 0; j < n; j++) {
                    if (a[j].flag == 1 && (a[j].a == i || a[j].b == i)) {
                        c = 1;
                        break;
                    }
                }
                if (c == 0 && i != 0) { // Start state assumed to be 0
                    a[i].flag = 0;
                    ch = 1;
                }
            }
        }
    } while (ch == 1);
}

int main() {
    printf("Enter the number of states: ");
    scanf("%d", &n);

    printf("Enter the transition table for DFA (state, a, b):\n");
    for (int i = 0; i < n; i++) {
        printf("State %d: ", i);
        scanf("%d %d %d", &a[i].f, &a[i].a, &a[i].b);
        sprintf(a[i].name, "q%d", i);
        a[i].flag = 1;
    }

    printf("Enter the number of final states: ");
    scanf("%d", &m);
    printf("Enter the final states: ");
    for (int i = 0; i < m; i++) {
        int final_state;
        scanf("%d", &final_state);
        a[final_state].f = 1;
    }

    unreachable();
    minimize();

    printf("\nMinimized DFA:\n");
    printf("State\tA\tB\n");
    for (int i = 0; i < n; i++) {
        if (a[i].flag == 1) {
            printf("%s\t%d\t%d\n", a[i].name, a[i].a, a[i].b);
        }
    }

    return 0;
}
