#include "game.h"

// Utility Functions
size_t myStrlen(char* input) {
    size_t len = 0;
    while (*input++) len++;
    return len;
}


int myIsdigit(char* input) {
    while (*input) {
        if (!(*input >= '0' && *input <= '9')) return 0;
        input++;
    }
    return 1;
}

// Validation Functions
int isValidLength(char* input) {
    return myStrlen(input) == 4;
}

int isUnique(char* input) {
    for (int i = 0; input[i] != '\0'; i++) {
        for (int j = i + 1; input[j] != '\0'; j++) {
            if (input[i] == input[j]) {
                return 0;
            }
        }
    }
    return 1;
}

int isPeace(char peace) {
    return (peace >= '0' && peace <= '8');
}

int checkPeaces(char* code) {
    while (*code) {
        if (!isPeace(*code)) return 0;
        code++;
    }
    return 1;
}

int isValidCodeInput(char* input) {
    if (!isValidLength(input)) {
        return 0;
    }
    if (!myIsdigit(input)) {
        return 0;
    }
    if (!isUnique(input)) {
        return 0;
    }
    if (!checkPeaces(input)) {
        return 0;
    }
    return 1;
}

// Flag Processing Functions
int isAttemptsFlag(char* flag) {
    return strcmp(flag, "-t") == 0;
}

int isSecretCodeFlag(char* flag) {
    return strcmp(flag, "-c") == 0;
}

void applyAttemptsValue(char* val, int* attempts) {
    *attempts = atoi(val);
}

void applySecretCodeValue(char* val, char** secretCode) {
    *secretCode = val;
}

int processFlag(char* flag, char* val, int* attempts, char** secretCode) {
    if (isAttemptsFlag(flag)) {
        if (!myIsdigit(val)) {
            return 0;
        }

        applyAttemptsValue(val, attempts);
        return 1;
    }

    if (isSecretCodeFlag(flag)) {
        if (!isValidCodeInput(val)) {
            return 0;
        }

        applySecretCodeValue(val, secretCode);
        return 1;
    }

    return 0;
}

// Parsing Input
int parseInput(int argc, char* argv[], int* attempts, char** secretCode) {
    for (int i = 1; i < argc; i += 2) {
        if (i + 1 >= argc) {
            printf("Missing value for flag %s.\n", argv[i]);
            return 0;
        }

        if (!processFlag(argv[i], argv[i + 1], attempts, secretCode)) {
            printf("Invalid flag or value: %s %s\n", argv[i], argv[i + 1]);
            return 0;
        }
    }

    return 1;
}
