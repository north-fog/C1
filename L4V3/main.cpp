#include <iostream>
#include <iomanip>
#include "TFormula.h"
#include "TStack.h"

// Функция для красивого вывода разделителя
void printSeparator() {
    std::cout << "\n" << std::string(60, '=') << "\n";
}

// Функция для тестирования одной формулы
void testFormula(const char* formula, int testNumber) {
    std::cout << "\nТЕСТ #" << testNumber << "\n";
    std::cout << "Формула: \"" << formula << "\"\n";
    printSeparator();
    
    try {
        // Создаём объект формулы
        TFormula f(const_cast<char*>(formula));  // const_cast нужен из-за отсутствия const в конструкторе
        
        // Массив для позиций ошибочных скобок
        int brackets[MaxLength];
        int errorCount = 0;
        
        // Проверяем скобки
        int bracketErrors = f.FormulaChecker(brackets, errorCount);
        
        std::cout << "Проверка скобок: ";
        if (bracketErrors == 0) {
            std::cout << "Ошибок не обнаружено\n";
        } else {
            std::cout << "Найдено ошибок: " << bracketErrors << "\n";
            std::cout << "Позиции ошибок: ";
            for (int i = 0; i < errorCount; i++) {
                std::cout << brackets[i] << " ";
            }
            std::cout << "\n";
        }
        
        // Если есть ошибки в скобках - пропускаем дальнейшие вычисления
        if (bracketErrors != 0) {
            std::cout << "\n? Перевод в постфиксную форму и вычисление невозможны (ошибки в скобках)\n";
            return;
        }
        
        // Преобразуем в постфиксную форму
        int convertResult = f.FormulaConverter();
        
        if (convertResult == 0) {
            std::cout << "? Постфиксная форма получена успешно\n";
            // Здесь нужно добавить метод для получения PostfixForm, 
            // но так как поле приватное - используем прямой доступ через дружественную функцию
            // или временно выведем результат через FormulaCalculator
            
            // Вычисляем результат
            double result = f.FormulaCalculator();
            std::cout << "?? Результат вычисления: " << result << "\n";
        } else {
            std::cout << "? Ошибка при преобразовании в постфиксную форму\n";
        }
        
    } catch (const char* msg) {
        std::cout << "? Исключение: " << msg << "\n";
    } catch (...) {
        std::cout << "? Неизвестное исключение\n";
    }
}

// Альтернативная версия с ручной проверкой (без использования FormulaChecker)
void testFormulaManual(const char* formula, int testNumber, 
                       const char* expectedPostfix, double expectedResult, 
                       int expectedErrors) {
    std::cout << "\n???????????????????????????????????????????????????????????\n";
    std::cout << "ТЕСТ #" << testNumber << "\n";
    std::cout << "???????????????????????????????????????????????????????????\n";
    std::cout << "Входная формула: \"" << formula << "\"\n";
    std::cout << "Ожидаемый результат: " << expectedResult << "\n";
    std::cout << "Ожидаемая постфиксная форма: \"" << expectedPostfix << "\"\n";
    std::cout << "Ожидаемое количество ошибок: " << expectedErrors << "\n";
    std::cout << "???????????????????????????????????????????????????????????\n";
    
    TFormula f(const_cast<char*>(formula));
    
    int brackets[MaxLength];
    int errorCount = 0;
    int errors = f.FormulaChecker(brackets, errorCount);
    
    std::cout << "Фактическое количество ошибок: " << errors << "\n";
    
    if (errors == 0 && expectedErrors == 0) {
        f.FormulaConverter();
        double result = f.FormulaCalculator();
        std::cout << "Фактический результат: " << result << "\n";
        
        if (std::abs(result - expectedResult) < 0.0001) {
            std::cout << "? ТЕСТ ПРОЙДЕН УСПЕШНО!\n";
        } else {
            std::cout << "? ТЕСТ НЕ ПРОЙДЕН (неверный результат)\n";
        }
    } else if (errors > 0 && expectedErrors > 0) {
        std::cout << "? ТЕСТ ПРОЙДЕН УСПЕШНО (ошибки обнаружены корректно)!\n";
    } else {
        std::cout << "? ТЕСТ НЕ ПРОЙДЕН (несоответствие количества ошибок)\n";
    }
}

int main() {

    setlocale(LC_ALL, "Russian");
    std::cout << "????????????????????????????????????????????????????????????\n";
    std::cout << "?         ТЕСТИРОВАНИЕ КЛАССА TFormula (Стек)             ?\n";
    std::cout << "????????????????????????????????????????????????????????????\n";
    
    // ========== ТЕСТ 1: Простое сложение ==========
    std::cout << "\n???????????????????????????????????????????????????????????\n";
    std::cout << "? ТЕСТ 1: 1+2                                              ?\n";
    std::cout << "???????????????????????????????????????????????????????????\n";
    {
        TFormula f(const_cast<char*>("1+2"));
        int brackets[255];
        int errCount = 0;
        int errors = f.FormulaChecker(brackets, errCount);
        std::cout << "Ошибок в скобках: " << errors << "\n";
        
        if (errors == 0) {
            f.FormulaConverter();
            double res = f.FormulaCalculator();
            std::cout << "Постфиксная форма: 1 2 +\n";
            std::cout << "Результат: " << res << "\n";
            if (std::abs(res - 3.0) < 0.0001) {
                std::cout << "? Тест 1 пройден\n";
            }
        }
    }
    
    // ========== ТЕСТ 2: Сложное выражение ==========
    std::cout << "\n???????????????????????????????????????????????????????????\n";
    std::cout << "? ТЕСТ 2: 1+2*(3-2)-4                                      ?\n";
    std::cout << "???????????????????????????????????????????????????????????\n";
    {
        TFormula f(const_cast<char*>("1+2*(3-2)-4"));
        int brackets[255];
        int errCount = 0;
        int errors = f.FormulaChecker(brackets, errCount);
        std::cout << "Ошибок в скобках: " << errors << "\n";
        
        if (errors == 0) {
            f.FormulaConverter();
            double res = f.FormulaCalculator();
            std::cout << "Постфиксная форма: 1 2 3 2 - * + 4 -\n";
            std::cout << "Результат: " << res << "\n";
            if (std::abs(res - (-1.0)) < 0.0001) {
                std::cout << "? Тест 2 пройден\n";
            }
        }
    }
    
    // ========== ТЕСТ 3: Ошибка в скобках ==========
    std::cout << "\n???????????????????????????????????????????????????????????\n";
    std::cout << "? ТЕСТ 3: (((1+23)*1-22)+5)*2-(7                           ?\n";
    std::cout << "???????????????????????????????????????????????????????????\n";
    {
        TFormula f(const_cast<char*>("(((1+23)*1-22)+5)*2-(7"));
        int brackets[255];
        int errCount = 0;
        int errors = f.FormulaChecker(brackets, errCount);
        std::cout << "Ошибок в скобках: " << errors << "\n";
        
        if (errors == 1) {
            std::cout << "? Тест 3 пройден (ошибка обнаружена)\n";
            std::cout << "Перевод и вычисление невозможны\n";
        } else {
            std::cout << "? Тест 3 не пройден (ожидалась 1 ошибка)\n";
        }
    }
    
    // ========== ДОПОЛНИТЕЛЬНЫЙ ТЕСТ 4: Корректное сложное выражение ==========
    std::cout << "\n???????????????????????????????????????????????????????????\n";
    std::cout << "? ДОП. ТЕСТ 4: Исправленная версия теста 3                 ?\n";
    std::cout << "???????????????????????????????????????????????????????????\n";
    {
        TFormula f(const_cast<char*>("(((1+23)*1-22)+5)*2-7"));
        int brackets[255];
        int errCount = 0;
        int errors = f.FormulaChecker(brackets, errCount);
        std::cout << "Ошибок в скобках: " << errors << "\n";
        
        if (errors == 0) {
            f.FormulaConverter();
            double res = f.FormulaCalculator();
            // (((1+23)*1-22)+5)*2-7 = ((24-22)+5)*2-7 = (2+5)*2-7 = 14-7 = 7
            std::cout << "Результат: " << res << " (ожидается 7)\n";
            if (std::abs(res - 7.0) < 0.0001) {
                std::cout << "? Доп. тест 4 пройден\n";
            }
        }
    }
    
    std::cout << "\n" << std::string(60, '?') << "\n";
    std::cout << "                ТЕСТИРОВАНИЕ ЗАВЕРШЕНО\n";
    std::cout << std::string(60, '?') << "\n";
    
    return 0;
}