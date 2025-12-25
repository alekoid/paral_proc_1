#include <iostream>     // библиотека для ввода и вывода (cout)
#include <vector>       // библиотека для работы с контейнером vector
#include <random>       // библиотека для генерации случайных чисел
#include <chrono>       // библиотека для измерения времени выполнения

int main() {                                                // точка входа в программу
    // Размер массива
    const int SIZE = 1'000'000;                             // количество элементов массива

    // Создание массива
    std::vector<int> array(SIZE);                           // создание вектора заданного размера

    // Инициализация генератора случайных чисел
    std::mt19937 generator(                                 // генератор псевдослучайных чисел Mersenne Twister
        static_cast<unsigned>(                              // приведение типа для инициализации генератора
            std::chrono::steady_clock::now()                // получение текущего времени
                .time_since_epoch().count()                 // количество тиков с начала эпохи
        )
    );
    std::uniform_int_distribution<int> distribution(1, 10'000'000); // равномерное распределение чисел

    // Заполнение массива случайными значениями
    for (int i = 0; i < SIZE; ++i) {                         // цикл по всем элементам массива
        array[i] = distribution(generator);                 // генерация случайного числа
    }

    // Начало измерения времени
    auto startTime = std::chrono::high_resolution_clock::now(); // фиксируем время начала выполнения

    // Последовательный поиск минимума и максимума
    int minValue = array[0];                                 // начальное значение минимума
    int maxValue = array[0];                                 // начальное значение максимума

    for (int i = 1; i < SIZE; ++i) {                         // проход по массиву начиная со второго элемента
        if (array[i] < minValue) {                           // проверка на новый минимум
            minValue = array[i];                             // обновление минимального значения
        }
        if (array[i] > maxValue) {                           // проверка на новый максимум
            maxValue = array[i];                             // обновление максимального значения
        }
    }

    // Конец измерения времени
    auto endTime = std::chrono::high_resolution_clock::now(); // фиксируем время окончания выполнения
    auto elapsedTime =                                       // вычисляем затраченное время
        std::chrono::duration_cast<std::chrono::milliseconds>(
            endTime - startTime                              // разница между концом и началом
        );

    // Вывод результатов
    std::cout << "Array size: " << SIZE << std::endl;        // вывод размера массива
    std::cout << "Minimum value: " << minValue << std::endl; // вывод минимального значения
    std::cout << "Maximum value: " << maxValue << std::endl; // вывод максимального значения
    std::cout << "Execution time: "                           // вывод текста
              << elapsedTime.count() << " ms" << std::endl;  // вывод времени выполнения

    return 0;                                                // завершение программы
}