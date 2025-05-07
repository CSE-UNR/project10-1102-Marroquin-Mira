//Author: Mira Marroquin
//Date:05/02/25
//Title: A Sick and Twisted Version of Wordle
//Purpose: To choke the happiness out of any coder. :D

#include <stdio.h>
#include <stdbool.h>


#define WORD_LENGTH 5
#define MAX_GUESSES 4

int stringAnalyze(const char *s1, const char *s2);
int stringLength(const char *str);
void mysteryWord(char *word);
void stringCopy(char *dest, const char *src);
void determineGuess(const char *guess, const char *mystery, char *print, char *pointerRow);
void initialGuesses(char guesses[][WORD_LENGTH + 1], char displays[][WORD_LENGTH + 1], char pointers[][WORD_LENGTH + 1], int count);
void lowerCase(char *word);
bool rightGuess(const char *guess);
bool correctGuess(const char *guess, const char *mystery); 



int main() {
    char mystery[WORD_LENGTH + 1];
    mysteryWord(mystery);

    int guessNumber = 0;
    char guesses[MAX_GUESSES][WORD_LENGTH + 1];
    char print[MAX_GUESSES][WORD_LENGTH + 1];
    char pointers[MAX_GUESSES][WORD_LENGTH + 1];

    while (guessNumber < MAX_GUESSES) {
        char guess[100];
        printf("\nGuess #%d! Enter your guess: ", guessNumber + 1);
        scanf("%s", guess);

        if (guessNumber == MAX_GUESSES - 1) {
        printf("\nFinal guess! Enter your guess: ", guessNumber + 1);
        scanf("%s", guess);
       }

        else if (!rightGuess(guess)) {
            printf("Your guess must be 5 letters long.\nPlease try again:\n");
            continue;
        }

        lowerCase(guess);
        stringCopy(guesses[guessNumber], guess);
        determineGuess(guess, mystery, print[guessNumber], pointers[guessNumber]);

        initialGuesses(guesses, print, pointers, guessNumber + 1);

        if (correctGuess(guess, mystery)) {
            printf("Congratulations! You found the word of the day!\n");
            return 0;
        }

        guessNumber++;
    }

    printf("Sorry! The word was: %s\n", mystery);
    return 0;
}

void mysteryWord(char *word) {
    FILE *file = fopen("word.txt", "r");
    if (file == NULL) {
        printf("Womp womp: Could not open word.txt\n");
        word[0] = '\0';
        return;
    }
    fscanf(file, "%5s", word);
    word[WORD_LENGTH] = '\0'; 
    fclose(file);
}

bool rightGuess(const char *guess) {
    int length = 0;
    while (guess[length] != '\0') {
        char c = guess[length];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            return false;
        }
        length++;
    }
    return length == WORD_LENGTH;
}

void lowerCase(char *word) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (word[i] >= 'A' && word[i] <= 'Z') {
            word[i] = word[i] + 32;
        }
    }
}

void determineGuess(const char *guess, const char *mystery, char *print, char *pointerRow) {
    bool deposit[WORD_LENGTH] = {false};

    for (int i = 0; i < WORD_LENGTH; i++) { //first
        if (guess[i] == mystery[i]) {
            print[i] = guess[i] - 32;  
            deposit[i] = true;
            pointerRow[i] = ' ';
        } else {
            print[i] = guess[i];
            pointerRow[i] = ' ';
        }
    }

    for (int i = 0; i < WORD_LENGTH; i++) { //sec
        if (print[i] == guess[i]) {
            for (int j = 0; j < WORD_LENGTH; j++) {
                if (!deposit[j] && guess[i] == mystery[j]) {
                    pointerRow[i] = '^';
                    deposit[j] = true;
                    break;
                }
            }
        }
    }

    print[WORD_LENGTH] = '\0';
    pointerRow[WORD_LENGTH] = '\0';
}

void initialGuesses(char guesses[][WORD_LENGTH + 1], char prints[][WORD_LENGTH + 1], char pointers[][WORD_LENGTH + 1], int count) {
    printf("\nYour guesses so far:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", prints[i]);
        printf("%s\n", pointers[i]);
    }
}

bool correctGuess(const char *guess, const char *mystery) {
    return stringAnalyze(guess, mystery) == 0;
}

int stringAnalyze(const char *s1, const char *s2) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
    }
    return 0;
}

void stringCopy(char *dest, const char *src) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        dest[i] = src[i];
    }
    dest[WORD_LENGTH] = '\0';
}

int stringLength(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}
