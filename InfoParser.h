#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "cryptocurrencies.h"

using namespace std;

class Parser {
public:
    // ������� ��� �������� ������ �� ���������� � �������������� �����������
    static vector<string> split(const string& str, char delimiter);

    // ������� ��� �������� �������� � ������ � ����� ������
    static void trim(string& s);

    // ������� ��� ��������� ������ � ������
    static Currency parseCurrency(const string& line);
};

#endif // PARSER_H
