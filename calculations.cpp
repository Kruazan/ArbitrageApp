#include "calculations.h"

using namespace Calculating;

float Calculation::FullVolumeProfit(AnalyzedAsset asset, Exchange exchange)
{
	float profit = exchange.GetBalance() * asset.GetSpread() - exchange.GetTransferFee();
	return profit;
}