#include "InfoParser.h"
#include <sstream>
#include <algorithm>

// Функция для разбивки строки на компоненты с использованием разделителя
vector<string> Parser::split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Функция для удаления пробелов в начале и конце строки
void Parser::trim(string& s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
                return !isspace(ch);
            }));
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
                return !isspace(ch);
            }).base(), s.end());
}

// Функция для обработки данных о валюте
Currency Parser::parseCurrency(const string& line) {
    vector<string> parts = split(line, ':');

    // Название валюты
    string name = parts[0];
    string price = parts[1];
    string change = parts[2];

    Currency currency(name, price, change);

    // Биржи и их цены с валютными парами
    for (size_t i = 3; i < parts.size(); i++) {
        vector<string> exchangeParts = split(parts[i], '$');
        if (exchangeParts.size() == 2) {
            string exchangeName = exchangeParts[0];
            string priceWithPair = exchangeParts[1];
            trim(priceWithPair);

            // Разделяем на цену и валютную пару
            size_t pos = priceWithPair.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
            if (pos != string::npos) {
                string exchangePrice = priceWithPair.substr(0, pos);
                string currencyPair = priceWithPair.substr(pos);
                Exchange ex(exchangeName, exchangePrice, currencyPair);
                currency.addExchange(ex);
            }
        }
    }

    return currency;
}
