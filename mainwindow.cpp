#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QImage>
#include <QPixmap>
#include <QDir>
#include <QDebug>
#include <fstream>
#include "exchange.h"
#include "cryptocurrencies.h"
#include "InfoParser.h"  // Подключаем файл с парсером
#include "accountsettings.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    setFixedSize(1152, 512);
    ui->setupUi(this);

    // Создаем таблицу с 10 строками и 11 столбцами
    int rows = 10;  // Здесь будет 10 строк, но можно менять динамически
    int columns = 10;  // 1 для картинки, 1 для name, 1 для price, 1 для chg/24h, 5 для бирж и 1 для процента

    ui->tableWidget->setRowCount(rows);
    ui->tableWidget->setColumnCount(columns);

    // Устанавливаем заголовки столбцов
    QStringList headers = {"Image", "Name", "Price", "chg/24h", "Exchange1", "Exchange2", "Exchange3", "Exchange4",
                           "Exchange5", "Difference %"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Устанавливаем ширины столбцов
    ui->tableWidget->setColumnWidth(0, 50);  // Столбец с изображениями
    ui->tableWidget->setColumnWidth(1, 150); // Столбец с "Name"
    ui->tableWidget->setColumnWidth(2, 100); // Столбец с "Price"
    ui->tableWidget->setColumnWidth(3, 100); // Столбец с "chg/24h"
    ui->tableWidget->setColumnWidth(4, 120); // Столбец с "Exchange1"
    ui->tableWidget->setColumnWidth(5, 120); // Столбец с "Exchange2"
    ui->tableWidget->setColumnWidth(6, 120); // Столбец с "Exchange3"
    ui->tableWidget->setColumnWidth(7, 120); // Столбец с "Exchange4"
    ui->tableWidget->setColumnWidth(8, 120); // Столбец с "Exchange5"
    ui->tableWidget->setColumnWidth(9, 100); // Столбец с "Difference %"

    // Заполняем таблицу данными
    populateTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateTable()
{
    // Путь к папке с картинками
    QString imageFolderPath = "D:/ArbitrageAppFolder/ArbitrageApp/cryptoImg/";

    // Читаем данные из файла с валютами (предположим, что файл называется "crypto_data.txt")
    ifstream file("D:/ArbitrageAppFolder/ArbitrageApp/cryptoInf/output.txt");

    if (!file.is_open()) {
        qDebug() << "Не удалось открыть файл с данными!";
        return;
    }

    string line;
    vector<Currency> currencies;

    // Чтение файла построчно и парсинг данных
    while (getline(file, line)) {
        Currency currency = Parser::parseCurrency(line);  // Используем парсер
        currencies.push_back(currency);
    }

    // Закрываем файл после чтения
    file.close();

    // Наполняем таблицу данными о криптовалютах
    for (int row = 0; row < currencies.size() && row < 10; ++row) {  // Ограничиваем 10 строками
        const Currency& currency = currencies[row];

        // Формируем путь к картинке для текущей строки
        QString imageFileName = QString::fromStdString(currency.getName()) + ".png";  // Динамически используем имя валюты
        QString imagePath = imageFolderPath + imageFileName;

        // Загружаем изображение
        QImage image(imagePath);
        if (!image.isNull()) {
            QTableWidgetItem *imageItem = new QTableWidgetItem;
            imageItem->setIcon(QIcon(QPixmap::fromImage(image)));  // Устанавливаем иконку на основе изображения
            ui->tableWidget->setItem(row, 0, imageItem);  // Вставляем картинку в первый столбец
        } else {
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem("Image not found"));
        }

        // Заполняем остальные столбцы таблицы
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(currency.getName())));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(currency.getPrice())));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(currency.getChange())));

        // Заполняем данные бирж (5 столбцов для бирж)
        const vector<Exchange>& exchanges = currency.getExchanges();
        for (int i = 0; i < 5 && i < exchanges.size(); ++i) {
            const Exchange& ex = exchanges[i];
            QString exchangeInfo = QString("%1 (%2)").arg(QString::fromStdString(ex.getName())).arg(QString::fromStdString(ex.getPrice()));
            ui->tableWidget->setItem(row, 4 + i, new QTableWidgetItem(exchangeInfo));
        }

        // Заполняем столбец "Difference %" (процент разницы между биржами)
        if (exchanges.size() >= 5) {
            double exchange1 = stod(exchanges[0].getPrice());
            double exchange2 = stod(exchanges[1].getPrice());
            double exchange3 = stod(exchanges[2].getPrice());
            double exchange4 = stod(exchanges[3].getPrice());
            double exchange5 = stod(exchanges[4].getPrice());

            // Находим среднее значение всех 5 бирж
            double averagePrice = (exchange1 + exchange2 + exchange3 + exchange4 + exchange5) / 5.0;

            // Рассчитываем процент разницы относительно среднего значения
            double percentageDifference = ((exchange1 - averagePrice) / averagePrice) * 100.0;

            ui->tableWidget->setItem(row, 9, new QTableWidgetItem(QString::number(percentageDifference, 'f', 2) + "%"));
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    AccountSettings *settingswin = new AccountSettings();

    settingswin->show();
}

