#include <iostream>
#include <cstdlib>
#include <ctime>
#include "TQueue.h"

using namespace std;

// Функция для вывода состояния очереди
void PrintQueueStatus(TQueue& q, const char* name) {
    cout << name << ": ";
    
    // Временно создаем копию очереди для вывода
    TQueue temp(q);
    
    if (temp.IsEmpty()) {
        cout << "пусто" << endl;
        return;
    }
    
    cout << "[";
    while (!temp.IsEmpty()) {
        cout << " " << temp.Get();
    }
    cout << " ]" << endl;
}

// Функция для вывода детальной информации об очереди
void PrintQueueInfo(TQueue& q, const char* name) {
    cout << "\n--- Информация об очереди " << name << " ---" << endl;
    cout << "Количество элементов: " << q.GetDataCount() << endl;
    cout << "Пуста? " << (q.IsEmpty() ? "да" : "нет") << endl;
    cout << "Полна? " << (q.IsFull() ? "да" : "нет") << endl;
    PrintQueueStatus(q, "Содержимое");
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));
    
    cout << "============================================" << endl;
    cout << "   ТЕСТИРОВАНИЕ ОЧЕРЕДИ (КОЛЬЦЕВОЙ БУФЕР)" << endl;
    cout << "============================================" << endl;
    
    // ========== ТЕСТ 1: Создание очереди ==========
    cout << "\n========== ТЕСТ 1: Создание очереди ==========" << endl;
    TQueue q1(5);
    PrintQueueInfo(q1, "q1");
    
    // ========== ТЕСТ 2: Добавление элементов ==========
    cout << "\n========== ТЕСТ 2: Добавление элементов (Put) ==========" << endl;
    cout << "Добавляем элементы: 10, 20, 30, 40, 50" << endl;
    q1.Put(10);
    q1.Put(20);
    q1.Put(30);
    q1.Put(40);
    q1.Put(50);
    PrintQueueInfo(q1, "q1");
    
    // ========== ТЕСТ 3: Проверка на переполнение ==========
    cout << "\n========== ТЕСТ 3: Попытка добавить в полную очередь ==========" << endl;
    cout << "Пытаемся добавить 60..." << endl;
    q1.Put(60);  // Должна быть ошибка
    PrintQueueInfo(q1, "q1");
    
    // ========== ТЕСТ 4: Извлечение элементов ==========
    cout << "\n========== ТЕСТ 4: Извлечение элементов (Get) ==========" << endl;
    cout << "Извлекаем элементы:" << endl;
    while (!q1.IsEmpty()) {
        cout << "  Get() = " << q1.Get() << endl;
    }
    PrintQueueInfo(q1, "q1");
    
    // ========== ТЕСТ 5: Попытка извлечь из пустой очереди ==========
    cout << "\n========== ТЕСТ 5: Попытка извлечь из пустой очереди ==========" << endl;
    cout << "Пытаемся извлечь элемент..." << endl;
    TElem val = q1.Get();  // Должна быть ошибка
    cout << "Извлечено: " << val << endl;
    
    // ========== ТЕСТ 6: Кольцевой буфер ==========
    cout << "\n========== ТЕСТ 6: Проверка кольцевого буфера ==========" << endl;
    TQueue q2(3);
    cout << "Создана очередь на 3 элемента" << endl;
    
    cout << "Добавляем 10, 20, 30:" << endl;
    q2.Put(10);
    q2.Put(20);
    q2.Put(30);
    PrintQueueStatus(q2, "q2");
    
    cout << "Извлекаем элемент: " << q2.Get() << endl;
    PrintQueueStatus(q2, "q2");
    
    cout << "Добавляем 40:" << endl;
    q2.Put(40);
    PrintQueueStatus(q2, "q2");
    
    cout << "Добавляем 50:" << endl;
    q2.Put(50);
    PrintQueueStatus(q2, "q2");
    
    cout << "Извлекаем все элементы:" << endl;
    while (!q2.IsEmpty()) {
        cout << "  Get() = " << q2.Get() << endl;
    }
    
    // ========== ТЕСТ 7: Конструктор копирования ==========
    cout << "\n========== ТЕСТ 7: Конструктор копирования ==========" << endl;
    TQueue q3(4);
    q3.Put(100);
    q3.Put(200);
    q3.Put(300);
    PrintQueueStatus(q3, "q3");
    
    TQueue q4(q3);
    PrintQueueStatus(q4, "q4 (копия q3)");
    
    cout << "Извлекаем из q3: " << q3.Get() << endl;
    PrintQueueStatus(q3, "q3 после извлечения");
    PrintQueueStatus(q4, "q4 (копия)");
    
    // ========== ТЕСТ 8: Оператор присваивания ==========
    cout << "\n========== ТЕСТ 8: Оператор присваивания ==========" << endl;
    TQueue q5(2);
    q5.Put(1);
    q5.Put(2);
    PrintQueueStatus(q5, "q5");
    
    TQueue q6(4);
    q6 = q5;
    PrintQueueStatus(q6, "q6 = q5");
    
    // ========== ТЕСТ 9: Случайные операции ==========
    cout << "\n========== ТЕСТ 9: Случайные операции ==========" << endl;
    TQueue q7(5);
    int operations = 15;
    
    cout << "Выполняем " << operations << " случайных операций (Put/Get):" << endl;
    for (int i = 0; i < operations; i++) {
        int op = rand() % 2;
        if (op == 0) {
            // Put
            int val = rand() % 100;
            if (!q7.IsFull()) {
                q7.Put(val);
                cout << "  Put(" << val << ") ? OK" << endl;
            } else {
                cout << "  Put(" << val << ") ? очередь полна, пропущено" << endl;
            }
        } else {
            // Get
            if (!q7.IsEmpty()) {
                cout << "  Get() = " << q7.Get() << " ? OK" << endl;
            } else {
                cout << "  Get() ? очередь пуста, пропущено" << endl;
            }
        }
        PrintQueueStatus(q7, "     Состояние");
    }
    
    // ========== ТЕСТ 10: Большая очередь ==========
    cout << "\n========== ТЕСТ 10: Работа с большой очередью ==========" << endl;
    TQueue q8(10);
    cout << "Добавляем 20 элементов с переполнением:" << endl;
    for (int i = 1; i <= 20; i++) {
        if (!q8.IsFull()) {
            q8.Put(i * 10);
            cout << "  Put(" << i * 10 << ") ? OK, элементов: " << q8.GetDataCount() << endl;
        } else {
            cout << "  Put(" << i * 10 << ") ? очередь полна, элемент потерян" << endl;
        }
    }
    PrintQueueStatus(q8, "Итоговая очередь");
    
    cout << "\n============================================" << endl;
    cout << "   ТЕСТИРОВАНИЕ ЗАВЕРШЕНО" << endl;
    cout << "============================================" << endl;
    
    return 0;
}