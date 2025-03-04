#include "Vector.h"
#include <iostream>
#include <stdexcept>
#include <fstream>

// Конструктор по умолчанию
Vector::Vector() : data(nullptr), size(0) {}

// Конструктор из массива
Vector::Vector(const double* arr, int n) : size(n) {
    data = new double[n];
    for (int i = 0; i < n; ++i) {
        data[i] = arr[i];
    }
}

// Конструктор копирования
Vector::Vector(const Vector& other) : size(other.size) {
    data = new double[size];
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

// Конструктор перемещения
Vector::Vector(Vector&& other) noexcept : data(other.data), size(other.size) {
    other.data = nullptr;
    other.size = 0;
}

// Деструктор
Vector::~Vector() {
    delete[] data;
}

// Перегрузка оператора []
double& Vector::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Присваивание с копированием
Vector& Vector::operator=(const Vector& other) {
    if (this == &other) return *this; // Проверка самоприсваивания

    delete[] data;

    size = other.size;
    data = new double[size];
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }

    return *this;
}

// Присваивание с перемещением
Vector& Vector::operator=(Vector&& other) noexcept {
    if (this == &other) return *this; // Проверка самоприсваивания

    delete[] data;

    data = other.data;
    size = other.size;

    other.data = nullptr;
    other.size = 0;

    return *this;
}

// Потоковый вывод
std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    os << "[";
    for (int i = 0; i < vec.size; ++i) {
        os << vec.data[i];
        if (i != vec.size - 1) os << ", ";
    }
    os << "]";
    return os;
}

// Потоковый ввод
std::istream& operator>>(std::istream& is, Vector& vec) {
    is >> vec.size;
    delete[] vec.data;
    vec.data = new double[vec.size];
    for (int i = 0; i < vec.size; ++i) {
        is >> vec.data[i];
    }
    return is;
}

// Перегрузка сложения: массив + вектор
Vector operator+(const double* array, const Vector& vec) {
    int newSize = vec.size * 2; // Длина нового вектора равна удвоенной длине существующего вектора
    Vector result;
    result.size = newSize;
    result.data = new double[newSize];

    // Копируем элементы массива в начало нового вектора
    for (int i = 0; i < vec.size; ++i) {
        result.data[i] = array[i];
    }

    // Копируем элементы вектора в конец нового вектора
    for (int i = 0; i < vec.size; ++i) {
        result.data[vec.size + i] = vec.data[i];
    }

    return result;
}
// Получение размера вектора
int Vector::getSize() const {
    return size;
}


int main() {
    // Чтение данных из файла input.txt
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 1;
    }

    Vector vec1;
    inputFile >> vec1; // Считываем вектор из файла

    inputFile.close();

    // Массив данных для сложения
    double array[] = {10.0, 20.0, 30.0, 40.0, 50.0};

    // Выполняем операцию сложения массива и вектора
    Vector result = array + vec1;

    // Записываем результат в output.txt
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output.txt" << std::endl;
        return 1;
    }

    outputFile << "First vector: " << vec1 << std::endl;
    outputFile << "Resulting vector: " << result << std::endl;

    outputFile.close();

    return 0;
}
