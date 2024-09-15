// MinimalSFML.cpp : Defines the entry point for the application.
//
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "tinyfiledialogs/tinyfiledialogs.h"
#include "Button.cpp"
#include "Label.cpp"
#include <sstream>
#include <iostream>
#include <locale>
#include <codecvt>
#include <string>
#include <vector>
#include <mutex>

// Глобальные переменные
std::mutex resultMutex;
std::vector<int> resultTable;

// Функция для выполнения в потоке
void workerFunction(int id) {
    // Симулируем выполнение работы
    sf::sleep(sf::milliseconds(5000));

    // Генерируем результат работы потока
    int result = id * 10;

    // Защищаем доступ к результирующей таблице с помощью мьютекса
    {
        std::lock_guard<std::mutex> lock(resultMutex);
        resultTable.push_back(result);
    }

    std::cout << "Worker " << id << " completed with result: " << result << std::endl;
}

// Поток, который запускает несколько потоков
void mainWorker() {
    std::vector<sf::Thread*> threads;

    // Создаем и запускаем потоки
    for (int i = 1; i <= 5; ++i) {
        sf::sleep(sf::milliseconds(5000));
        threads.push_back(new sf::Thread(&workerFunction, i));
        threads.back()->launch();
    }

    // Ожидаем завершения потоков
    for (auto& thread : threads) {
        thread->wait();
        delete thread; // Освобождаем память
    }

    std::cout << "All worker threads completed." << std::endl;
}
int counter = 0;
bool buttonClicked = false;
sf::Thread mainThread(&mainWorker);

int main() {
    // Создаем окно SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Multithreading Example");
    // Создаем кнопку и лейбл
    Button button(sf::Vector2f(300, 250), sf::Vector2f(150, 50), "start");
    Button buttonDown(sf::Vector2f(100, 100), sf::Vector2f(150, 50), "Click me");
    Label label(sf::Vector2f(350, 350), "Label");

    
    
    

    // Главный цикл приложения
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Обработка нажатия кнопки мыши
            if (event.type == sf::Event::MouseButtonPressed) {
                if (button.isClicked(sf::Mouse::getPosition(window))) {
                    buttonClicked = true;
                    label.setText("Thread started!");
                    // Запускаем главный поток
                    
                    mainThread.launch();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (buttonDown.isClicked(sf::Mouse::getPosition(window))) {
                    counter++;
                    std::stringstream ss;
                    ss << counter << " clicked";
                    std::string formattedText = ss.str();
                    label.setText(formattedText);
                }
            }
        }
        // Очищаем окно
        window.clear(sf::Color::Blue);

        buttonDown.draw(window);
        button.draw(window);
        label.draw(window);

        // Отображаем результаты работы потоков
        window.display();
    }

    // Ожидаем завершения главного потока
    mainThread.wait();

    // Выводим итоговую таблицу
    std::cout << "Result table:" << std::endl;
    for (const int& result : resultTable) {
        std::cout << result << " ";
    }
    std::cout << std::endl;

    return 0;
}

