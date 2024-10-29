#pragma once

#include "cryptocurrencies.h"
#include "exchange.h"

using namespace CryptoCurrencies;
using namespace Exchanges;

namespace Calculating 
{
	class Calculation
	{
		float FullVolumeProfit(AnalyzedAsset asset, Exchange exchange);
	};
}