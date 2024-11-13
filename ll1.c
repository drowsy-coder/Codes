#include <stdio.h>
#include <ctype.h>
#include <string.h>

void followfirst(char, int, int);
void findfirst(char, int, int);
void follow(char c);

int prod_count, first_count = 0;
char calc_first[10][100];
char calc_follow[10][100];
int follow_count = 0;
char production[10][10], first[10];
char follow_result[10];
int first_index;
char current_char;
int epsilon;

int main(int argc, char **argv) {
    int first_index_temp = 0;
    int follow_index_temp = 0;
    int i, choice;
    char c, ch;

    printf("Enter the number of productions: ");
    scanf("%d", &prod_count);

    printf("\nEnter %d productions in the form A=B where A and B are grammar symbols:\n\n", prod_count);
    for (i = 0; i < prod_count; i++) {
        scanf("%s%c", production[i], &ch);
    }

    char done[prod_count];
    int ptr = -1;

    for (first_index = 0; first_index < prod_count; first_index++) {
        for (int kay = 0; kay < 100; kay++) {
            calc_first[first_index][kay] = '!';
        }
    }

    for (first_index = 0; first_index < prod_count; first_index++) {
        c = production[first_index][0];
        int point1 = 0, point2 = 0, xxx = 0;

        for (int kay = 0; kay <= ptr; kay++) {
            if (c == done[kay]) {
                xxx = 1;
            }
        }
        if (xxx == 1) continue;

        findfirst(c, 0, 0);
        ptr += 1;
        done[ptr] = c;

        printf("\n First(%c)= { ", c);
        calc_first[point1][point2++] = c;

        for (i = 0 + first_index_temp; i < first_count; i++) {
            int lark = 0, chk = 0;
            for (lark = 0; lark < point2; lark++) {
                if (first[i] == calc_first[point1][lark]) {
                    chk = 1;
                    break;
                }
            }
            if (chk == 0) {
                printf("%c, ", first[i]);
                calc_first[point1][point2++] = first[i];
            }
        }
        printf("}\n");
        first_index_temp = first_count;
        point1++;
    }

    printf("\n");
    printf("-------------------------------------------------\n\n");

    char done_follow[prod_count];
    ptr = -1;

    for (first_index = 0; first_index < prod_count; first_index++) {
        for (int kay = 0; kay < 100; kay++) {
            calc_follow[first_index][kay] = '!';
        }
    }

    int point1 = 0;
    int follow_land = 0;

    for (epsilon = 0; epsilon < prod_count; epsilon++) {
        current_char = production[epsilon][0];
        int point2 = 0, xxx = 0;

        for (int kay = 0; kay <= ptr; kay++) {
            if (current_char == done_follow[kay]) {
                xxx = 1;
            }
        }
        if (xxx == 1) continue;

        follow_land += 1;
        follow(current_char);
        ptr += 1;
        done_follow[ptr] = current_char;

        printf(" Follow(%c) = { ", current_char);
        calc_follow[point1][point2++] = current_char;

        for (i = 0 + follow_index_temp; i < follow_count; i++) {
            int lark = 0, chk = 0;
            for (lark = 0; lark < point2; lark++) {
                if (follow_result[i] == calc_follow[point1][lark]) {
                    chk = 1;
                    break;
                }
            }
            if (chk == 0) {
                printf("%c, ", follow_result[i]);
                calc_follow[point1][point2++] = follow_result[i];
            }
        }
        printf(" }\n\n");
        follow_index_temp = follow_count;
        point1++;
    }

    char terminals[10];
    for (first_index = 0; first_index < 10; first_index++) {
        terminals[first_index] = '!';
    }

    int terminal_index = 0;

    for (first_index = 0; first_index < prod_count; first_index++) {
        for (int kay = 0; kay < prod_count; kay++) {
            if (!isupper(production[first_index][kay]) &&
                production[first_index][kay] != '#' && production[first_index][kay] != '=' &&
                production[first_index][kay] != '\0') {

                int vp = 0;
                for (int ap = 0; ap < terminal_index; ap++) {
                    if (production[first_index][kay] == terminals[ap]) {
                        vp = 1;
                        break;
                    }
                }
                if (vp == 0) {
                    terminals[terminal_index] = production[first_index][kay];
                    terminal_index++;
                }
            }
        }
    }

    terminals[terminal_index] = '$';
    terminal_index++;

    printf("\nThe LL(1) Parsing Table for the given grammar:\n");
    printf("==========================================================\n");
    printf("\t\t|\t");
    for (int ap = 0; ap < terminal_index; ap++) {
        printf("%c\t", terminals[ap]);
    }
    printf("\n==========================================================\n");

    char first_prod[prod_count][terminal_index];

    for (int ap = 0; ap < prod_count; ap++) {
        int destiny = 0;
        first_index = 2;
        int ct = 0;
        char tem[100];

        while (production[ap][first_index] != '\0') {
            if (!isupper(production[ap][first_index])) {
                tem[ct++] = production[ap][first_index];
                tem[ct++] = '_';
                tem[ct++] = '\0';
                first_index++;
                break;
            } else {
                for (int zap = 0; zap < prod_count; zap++) {
                    if (calc_first[zap][0] == production[ap][first_index]) {
                        for (int tuna = 1; tuna < 100; tuna++) {
                            if (calc_first[zap][tuna] != '!') {
                                tem[ct++] = calc_first[zap][tuna];
                            } else {
                                break;
                            }
                        }
                        break;
                    }
                }
                tem[ct++] = '_';
            }
            first_index++;
        }

        for (int tuna = 0; tuna < ct; tuna++) {
            if (tem[tuna] == '#') {
                continue;
            } else if (tem[tuna] == '_') {
                break;
            } else {
                first_prod[ap][destiny++] = tem[tuna];
            }
        }
    }

    char table[follow_land][terminal_index + 1];
    ptr = -1;

    for (int ap = 0; ap < follow_land; ap++) {
        for (int kay = 0; kay < (terminal_index + 1); kay++) {
            table[ap][kay] = '!';
        }
    }

    for (int ap = 0; ap < prod_count; ap++) {
        current_char = production[ap][0];
        int xxx = 0;

        for (int kay = 0; kay <= ptr; kay++) {
            if (current_char == table[kay][0]) {
                xxx = 1;
            }
        }
        if (xxx == 1) continue;

        ptr = ptr + 1;
        table[ptr][0] = current_char;
    }

    for (int ap = 0; ap < prod_count; ap++) {
        int tuna = 0;
        while (first_prod[ap][tuna] != '\0') {
            int to, ni = 0;
            for (to = 0; to < terminal_index; to++) {
                if (first_prod[ap][tuna] == terminals[to]) {
                    ni = 1;
                }
            }
            if (ni == 1) {
                char xz = production[ap][0];
                int cz = 0;
                while (table[cz][0] != xz) {
                    cz = cz + 1;
                }
                int vz = 0;
                while (terminals[vz] != first_prod[ap][tuna]) {
                    vz = vz + 1;
                }
                table[cz][vz + 1] = (char)(ap + 65);
            }
            tuna++;
        }
    }

    for (first_index = 0; first_index < terminal_index; first_index++) {
        for (int kay = 0; kay < 100; kay++) {
            if (calc_first[first_index][kay] == '!') {
                break;
            } else if (calc_first[first_index][kay] == '#') {
                int fz = 1;
                while (calc_follow[first_index][fz] != '!') {
                    char xz = production[first_index][0];
                    int cz = 0;
                    while (table[cz][0] != xz) {
                        cz = cz + 1;
                    }
                    int vz = 0;
                    while (terminals[vz] != calc_follow[first_index][fz]) {
                        vz = vz + 1;
                    }
                    table[first_index][vz + 1] = '#';
                    fz++;
                }
                break;
            }
        }
    }

    for (int ap = 0; ap < follow_land; ap++) {
        printf("\t\t %c\t|\t", table[ap][0]);
        for (int kay = 1; kay < (terminal_index + 1); kay++) {
            if (table[ap][kay] == '!') {
                printf("\t");
            } else if (table[ap][kay] == '#') {
                printf("%c=#\t", table[ap][0]);
            } else {
                int mum = (int)(table[ap][kay]);
                mum -= 65;
                printf("%s\t", production[mum]);
            }
        }
        printf("\n");
        printf("----------------------------------------------------------\n");
    }

    printf("\n\nPlease enter the desired INPUT STRING = ");
    char input[100];
    scanf("%s%c", input, &ch);

    printf("\n==========================================================\n");
    printf("\t\tStack\t\tInput\t\tAction");
    printf("\n==========================================================\n");

    int i_ptr = 0, s_ptr = 1;
    char stack[100];
    stack[0] = '$';
    stack[1] = table[0][0];

    while (s_ptr != -1) {
        printf("\t\t");
        for (int vamp = 0; vamp <= s_ptr; vamp++) {
            printf("%c", stack[vamp]);
        }
        printf("\t\t");
        for (int vamp = i_ptr; input[vamp] != '\0'; vamp++) {
            printf("%c", input[vamp]);
        }
        printf("\t\t");

        char her = input[i_ptr];
        char him = stack[s_ptr];
        s_ptr--;

        if (!isupper(him)) {
            if (her == him) {
                i_ptr++;
                printf("POP ACTION\n");
            } else {
                printf("\nString Not Accepted by LL(1) Parser !!\n");
                exit(0);
            }
        } else {
            int i;
            for (i = 0; i < terminal_index; i++) {
                if (terminals[i] == her) break;
            }

            char produ[100];
            int j;
            for (j = 0; j < follow_land; j++) {
                if (him == table[j][0]) {
                    if (table[j][i + 1] == '#') {
                        printf("%c=#\n", table[j][0]);
                        produ[0] = '#';
                        produ[1] = '\0';
                    } else if (table[j][i + 1] != '!') {
                        int mum = (int)(table[j][i + 1]);
                        mum -= 65;
                        strcpy(produ, production[mum]);
                        printf("%s\n", produ);
                    } else {
                        printf("\nString Not Accepted by LL(1) Parser !!\n");
                        exit(0);
                    }
                }
            }

            int le = strlen(produ);
            le = le - 1;
            if (le == 0) {
                continue;
            }
            for (j = le; j >= 2; j--) {
                s_ptr++;
                stack[s_ptr] = produ[j];
            }
        }
    }

    printf("\n==========================================================\n");
    if (input[i_ptr] == '\0') {
        printf("\t\t\tYOUR STRING HAS BEEN ACCEPTED !!\n");
    } else {
        printf("\n\t\t\tYOUR STRING HAS BEEN REJECTED !!\n");
    }
    printf("==========================================================\n");

    return 0;
}

void follow(char c) {
    if (production[0][0] == c) {
        follow_result[follow_count++] = '$';
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 2; j < 10; j++) {
            if (production[i][j] == c) {
                if (production[i][j + 1] != '\0') {
                    followfirst(production[i][j + 1], i, (j + 2));
                }
                if (production[i][j + 1] == '\0' && c != production[i][0]) {
                    follow(production[i][0]);
                }
            }
        }
    }
}

void findfirst(char c, int q1, int q2) {
    if (!isupper(c)) {
        first[first_count++] = c;
        return;
    }

    for (int j = 0; j < prod_count; j++) {
        if (production[j][0] == c) {
            if (production[j][2] == '#') {
                if (production[q1][q2] == '\0') {
                    first[first_count++] = '#';
                } else if (production[q1][q2] != '\0' && (q1 != 0 || q2 != 0)) {
                    findfirst(production[q1][q2], q1, (q2 + 1));
                } else {
                    first[first_count++] = '#';
                }
            } else if (!isupper(production[j][2])) {
                first[first_count++] = production[j][2];
            } else {
                findfirst(production[j][2], j, 3);
            }
        }
    }
}

void followfirst(char c, int c1, int c2) {
    if (!isupper(c)) {
        follow_result[follow_count++] = c;
    } else {
        int i = 0, j = 1;
        for (i = 0; i < prod_count; i++) {
            if (calc_first[i][0] == c) break;
        }

        while (calc_first[i][j] != '!') {
            if (calc_first[i][j] != '#') {
                follow_result[follow_count++] = calc_first[i][j];
            } else {
                if (production[c1][c2] == '\0') {
                    follow(production[c1][0]);
                } else {
                    followfirst(production[c1][c2], c1, c2 + 1);
                }
            }
            j++;
        }
    }
}
