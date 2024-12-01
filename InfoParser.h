#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "cryptocurrencies.h"

using namespace std;

class Parser {
public:
    // Функция для разбивки строки на компоненты с использованием разделителя
    static vector<string> split(const string& str, char delimiter);

    // Функция для удаления пробелов в начале и конце строки
    static void trim(string& s);

    // Функция для обработки данных о валюте
    static Currency parseCurrency(const string& line);
};

#endif // PARSER_H
