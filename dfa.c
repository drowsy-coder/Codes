#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_ALPHABET 26
#define MAX_STATE_NAME_LENGTH 10

typedef struct {
    int numStates;
    int numFinalStates;
    char states[MAX_STATES][MAX_STATE_NAME_LENGTH];
    char finalStates[MAX_STATES][MAX_STATE_NAME_LENGTH];
    int transition[MAX_STATES][MAX_ALPHABET];
    char startState[MAX_STATE_NAME_LENGTH];
    char alphabet[MAX_ALPHABET];
} DFA;

void initializeDFA(DFA* dfa) {
    dfa->numStates = 0;
    dfa->numFinalStates = 0;
    memset(dfa->transition, -1, sizeof(dfa->transition));
}

int getAlphabetIndex(DFA* dfa, char symbol) {
    for (int i = 0; i < strlen(dfa->alphabet); i++) {
        if (dfa->alphabet[i] == symbol) {
            return i;
        }
    }
    return -1;
}

int getStateIndex(DFA* dfa, char* state) {
    for (int i = 0; i < dfa->numStates; i++) {
        if (strcmp(dfa->states[i], state) == 0) {
            return i;
        }
    }
    return -1;
}

void inputDFA(DFA* dfa) {
    printf("Enter number of states: ");
    scanf("%d", &dfa->numStates);

    printf("Enter the state names:\n");
    for (int i = 0; i < dfa->numStates; i++) {
        scanf("%s", dfa->states[i]);
    }

    printf("Enter alphabet symbols: ");
    scanf("%s", dfa->alphabet);

    printf("Enter number of final states: ");
    scanf("%d", &dfa->numFinalStates);

    printf("Enter final states:\n");
    for (int i = 0; i < dfa->numFinalStates; i++) {
        scanf("%s", dfa->finalStates[i]);
    }

    printf("Enter start state: ");
    scanf("%s", dfa->startState);

    printf("Enter transition rules:\n");
    char fromState[MAX_STATE_NAME_LENGTH], toState[MAX_STATE_NAME_LENGTH];
    for (int i = 0; i < dfa->numStates; i++) {
        for (int j = 0; j < strlen(dfa->alphabet); j++) {
            printf("δ(%s, %c) = ", dfa->states[i], dfa->alphabet[j]);
            scanf("%s", toState);
            int toStateIndex = getStateIndex(dfa, toState);
            dfa->transition[i][j] = toStateIndex;
        }
    }
}

void printTransitionTable(DFA* dfa) {
    printf("\nTransition Table:\n");
    printf("State\\Symbol\t");
    for (int i = 0; i < strlen(dfa->alphabet); i++) {
        printf("%c\t", dfa->alphabet[i]);
    }
    printf("\n");

    for (int i = 0; i < dfa->numStates; i++) {
        printf("%s\t\t", dfa->states[i]);
        for (int j = 0; j < strlen(dfa->alphabet); j++) {
            if (dfa->transition[i][j] != -1) {
                printf("%s\t", dfa->states[dfa->transition[i][j]]);
            } else {
                printf("NULL\t");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int isAccepted(DFA* dfa, char* inputString) {
    int currentStateIndex = getStateIndex(dfa, dfa->startState);
    for (int i = 0; i < strlen(inputString); i++) {
        int alphabetIndex = getAlphabetIndex(dfa, inputString[i]);
        if (alphabetIndex == -1) {
            return 0;
        }
        currentStateIndex = dfa->transition[currentStateIndex][alphabetIndex];
        if (currentStateIndex == -1) {
            return 0;
        }
    }

    for (int i = 0; i < dfa->numFinalStates; i++) {
        if (strcmp(dfa->states[currentStateIndex], dfa->finalStates[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    DFA dfa;
    initializeDFA(&dfa);
    inputDFA(&dfa);
    printTransitionTable(&dfa);

    char inputString[100];
    while (1) {
        printf("Enter the string to be checked: ");
        scanf("%s", inputString);
        if (strcmp(inputString, "end") == 0) {
            return 0;
        }
        if (isAccepted(&dfa, inputString)) {
            printf("The string is accepted by the DFA.\n");
        } else {
            printf("The string is not accepted by the DFA.\n");
        }
    }
    return 0;
}
