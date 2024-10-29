#include "cryptocurrencies.h"

using namespace CryptoCurrencies;

CryptoCurrency::CryptoCurrency(std::string name, std::string alphabetCode, float price)
{
	this->name = name;
	this->alphabetCode = alphabetCode;
	this->price = price;
}

Asset::Asset(std::string name, std::string alphabetCode, float price,
	float currentPrice, float dailyVolume, float marketCap)
	: CryptoCurrency(name, alphabetCode, price)
{
	this->currentPrice = currentPrice;
	this->dailyVolume = dailyVolume;
	this->marketCap = marketCap;
}

AnalyzedAsset::AnalyzedAsset(std::string name, std::string alphabetCode, float price,
	float currentPrice, float dailyVolume, float marketCap,
	std::string assetLink, float spread)
	: Asset(name, alphabetCode, price, currentPrice, dailyVolume, marketCap)
{
	this->assetLink = assetLink;
	this->spread = spread;
}