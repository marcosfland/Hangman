#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h> // Add this line to include the necessary header file for the bool type

#define MAX_WORDS 10
#define MAX_WORD_LENGTH 20

const char *wordList[MAX_WORDS] = {
    "programming",
    "hangman",
    "computer",
    "software",
    "algorithm",
    "developer",
    "challenge",
    "language",
    "creative",
    "coding"
};

const char *selectRandomWord() {
    srand(time(NULL));
    return wordList[rand() % MAX_WORDS];
}

void initializeGuessedWord(char *guessedWord, const char *word) {
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        guessedWord[i] = '_';
    }
    guessedWord[length] = '\0';
}

void displayGuessedWord(const char *guessedWord) {
    printf("Current Word: %s\n", guessedWord);
}

// Function to check if the guessed word is complete
int isWordComplete(const char *guessedWord) {
    return strchr(guessedWord, '_') == NULL;
}

void updateGuessedWord(char *guessedWord, const char *word, char guessedLetter) {
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        if (word[i] == guessedLetter) {
            guessedWord[i] = guessedLetter;
        }
    }
}

int main() {
    const char *selectedWord = selectRandomWord();
    char guessedWord[MAX_WORD_LENGTH];

    initializeGuessedWord(guessedWord, selectedWord);

    int attempts = 6; // Number of allowed incorrect attempts
    char guessedLetters[MAX_WORD_LENGTH];
    int numGuessedLetters = 0;

    printf("Welcome to Hangman!\n");

    while (attempts > 0 && !isWordComplete(guessedWord)) {
        displayGuessedWord(guessedWord);
        printf("Attempts left: %d\n", attempts);
        printf("Guessed letters: ");
        for (int i = 0; i < numGuessedLetters; i++) {
            printf("%c ", guessedLetters[i]);
        }

        printf("\n");

        printf("Enter a letter: ");
        char guess;
        scanf(" %c", &guess); // Note the space before %c to consume leftover newline

        // Check if the guessed letter is already guessed
        int alreadyGuessed = 0;
        for (int i = 0; i < numGuessedLetters; i++) {
            if (guessedLetters[i] == guess) {
                alreadyGuessed = 1;
                break;
            }
        }

        if (alreadyGuessed) {
            printf("You already guessed the letter '%c'. Try again.\n", guess);
            continue;
        }

        guessedLetters[numGuessedLetters++] = guess;
        if (strchr(selectedWord, guess) != NULL) {
            printf("Good guess!\n");
            updateGuessedWord(guessedWord, selectedWord, guess);
        } else {
            printf("Incorrect guess. Try again.\n");
            attempts--;
        }
        for (int i = 0; i < numGuessedLetters; i++) {
            printf("%c ", guessedLetters[i]); // Print guessed letters with a space
        }
        printf("\n"); // Newline for better formatting

        printf("Enter a letter: ");
        scanf(" %c", &guess); // Consume potential leftover newline

        // Check if the guessed letter is already guessed
        alreadyGuessed = 0;
        for (int i = 0; i < numGuessedLetters; i++) {
            if (guessedLetters[i] == guess) {
                alreadyGuessed = 1;
                break;
            }
        }

        if (alreadyGuessed) {
            printf("You already guessed the letter '%c'. Try again.\n", guess);
            continue; // Skip to next iteration of the game loop
        }

        guessedLetters[numGuessedLetters++] = guess; // Add the guess and increment the counter

        if (strchr(selectedWord, guess) != NULL) { // Check if guess is in the selected word
            printf("Good guess!\n");
            updateGuessedWord(guessedWord, selectedWord, guess);
        } else {
            printf("Incorrect guess. Try again.\n");
            attempts--;
        }
    }

    if (isWordComplete(guessedWord)) {
        printf("Congratulations! You guessed the word: %s\n", selectedWord);
    } else {
        printf("Sorry! You ran out of attempts.\n");
        printf("The correct word was: %s\n", selectedWord);
    }

    return 0;
}
