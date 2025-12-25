#include <iostream>     // библиотека для ввода и вывода (cout)
#include <vector>       // библиотека для работы с динамическим массивом vector
#include <random>       // библиотека для генерации случайных чисел
#include <chrono>       // библиотека для измерения времени выполнения

int main() {                                                // точка входа в программу

    const int SIZE = 1'000'000;                             // размер массива (1 миллион элементов)

    std::vector<int> array(SIZE);                           // создание массива заданного размера

    std::mt19937 generator(                                 // генератор псевдослучайных чисел
        static_cast<unsigned>(                              // приведение типа для seed
            std::chrono::steady_clock::now()                // текущее время
                .time_since_epoch().count()                 // количество тиков с начала эпохи
        )
    );
    std::uniform_int_distribution<int> distribution(1, 10'000'000); // диапазон случайных чисел

    for (int i = 0; i < SIZE; ++i) {                         // цикл заполнения массива
        array[i] = distribution(generator);                 // генерация случайного значения
    }

    auto startTime = std::chrono::high_resolution_clock::now(); // начало замера времени

    int minValue = array[0];                                 // начальное минимальное значение
    int maxValue = array[0];                                 // начальное максимальное значение

    for (int i = 1; i < SIZE; ++i) {                         // проход по массиву
        if (array[i] < minValue) {                           // проверка на минимум
            minValue = array[i];                             // обновление минимума
        }
        if (array[i] > maxValue) {                           // проверка на максимум
            maxValue = array[i];                             // обновление максимума
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now(); // конец замера времени
    auto elapsedTime =                                       // вычисление времени выполнения
        std::chrono::duration_cast<std::chrono::milliseconds>(
            endTime - startTime                              // разница между концом и началом
        );

    std::cout << "Array size: " << SIZE << std::endl;        // вывод размера массива
    std::cout << "Minimum value: " << minValue << std::endl; // вывод минимального значения
    std::cout << "Maximum value: " << maxValue << std::endl; // вывод максимального значения
    std::cout << "Execution time: "                           // вывод времени выполнения
              << elapsedTime.count() << " ms" << std::endl;

    return 0;                                                // завершение программы
}