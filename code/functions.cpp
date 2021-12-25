// Copyright 2021 qqq <polyakovdd@student.bmstu.ru>

#include "functions.h"

void printMenu() {
    const char *menu[7] = {"Show dictionary",
                           "Add record to dictionary",
                           "Delete record from dictionary",
                           "Translate word from English to Russian",
                           "Translate word from Russian to English",
                           "Save dictionary",
                           "Exit"};
    for (size_t i = 0; i < 7; ++i) {
        std::cout << i + 1 << ". " << menu[i] << '\n';
    }
    std::cout << "Enter needed number:\n";
}

void menu(Word *dictionary, size_t &sizeOfDictionary) {
    int menuPoint;
    while (true) {
        printMenu();
        std::cin >> menuPoint;
        switch (menuPoint) {
            case ShowDictionary:
                showDictionary(dictionary, sizeOfDictionary);
                break;
            case AddRecord:
                addRecord(dictionary, sizeOfDictionary);
                break;
            case DeleteRecord:
                deleteRecord(dictionary, sizeOfDictionary);
                break;
            case TranslateEtoR:
                translateEnglishToRussian(dictionary, sizeOfDictionary);
                break;
            case TranslateRtoE:
                translateRussianToEnglish(dictionary, sizeOfDictionary);
                break;
            case SaveDictionary:
                saveDictionary(dictionary, sizeOfDictionary);
                break;
            case Exit:
                return;
            default:
                break;
        }
    }
}

size_t getDictionary(Word *dictionary) {
    std::ifstream dictionaryFile(dictionaryFileName);
    size_t i = 0;
    while (!dictionaryFile.eof()) {
        dictionaryFile >> dictionary[i].English >> dictionary[i].Russian;
        i++;
    }
    dictionaryFile.close();
    return i;
}

int findEnglishWord(Word *dictionary, const size_t sizeOfDictionary, Word wordToFind) {
    bool translated = false;
    int begin = 0;
    int end = sizeOfDictionary - 1;
    int current_position = (end - begin) / 2;
    while (!translated) {
        if (strcmp(dictionary[current_position].English, wordToFind.English) == 0)
            translated = true;
        else if (strcmp(dictionary[current_position].English, wordToFind.English) > 0) {
            end = current_position;
            current_position -= (end - begin) / 2;
            if (end - begin == 1) {
                if (begin == 0) {
                    current_position--;
                    if (strcmp(dictionary[current_position].English, wordToFind.English) == 0) translated = true;
                    else break;
                } else break;
            }
        } else {
            begin = current_position;
            current_position += (end - begin) / 2;
            if (end - begin == 1) {
                if (end == sizeOfDictionary - 1) {
                    current_position++;
                    if (strcmp(dictionary[current_position].English, wordToFind.English) == 0) translated = true;
                    else break;
                } else break;
            }
        }
    }
    if (translated)
        return current_position;
    else
        return -1;
}

int findRussianWord(Word *dictionary, const size_t sizeOfDictionary, Word wordToFind) {
    int pos = -1;
    for (size_t i = 0; i < sizeOfDictionary; ++i) {
        if (strcmp(dictionary[i].Russian,wordToFind.Russian)==0)
        {
            pos = i;
            break;
        }
    }
    return pos;
}

void saveDictionary(Word *dictionary, const size_t sizeOfDictionary) {
    std::ofstream dictionaryFile(dictionaryFileName, std::ios::out | std::ios::trunc);
    for (size_t i = 0; i < sizeOfDictionary - 1; ++i) {
        dictionaryFile << dictionary[i].English << ' ' << dictionary[i].Russian << std::endl;
    }
    dictionaryFile << dictionary[sizeOfDictionary - 1].English << ' ' << dictionary[sizeOfDictionary - 1].Russian;
    dictionaryFile.close();
}

void showDictionary(Word *dictionary, const size_t sizeOfDictionary) {
    if (sizeOfDictionary == 0) {
        std::cout << "Dictionary is clear!" << std::endl;
    } else
        for (size_t i = 0; i < sizeOfDictionary; ++i) {
            std::cout << std::setw(31) << std::right << dictionary[i].English << " — " << std::setw(31) << std::left
                      << dictionary[i].Russian
                      << std::endl;
        }
}

void addRecord(Word *dictionary, size_t &sizeOfDictionary) {
    std::cout << "Enter word in format \"English Russian\":" << std::endl;
    Word tempWord = {"", ""};
    std::cin >> tempWord.English >> tempWord.Russian;
    size_t pos = sizeOfDictionary;
    for (size_t i = 0; i < sizeOfDictionary; ++i) {
        if (strcmp(dictionary[i].English, tempWord.English) > 0) {
            pos = i;
            break;
        }
    }
    sizeOfDictionary++;
    for (size_t i = sizeOfDictionary; i > pos; --i) {
        dictionary[i] = dictionary[i - 1];
    }
    dictionary[pos] = tempWord;
    std::cout << "Word has been added" << std::endl;
}

void deleteRecord(Word *dictionary, size_t &sizeOfDictionary) {
    std::cout << "Enter word to delete in English:" << std::endl;
    Word tempWord = {"", ""};
    std::cin >> tempWord.English;
    int pos = findEnglishWord(dictionary, sizeOfDictionary, tempWord);
    if (pos == -1) {
        std::cout << "Word not found!" << std::endl;
    } else {
        for (size_t i = pos; i < sizeOfDictionary; ++i) {
            dictionary[i] = dictionary[i + 1];
        }
        sizeOfDictionary--;
        std::cout << "Word has been deleted" << std::endl;
    }
}

void translateEnglishToRussian(Word *dictionary, const size_t sizeOfDictionary) {
    std::cout << "Enter word to translate in English:" << std::endl;
    Word tempWord = {"", ""};
    std::cin >> tempWord.English;
    int pos = findEnglishWord(dictionary, sizeOfDictionary, tempWord);
    if (pos == -1) {
        std::cout << "Word not found!" << std::endl;
    } else {
        std::cout << dictionary[pos].English << " — " << dictionary[pos].Russian << std::endl;
    }
}

void translateRussianToEnglish(Word *dictionary, const size_t sizeOfDictionary) {
    std::cout << "Enter word to translate in Russian:" << std::endl;
    Word tempWord = {"", ""};
    std::cin >> tempWord.Russian;
    int pos = findRussianWord(dictionary, sizeOfDictionary, tempWord);
    if (pos == -1) {
        std::cout << "Word not found!" << std::endl;
    } else {
        std::cout << dictionary[pos].English << " — " << dictionary[pos].Russian << std::endl;
    }
}