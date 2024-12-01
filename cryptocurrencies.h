#ifndef CURRENCY_H
#define CURRENCY_H

#include <string>
#include <vector>
#include "exchange.h"

using namespace std;

class Currency {
private:
    string name;          // Название валюты
    string price;         // Цена валюты
    string change;        // Изменение цены
    vector<Exchange> exchanges; // Список бирж с их ценами и валютными парами

public:
    Currency(const string& name, const string& price, const string& change)
        : name(name), price(price), change(change) {}

    // Методы для добавления биржи
    void addExchange(const Exchange& exchange) {
        exchanges.push_back(exchange);
    }

    // Геттеры
    string getName() const { return name; }
    string getPrice() const { return price; }
    string getChange() const { return change; }
    vector<Exchange> getExchanges() const { return exchanges; }
};

#endif // CURRENCY_H
