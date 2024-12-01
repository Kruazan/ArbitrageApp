import os
import requests
import random
import time
from bs4 import BeautifulSoup

# URL главной страницы
base_url = 'https://cryptorank.io/'

# Папка для сохранения файлов
save_folder = r'D:\ArbitrageAppFolder\ArbitrageApp\pages'

# Список User-Agent строк для имитации браузера
USER_AGENTS = [
    "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:39.0) Gecko/20100101 Firefox/39.0",
    "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.97 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.3; rv:40.0) Gecko/20100101 Firefox/40.0"
]

# Функция для скачивания главной страницы и извлечения данных
def parsing_arbitrage_page(arbitrage_url):
    url = arbitrage_url
    headers = {
        "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7",
        "User-Agent": random.choice(USER_AGENTS)
    }

    response = requests.get(url, headers=headers)
    if response.status_code == 429:
        print(f"Ошибка 429 для {url}. Пауза на 10 секунд...")
        time.sleep(10)  # Ожидаем перед повторным запросом
        response = requests.get(url, headers=headers)

    # Проверяем, что запрос прошел успешно
    if response.status_code != 200:
        print(f"Ошибка при запросе страницы. Статус: {response.status_code}")
        return
    
    # Парсим HTML с помощью BeautifulSoup
    exchangesList = []

    soup = BeautifulSoup(response.content, 'lxml')
    name = soup.find('span', class_="sc-56567222-0 sc-6b8bdf7b-9 bvDjHS kWWoia").getText(strip=True)
    price = soup.find('div', class_="sc-cb748c3-0 cwWsJH").getText(strip=True)
    change = soup.find('span', class_="sc-56567222-0 sc-92cddc74-0 jvlrjM koiTCg")

    if os.path.exists(f"D:/ArbitrageAppFolder/ArbitrageApp/cryptoImg/{name}.png"):
        print(f"Файл '{name}.png' уже существует. Скачивание не требуется.")
    else:
        img = soup.find('img', class_="sc-6b8bdf7b-6 ikTxnT")
        img_url = img.get('src')
        try:
            # Отправляем GET-запрос по URL
            response = requests.get(img_url)
            
            # Проверяем успешность запроса
            if response.status_code == 200:
                # Открываем файл для записи в бинарном режиме и записываем контент изображения
                with open(f"D:/ArbitrageAppFolder/ArbitrageApp/cryptoImg/{name}.png", 'wb') as file:
                    file.write(response.content)
                print(f"Изображение успешно сохранено в D:/ArbitrageAppFolder/ArbitrageApp/cryptoImg/{name}.png")
            else:
                print(f"Ошибка при скачивании изображения. Статус код: {response.status_code}")
        except Exception as e:
            print(f"Произошла ошибка: {e}")
        

    if not change:
        change = soup.find('span', class_="sc-56567222-0 sc-92cddc74-0 jvlrjM iksbwa")
        changeTxt = change.getText(strip=True)
        changeTxt = '-' + changeTxt
    else:
        changeTxt = change.getText(strip=True)

    exchanges = soup.find_all('th', class_="sc-5685a828-2 sc-93f0dec-3 hzTkAB fgTRBH")
    for exchange in exchanges:
        exchangesList.append(exchange.getText(strip=True))

    # Открываем файл для записи данных
    with open("D:/ArbitrageAppFolder/ArbitrageApp/cryptoInf/output.txt", "a", encoding="utf-8") as file:
        file.write(f"{name}:{price}:{changeTxt}")
        for i in range(len(exchangesList)):
            file.write(f":{exchangesList[i]}")
        file.write("\n")

    print(f"Данные для {name} записаны в файл.")

# Функция для скачивания и обработки ссылок криптовалют
def download_and_process_links():
    headers = {
        "User-Agent": random.choice(USER_AGENTS)
    }

    response = requests.get(base_url, headers=headers)
    if response.status_code == 429:
        print(f"Ошибка 429 для главной страницы. Пауза на 10 секунд...")
        time.sleep(10)
        response = requests.get(base_url, headers=headers)

    if response.status_code == 200:
        soup = BeautifulSoup(response.text, 'lxml')
        links = soup.find_all('a', class_='sc-39ba2409-1 bgOSTi')

        crypto_links = []
        for link in links:
            href = link.get('href')
            if href and href.startswith('/price/'):
                full_url = base_url + href[1:]  # преобразуем в полный URL
                crypto_links.append(full_url)

        for index, url in enumerate(crypto_links, start=1):
            arbitrage_url = url + '/arbitrage'

            arbitrage_response = requests.get(arbitrage_url, headers=headers)
            if arbitrage_response.status_code == 429:
                print(f"Ошибка 429 для {arbitrage_url}. Пауза на 10 секунд...")
                time.sleep(10)
                arbitrage_response = requests.get(arbitrage_url, headers=headers)
            
            if arbitrage_response.status_code == 200:
                parsing_arbitrage_page(arbitrage_url)

    else:
        print(f"Ошибка при скачивании главной страницы! Код ошибки: {response.status_code}")


# Основной процесс
def main():
    open("D:/ArbitrageAppFolder/ArbitrageApp/cryptoInf/output.txt", "w", encoding="utf-8")
    download_and_process_links()

if __name__ == '__main__':
    main()