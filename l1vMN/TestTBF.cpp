#include <iostream>
#include <cstdlib>
#include "TBitField.h"
#include "TSet.h"

using namespace std;

// Вспомогательная функция для вывода битового поля с именем
void printBitField(const char* name, const TBitField& bf) {
    cout << name << " (битовое поле):" << endl;
    cout << bf << endl;
}

// Функция для красивого вывода разделителей
void printSeparator() {
    cout << "----------------------------------------" << endl;
}

void printResult(const char* testName, bool success) {
    cout << "[" << (success ? "OK" : "FAIL") << "] " << testName << endl;
}

//------------------------------------------------------------------------------
// ТЕСТЫ ДЛЯ TBitField
//------------------------------------------------------------------------------

void testBitFieldCreate() {
    printSeparator();
    cout << "--- Тест создания битового поля ---\n";
    
    try {
        cout << "Создание поля длиной 100... ";
        TBitField bf1(100);
        cout << "готово. Длина: " << bf1.GetLen() << endl;
        printBitField("bf1", bf1);
        printResult("Создание поля длиной 100", bf1.GetLen() == 100);
        
        cout << "\nСоздание поля длиной 1... ";
        TBitField bf2(1);
        cout << "готово. Длина: " << bf2.GetLen() << endl;
        printBitField("bf2", bf2);
        printResult("Создание поля длиной 1", bf2.GetLen() == 1);
        
        cout << "\nСоздание поля длиной 32... ";
        TBitField bf3(32);
        cout << "готово. Длина: " << bf3.GetLen() << endl;
        printBitField("bf3", bf3);
        printResult("Создание поля длиной 32", bf3.GetLen() == 32);
        
    } catch (const char* msg) {
        cout << "\nОШИБКА: " << msg << endl;
    }
}

void testBitFieldSetGet() {
    printSeparator();
    cout << "--- Тест установки и получения битов ---\n";
    
    TBitField bf(16);
    printBitField("Начальное поле (16 бит)", bf);
    
    cout << "\nУстанавливаем биты: 0, 5, 10, 15\n";
    bf.SetBit(0);
    printBitField("  после SetBit(0)", bf);
    
    bf.SetBit(5);
    printBitField("  после SetBit(5)", bf);
    
    bf.SetBit(10);
    printBitField("  после SetBit(10)", bf);
    
    bf.SetBit(15);
    printBitField("  после SetBit(15)", bf);
    
    // Проверяем установленные
    bool ok = true;
    cout << "\nПроверка установленных битов:" << endl;
    cout << "  бит 0: " << bf.GetBit(0) << " (должен быть 1)" << endl;
    cout << "  бит 5: " << bf.GetBit(5) << " (должен быть 1)" << endl;
    cout << "  бит 10: " << bf.GetBit(10) << " (должен быть 1)" << endl;
    cout << "  бит 15: " << bf.GetBit(15) << " (должен быть 1)" << endl;
    
    ok = ok && (bf.GetBit(0) == 1);
    ok = ok && (bf.GetBit(5) == 1);
    ok = ok && (bf.GetBit(10) == 1);
    ok = ok && (bf.GetBit(15) == 1);
    
    // Проверяем неустановленные
    cout << "\nПроверка неустановленных битов:" << endl;
    cout << "  бит 1: " << bf.GetBit(1) << " (должен быть 0)" << endl;
    cout << "  бит 7: " << bf.GetBit(7) << " (должен быть 0)" << endl;
    
    ok = ok && (bf.GetBit(1) == 0);
    ok = ok && (bf.GetBit(7) == 0);
    
    printResult("Установка и чтение битов", ok);
}

void testBitFieldClear() {
    printSeparator();
    cout << "--- Тест очистки битов ---\n";
    
    TBitField bf(8);
    bf.SetBit(2);
    bf.SetBit(4);
    bf.SetBit(6);
    
    printBitField("Начальное поле (установлены биты 2,4,6)", bf);
    
    cout << "\nОчищаем биты 2 и 6..." << endl;
    bf.ClrBit(2);
    bf.ClrBit(6);
    
    printBitField("После очистки", bf);
    
    bool ok = true;
    cout << "\nПроверка:" << endl;
    cout << "  бит 2: " << bf.GetBit(2) << " (должен быть 0)" << endl;
    cout << "  бит 6: " << bf.GetBit(6) << " (должен быть 0)" << endl;
    cout << "  бит 4: " << bf.GetBit(4) << " (должен быть 1)" << endl;
    
    ok = ok && (bf.GetBit(2) == 0);
    ok = ok && (bf.GetBit(6) == 0);
    ok = ok && (bf.GetBit(4) == 1);
    
    printResult("Очистка битов", ok);
}

void testBitFieldOperations() {
    printSeparator();
    cout << "--- Тест операций &, |, ~ ---\n";
    
    TBitField bf1(8);
    TBitField bf2(8);
    
    // bf1 = 10101010
    bf1.SetBit(0); bf1.SetBit(2); bf1.SetBit(4); bf1.SetBit(6);
    // bf2 = 01010101
    bf2.SetBit(1); bf2.SetBit(3); bf2.SetBit(5); bf2.SetBit(7);
    
    printBitField("bf1 (10101010)", bf1);
    printBitField("bf2 (01010101)", bf2);
    
    TBitField bfAnd = bf1 & bf2;
    TBitField bfOr = bf1 | bf2;
    TBitField bfNot = ~bf1;
    
    cout << "\nРезультаты:" << endl;
    printBitField("bf1 & bf2 (должно быть 00000000)", bfAnd);
    printBitField("bf1 | bf2 (должно быть 11111111)", bfOr);
    printBitField("~bf1     (должно быть 01010101)", bfNot);
    
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
    printSeparator();
    cout << "--- Тест копирования и присваивания ---\n";
    
    // Создаем оригинал
    TBitField original(10);
    original.SetBit(1);
    original.SetBit(3);
    original.SetBit(5);
    
    printBitField("Оригинал (10 бит, установлены 1,3,5)", original);
    
    // ТЕСТ 1: Конструктор копирования
    cout << "\n1. Создаем копию через конструктор копирования..." << endl;
    TBitField copyConst(original);
    printBitField("   Копия (конструктор)", copyConst);
    
    // ТЕСТ 2: Оператор присваивания
    cout << "\n2. Создаем поле 5 бит и присваиваем ему оригинал..." << endl;
    TBitField copyAssign(5);
    printBitField("   До присваивания (5 бит)", copyAssign);
    copyAssign = original;
    printBitField("   После присваивания", copyAssign);
    
    // Проверка 1: Сейчас они все одинаковые
    bool initOK = true;
    for (int i = 0; i < 10; i++) {
        if (original.GetBit(i) != copyConst.GetBit(i)) initOK = false;
        if (original.GetBit(i) != copyAssign.GetBit(i)) initOK = false;
    }
    cout << "\nНачальное равенство всех трех: " << (initOK ? "OK" : "FAIL") << endl;
    
    // Проверка 2: Изменяем оригинал
    cout << "\n3. Изменяем оригинал (устанавливаем бит 7)..." << endl;
    original.SetBit(7);
    
    printBitField("   Оригинал после изменения", original);
    printBitField("   Копия (конструктор)", copyConst);
    printBitField("   Копия (присваивание)", copyAssign);
    
    // Проверяем, что копии НЕ изменились
    bool independentOK = true;
    
    if (copyConst.GetBit(7) != 0) {
        cout << "   FAIL: конструктор копирования изменился!" << endl;
        independentOK = false;
    }
    if (copyAssign.GetBit(7) != 0) {
        cout << "   FAIL: оператор присваивания изменился!" << endl;
        independentOK = false;
    }
    if (original.GetBit(7) != 1) {
        cout << "   FAIL: оригинал не изменился!" << endl;
        independentOK = false;
    }
    
    cout << "   Независимость копий: " << (independentOK ? "OK" : "FAIL") << endl;
    
    // Проверка 3: Изменяем копию
    cout << "\n4. Изменяем копию (конструктор) - очищаем бит 3..." << endl;
    copyConst.ClrBit(3);
    
    printBitField("   Оригинал", original);
    printBitField("   Копия (конструктор)", copyConst);
    printBitField("   Копия (присваивание)", copyAssign);
    
    // Проверяем, что оригинал и другая копия не изменились
    bool reverseOK = true;
    
    if (original.GetBit(3) != 1) {
        cout << "   FAIL: оригинал изменился!" << endl;
        reverseOK = false;
    }
    if (copyAssign.GetBit(3) != 1) {
        cout << "   FAIL: другая копия изменилась!" << endl;
        reverseOK = false;
    }
    
    cout << "   Обратная независимость: " << (reverseOK ? "OK" : "FAIL") << endl;
    
    // Итог
    cout << "\nИТОГ: ";
    if (initOK && independentOK && reverseOK) {
        cout << "? Копирование и присваивание работают правильно!" << endl;
    } else {
        cout << "? Есть проблемы с копированием!" << endl;
    }
}

void testBitFieldErrors() {
    printSeparator();
    cout << "--- Тест обработки ошибок ---\n";
    
    // Тест 1: отрицательная длина
    cout << "Тест 1: создание поля с отрицательной длиной -5" << endl;
    try {
        TBitField bf(-5);
        cout << "  [FAIL] Отрицательная длина не вызвала исключение!" << endl;
    } catch (const char* msg) {
        cout << "  [OK] " << msg << endl;
    }
    
    // Тест 2: выход за границы в SetBit
    cout << "\nТест 2: SetBit(20) для поля длиной 10" << endl;
    try {
        TBitField bf(10);
        bf.SetBit(20);
        cout << "  [FAIL] SetBit за границами не вызвал исключение!" << endl;
    } catch (const char* msg) {
        cout << "  [OK] " << msg << endl;
    }
    
    // Тест 3: выход за границы в GetBit
    cout << "\nТест 3: GetBit(20) для поля длиной 10" << endl;
    try {
        TBitField bf(10);
        bf.GetBit(20);
        cout << "  [FAIL] GetBit за границами не вызвал исключение!" << endl;
    } catch (const char* msg) {
        cout << "  [OK] " << msg << endl;
    }
    
    // Тест 4: отрицательный индекс
    cout << "\nТест 4: SetBit(-1)" << endl;
    try {
        TBitField bf(10);
        bf.SetBit(-1);
        cout << "  [FAIL] Отрицательный индекс не вызвал исключение!" << endl;
    } catch (const char* msg) {
        cout << "  [OK] " << msg << endl;
    }
}

//------------------------------------------------------------------------------
// ТЕСТЫ ДЛЯ TSet
//------------------------------------------------------------------------------

void testSetCreate() {
    printSeparator();
    cout << "--- Тест создания множества ---\n";
    
    cout << "Создаем пустое множество мощностью 20..." << endl;
    TSet s1(20);
    cout << "Множество: " << s1 << endl;
    
    // Преобразуем в битовое поле и выводим
    TBitField bf = (TBitField)s1;
    printBitField("Битовое поле множества", bf);
    
    bool ok = (s1.isMember(0) == 0) && (s1.isMember(19) == 0);
    cout << "Проверка: элемент 0 - " << s1.isMember(0) 
         << ", элемент 19 - " << s1.isMember(19) << endl;
    
    printResult("Создание пустого множества", ok);
}

void testSetInsDel() {
    printSeparator();
    cout << "--- Тест добавления и удаления элементов ---\n";
    
    TSet s(10);
    cout << "Пустое множество: " << s << endl;
    TBitField bfEmpty = (TBitField)s;
    printBitField("Битовое поле (пустое)", bfEmpty);
    
    cout << "\nДобавляем элементы: 2, 4, 6, 8" << endl;
    s.InsElem(2);
    s.InsElem(4);
    s.InsElem(6);
    s.InsElem(8);
    
    cout << "После добавления: " << s << endl;
    TBitField bfAfterAdd = (TBitField)s;
    printBitField("Битовое поле после добавления", bfAfterAdd);
    
    bool ok = true;
    cout << "\nПроверка наличия:" << endl;
    cout << "  элемент 2: " << s.isMember(2) << " (должен быть 1)" << endl;
    cout << "  элемент 4: " << s.isMember(4) << " (должен быть 1)" << endl;
    cout << "  элемент 6: " << s.isMember(6) << " (должен быть 1)" << endl;
    cout << "  элемент 8: " << s.isMember(8) << " (должен быть 1)" << endl;
    cout << "  элемент 0: " << s.isMember(0) << " (должен быть 0)" << endl;
    
    ok = ok && (s.isMember(2) == 1);
    ok = ok && (s.isMember(4) == 1);
    ok = ok && (s.isMember(6) == 1);
    ok = ok && (s.isMember(8) == 1);
    ok = ok && (s.isMember(0) == 0);
    
    cout << "\nУдаляем элементы 4 и 8..." << endl;
    s.DelElem(4);
    s.DelElem(8);
    
    cout << "После удаления: " << s << endl;
    TBitField bfAfterDel = (TBitField)s;
    printBitField("Битовое поле после удаления", bfAfterDel);
    
    cout << "\nПроверка:" << endl;
    cout << "  элемент 4: " << s.isMember(4) << " (должен быть 0)" << endl;
    cout << "  элемент 8: " << s.isMember(8) << " (должен быть 0)" << endl;
    cout << "  элемент 2: " << s.isMember(2) << " (должен быть 1)" << endl;
    cout << "  элемент 6: " << s.isMember(6) << " (должен быть 1)" << endl;
    
    ok = ok && (s.isMember(4) == 0);
    ok = ok && (s.isMember(8) == 0);
    ok = ok && (s.isMember(2) == 1);
    ok = ok && (s.isMember(6) == 1);
    
    printResult("Добавление и удаление", ok);
}

void testSetOperations() {
    printSeparator();
    cout << "--- Тест операций над множествами ---\n";
    
    TSet A(10), B(10);
    
    // A = {1,3,5,7,9}
    for (int i = 1; i < 10; i += 2) A.InsElem(i);
    // B = {0,2,4,6,8}
    for (int i = 0; i < 10; i += 2) B.InsElem(i);
    
    cout << "A (нечетные): " << A << endl;
    printBitField("Битовое поле A", (TBitField)A);
    
    cout << "\nB (четные): " << B << endl;
    printBitField("Битовое поле B", (TBitField)B);
    
    TSet C = A + B;  // объединение
    TSet D = A * B;  // пересечение
    TSet E = ~A;     // дополнение
    
    cout << "\nA ? B (объединение): " << C << endl;
    printBitField("Битовое поле объединения", (TBitField)C);
    
    cout << "\nA ? B (пересечение): " << D << endl;
    printBitField("Битовое поле пересечения", (TBitField)D);
    
    cout << "\n¬A (дополнение A): " << E << endl;
    printBitField("Битовое поле дополнения", (TBitField)E);
    
    bool ok = true;
    
    // Проверка объединения (должны быть все числа 0-9)
    cout << "\nПроверка объединения (должны быть все 0-9):" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "  элемент " << i << ": " << C.isMember(i) << " (должен быть 1)" << endl;
        if (C.isMember(i) != 1) ok = false;
    }
    
    // Проверка пересечения (должно быть пусто)
    cout << "\nПроверка пересечения (должны быть все 0):" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "  элемент " << i << ": " << D.isMember(i) << " (должен быть 0)" << endl;
        if (D.isMember(i) != 0) ok = false;
    }
    
    printResult("Операции над множествами", ok);
}

void testSetComparison() {
    printSeparator();
    cout << "--- Тест сравнения множеств ---\n";
    
    TSet A(10), B(10), C(10);
    
    A.InsElem(1); A.InsElem(3); A.InsElem(5);
    B.InsElem(1); B.InsElem(3); B.InsElem(5);
    C.InsElem(2); C.InsElem(4); C.InsElem(6);
    
    cout << "A: " << A << endl;
    printBitField("Битовое поле A", (TBitField)A);
    
    cout << "\nB: " << B << endl;
    printBitField("Битовое поле B", (TBitField)B);
    
    cout << "\nC: " << C << endl;
    printBitField("Битовое поле C", (TBitField)C);
    
    cout << "\nA == B: " << (A == B ? "true" : "false") << " (должно быть true)" << endl;
    cout << "A == C: " << (A == C ? "true" : "false") << " (должно быть false)" << endl;
    
    bool ok = (A == B) && !(A == C);
    printResult("Сравнение множеств", ok);
}

void testSetConversion() {
    printSeparator();
    cout << "--- Тест преобразования в битовое поле ---\n";
    
    TSet s(8);
    s.InsElem(1);
    s.InsElem(3);
    s.InsElem(5);
    s.InsElem(7);
    
    cout << "Множество: " << s << endl;
    
    TBitField bf = (TBitField)s;
    printBitField("Битовое поле из множества", bf);
    
    bool ok = true;
    cout << "\nПроверка соответствия:" << endl;
    cout << "  бит 1: " << bf.GetBit(1) << " (должен быть 1)" << endl;
    cout << "  бит 3: " << bf.GetBit(3) << " (должен быть 1)" << endl;
    cout << "  бит 5: " << bf.GetBit(5) << " (должен быть 1)" << endl;
    cout << "  бит 7: " << bf.GetBit(7) << " (должен быть 1)" << endl;
    cout << "  бит 0: " << bf.GetBit(0) << " (должен быть 0)" << endl;
    
    ok = ok && (bf.GetBit(1) == 1);
    ok = ok && (bf.GetBit(3) == 1);
    ok = ok && (bf.GetBit(5) == 1);
    ok = ok && (bf.GetBit(7) == 1);
    ok = ok && (bf.GetBit(0) == 0);
    
    printResult("Преобразование в битовое поле", ok);
}

//------------------------------------------------------------------------------
// ГЛАВНАЯ ФУНКЦИЯ
//------------------------------------------------------------------------------

int main() {
    setlocale(LC_ALL, "Rus");
    int t = 1;
    
    cout << "\n============================================" << endl;
    cout << "      ТЕСТИРОВАНИЕ ПРОГРАММЫ" << endl;
    cout << "============================================\n" << endl;
    
    while(t > 0) {
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
            
            cout << "\n============================================" << endl;
            cout << "       ВСЕ ТЕСТЫ ВЫПОЛНЕНЫ" << endl;
            cout << "============================================\n" << endl;
            
        } catch (const char* msg) {
            cout << "\n НЕПРЕДВИДЕННАЯ ОШИБКА: " << msg << endl;
            return 1;
        } catch (...) {
            cout << "\n НЕИЗВЕСТНАЯ ОШИБКА!" << endl;
            return 1;
        }
        
        cout << "Хотите повторить тесты? (1 - да, 0 - нет): ";
        cin >> t;
    }
    
    cout << "\nТестирование завершено." << endl;
    return 0;
}