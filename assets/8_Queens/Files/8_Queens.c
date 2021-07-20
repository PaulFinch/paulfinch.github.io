#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int cpt;
int solutions[92];

void record(int tab[])
{
    int temp;
    temp = 10000000 * (tab[0] + 1) + 1000000 * (tab[1] + 1) + 100000 * (tab[2] + 1) + 10000 * (tab[3] + 1) + 1000 * (tab[4] + 1) + 100 * (tab[5] + 1) + 10 * (tab[6] + 1) + (tab[7] + 1);
    solutions[cpt] = temp;
}

void exporter()
{
    FILE* P_FILE;
    P_FILE = fopen("8Queens.txt", "w");
    for (int i = 0; i < 92; i++) {
        fprintf(P_FILE, "%d\n", solutions[i]);
    }
    fprintf(P_FILE, "\n");
    fclose(P_FILE);
    printf("  The result has been exported in file : 8Queens.txt\n\n");
}

void display()
{
    system("cls");
    printf("\n");
    printf(" Solutions :\n");
    printf("\n");
    for (int i = 0; i < 92; i++) {
        printf("   %d\n", solutions[i]);
    }
    printf("\n");
}

void show(int tab[])
{
    system("cls");
    printf("\n");
    int i, j;
    printf("   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 203, 205, 205, 205, 203, 205, 205, 205, 203, 205, 205, 205, 203, 205, 205, 205, 203, 205, 205, 205, 203, 205, 205, 205, 203, 205, 205, 205, 187);
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (j == 0) {
                printf("   %c", 186);
            }

            if (tab[j] == i) {
                printf(" %c ", 157);
            } else {
                printf("   ");
            }

            if (j == 7) {
                printf("%c\n", 186);
            } else {
                printf("%c", 186);
            }
        }
        if (i == 7) {
            printf("   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n", 200, 205, 205, 205, 202, 205, 205, 205, 202, 205, 205, 205, 202, 205, 205, 205, 202, 205, 205, 205, 202, 205, 205, 205, 202, 205, 205, 205, 202, 205, 205, 205, 188);
        } else {
            printf("   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185);
        }
    }
    printf("\n");
    printf("          Solution %d ", cpt + 1);
    printf("%d", tab[0] + 1);
    printf("%d", tab[1] + 1);
    printf("%d", tab[2] + 1);
    printf("%d", tab[3] + 1);
    printf("%d", tab[4] + 1);
    printf("%d", tab[5] + 1);
    printf("%d", tab[6] + 1);
    printf("%d\n", tab[7] + 1);
    Sleep(50);
}

int valid(int ix, int iy, int tab[])
{
    int i;
    for (i = 0; i < iy; i++) {
        if ((tab[i] == ix) || (abs(tab[i] - ix) == abs(i - iy))) {
            return 0;
        }
    }
    return 1;
}

void place(int n, int tab[])
{
    int i;
    if (n == 8) {
        record(tab);
        show(tab);
        cpt++;
    } else {
        for (i = 0; i < 8; i++) {
            if (valid(i, n, tab)) {
                tab[n] = i;
                place(n + 1, tab);
            }
        }
    }
}

int main()
{
    cpt = 0;
    system("cls");
    printf("\n");
    printf("  8 Queens Puzzle\n");
    printf("\n");
    Sleep(1000);

    int tab[8];
    place(0, tab);
    display();
    exporter();
    system("PAUSE");
    return 0;
}