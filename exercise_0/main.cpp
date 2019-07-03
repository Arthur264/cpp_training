#include <iostream>
#include <fstream>
#include <string>

#define STOP_LETTER "q"
#define VOWELS "aeiou"

using namespace std;

struct Sounds {
    int vowels = 0;
    int consonants = 0;
    int other = 0;
};

inline bool start_with_vowels(const char letter) {
    char lower_letter = tolower(letter);
    for (int i = 0; i < VOWELS[i]; ++i) {
        if (lower_letter == VOWELS[i]) {
            return true;
        }
    }
    return false;
}

void increment(const char letter, Sounds& sound) {
    if (isalpha(letter)) {
        if (start_with_vowels(letter)) {
            ++sound.vowels;
        } else {
            ++sound.consonants;
        }
    } else {
        ++sound.other;
    }
}

void read_from_file(Sounds& sound, const char file_path[150]) {
    string line;
    ifstream infile(file_path);

    if (infile.fail()) {
        cerr << "File not exist" << endl;
        exit(1);
    }

    while (getline(infile, line)) {
        increment(line[0], sound);
    }
}

void read_from_console(Sounds& sound) {
    string word;
    cout << "Type words (enter q for stop.)!" << std::endl;

    while (cin >> word) {
        if (word == STOP_LETTER) {
            break;
        }
        increment(word[0], sound);
    }
}


int main(int argc, char **argv) {
    Sounds sound;

    if (argc == 1) {
        read_from_console(sound);
    } else {
        read_from_file(sound, argv[1]);
    }

    cout << sound.vowels << " words start with vowels" << std::endl;
    cout << sound.consonants << " words start with consonants" << std::endl;
    cout << sound.other << " words start with other" << std::endl;
    return 0;
}