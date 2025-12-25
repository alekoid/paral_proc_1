#include <iostream>     // библиотека для ввода и вывода (cout)
#include <vector>       // библиотека для работы с контейнером vector
#include <random>       // библиотека для генерации случайных чисел
#include <chrono>       // библиотека для измерения времени выполнения
#include <omp.h>        // библиотека OpenMP для параллельных вычислений

int main() {                                                // точка входа в программу
    const int SIZE = 5'000'000;                             // размер массива

    // --- генерация массива --- //
    std::vector<int> data(SIZE);                            // создание массива заданного размера

    std::mt19937 gen(                                       // генератор псевдослучайных чисел
        static_cast<unsigned>(                              // приведение типа для seed
            std::chrono::steady_clock::now()                // получение текущего времени
                .time_since_epoch().count()                 // количество тиков с начала эпохи
        )
    );
    std::uniform_int_distribution<int> dist(1, 100);       // диапазон случайных чисел от 1 до 100

    for (int i = 0; i < SIZE; ++i) {                         // цикл заполнения массива
        data[i] = dist(gen);                                // генерация случайного значения
    }

    // --- последовательное вычисление --- //
    auto t1 = std::chrono::high_resolution_clock::now();   // начало замера времени (seq)

    long long sumSeq = 0;                                   // переменная для суммы элементов
    for (int x : data) {                                    // последовательный проход по массиву
        sumSeq += x;                                        // добавление элемента к сумме
    }
    double avgSeq = static_cast<double>(sumSeq) / SIZE;    // вычисление среднего значения

    auto t2 = std::chrono::high_resolution_clock::now();   // конец замера времени (seq)
    auto timeSeq = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count(); 
                                                            // время выполнения последовательной версии

    // --- параллельное вычисление (OpenMP) --- //
    auto t3 = std::chrono::high_resolution_clock::now();   // начало замера времени (OMP)

    long long sumPar = 0;                                   // переменная для параллельной суммы
#pragma omp parallel for reduction(+:sumPar)               // параллельный цикл с редукцией суммы
    for (int i = 0; i < SIZE; ++i) {                         // итерации распределяются между потоками
        sumPar += data[i];                                  // локальное суммирование в потоках
    }
    double avgPar = static_cast<double>(sumPar) / SIZE;    // вычисление среднего значения

    auto t4 = std::chrono::high_resolution_clock::now();   // конец замера времени (OMP)
    auto timePar = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count(); 
                                                            // время выполнения параллельной версии

    // --- вывод --- //
    std::cout << "Array size: " << SIZE << '\n';            // вывод размера массива
    std::cout << "Sequential average: " << avgSeq           // вывод среднего (seq)
              << ", time: " << timeSeq << " ms\n";          // вывод времени выполнения
    std::cout << "Parallel average (OpenMP): " << avgPar    // вывод среднего (OMP)
              << ", time: " << timePar << " ms\n";          // вывод времени выполнения
    std::cout << "OpenMP threads count: "                   // вывод количества потоков OpenMP
              << omp_get_max_threads() << '\n';

    return 0;                                               // завершение программы
}