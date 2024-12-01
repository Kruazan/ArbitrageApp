#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <string>

using namespace std;

class Exchange {
private:
    string name;          // Название биржи
    string price;         // Цена на бирже
    string currencyPair;  // Валютная пара (например, BTC/USD)

public:
    Exchange(const string& name, const string& price, const string& currencyPair)
        : name(name), price(price), currencyPair(currencyPair) {}

    // Геттеры
    string getName() const { return name; }
    string getPrice() const { return price; }
    string getCurrencyPair() const { return currencyPair; }
};

#endif // EXCHANGE_H
