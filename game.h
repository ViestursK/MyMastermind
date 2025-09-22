#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SECRET_CODE_BUFFER 1024

// Utility Functions
size_t myStrlen(char* input);
int myIsdigit(char* input);

// Validation Functions
int isValidLength(char* input);
int isUnique(char* input);
int isPeace(char peace);
int checkPeaces(char* code);
int isValidCodeInput(char* input);

// Flag Processing Functions
int isAttemptsFlag(char* flag);
int isSecretCodeFlag(char* flag);
void applyAttemptsValue(char* val, int* attempts);
void applySecretCodeValue(char* val, char** secretCode);
int processFlag(char* flag, char* val, int* attempts, char** secretCode);

// Parsing Input
int parseInput(int argc, char* argv[], int* attempts, char** secretCode);

// Secret Code Generation
void generateSecretCode(char charList[], char* code);
void mix(char* charList, int count);
char* getSecretCode();

// Game Functions
void printStartGameMessage();
void printRound(int round);
int countCorrectPositions(char* secret, char* guess, int size, int* visited);
int countMisplacedPositions(char* secret, char* guess, int size, int* visited);
void countPositions(char* secret, char* guess);
int getGuess(char* guessBuffer);
int isValidFormatGuess(char* guessBuffer);
int guess(char* guessBuffer);
void isGameOver(int currentRound, int attempts, char* secretCode);
int isCorrectGuess(char* guessBuffer, char* secretCode);
void startGame(int attempts, char* secretCode);
void startWithDefaultSettings(int attempts);  
void startWithCustomSettings(int argc, char* argv[], int* attempts, char** secretCode); 

#endif // GAME_H
