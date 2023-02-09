#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <unordered_map>
using namespace std;

int main(){
    int guess_count = 1;                    // number of words that the user has guessed
    int guess_attempts = 6;                 // remaining guess attempts
    string guess = "";                      // word that the user is guessing
    string string_output = "_____";         // outputs correct letters in correct order
    ifstream file_in;                       // reading in from words.txt file (5,757 5-letter words)
    unordered_map<string, int> words;       // map containing all 5,757 words
    unordered_map<char, int> chars;         // map with all chars in word
    unordered_map<char, int> correct_chars; // map containing correctly guessed letters

    file_in.open("words.txt");          // be sure to have words.txt in the same directory as wordle.cpp

    // read all words into map
    string read_word = "";
    while(!file_in.eof()){
        file_in >> read_word;
        words[read_word]++;
    }

    // create random integer based on current time, using time()
    srand(time(0));
    int word_index = rand() % words.size();

    // select random word
    auto it = words.begin();
    advance(it, word_index);
    //string random_word = it->first;
    string random_word = "peeps";
    for(int i = 0; i < random_word.size(); i++){
        chars[random_word[i]]++;
        cout << random_word[i] << endl;
    }

    while(guess_count <= 6 && guess != random_word){
        cout << "You have " << guess_attempts << " attempts. Enter guess " << guess_count << ": ";
        cin >> guess;
        cout << "\n----------------------------------------\n";

        if(words[guess] == 0 || guess.size() != 5){
            cout << "\nInvalid word. Try again.\n";     // if word is not found in map, output error
            continue;                                   // and re-try loop without lowering remaining attempts
        }

        else if(words[guess] == 2){     // do not let the user guess a word more than one time
            cout << "\nWord has already been guessed. Try again\n"; 
            continue;
        }

        // if word has been guessed, change value to 2
        words[guess] = 2;

        guess_attempts--;
        guess_count++;

        if(guess == random_word){
            cout << "\nYou guessed the word correctly!\nThe word was: " << random_word << endl;
            cout << "\n----------------------------------------\n";
            exit(0);  // if user guesses word correctly, output message and exit
        }

        for(int i = 0; i < random_word.size(); i++){
            for(int j = 0; j < guess.size(); j++){
                if(guess[j] == random_word[i]){

                    if(guess[j] == random_word[j]){
                        string_output[j] = guess[j];
                        
                        continue;
                    }

                    if(chars[guess[j]] > 1){
                        correct_chars[guess[j]]++;
                        continue;
                    }

                    correct_chars[guess[j]]++;
                }
            }
        }

        cout << "\nCorrect letters, but in the wrong spot: ";
        for(auto i = correct_chars.begin(); i != correct_chars.end(); i++){
            if(i->second == 1){
                cout << i->first << " ";
            }
        }

        cout << "\nCorrect letters that occur more than once: ";
        for(auto i = correct_chars.begin(); i != correct_chars.end(); i++){
            if(i->second > 1){
                cout << i->first << " ";
            }
        }
        cout << "\nCurrent progress: " << string_output << endl;
    }

    cout << "\n----------------------------------------\n";
    cout << "You did not guess the word.\nThe word was: "; 
    cout << random_word << "\nBetter luck next time!\n";

    exit(0);
}
