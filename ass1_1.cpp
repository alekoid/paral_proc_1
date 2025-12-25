#include <iostream>      // библиотека для ввода и вывода (cout)
#include <cstdlib>       // библиотека для rand() и srand()
#include <ctime>         // библиотека для работы со временем (time)
#include <windows.h>     // библиотека Windows для работы с кодировками консоли

int main() {                                             // точка входа в программу

    SetConsoleOutputCP(CP_UTF8);                          // установка кодировки вывода UTF-8
    SetConsoleCP(CP_UTF8);                                // установка кодировки ввода UTF-8

    const int SIZE = 50000;                               // размер массива

    int* array = new int[SIZE];                           // динамическое выделение памяти под массив

    std::srand(static_cast<unsigned>(std::time(nullptr)));// инициализация генератора случайных чисел

    long long sum = 0;                                    // переменная для хранения суммы элементов массива
    for (int i = 0; i < SIZE; ++i) {                      // цикл заполнения массива
        array[i] = std::rand() % 100 + 1;                 // генерация случайного числа от 1 до 100
        sum += array[i];                                  // добавление элемента массива к сумме
    }

    double average = static_cast<double>(sum) / SIZE;    // вычисление среднего значения элементов массива

    std::cout << "Среднее значение элементов массива: "   // вывод текста
              << average << std::endl;                    // вывод среднего значения

    delete[] array;                                       // освобождение динамически выделенной памяти

    return 0;                                             // завершение программы
}