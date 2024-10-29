#pragma once

#include <iostream>
#include <string>

namespace CryptoCurrencies
{
	class CryptoCurrency
	{
	private:
		std::string name;
		std::string alphabetCode;
		float price;
	public:
		CryptoCurrency(std::string name, std::string alphabetCode, float price);

		std::string GetName() { return name; }
		std::string GetAlphabetCode() { return alphabetCode; }
		float GetPrice() { return price; }
	};

	class Asset : public CryptoCurrency
	{
	private:
		float currentPrice;
		float dailyVolume;
		float marketCap;
	public:
		Asset(std::string name, std::string alphabetCode, float price,
			float currentPrice, float dailyVolume, float marketCap);

		float GetCurrentPrice() { return currentPrice; }
		float GetDailyVolume() { return dailyVolume; }
		float GetMarketCap() { return marketCap; }
	};

	class AnalyzedAsset : public Asset
	{
	private:
		std::string assetLink;
		float spread;
		//todo картинка графика
	public:
		AnalyzedAsset(std::string name, std::string alphabetCode, float price,
			float currentPrice, float dailyVolume, float marketCap,
			std::string assetLink, float spread);

		std::string GetAssetLink() { return assetLink; }
		float GetSpread() { return spread; }
	};
}
