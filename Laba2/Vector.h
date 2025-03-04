#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vector {
private:
    double* data; // Указатель на массив элементов
    int size;     // Размерность вектора

public:
    // Конструкторы
    Vector(); // Конструктор по умолчанию
    Vector(const double* arr, int n); // Конструктор из массива
    Vector(const Vector& other); // Конструктор копирования
    Vector(Vector&& other) noexcept; // Конструктор перемещения

    // Деструктор
    ~Vector();

    // Перегрузка операторов
    double& operator[](int index); // Оператор доступа по индексу
    Vector& operator=(const Vector& other); // Присваивание с копированием
    Vector& operator=(Vector&& other) noexcept; // Присваивание с перемещением

    // Потоковый ввод/вывод
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec);
    friend std::istream& operator>>(std::istream& is, Vector& vec);

    // Перегрузка сложения: массив + вектор
    friend Vector operator+(const double* array, const Vector& vec);

    // Получение размера вектора
    int getSize() const;
};

#endif // VECTOR_H
