#include <iostream>
#include <cstdlib>
#include <ctime>
#include "TBitField.h"
#include "TSet.h"

using namespace std;


void printResult(const char* testName, bool success) {
    cout << "[" << (success ? "OK" : "FAIL") << "] " << testName << endl;
}



void testBitFieldCreate() {
    cout << "\n--- Тест создания битового поля ---\n";
    bool ok = true;
    
    try {
        TBitField bf1(100);
        printResult("Создание поля длиной 100", bf1.GetLen() == 100);
        
        TBitField bf2(1);
        printResult("Создание поля длиной 1", bf2.GetLen() == 1);
        
        TBitField bf3(32);
        printResult("Создание поля длиной 32", bf3.GetLen() == 32);
        
    } catch (const char* msg) {
        cout << "Ошибка: " << msg << endl;
        ok = false;
    }
    
    if (ok) cout << " Тест создания пройден\n";
}

void testBitFieldSetGet() {
    cout << "\n--- Тест установки и получения битов ---\n";
    
    TBitField bf(16);
    
    // Устанавливаем биты
    bf.SetBit(0);
    bf.SetBit(5);
    bf.SetBit(10);
    bf.SetBit(15);
    
    cout << "Битовое поле: " << bf << endl;
    
    // Проверяем установленные
    bool ok = true;
    ok = ok && (bf.GetBit(0) == 1);
    ok = ok && (bf.GetBit(5) == 1);
    ok = ok && (bf.GetBit(10) == 1);
    ok = ok && (bf.GetBit(15) == 1);
    
    // Проверяем неустановленные
    ok = ok && (bf.GetBit(1) == 0);
    ok = ok && (bf.GetBit(7) == 0);
    
    printResult("Установка и чтение битов", ok);
}

void testBitFieldClear() {
    cout << "\n--- Тест очистки битов ---\n";
    
    TBitField bf(8);
    bf.SetBit(2);
    bf.SetBit(4);
    bf.SetBit(6);
    
    cout << "До очистки: " << bf << endl;
    
    bf.ClrBit(2);
    bf.ClrBit(6);
    
    cout << "После очистки: " << bf << endl;
    
    bool ok = true;
    ok = ok && (bf.GetBit(2) == 0);
    ok = ok && (bf.GetBit(6) == 0);
    ok = ok && (bf.GetBit(4) == 1);
    
    printResult("Очистка битов", ok);
}

void testBitFieldOperations() {
    cout << "\n--- Тест операций &, |, ~ ---\n";
    
    TBitField bf1(8);
    TBitField bf2(8);
    
    // bf1 = 10101010
    bf1.SetBit(0); bf1.SetBit(2); bf1.SetBit(4); bf1.SetBit(6);
    
    // bf2 = 01010101
    bf2.SetBit(1); bf2.SetBit(3); bf2.SetBit(5); bf2.SetBit(7);
    
    cout << "bf1: " << bf1 << endl;
    cout << "bf2: " << bf2 << endl;
    
    TBitField bfAnd = bf1 & bf2;
    TBitField bfOr = bf1 | bf2;
    TBitField bfNot = ~bf1;
    
    cout << "bf1 & bf2: " << bfAnd << endl;
    cout << "bf1 | bf2: " << bfOr << endl;
    cout << "~bf1: " << bfNot << endl;
    
    // Проверка результатов
    bool ok = true;
    
    // AND должно быть 00000000
    for (int i = 0; i < 8; i++) {
        if (bfAnd.GetBit(i) != 0) ok = false;
    }
    
    // OR должно быть 11111111
    for (int i = 0; i < 8; i++) {
        if (bfOr.GetBit(i) != 1) ok = false;
    }
    
    // NOT bf1 должно быть 01010101 (как bf2)
    for (int i = 0; i < 8; i++) {
        if (bfNot.GetBit(i) != bf2.GetBit(i)) ok = false;
    }
    
    printResult("Операции &, |, ~", ok);
}

void testBitFieldCopy() {
    cout << "\n--- Тест копирования и присваивания ---\n";
    
    // Создаем оригинал
    TBitField original(10);
    original.SetBit(1);
    original.SetBit(3);
    original.SetBit(5);
    
    cout << "Оригинал: " << original << endl;
    
    // ТЕСТ 1: Конструктор копирования
    TBitField copyConst(original);
    cout << "Копия (конструктор): " << copyConst << endl;
    
    // ТЕСТ 2: Оператор присваивания
    TBitField copyAssign(5);  // создаем с другой длиной
    copyAssign = original;
    cout << "Копия (присваивание): " << copyAssign << endl;
    
    // Проверка 1: Сейчас они все одинаковые
    bool initOK = true;
    for (int i = 0; i < 10; i++) {
        if (original.GetBit(i) != copyConst.GetBit(i)) initOK = false;
        if (original.GetBit(i) != copyAssign.GetBit(i)) initOK = false;
    }
    cout << "Начальное равенство: " << (initOK ? "OK" : "FAIL") << endl;
    
    // Проверка 2: Изменяем оригинал
    cout << "\nИзменяем оригинал (устанавливаем бит 7)..." << endl;
    original.SetBit(7);
    
    cout << "Оригинал после изменения: " << original << endl;
    cout << "Копия (конструктор): " << copyConst << endl;
    cout << "Копия (присваивание): " << copyAssign << endl;
    
    // Проверяем, что копии НЕ изменились
    bool independentOK = true;
    
    // В копиях бит 7 должен остаться 0
    if (copyConst.GetBit(7) != 0) {
        cout << "FAIL: конструктор копирования изменился!" << endl;
        independentOK = false;
    }
    if (copyAssign.GetBit(7) != 0) {
        cout << "FAIL: оператор присваивания изменился!" << endl;
        independentOK = false;
    }
    
    // Оригинал должен иметь бит 7 = 1
    if (original.GetBit(7) != 1) {
        cout << "FAIL: оригинал не изменился!" << endl;
        independentOK = false;
    }
    
    cout << "Независимость копий: " << (independentOK ? "OK" : "FAIL") << endl;
    
    // Проверка 3: Изменяем копию
    cout << "\nИзменяем копию (конструктор) - очищаем бит 3..." << endl;
    copyConst.ClrBit(3);
    
    cout << "Оригинал: " << original << endl;
    cout << "Копия (конструктор): " << copyConst << endl;
    cout << "Копия (присваивание): " << copyAssign << endl;
    
    // Проверяем, что оригинал и другая копия не изменились
    bool reverseOK = true;
    
    if (original.GetBit(3) != 1) {
        cout << "FAIL: оригинал изменился!" << endl;
        reverseOK = false;
    }
    if (copyAssign.GetBit(3) != 1) {
        cout << "FAIL: другая копия изменилась!" << endl;
        reverseOK = false;
    }
    
    cout << "Обратная независимость: " << (reverseOK ? "OK" : "FAIL") << endl;
    
    // Итог
    cout << "\nИТОГ: ";
    if (initOK && independentOK && reverseOK) {
        cout << "? Копирование и присваивание работают правильно!" << endl;
    } else {
        cout << "? Есть проблемы с копированием!" << endl;
    }
}

void testBitFieldErrors() {
    cout << "\n--- Тест обработки ошибок ---\n";
    
    // Тест 1: отрицательная длина
    try {
        TBitField bf(-5);
        cout << "[FAIL] Отрицательная длина не вызвала исключение!" << endl;
    } catch (const char* msg) {
        cout << "[OK] Отрицательная длина: " << msg << endl;
    }
    
    // Тест 2: выход за границы в SetBit
    try {
        TBitField bf(10);
        bf.SetBit(20);
        cout << "[FAIL] SetBit за границами не вызвал исключение!" << endl;
    } catch (const char* msg) {
        cout << "[OK] SetBit за границами: " << msg << endl;
    }
    
    // Тест 3: выход за границы в GetBit
    try {
        TBitField bf(10);
        bf.GetBit(20);
        cout << "[FAIL] GetBit за границами не вызвал исключение!" << endl;
    } catch (const char* msg) {
        cout << "[OK] GetBit за границами: " << msg << endl;
    }
    
    // Тест 4: отрицательный индекс
    try {
        TBitField bf(10);
        bf.SetBit(-1);
        cout << "[FAIL] Отрицательный индекс не вызвал исключение!" << endl;
    } catch (const char* msg) {
        cout << "[OK] Отрицательный индекс: " << msg << endl;
    }
}

//------------------------------------------------------------------------------
// ТЕСТЫ ДЛЯ TSet
//------------------------------------------------------------------------------

void testSetCreate() {
    cout << "\n--- Тест создания множества ---\n";
    
    TSet s1(20);
    cout << "Пустое множество (мощность 20): " << s1 << endl;
    
    bool ok = (s1.isMember(0) == 0) && (s1.isMember(19) == 0);
    printResult("Создание пустого множества", ok);
}

void testSetInsDel() {
    cout << "\n--- Тест добавления и удаления элементов ---\n";
    
    TSet s(10);
    
    s.InsElem(2);
    s.InsElem(4);
    s.InsElem(6);
    s.InsElem(8);
    
    cout << "После добавления {2,4,6,8}: " << s << endl;
    
    bool ok = true;
    ok = ok && (s.isMember(2) == 1);
    ok = ok && (s.isMember(4) == 1);
    ok = ok && (s.isMember(6) == 1);
    ok = ok && (s.isMember(8) == 1);
    ok = ok && (s.isMember(0) == 0);
    
    s.DelElem(4);
    s.DelElem(8);
    
    cout << "После удаления 4 и 8: " << s << endl;
    
    ok = ok && (s.isMember(4) == 0);
    ok = ok && (s.isMember(8) == 0);
    ok = ok && (s.isMember(2) == 1);
    ok = ok && (s.isMember(6) == 1);
    
    printResult("Добавление и удаление", ok);
}

void testSetOperations() {
    cout << "\n--- Тест операций над множествами ---\n";
    
    TSet A(10), B(10);
    
    // A = {1,3,5,7,9}
    for (int i = 1; i < 10; i += 2) A.InsElem(i);
    
    // B = {0,2,4,6,8}
    for (int i = 0; i < 10; i += 2) B.InsElem(i);
    
    cout << "A: " << A << endl;
    cout << "B: " << B << endl;
    
    TSet C = A + B;  // объединение
    TSet D = A * B;  // пересечение
    TSet E = ~A;     // дополнение
    
    cout << "A и B: " << C << endl;
    cout << "A или B: " << D << endl;
    cout << "не A: " << E << endl;
    
    bool ok = true;
    
    // Проверка объединения (должны быть все числа 0-9)
    for (int i = 0; i < 10; i++) {
        if (C.isMember(i) != 1) ok = false;
    }
    
    // Проверка пересечения (должно быть пусто)
    for (int i = 0; i < 10; i++) {
        if (D.isMember(i) != 0) ok = false;
    }
    
    printResult("Операции над множествами", ok);
}

void testSetComparison() {
    cout << "\n--- Тест сравнения множеств ---\n";
    
    TSet A(10), B(10), C(10);
    
    A.InsElem(1); A.InsElem(3); A.InsElem(5);
    B.InsElem(1); B.InsElem(3); B.InsElem(5);
    C.InsElem(2); C.InsElem(4); C.InsElem(6);
    
    cout << "A: " << A << endl;
    cout << "B: " << B << endl;
    cout << "C: " << C << endl;
    
    bool ok = true;
    ok = ok && (A == B);
    ok = ok && !(A == C);
    
    printResult("Сравнение множеств", ok);
}

void testSetConversion() {
    cout << "\n--- Тест преобразования в битовое поле ---\n";
    
    TSet s(8);
    s.InsElem(1);
    s.InsElem(3);
    s.InsElem(5);
    s.InsElem(7);
    
    cout << "Множество: " << s << endl;
    
    TBitField bf = (TBitField)s;
    cout << "Битовое поле: " << bf << endl;
    
    bool ok = true;
    ok = ok && (bf.GetBit(1) == 1);
    ok = ok && (bf.GetBit(3) == 1);
    ok = ok && (bf.GetBit(5) == 1);
    ok = ok && (bf.GetBit(7) == 1);
    ok = ok && (bf.GetBit(0) == 0);
    
    printResult("Преобразование в битовое поле", ok);
}


int main() {
    setlocale(LC_ALL, "Rus");
    int t = 1;
    while(t>0){
    try {
        // Тесты TBitField
        cout << "\n********** ТЕСТЫ КЛАССА TBitField **********\n";
        testBitFieldCreate();
        testBitFieldSetGet();
        testBitFieldClear();
        testBitFieldOperations();
        testBitFieldCopy();
        testBitFieldErrors();
        
        // Тесты TSet
        cout << "\n********** ТЕСТЫ КЛАССА TSet **********\n";
        testSetCreate();
        testSetInsDel();
        testSetOperations();
        testSetComparison();
        testSetConversion();
        
    } catch (const char* msg) {
        cout << "\n НЕПРЕДВИДЕННАЯ ОШИБКА: " << msg << endl;
        return 1;
    } catch (...) {
        cout << "\n НЕИЗВЕСТНАЯ ОШИБКА!" << endl;
        return 1;
    }
    cout << "хотите повторить тест(1 - да, 0 - нет)?:";
    cin >> t;
    }
    
    
}