// Copyright 2021 qqq <polyakovdd@student.bmstu.ru>


#ifndef CODE_FUNCTIONS_H
#define CODE_FUNCTIONS_H

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <iomanip>
#include <fstream>


#define dictionaryFileName "dictionary.qqq"
#define maxWordLength 33
#define dictionarySize 100

enum MenuItem {
    ShowDictionary = 1,
    AddRecord,
    DeleteRecord,
    TranslateEtoR,
    TranslateRtoE,
    SaveDictionary,
    Exit
};

struct Word {
    char English[maxWordLength];
    char Russian[maxWordLength];
};


void printMenu();

void menu(Word *, size_t &);

void showDictionary(Word *, const size_t);

void addRecord(Word *, size_t &);

void deleteRecord(Word *, size_t &);

void saveDictionary(Word *, const size_t);

void translateEnglishToRussian(Word *, const size_t);

void translateRussianToEnglish(Word *, const size_t);

size_t getDictionary(Word *);

#endif //CODE_FUNCTIONS_H
