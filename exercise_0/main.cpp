#include <iostream>
#include <fstream>
#include <string>

using namespace std;

constexpr char STOP_LETTER = 'q';

struct Sounds {
    int vowels{0};
    int consonants{0};
    int other{0};
};

inline bool is_vowel(const char &letter) {
    const string vowels = "aeiou";
    char lower_letter = tolower(letter);
    return vowels.find(lower_letter) != string::npos;
}

void increment_sound(const char &letter, Sounds &sound) {
    if (isalpha(letter)) {
        if (is_vowel(letter)) {
            ++sound.vowels;
        } else {
            ++sound.consonants;
        }
    } else {
        ++sound.other;
    }
}

void read_from_file(Sounds &sound, const string &file_path) {
    string line;
    ifstream infile(file_path);

    if (infile.fail()) {
        cerr << "File not exist" << endl;
        exit(1);
    }

    while (infile >> line) {
        increment_sound(line[0], sound);
    }
}

void read_from_console(Sounds &sound) {
    string word;
    cout << "Type words (enter " << STOP_LETTER << " for stop.)!" << std::endl;

    while (cin >> word) {
        if (word.size() == 1 && STOP_LETTER == word[0]) {
            break;
        }
        increment_sound(word[0], sound);
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