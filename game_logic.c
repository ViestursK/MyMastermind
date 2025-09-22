#include "game.h"

// Global variables for guess processing
char inputBuffer[SECRET_CODE_BUFFER];
int inputBufferPosition = 0;
int inputBufferLength = 0;

// Secret Code Generation Functions
void generateSecretCode(char charList[], char* code) {
    strncpy(code, charList, 4);
    code[4] = '\0';
}

// Fisher-Yates algorithm for shuffling array
void mix(char* charList, int count) {
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = charList[i];
        charList[i] = charList[j];
        charList[j] = temp;
    }
}

// Getting the aut-generated code
char* getSecretCode() {
    static char randomCharacters[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
    static char code[SECRET_CODE_BUFFER];
    mix(randomCharacters, 9);
    generateSecretCode(randomCharacters, code);
    return code;
}

// Game Message Functions
void printStartGameMessage() {
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
}

void printRound(int round) {
    printf("---\nRound %d\n", round);
}

// Counting Position Functions
void resetVisitedArray(int* visited, int size) {
    for (int i = 0; i < size; i++) visited[i] = 0;
}

int countCorrectPositions(char* secret, char* guess, int size, int* visited) {
    int correct = 0;
    for (int i = 0; i < size; i++) {
        if (secret[i] == guess[i]) {
            correct++;
            visited[i] = 1;
        }
    }
    return correct;
}

int countMisplacedPositions(char* secret, char* guess, int size, int* visited) {
    int misplaced = 0;
    for (int i = 0; i < size; i++) {
        if (secret[i] != guess[i]) {
            for (int j = 0; j < size; j++) {
                if (secret[i] == guess[j] && visited[j] == 0) {
                    misplaced++;
                    visited[j] = 1;
                    break;
                }
            }
        }
    }
    return misplaced;
}

// For getting game stats
void countPositions(char* secret, char* guess) {
    int size = myStrlen(secret);
    int visited[size];
    resetVisitedArray(visited, size);

    int correct = countCorrectPositions(secret, guess, size, visited);
    resetVisitedArray(visited, size);  // Reset for misplaced count
    int misplaced = countMisplacedPositions(secret, guess, size, visited);

    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", correct, misplaced);
}

// Guess Input Functions 
int readInput() {
    ssize_t bytes_read = read(STDIN_FILENO, inputBuffer, SECRET_CODE_BUFFER - 1);
    if (bytes_read <= 0) {
        return (bytes_read == 0) ? 0 : -1;  // Handle EOF or error
    }
    
    inputBuffer[bytes_read] = '\0';
    inputBufferLength = bytes_read;
    inputBufferPosition = 0;
    return 1;
}

int extractGuess(char* guessBuffer) {
    int guessPosition = 0;
    while (inputBufferPosition < inputBufferLength && inputBuffer[inputBufferPosition] != '\n') {
        guessBuffer[guessPosition++] = inputBuffer[inputBufferPosition++];
    }

    if (inputBuffer[inputBufferPosition] == '\n') inputBufferPosition++;
    guessBuffer[guessPosition] = '\0';
    return guessPosition;
}

int getGuess(char* guessBuffer) {
    if (inputBufferPosition >= inputBufferLength && readInput() <= 0) return 0;
    extractGuess(guessBuffer);
    return 1;
}

int isValidFormatGuess(char* guessBuffer) {
    if (!isValidCodeInput(guessBuffer)) {
        printf("Wrong input!\n");
        return 0;
    }
    return 1;
}

// Main guessing function that manages user input and game logic
int guess(char* guessBuffer) {
    if (!getGuess(guessBuffer)) return -1;
    return isValidFormatGuess(guessBuffer) ? 1 : 0;
}

// Game Termination Functions
void isGameOver(int currentRound, int attempts, char* secretCode) {
    if (currentRound >= attempts) {
        printf("Game over. The secret code was: %s", secretCode);
    }
}

int isCorrectGuess(char* guessBuffer, char* secretCode) {
    if (strcmp(guessBuffer, secretCode) == 0) {
        printf("Congratulations! You did it!");
        return 1;
    }
    return 0;
}

// Game Loop Functions
void processGuess(char* guessBuffer, char* secretCode, int* currentRound) {
    countPositions(secretCode, guessBuffer);
    (*currentRound)++;
}

// Function to start the game
void startGame(int attempts, char* secretCode) {
    printf("Game started with %d attempts and secret code: %s\n", attempts, secretCode);
    printStartGameMessage();
    int currentRound = 0;
    char guessBuffer[SECRET_CODE_BUFFER];

    while (currentRound < attempts) {
        int result = guess(guessBuffer); // Prompt and validate guess
        if (result == -1) {
            printf("Exiting...");
            return; // EOF or error, exit
        }
        if (result == 1) {
            if (isCorrectGuess(guessBuffer, secretCode)) return;
            processGuess(guessBuffer, secretCode, &currentRound);
            printRound(currentRound);
        }
    }
    isGameOver(currentRound, attempts, secretCode);
}

// Function to start the game with default settings
void startWithDefaultSettings(int attempts) {
    char* secretCode = getSecretCode();
    startGame(attempts, secretCode);
}

// Function to start the game with custom settings 
void startWithCustomSettings(int argc, char* argv[], int* attempts, char** secretCode) {
    if (!parseInput(argc, argv, attempts, secretCode)) {
        return; // Error
    }

    // If the secret code is the default value, generate a new one
    if (strcmp(*secretCode, "0000") == 0) {
        *secretCode = getSecretCode();
    }

    startGame(*attempts, *secretCode);
}

// Main function to initiate the program
int main(int argc, char* argv[]) {
    char* secretCode = "0000"; // Default secret code
    int attempts = 10; // Default number of attempts
    srand(time(NULL)); // Seed the random number generator

    // Check if any command-line arguments were provided
    if (argc == 1) {
        startWithDefaultSettings(attempts);
    }
    else {
        startWithCustomSettings(argc, argv, &attempts, &secretCode);
    }

    return 0;
}
