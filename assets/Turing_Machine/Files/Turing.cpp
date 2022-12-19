#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXRULES 100
#define TAPESIZE 30
#define START 10

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

typedef struct Rules {
    char state;
    char in;
    char out;
    char move;
    char next_state;
} Rule;

char tape[TAPESIZE];
int cursor;
char state;
int steps;
Rule rules[MAXRULES];

void load_tape()
{
    int i;
    for (i = 0; i < TAPESIZE; i++) {
        tape[i] = '_';
    }
}

void load_input(char input[])
{
    int i;
    for (i = 0; i < strlen(input); i++) {
        tape[i + START] = input[i];
    }
}

void display_tape()
{
    int i;
    char value;

    printf("|");
    for (i = 0; i < TAPESIZE; i++) {
        if (i == cursor)
            printf(" %s%c%s ", KGRN, tape[i], KNRM);
        else
            printf(" %c ", tape[i]);
        printf("|");
    }
    printf("\n");
}

bool load_rules(char filename[])
{
    int cpt = 0;
    int cur = 0;

    if (FILE* file = fopen(filename, "r")) {
        int c;
        while ((c = fgetc(file)) != EOF) {
            switch (c) {
            case ';':
                if (cur < 4)
                    cur++;
                else
                    cur = 0;
                break;
            case '\n':
                cpt++;
                cur = 0;
                break;
            default:
                switch (cur) {
                case 0:
                    rules[cpt].state = c;
                    break;
                case 1:
                    rules[cpt].in = c;
                    break;
                case 2:
                    rules[cpt].out = c;
                    break;
                case 3:
                    rules[cpt].move = c;
                    break;
                case 4:
                    rules[cpt].next_state = c;
                    break;
                }
                break;
            }
        }
        fclose(file);
        return true;
    }
    return false;
}

void display_rules()
{
    int cpt;
    for (cpt = 0; cpt < sizeof(rules); cpt++) {
        if (isalnum(rules[cpt].state))
            printf("Rule %d : %c %c %c %c %c\n", cpt, rules[cpt].state, rules[cpt].in, rules[cpt].out, rules[cpt].move, rules[cpt].next_state);
    }
}

void apply_rules()
{
    int i;
    display_tape();
    while (state != 'H') {
        for (i = 0; i < sizeof(rules); i++) {
            if ((rules[i].state == state) && (rules[i].in == tape[cursor])) {
                tape[cursor] = rules[i].out;

                if (rules[i].move == 'L')
                    cursor++;

                if (rules[i].move == 'R')
                    cursor--;

                state = rules[i].next_state;
                steps++;
                display_tape();
                break;
            }
        }
    }
}

void display_result()
{
    int i;
    printf("Result : ");
    for (i = 0; i < TAPESIZE; i++) {
        if (tape[i] != '_')
            printf("%c", tape[i]);
    }
    printf(" (%d steps)\n", steps);
}

int main(int argc, char* argv[])
{
    if (argc > 1) {
        system("clear");
        cursor = START;
        state = 'A';
        steps = 1;

        load_tape();

        if (argc > 2)
            load_input(argv[2]);

        printf("-------------------------------------------------------------------------------------------------------------------------\n");
        printf("|                                                    TURING MACHINE                                                     |\n");
        printf("- TAPE ------------------------------------------------------------------------------------------------------------------\n");
        display_tape();
        if (load_rules(argv[1])) {
            printf("- RULES -----------------------------------------------------------------------------------------------------------------\n");
            display_rules();
            printf("- WORK ------------------------------------------------------------------------------------------------------------------\n");
            apply_rules();
            printf("-------------------------------------------------------------------------------------------------------------------------\n");
            display_result();
        }
        printf("-------------------------------------------------------------------------------------------------------------------------\n");

        return EXIT_SUCCESS;
    } else {
        printf("Too few Arguments : RULEFILE [INPUT]\n");
        return EXIT_FAILURE;
    }
}