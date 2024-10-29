#pragma once

#include <iostream>
#include <string>

namespace Exchanges
{
	class Exchange
	{
	private:
		std::string nickname;
		std::string name;

		float balance;
		float transferFee;
	public:
		Exchange(std::string name,std::string nickname,float balance, float transferFee);

		std::string GetName() { return name; }
		float GetTransferFee() { return transferFee; }
		std::string GetNickname() { return nickname; }
		float GetBalance() { return balance; }

	};
}