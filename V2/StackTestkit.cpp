#include <iostream>
#include <iomanip>
#include "TFormula.h"

void printMenu() {
    std::cout << "\n=== Лабораторная работа №3 ===" << std::endl;
    std::cout << "Вычисление арифметических выражений (стеки)" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "\nМеню:" << std::endl;
    std::cout << "1. Проверить расстановку скобок" << std::endl;
    std::cout << "2. Преобразовать в постфиксную форму" << std::endl;
    std::cout << "3. Вычислить выражение" << std::endl;
    std::cout << "4. Выполнить все операции" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите действие: ";
}


int main() {
    setlocale(LC_ALL, "RUS");
    int choice;
    TFormula formula;
    
    do {
        printMenu();
        std::cin >> choice;
        std::cin.ignore(); // Clear buffer
        
        if (choice == 0) {
            break;
        }
        
        if (choice >= 1 && choice <= 4) {
            std::cout << "\nВведите арифметическое выражение: ";
            std::cin >> formula;
            
            try {
                if (choice == 1 ) {
                    int errors[100];
                    int errorCount = 0;
                    formula.checkbrackets(errors, errorCount);
                    std::cout << "Найдено ошибок: " << errorCount << std::endl;
                }
                
                else if (choice == 2 ) {
                    char* postfix = formula.Postfix();
                    std::cout << "Постфиксная форма: " << postfix << std::endl;
                    delete[] postfix;
                }
                
                else if (choice == 3 ) {
                    int r = 0;
                    double result = formula.calculate(r);
                    std::cout << "Результат: " << std::fixed << std::setprecision(4) << result << std::endl;
                }
                else if(choice == 4){
                    int errors[100];
                    int errorCount = 0;
                    formula.checkbrackets(errors, errorCount);
                    std::cout << "Найдено ошибок: " << errorCount << std::endl;
                    char* postfix = formula.Postfix();
                    std::cout << "Постфиксная форма: " << postfix << std::endl;
                    delete[] postfix;
                    int r = 0;
                    double result = formula.calculate(r);
                    std::cout << "Результат: " << std::fixed << std::setprecision(4) << result << std::endl;

                }
            }
            catch (int expt) {
                switch (expt) {
                    case 1:
                        std::cout << "Ошибка: Неправильная расстановка скобок" << std::endl;
                        break;
                    case 2:
                        std::cout << "Ошибка: Неправильное использование десятичной точки" << std::endl;
                        break;
                    case 3:
                        std::cout << "Ошибка: Нет цифр в числе!" << std::endl;
                        break;
                    case 4:
                        std::cout << "Ошибка: Неизвестный символ в выражении" << std::endl;
                        break;
                    case 5:
                        std::cout << "Ошибка: Переполнение памяти" << std::endl;
                        break;
                    case 6:
                        std::cout << "Ошибка: Два оператора подряд" << std::endl;
                        break;
                    case 7:
                        std::cout << "Ошибка: Деление на ноль" << std::endl;
                        break;
                    case 8:
                        std::cout << "Ошибка: Отсутвует оперант" << std::endl;
                        break;    
                    default:
                        std::cout << "Неизвестная ошибка с кодом: " << expt << std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cout << "Ошибка: " << e.what() << std::endl;
            }
        
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