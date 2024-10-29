#pragma once

#include <iostream>

namespace Settings 
{
	class RiskParameters
	{
	public:
		float minVolume;
		float minSpread;
		float balancePercent;
		float minProfitPercent;
	};
}