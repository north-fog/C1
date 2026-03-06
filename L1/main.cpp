#include <iostream>
#include "Tbitfield.h"
#include "Tset.h"

int main() {
    setlocale(LC_ALL, "RUS");

    // Создаем два битовых поля разной длины
    TBitField lamps(8);    // 8 бит
    TBitField vvoju(4);    // 4 бита
    
    // Тестирование ввода битового поля
    std::cout << "Вводим: ";
    std::cin >> vvoju;
    
    // Вывод текущего состояния
    std::cout << "vvoju: " << vvoju << std::endl 
              << "lamps: " << lamps << std::endl 
              << "Включили первые две" << std::endl;
    
    // Устанавливаем биты (включаем "лампочки")
    lamps.SetBit(0);  // Устанавливаем бит 0
    lamps.SetBit(1);  // Устанавливаем бит 1
    vvoju.SetBit(0);
    vvoju.SetBit(1);
    
    std::cout << "vvoju: " << vvoju << std::endl 
              << "lamps: " << lamps << std::endl 
              << "Выключили вторую" << std::endl;
    
    // Сбрасываем биты (выключаем "лампочки")
    lamps.ClearBit(1);  // Сбрасываем бит 1
    vvoju.ClearBit(1);
    
    // Проверяем состояние конкретного бита
    int index = 4;
    std::cout << "Лампочка по индексу " << index << ": ";
    
    if (lamps.GetBit(index)) {
        std::cout << "у lamps включена    ";
    }
    else {
        std::cout << "у lamps выключена    ";
    }
    
    if (vvoju.GetBit(index)) {
        std::cout << "у vvoju включена" << std::endl;
    }
    else {
        std::cout << "у vvoju выключена" << std::endl;
    }
    
    // Сравнение битовых полей
    std::cout << "vvoju: " << vvoju << std::endl 
              << "lamps: " << lamps << std::endl 
              << "Оператор сравнения{vvoju==lamps}:" << std::endl 
              << "Получили: ";
    
    if (lamps == vvoju) {
        std::cout << "lamps и vvoju равны";
    }
    else {
        std::cout << "lamps и vvoju не равны";
    }
    
    // Тестирование битовых операций
    TBitField example(1);
    std::cout << std::endl << "vvoju: " << vvoju << std::endl 
              << "lamps: " << lamps << std::endl 
              << "Оператор логическоеИ: ";
    
    example = lamps & vvoju;  // Побитовое И
    std::cout << example << std::endl;
    
    std::cout << "Оператор логическоеИЛИ: ";
    example = lamps | vvoju;  // Побитовое ИЛИ
    std::cout << example;
    
    // Тестирование оператора присваивания
    std::cout << std::endl << "vvoju: " << vvoju << std::endl 
              << "lamps: " << lamps << std::endl 
              << "Оператор присваивания{vvoju = lamps}    " 
              << "vvoju: ";
    
    vvoju = lamps;  // Присваивание
    std::cout << vvoju << std::endl;
    
    // Тестирование TSet (множества)
    std::cout << "Теперь множества" << std::endl;
    
    TSet mnoj(10);    // Множество с универсумом 0-9
    TSet vveli(5);    // Множество с универсумом 0-4
    
    // Тестирование ввода множества
    std::cout << "Введите элементы множества vveli (0-4):" << std::endl;
    std::cin >> vveli;
    
    // Для более полного тестирования можно добавить:
    
    // 1. Проверку операций над множествами
    TSet result = mnoj + vveli;  // Объединение
    std::cout << "Объединение mnoj + vveli: " << result << std::endl;
    
    // 2. Проверку принадлежности элемента
    int element = 3;
    if (vveli.isMember(element)) {
        std::cout << "Элемент " << element << " принадлежит vveli" << std::endl;
    }
    
    // 3. Проверку оператора преобразования
    TBitField bf_from_set = vveli;  // Преобразование TSet в TBitField
    std::cout << "Битовое поле из vveli: " << bf_from_set << std::endl;
    
    return 0;
}