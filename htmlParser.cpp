#include "htmlParser.h"
using namespace parser;

void ParserHTML::findSpansByClass() 
{
    std::ifstream file("D:/Cursach/pages/bitcoin.html");
    if (!file.is_open()) 
    {
        std::cerr << "Ошибка при открытии файла." << std::endl;
        return;
    }

    //todo допилить получение названия

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::regex re(R"(<tr[^>]*>.*?<span[^>]*><a[^>]*>(.*?)</a></span>.*?<span class="sc-56567222-0 sc-92cddc74-0 ftrvre koiTCg">([\+\d\.]+%)</span>.*?</tr>)");
    std::smatch match;

    std::string::const_iterator searchStart(content.cbegin());
    while (std::regex_search(searchStart, content.cend(), match, re)) 
    {
        std::string exchangeName = match[1];  // Название биржи
        std::string value = match[2];          // Значение
        if (value != "+99.9%") 
        {
            std::cout << "Биржа: " << exchangeName << ", Значение: " << value << std::endl;
        }
        searchStart = match[0].second;
    }

}
