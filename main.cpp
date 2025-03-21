#include <iostream>
#include <stdexcept>
#include <fstream>


/* Вариант 6

Дан класс (например, с именем Vector), задающий вектор размерности n. Поля
класса: указатель на массив, задающий вектор (тип элемента int или double в зависимости
от варианта), массив должен создаваться динамически, число элементов (размерность)
вектора (тип int). Класс включает: конструктор без параметров, задающий пустой вектор
(число элементов равно 0), конструктор, создающий объект вектор на основе обычного
одномерного
массива
размерности
n,
конструктор
копирования,
конструктор
перемещения, деструктор.
Необходимо перегрузить операции и продемонстрировать их работу. Перегрузить
операцию [] (обращение к элементу вектора по индексу), операцию = (присваивание с
копированием), операцию = (присваивание с перемещением), а также операцию вставки
(<<) объекта в поток cout или в файл (объект класса ostream) и операцию извлечения (>>)
объекта из потока cin или из файла (объект класса istream). Также продемонстрировать
разницу между конструктором копирования и конструктором перемещения и между
операциями присваивания с копированием и перемещением. Исходные коды класса
разместить в двух файлах: в заголовочном файле класса и файле реализации класса.
При выполнении работы все входные данные читаются из текстового файла
input.txt (создать этот файл любым текстовым редактором), результаты выводятся в файл
output.txt. В отчете представить содержимое этих файлов.

+ сложение векторов, на выходе вектор, длина
которого сумме длин векторов вначале идут
элементы первого вектора, затем второго,
если один из векторов задан обычным
массивом, то считать, что его длина равна
длине вектора, заданным объектом класса*/

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
