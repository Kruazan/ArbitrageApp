#include "exchange.h"

using namespace Exchanges;

Exchange::Exchange(std::string name, std::string nickname, float balance, float transferFee)
{
	this->name = name;
	this->transferFee = transferFee;
	this->nickname = nickname;
	this->balance = balance;
}