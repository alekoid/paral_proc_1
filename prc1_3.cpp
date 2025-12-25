#include <iostream>     //библиотека ввода и вывода (cout, cin)
#include <random>       //генератор случайных чисел C++
#include <chrono>       //работа со временем и замеры производительности
#include <omp.h>        //библиотека OpenMP для параллельных вычислений

using namespace std;    //использование стандартного пространства имён

double average_seq(const int* arr, int N) {   //последовательное вычисление среднего
    long long sum = 0;                        //переменная для накопления суммы

    for (int i = 0; i < N; ++i)               //цикл по всем элементам массива
        sum += arr[i];                        //добавление текущего элемента к сумме

    return static_cast<double>(sum) / N;      //возврат среднего значения
}

double average_par(const int* arr, int N) {   //параллельное вычисление среднего
    long long sum = 0;                        //общая переменная суммы

#pragma omp parallel for reduction(+:sum)     //параллельный цикл с редукцией суммы
    for (int i = 0; i < N; ++i)               //итерации распределяются между потоками
        sum += arr[i];                        //локальное суммирование в потоках

    return static_cast<double>(sum) / N;      //возврат среднего значения
}

int main() {                                  //точка входа в программу
    setlocale(0, "");                         //корректное отображение русских символов

    int N;                                    //переменная для размера массива
    cout << "Enter N (array size): ";         //запрос размера массива
    cin >> N;                                 //ввод размера массива

    if (N <= 0) {                             //проверка корректности размера
        cout << "Invalid N\n";                //сообщение об ошибке
        return 1;                             //завершение программы с ошибкой
    }

    int* arr = new int[N];                    //динамическое выделение памяти под массив

    mt19937 gen(42);                          //генератор случайных чисел с фиксированным seed
    uniform_int_distribution<> dist(1, 100); //равномерное распределение от 1 до 100

    for (int i = 0; i < N; ++i)               //заполнение массива
        arr[i] = dist(gen);                   //генерация случайного числа

    auto t1 = chrono::high_resolution_clock::now(); //начало замера времени (последовательно)
    double avg_seq = average_seq(arr, N);           //последовательное вычисление среднего
    auto t2 = chrono::high_resolution_clock::now(); //конец замера времени

    auto t3 = chrono::high_resolution_clock::now(); //начало замера времени (параллельно)
    double avg_par = average_par(arr, N);           //параллельное вычисление среднего
    auto t4 = chrono::high_resolution_clock::now(); //конец замера времени

    double time_seq = chrono::duration<double, milli>(t2 - t1).count(); //вывод времени последовательной версии
    double time_par = chrono::duration<double, milli>(t4 - t3).count(); //вывод времени параллельной версии

    cout << "Sequential average = " << avg_seq       //вывод среднего (последовательно)
         << ", time = " << time_seq << " ms\n";      // и также его времени выполнения

    cout << "Parallel average   = " << avg_par       //вывод среднего (параллельно)
         << ", time = " << time_par << " ms\n";      // и также его времени выполнения

    cout << "OpenMP threads     = "                  //вывод количества потоков OpenMP
         << omp_get_max_threads() << "\n";

    delete[] arr;                             //освобождение динамически выделенной памяти
    return 0;                                 //завершение программы
}
