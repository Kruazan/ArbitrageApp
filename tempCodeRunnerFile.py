file_path = os.path.join(save_folder, f'price{index}.html')
                
            #     # Сохраняем HTML в файл
            #     with open(file_path, 'w', encoding='utf-8') as file:
            #         file.write(arbitrage_response.text)
                
            #     print(f"Страница арбитража сохранена как {file_path}")
            # else:
            #     print(f"Ошибка при скачивании страницы арбитража для {arbitrage_url}. Код ошибки: {arbitrage_response.status_code}")