#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <unordered_map>
#include <map>
using namespace std;

void header(){
    cout << "\n+------------------------------------------------+\n";
    cout << "|-------[ Welcome to a C++ Wordle Remake ]-------|";
    cout << "\n+------------------------------------------------+\n\n";
}

string to_lower(string s){
    string rs = ""; // return string

    for(unsigned int i = 0; i < s.size(); i++){
        rs += tolower(s[i]);
    }

    return rs;
}

string get_input(){
    string guess = "";
    getline(cin, guess);
    guess = to_lower(guess);
    return guess;
}

void ask_user(){
    string response = "";
    cout << "\nDo you know how to play Wordle? (Type YES or NO): ";
    getline(cin, response);
    response = to_lower(response);

    if(response == "yes"){
        cout << "\nGreat! The random word has been generated. Have fun!\n\n";
    }

    else if(response == "no"){
        cout << "\nHere's a quick how-to:\n";
        cout << "- A random five-letter word will be generated.\n";
        cout << "- You will have six guesses to figure out what the word is.\n";
        cout << "- If a letter is in the correct position, it will be displayed.\n";
        cout << "- The game will also tell you if you have a correct letter but in the wrong position.\n";
        cout << "- You cannot repeat guesses.\n";
        cout << "- Word must be a real English word.\n";
        cout << "\nA random word has been generated. Good luck!\n\n";
    }

    else{
        cout << "Error: Invalid response. Try again.\n";
        ask_user();
    }
}

int main(){
    int guess_count = 1;                    // number of words that the user has guessed
    int guess_attempts = 6;                 // remaining guess attempts
    string guess = "";                      // word that the user is guessing
    string string_output = "_____";         // outputs correct letters in correct order
    ifstream file_in;                       // reading in from words.txt file (4,000 5-letter words)
    unordered_map<string, int> words;       // map containing all 4,000 words
    unordered_map<char, int> chars;         // map with all chars in word
    unordered_map<char, bool> correct_chars;// map containing correctly guessed letters
    map<char, bool> all_chars;              // map of all chars that have been guessed, regardless if correct

    file_in.open("words.txt");              // be sure to have words.txt in the same directory as wordle.cpp

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
    string random_word = it->first;
    
    // add characters to character map, all correct letters
    for(unsigned int i = 0; i < random_word.size(); i++){
        chars[random_word[i]]++;
    }

    header(); 
    ask_user();

    while(guess_count <= 6 && guess != random_word){
        cout << "You have " << guess_attempts << " attempts. Enter guess " << guess_count << ": ";

        guess = get_input();

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

        for(unsigned int i = 0; i < random_word.size(); i++){
            for(unsigned int j = 0; j < guess.size(); j++){
                all_chars[guess[j]] = 1;
                if(guess[j] == random_word[i]){

                    // add correct char to correct char map, assume in wrong position for now
                    correct_chars[guess[j]] = false;

                    // check to see if letter is in correct spot
                    if(guess[j] == random_word[j]){
                        string_output[j] = guess[j];
                        correct_chars[guess[j]] = true;
                    }
                    // update value if character is correct and in right spot
                }
            }
        }

        cout << "\nAll guessed letters: ";
        for(auto i = all_chars.begin(); i != all_chars.end(); i++){
            cout << i->first << " ";
        }

        cout << "\nCorrect letters, but in the wrong spot: ";
        for(auto i = correct_chars.begin(); i != correct_chars.end(); i++){
            if(chars[i->first] == 1 && correct_chars[i->first] == false){
                cout << i->first << " ";
            }
        }

        cout << "\nCorrect letters that occur more than once: ";
        for(auto i = correct_chars.begin(); i != correct_chars.end(); i++){
            if(chars[i->first] > 1){
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
