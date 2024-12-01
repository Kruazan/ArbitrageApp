#pragma once

#include <iostream>

namespace Settings 
{
	class RiskParameters
	{
	public:
		float minSpread;
        float balancePercent; //если будет проведены транзакции на весь баланс
        float minProfitPercent; //если будет проведена 1 транзакция
        float minBalance; //минимальная сумма на балансе для связки
	};
}
