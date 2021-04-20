#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define X 78
#define Y 20

int Tab1[X][Y];
int Tab2[X][Y];
static const char filename[] = "Universe.txt";

void init()
{
    int i, j;
    for (j = 0; j < Y; j++) {
        for (i = 0; i < X; i++) {
            Tab1[i][j] = 0;
            Tab2[i][j] = 0;
        }
    }

    FILE* file = fopen(filename, "r");

    if (file != NULL) {
        int row = 0;
        int col = 0;

        int c;
        while ((c = getc(file)) != EOF) {
            if (c == 10) {
                row++;
                col = 0;
            } else {
                c -= 48;
                if (c == 1) {
                    Tab1[col][row] = 1;
                }
                col++;
            }
        }
        fclose(file);
    }
}

int check(int i, int j)
{
    int nb = 0;
    int x, y;

    for (x = i - 1; x <= (i + 1); x++) {
        for (y = j - 1; y <= (j + 1); y++) {
            if ((x == i) && (y == j)) {
                continue;
            }

            if ((y < Y) && (x < X) && (x >= 0) && (y >= 0)) {
                nb += Tab1[x][y];
            }
        }
    }

    return nb;
}

void show()
{
    int i, j;
    for (i = 0; i < (X + 2); i++) {
        printf("#");
    }

    printf("\n");

    for (j = 0; j < Y; j++) {
        printf("#");
        for (i = 0; i < X; i++) {
            if (Tab1[i][j] == 0) {
                printf(" ");
            }
            if (Tab1[i][j] == 1) {
                printf("O");
            }
        }
        printf("#");
        printf("\n");
    }

    for (i = 0; i < (X + 2); i++) {
        printf("#");
    }

    printf("\n");
}

void copy()
{
    int i, j;
    for (j = 0; j < Y; j++) {
        for (i = 0; i < X; i++) {
            Tab1[i][j] = Tab2[i][j];
        }
    }
}

void main()
{
    init();
    while (1) {
        system("cls");
        show();

        int i, j;
        for (j = 0; j < Y; j++) {
            for (i = 0; i < X; i++) {
                if (check(i, j) == 3) {
                    Tab2[i][j] = 1;
                }

                if (check(i, j) == 2) {
                    Tab2[i][j] = Tab1[i][j];
                }

                if ((check(i, j) < 2) || (check(i, j) > 3)) {
                    Tab2[i][j] = 0;
                }
            }
        }

        copy();
        Sleep(1000);
    }
}
