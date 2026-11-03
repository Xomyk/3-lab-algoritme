#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Vector {
private:
    T* data;    
    int sz;     // кол элем
    int cap;    // размер памятти

public:
    Vector() : data(nullptr), sz(0), cap(0) {
        cout << "Вызван конструктор по умолчанию." << endl;
    }
    Vector(const Vector& other) : sz(other.sz), cap(other.cap) {
        cout << "Вызван конструктор копирования (глубокое копирование)." << endl;
        data = new T[cap];
        for (int i = 0; i < sz; i++) {
            data[i] = other.data[i];
        }
    }
    Vector& operator=(const Vector& other) {
        if (this != &other) { 
            Vector temp(other);
            swap(data, temp.data);
            swap(sz, temp.sz);
            swap(cap, temp.cap);
        }
        return *this;
    }
    ~Vector() {
        delete[] data;
        cout << "Вызван деструктор (память освобождена)." << endl;
    }

    void reserve(int newCap) {
        if (newCap <= cap) return; 

        T* newData = new T[newCap];
        for (int i = 0; i < sz; i++) {
            newData[i] = data[i]; 
        }
        delete[] data;
        data = newData;
        cap = newCap;
    }
    void push_back(const T& value) {
        if (sz >= cap) {
            int newCap = (cap == 0) ? 1 : cap * 2;
            reserve(newCap);
        }
        data[sz++] = value;
    }
    void pop_back() {
        if (sz > 0) {
            sz--;
        } else {
            cout << "Ошибка: попытка удалить элемент из пустого вектора!" << endl;
        }
    }
    int size() const { return sz; }
    int capacity() const { return cap; }

    void print() const {
        cout << "[";
        for (int i = 0; i < sz; i++) {
            cout << data[i];
            if (i < sz - 1) cout << ", ";
        }
        cout << "]";
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    cout << "--- 1. Создание вектора и использование push_back ---" << endl;
    Vector<int> v1;
    for (int i = 1; i <= 5; i++) {
        v1.push_back(i * 10);
    }
    cout << "Вектор v1: ";
    v1.print();
    cout << " (Размер: " << v1.size() << ", Ёмкость: " << v1.capacity() << ")\n\n";

    cout << "--- 2. Использование метода reserve ---" << endl;
    Vector<int> v2;
    v2.reserve(10); 
    cout << "После reserve(10): Размер: " << v2.size() << ", Ёмкость: " << v2.capacity() << endl;
    v2.push_back(99);
    cout << "Вектор v2: ";
    v2.print();
    cout << "\n\n";
    cout << "--- 3. Демонстрация pop_back ---" << endl;
    v1.pop_back();
    cout << "Вектор v1 после pop_back: ";
    v1.print();
    cout << " (Размер: " << v1.size() << ")\n\n";
    cout << "--- 4. Демонстрация конструктора копирования ---" << endl;
    Vector<int> v3 = v1;
    cout << "Вектор v3 (копия v1): ";
    v3.print();
    cout << "\n\n";
    cout << "--- 5. Демонстрация оператора присваивания ---" << endl;
    Vector<int> v4;
    v4 = v2; // Присваивание
    cout << "Вектор v4 (присвоен из v2): ";
    v4.print();
    cout << "\n\n";
    cout << "--- Конец программы (вызов деструкторов) ---" << endl;
    return 0;
}