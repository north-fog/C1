#include <iostream>
#include "DatList.h"
using namespace std;

// Класс для тестового значения
class TestValue : public TDatValue {
private:
    int data;
public:
    TestValue(int d = 0) : data(d) {}
    TDatValue* GetCopy() override { return new TestValue(data); }
    int GetData() const { return data; }
    void SetData(int d) { data = d; }
};

void main() {
    cout << "=== Тестирование списковой структуры хранения ===\n\n";
    
    TDatList list;
    
    // 1. Проверка пустого списка
    cout << "1. Проверка пустого списка:" << endl;
    cout << "   Пуст? " << (list.IsEmpty() ? "да" : "нет") << endl;
    cout << "   Длина: " << list.GetListLength() << endl;
    
    // 2. Добавление элементов в конец
    cout << "\n2. Добавляем элементы 10, 20, 30 в конец:" << endl;
    list.InsLast(new TestValue(10));
    list.InsLast(new TestValue(20));
    list.InsLast(new TestValue(30));
    
    cout << "   Длина после добавления: " << list.GetListLength() << endl;
    
    // 3. Вывод элементов
    cout << "\n3. Вывод элементов:" << endl;
    list.Reset();
    cout << "   Элементы: ";
    while (!list.IsListEnded()) {
        TestValue* val = static_cast<TestValue*>(list.GetDatValue());
        cout << val->GetData() << " ";
        list.GoNext();
    }
    cout << endl;
    
    // 4. Добавление в начало
    cout << "\n4. Добавляем 5 в начало:" << endl;
    list.InsFirst(new TestValue(5));
    
    list.Reset();
    cout << "   Элементы: ";
    while (!list.IsListEnded()) {
        TestValue* val = static_cast<TestValue*>(list.GetDatValue());
        cout << val->GetData() << " ";
        list.GoNext();
    }
    cout << endl;
    
    // 5. Установка текущей позиции
    cout << "\n5. Устанавливаем текущую позицию = 2:" << endl;
    list.SetCurrentPos(2);
    TestValue* val = static_cast<TestValue*>(list.GetDatValue());
    cout << "   Текущий элемент: " << val->GetData() << endl;
    
    // 6. Вставка перед текущим
    cout << "\n6. Вставляем 15 перед текущим элементом:" << endl;
    list.InsCurrent(new TestValue(15));
    
    list.Reset();
    cout << "   Элементы: ";
    while (!list.IsListEnded()) {
        TestValue* v = static_cast<TestValue*>(list.GetDatValue());
        cout << v->GetData() << " ";
        list.GoNext();
    }
    cout << endl;
    
    // 7. Удаление первого элемента
    cout << "\n7. Удаляем первый элемент:" << endl;
    list.DelFirst();
    
    list.Reset();
    cout << "   Элементы: ";
    while (!list.IsListEnded()) {
        TestValue* v = static_cast<TestValue*>(list.GetDatValue());
        cout << v->GetData() << " ";
        list.GoNext();
    }
    cout << endl;
    
    // 8. Удаление текущего элемента
    cout << "\n8. Удаляем текущий элемент (позиция 2):" << endl;
    list.SetCurrentPos(2);
    list.DelCurrent();
    
    list.Reset();
    cout << "   Элементы: ";
    while (!list.IsListEnded()) {
        TestValue* v = static_cast<TestValue*>(list.GetDatValue());
        cout << v->GetData() << " ";
        list.GoNext();
    }
    cout << endl;
    
    // 9. Удаление всего списка
    cout << "\n9. Удаляем весь список:" << endl;
    list.DelList();
    cout << "   Пуст? " << (list.IsEmpty() ? "да" : "нет") << endl;
    cout << "   Длина: " << list.GetListLength() << endl;
    
    cout << "\n=== Тестирование завершено ===" << endl;
    
    
}