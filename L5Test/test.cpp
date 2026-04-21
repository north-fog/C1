#include <iostream>
#include "TList.h"
using namespace std;

// Простой класс значения для тестирования (аналог TMonom)
class TestValue : public TDatValue {
private:
    int data;
public:
    TestValue(int d = 0) : data(d) {}
    
    TDatValue* GetCopy() override {
        return new TestValue(data);
    }
    
    int GetData() const { return data; }
    void SetData(int d) { data = d; }
};

int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "============================================" << endl;
    cout << "   ТЕСТИРОВАНИЕ СПИСКОВОЙ СТРУКТУРЫ" << endl;
    cout << "============================================" << endl;
    
    TList list;
    
    // ========== ТЕСТ 1: Проверка пустого списка ==========
    cout << "\n1. Проверка пустого списка:" << endl;
    cout << "   Пуст? " << (list.IsEmpty() ? "да" : "нет") << endl;
    cout << "   Длина: " << list.GetLength() << endl;
    
    // ========== ТЕСТ 2: Добавление в конец ==========
    cout << "\n2. Добавляем элементы в конец: 10, 20, 30" << endl;
    list.InsLast(new TestValue(10));
    list.InsLast(new TestValue(20));
    list.InsLast(new TestValue(30));
    cout << "   Длина после добавления: " << list.GetLength() << endl;
    
    // ========== ТЕСТ 3: Вывод элементов ==========
    cout << "\n3. Вывод всех элементов:" << endl;
    cout << "   Элементы: ";
    list.Reset();
    while (!list.IsEnd()) {
        TestValue* val = static_cast<TestValue*>(list.GetCurrent());
        cout << val->GetData() << " ";
        list.GoNext();
    }
    cout << endl;
    
    // ========== ТЕСТ 4: Добавление в начало ==========
    cout << "\n4. Добавляем элемент 5 в начало" << endl;
    list.InsFirst(new TestValue(5));
    
    cout << "   Все элементы: ";
    list.Reset();
    while (!list.IsEnd()) {
        TestValue* val = static_cast<TestValue*>(list.GetCurrent());
        cout << val->GetData() << " ";
        list.GoNext();
    }
    cout << endl;
    
    // ========== ТЕСТ 5: Удаление первого элемента ==========
    cout << "\n5. Удаляем первый элемент" << endl;
    list.DelFirst();
    
    cout << "   Все элементы: ";
    list.Reset();
    while (!list.IsEnd()) {
        TestValue* val = static_cast<TestValue*>(list.GetCurrent());
        cout << val->GetData() << " ";
        list.GoNext();
    }
    cout << endl;
    
    // ========== ТЕСТ 6: Вставка перед текущим ==========
    cout << "\n6. Вставляем элемент 15 перед текущим (позиция 2)" << endl;
    
    // Устанавливаем текущий на 2-й элемент
    list.Reset();
    list.GoNext();  // на 2-й элемент
    
    list.InsCurrent(new TestValue(15));
    
    cout << "   Все элементы: ";
    list.Reset();
    while (!list.IsEnd()) {
        TestValue* val = static_cast<TestValue*>(list.GetCurrent());
        cout << val->GetData() << " ";
        list.GoNext();
    }
    cout << endl;
    
    // ========== ТЕСТ 7: Удаление текущего элемента ==========
    cout << "\n7. Удаляем текущий элемент (должен быть 15)" << endl;
    list.DelCurrent();
    
    cout << "   Все элементы: ";
    list.Reset();
    while (!list.IsEnd()) {
        TestValue* val = static_cast<TestValue*>(list.GetCurrent());
        cout << val->GetData() << " ";
        list.GoNext();
    }
    cout << endl;
    
    // ========== ТЕСТ 8: Очистка списка ==========
    cout << "\n8. Очищаем список" << endl;
    list.Clear();
    cout << "   Пуст? " << (list.IsEmpty() ? "да" : "нет") << endl;
    cout << "   Длина: " << list.GetLength() << endl;
    
    cout << "\n============================================" << endl;
    cout << "            ТЕСТИРОВАНИЕ ЗАВЕРШЕНО" << endl;
    cout << "============================================" << endl;
    
    return 0;
}