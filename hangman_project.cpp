#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>

#define MAX_TRIES 6

using namespace std;

// List of words for the game
const string wordBankArr[] = {"apple", "banana", "cherry", "orange", "grape", "mango"};
const vector<string> wordBank(wordBankArr, wordBankArr + sizeof(wordBankArr) / sizeof(wordBankArr[0]));

// Function to display the current state of the word
void displayWord(const string &word, const vector<bool> &guessed) {
    for (size_t i = 0; i < word.length(); i++) {
        if (guessed[i]) {
            cout << word[i] << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

// Function to check if the player has won
bool isWordGuessed(const vector<bool> &guessed) {
    for (size_t i = 0; i < guessed.size(); i++) {
        if (!guessed[i]) {
            return false;
        }
    }
    return true;
}

// Function to display Hangman
void displayHangman(int attempts) {
    static const char* hangmanStages[] = {
        "\n\n\n\n\n",
        "\n\n\n\n____",
        "|\n|\n|\n|\n____",
        "________\n|\n|\n|\n|\n____",
        "________\n|      |\n|\n|\n|\n____",
        "________\n|      |\n|      O\n|\n|\n____",
        "________\n|      |\n|      O\n|     /|\\\n|     / \\\n____"
    };
    
    if (attempts >= 0 && attempts <= MAX_TRIES) {
        cout << hangmanStages[attempts] << endl;
    }
}

// Function to play the game
void playGame() {
    string word = wordBank[rand() % wordBank.size()];
    vector<bool> guessed(word.length(), false);
    
    int attempts = 0;
    char guess;

    cout << "\nWelcome to Hangman!" << endl;
    
    while (attempts < MAX_TRIES) {
        cout << "\nWord: ";
        displayWord(word, guessed);
        displayHangman(attempts);
        cout << "Attempts left: " << (MAX_TRIES - attempts) << endl;
        cout << "Enter your guess: ";
        cin >> guess;
        guess = tolower(guess);

        bool found = false;
        for (size_t i = 0; i < word.length(); i++) {
            if (word[i] == guess && !guessed[i]) {
                guessed[i] = true;
                found = true;
            }
        }

        if (!found) {
            attempts++;
            cout << "Incorrect guess!" << endl;
        } else {
            cout << "Correct guess!" << endl;
        }

        if (isWordGuessed(guessed)) {
            cout << "\nCongratulations! You guessed the word: " << word << endl;
            return;
        }
    }

    displayHangman(attempts);
    cout << "\nGame Over! The correct word was: " << word << endl;
}

int main() {
    srand(time(NULL));

    char playAgain = 'y';
    while (playAgain == 'y' || playAgain == 'Y') {
        playGame();

        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;
    }

    cout << "Thanks for playing! Goodbye!" << endl;
    return 0;
}

