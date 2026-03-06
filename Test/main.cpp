#include <iostream>
#include <iomanip>
#include "formula.h"

void printMenu() {
    std::cout << "\n=== ЛАБОРАТОРНАЯ РАБОТА №3 ===" << std::endl;
    std::cout << "Вычисление арифметических выражений (стеки)" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "\nМЕНЮ:" << std::endl;
    std::cout << "1. Проверить расстановку скобок" << std::endl;
    std::cout << "2. Перевести в постфиксную форму" << std::endl;
    std::cout << "3. Вычислить выражение" << std::endl;
    std::cout << "4. Выполнить все операции" << std::endl;
    std::cout << "5. Запустить тесты из задания" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите действие: ";
}

void runTests() {
    std::cout << "\n=== ТЕСТЫ ИЗ ЗАДАНИЯ ===" << std::endl;
    
    // Тест 1 (зачем а почему бы и нет)
    try {
        std::cout << "\nТест 1: 1+2" << std::endl;
        TFormula test1("1+2");
        
        int errors[100];
        int errorCount = 0;
        test1.checkbrackets(errors, errorCount);
        std::cout << "Ошибок: " << errorCount << std::endl;
        
        char* postfix = test1.Postfix();
        std::cout << "Постфиксная форма: " << postfix << std::endl;
        delete[] postfix;
        
        double result = test1.calculate();
        std::cout << "Результат: " << std::fixed << std::setprecision(4) << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
    
    // Тест 2
    try {
        std::cout << "\nТест 2: 1+2*(3-2)-4" << std::endl;
        TFormula test2("1+2*(3-2)-4");
        
        int errors[100];
        int errorCount = 0;
        test2.checkbrackets(errors, errorCount);
        std::cout << "Ошибок: " << errorCount << std::endl;
        
        char* postfix = test2.Postfix();
        std::cout << "Постфиксная форма: " << postfix << std::endl;
        delete[] postfix;
        
        double result = test2.calculate();
        std::cout << "Результат: " << std::fixed << std::setprecision(4) << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
    
    // Тест 3
    try {
        std::cout << "\nТест 3: (((1+23)*1-22)+5)*2-(7" << std::endl;
        TFormula test3("(((1+23)*1-22)+5)*2-(7");
        
        int errors[100];
        int errorCount = 0;
        test3.checkbrackets(errors, errorCount);
        std::cout << "Ошибок: " << errorCount << std::endl;
        
        if (errorCount > 0) {
            std::cout << "Перевод и вычисление невозможны" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
    
    // Тест 4
    try {
        std::cout << "\nТест 4: 1+2/(3-3)" << std::endl;
        TFormula test4("1+2/(3-3)");
        
        int errors[100];
        int errorCount = 0;
        test4.checkbrackets(errors, errorCount);
        std::cout << "Ошибок: " << errorCount << std::endl;
        
        char* postfix = test4.Postfix();
        std::cout << "Постфиксная форма: " << postfix << std::endl;
        delete[] postfix;
        
        double result = test4.calculate();
        std::cout << "Результат: " << std::fixed << std::setprecision(4) << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
    
    // Тест 5
    try {
        std::cout << "\nТест 5: 1++1" << std::endl;
        TFormula test5("1++1");
        
        int errors[100];
        int errorCount = 0;
        test5.checkbrackets(errors, errorCount);
        std::cout << "Ошибок: " << errorCount << std::endl;
        
        char* postfix = test5.Postfix();
        std::cout << "Постфиксная форма: " << postfix << std::endl;
        delete[] postfix;
        
        double result = test5.calculate();
        std::cout << "Результат: " << std::fixed << std::setprecision(4) << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

int main() {
    int choice;
    TFormula formula;
    
    do {
        printMenu();
        std::cin >> choice;
        std::cin.ignore(); // Очистка буфера
        
        if (choice == 0) {
            break;
        }
        
        if (choice >= 1 && choice <= 4) {
            std::cout << "\nВведите арифметическое выражение: ";
            std::cin >> formula;
            
            try {
                if (choice == 1 || choice == 4) {
                    int errors[100];
                    int errorCount = 0;
                    formula.checkbrackets(errors, errorCount);
                }
                
                if (choice == 2 || choice == 4) {
                    char* postfix = formula.Postfix();
                    std::cout << "Постфиксная форма: " << postfix << std::endl;
                    delete[] postfix;
                }
                
                if (choice == 3 || choice == 4) {
                    double result = formula.calculate();
                    std::cout << "Результат: " << std::fixed << std::setprecision(4) << result << std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cout << "Ошибка: " << e.what() << std::endl;
            }
        }
        else if (choice == 5) {
            runTests();
        }
        else {
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }
        
        std::cout << "\nНажмите Enter для продолжения...";
        std::cin.get();
        
    } while (choice != 0);
    
    std::cout << "Программа завершена." << std::endl;
    return 0;
}