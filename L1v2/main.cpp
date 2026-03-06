#include <iostream>
#include <string>
#include <sstream>
#include "TBitField.h"

void menu() {
    std::cout << "1. Установить бит с заданным номером." << "\n"
        << "2. Очистить бит с заданным номером." << "\n"
        << "3. Узнать состояние бита с заданным номером." << "\n"
        << "4. Присвоить одному битовому полю другое." << "\n"
        << "5. Сравнить два битовых поля между собой на равенство." << "\n"
        << "6. Протестировать оператор & ('И')." << "\n"
        << "7. Протестировать оператор | ('ИЛИ')." << "\n"
        << "8. Протестировать оператор ~ ('Отрицание')." << "\n"
        << "9. Выход." << "\n";
}

int main() {
    setlocale(LC_ALL, "Rus");
    
    std::string input;
    int len1, len2;
    
    // Ввод первого поля
    do {
        std::cout << "Введите длину желаемого битового поля №1: ";
        std::getline(std::cin, input);
        std::stringstream ss(input);
        ss >> len1;
        if (len1 <= 0) {
            std::cout << "Ошибка: длина должна быть положительным числом!" << std::endl;
        }
    } while (len1 <= 0);
    
    TBitField t1(len1);
    std::cout << "Пустое битовое поле: " << t1 << std::endl;
    
    std::cout << "Введите биты (только 0 и 1, например: 101010): ";
    std::cin >> t1; 
    
    std::cout << "Результат (Битовое поле № 1): " << t1 << std::endl;
    
    // Ввод второго поля
    do {
        std::cout << "Введите длину желаемого битового поля №2: ";
        std::getline(std::cin, input);
        std::stringstream ss(input);
        ss >> len2;
        if (len2 <= 0) {
            std::cout << "Ошибка: длина должна быть положительным числом!" << std::endl;
        }
    } while (len2 <= 0);
    
    TBitField t2(len2);
    
    std::cout << "Введите биты (только 0 и 1, например: 101010): ";
    std::cin >> t2;
    
    std::cout << "Результат (Битовое поле № 2): " << t2 << std::endl;
    
    int flag, n, count;
    int flagg = 1;
    
    do {
        if (flagg == 1) {
            menu();
            
            // Ввод пункта меню
            do {
                std::cout << "Введите номер желаемого пункта из меню: " << "\n";
                std::getline(std::cin, input);
                std::stringstream ss(input);
                ss >> flag;
                if (flag < 1 || flag > 9) {
                    std::cout << "Ошибка: введите число от 1 до 9!" << std::endl;
                }
            } while ((flag < 1) || (flag > 9));
            
            switch (flag) {
            case 1:
                std::cout << "Введите номер бита, который вы хотите установить: " << "\n";
                std::getline(std::cin, input);
                std::stringstream(input) >> n;
                
                do {
                    std::cout << "Введите номер битового поля (1 или 2): " << "\n";
                    std::getline(std::cin, input);
                    std::stringstream(input) >> count;
                } while ((count < 1) || (count > 2));
                
                if (count == 1) {
                    if (n >= 0 && n < t1.GetLen()) {
                        t1.SetBit(n);
                        std::cout << "Результат: " << t1 << std::endl;
                    } else {
                        std::cout << "Ошибка: бит " << n << " вне диапазона (0-" << t1.GetLen()-1 << ")" << std::endl;
                    }
                }
                else {
                    if (n >= 0 && n < t2.GetLen()) {
                        t2.SetBit(n);
                        std::cout << "Результат: " << t2 << std::endl;
                    } else {
                        std::cout << "Ошибка: бит " << n << " вне диапазона (0-" << t2.GetLen()-1 << ")" << std::endl;
                    }
                }
                break;
                
            case 2:
                std::cout << "Введите номер бита, который вы хотите очистить: " << "\n";
                std::getline(std::cin, input);
                std::stringstream(input) >> n;
                
                do {
                    std::cout << "Введите номер битового поля (1 или 2): " << "\n";
                    std::getline(std::cin, input);
                    std::stringstream(input) >> count;
                } while ((count < 1) || (count > 2));
                
                if (count == 1) {
                    if (n >= 0 && n < t1.GetLen()) {
                        t1.ClrBit(n);
                        std::cout << "Результат: " << t1 << std::endl;
                    } else {
                        std::cout << "Ошибка: бит " << n << " вне диапазона (0-" << t1.GetLen()-1 << ")" << std::endl;
                    }
                }
                else {
                    if (n >= 0 && n < t2.GetLen()) {
                        t2.ClrBit(n);
                        std::cout << "Результат: " << t2 << std::endl;
                    } else {
                        std::cout << "Ошибка: бит " << n << " вне диапазона (0-" << t2.GetLen()-1 << ")" << std::endl;
                    }
                }
                break;
                
            case 3:
                std::cout << "Введите номер бита, состояние которого Вы хотите узнать: " << "\n";
                std::getline(std::cin, input);
                std::stringstream(input) >> n;
                
                do {
                    std::cout << "Введите номер битового поля (1 или 2): " << "\n";
                    std::getline(std::cin, input);
                    std::stringstream(input) >> count;
                } while ((count < 1) || (count > 2));
                
                if (count == 1) {
                    if (n >= 0 && n < t1.GetLen()) {
                        std::cout << "Бит " << n << " = " << t1.GetBit(n) << std::endl;
                    } else {
                        std::cout << "Ошибка: бит вне диапазона" << std::endl;
                    }
                }
                else {
                    if (n >= 0 && n < t2.GetLen()) {
                        std::cout << "Бит " << n << " = " << t2.GetBit(n) << std::endl;
                    } else {
                        std::cout << "Ошибка: бит вне диапазона" << std::endl;
                    }
                }
                break;
                
            case 4:
                do {
                    std::cout << "Введите номер битового поля, которому присвоить другое (1 или 2): " << "\n";
                    std::getline(std::cin, input);
                    std::stringstream(input) >> count;
                } while ((count < 1) || (count > 2));
                
                if (count == 1) {
                    t1 = t2;
                    std::cout << "Результат (поле №1 = поле №2): " << t1 << std::endl;
                }
                else {
                    t2 = t1;
                    std::cout << "Результат (поле №2 = поле №1): " << t2 << std::endl;
                }
                break;
                
            case 5:
                if (t1 == t2) {
                    std::cout << "Результат: битовые поля равны!" << "\n";
                }
                else {
                    std::cout << "Результат: битовые поля отличаются!" << "\n";
                }
                break;
                
            case 6:
                std::cout << "Результат И: " << (t1 & t2) << "\n";
                break;
                
            case 7:
                std::cout << "Результат ИЛИ: " << (t1 | t2) << "\n";
                break;
                
            case 8:
                do {
                    std::cout << "Введите номер битового поля для отрицания (1 или 2): " << "\n";
                    std::getline(std::cin, input);
                    std::stringstream(input) >> count;
                } while ((count < 1) || (count > 2));
                
                if (count == 1) {
                    std::cout << "Результат ~: " << (~t1) << "\n";
                }
                else {
                    std::cout << "Результат ~: " << (~t2) << "\n";
                }
                break;
                
            case 9:
                std::cout << "До свидания!" << "\n";
                flagg = 0;
                break;
            }
        }
    } while (flagg == 1);
    
    return 0;
}