#include "functions.h"

int main() {
    auto dictionary = new Word[dictionarySize];
    size_t size = getDictionary(dictionary);
    menu(dictionary, size);
    return 0;
}
