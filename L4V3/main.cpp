#include <iostream>
#include <iomanip>
#include <cmath>
#include "TFormula.h"
#include "TStack.h"

using namespace std;

void printSeparator() {
    cout << "\n" << string(60, '=') << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "========================================\n";
    cout << "    ТЕСТИРОВАНИЕ КЛАССА TFormula\n";
    cout << "========================================\n";
    
    // ========== ТЕСТ 1: Простое сложение ==========
    cout << "\n========== ТЕСТ 1: 1+2 ==========\n";
    {
        TFormula f(const_cast<char*>("1+2"));
        int brackets[255];
        int errCount = 0;
        int errors = f.FormulaChecker(brackets, errCount);
        cout << "Ошибок в скобках: " << errors << "\n";
        
        if (errors == 0) {
            f.FormulaConverter();
            double res = f.FormulaCalculator();
            cout << "Результат: " << res << "\n";
            if (fabs(res - 3.0) < 0.0001) {
                cout << "--> Тест 1 пройден\n";
            } else {
                cout << "--> Тест 1 не пройден (результат " << res << " != 3)\n";
            }
        } else {
            cout << "--> Тест 1 не пройден (ошибки в скобках)\n";
        }
    }
    
    // ========== ТЕСТ 2: Сложное выражение ==========
    cout << "\n========== ТЕСТ 2: 1+2*(3-2)-4 ==========\n";
    {
        TFormula f(const_cast<char*>("1+2*(3-2)-4"));
        int brackets[255];
        int errCount = 0;
        int errors = f.FormulaChecker(brackets, errCount);
        cout << "Ошибок в скобках: " << errors << "\n";
        
        if (errors == 0) {
            f.FormulaConverter();
            double res = f.FormulaCalculator();
            cout << "Результат: " << res << "\n";
            if (fabs(res - (-1.0)) < 0.0001) {
                cout << "--> Тест 2 пройден\n";
            } else {
                cout << "--> Тест 2 не пройден (результат " << res << " != -1)\n";
            }
        } else {
            cout << "--> Тест 2 не пройден (ошибки в скобках)\n";
        }
    }
    
    // ========== ТЕСТ 3: Ошибка в скобках ==========
    cout << "\n========== ТЕСТ 3: (((1+23)*1-22)+5)*2-(7 ==========\n";
    {
        TFormula f(const_cast<char*>("(((1+23)*1-22)+5)*2-(7"));
        int brackets[255];
        int errCount = 0;
        int errors = f.FormulaChecker(brackets, errCount);
        cout << "Ошибок в скобках: " << errors << "\n";
        
        if (errors == 1) {
            cout << "--> Тест 3 пройден (ошибка обнаружена)\n";
        } else {
            cout << "--> Тест 3 не пройден (ожидалась 1 ошибка, получено " << errors << ")\n";
        }
    }
    
    // ========== ТЕСТ 4: Корректное выражение со скобками ==========
    cout << "\n========== ТЕСТ 4: (((1+23)*1-22)+5)*2-7 ==========\n";
    {
        TFormula f(const_cast<char*>("(((1+23)*1-22)+5)*2-7"));
        int brackets[255];
        int errCount = 0;
        int errors = f.FormulaChecker(brackets, errCount);
        cout << "Ошибок в скобках: " << errors << "\n";
        
        if (errors == 0) {
            f.FormulaConverter();
            double res = f.FormulaCalculator();
            cout << "Результат: " << res << " (ожидается 7)\n";
            if (fabs(res - 7.0) < 0.0001) {
                cout << "--> Тест 4 пройден\n";
            } else {
                cout << "--> Тест 4 не пройден (результат " << res << " != 7)\n";
            }
        } else {
            cout << "--> Тест 4 не пройден (ошибки в скобках)\n";
        }
    }
    
    // ========== ТЕСТ 5: Деление на ноль ==========
    cout << "\n========== ТЕСТ 5: 1+2/(3-3) ==========\n";
    {
        TFormula f(const_cast<char*>("1+2/(3-3)"));
        int brackets[255];
        int errCount = 0;
        int errors = f.FormulaChecker(brackets, errCount);
        cout << "Ошибок в скобках: " << errors << "\n";
        
        if (errors == 0) {
            f.FormulaConverter();
            double res = f.FormulaCalculator();
            if (std::isinf(res) || std::isnan(res)) {
                cout << "Результат: бесконечность/не число\n";
                cout << "--> Тест 5 пройден (деление на ноль)\n";
            } else {
                cout << "Результат: " << res << "\n";
                cout << "--> Тест 5 не пройден (деление на ноль не обнаружено)\n";
            }
        }
    }
    
    // ========== ТЕСТ 6: Два оператора подряд ==========
    cout << "\n========== ТЕСТ 6: 1++1 ==========\n";
    {
        TFormula f(const_cast<char*>("1++1"));
        int brackets[255];
        int errCount = 0;
        int errors = f.FormulaChecker(brackets, errCount);
        cout << "Ошибок в скобках: " << errors << "\n";
        
        if (errors == 0) {
            f.FormulaConverter();
            double res = f.FormulaCalculator();
            cout << "Результат: " << res << "\n";
            cout << "--> Тест 6 завершён (проверьте корректность)\n";
        }
    }
    
    // ========== ТЕСТ 7: Проверка со скобками из методички ==========
    cout << "\n========== ТЕСТ 7: (a+b1)/2+6.5)*(4.8+sin(x) ==========\n";
    {
        TFormula f(const_cast<char*>("(a+b1)/2+6.5)*(4.8+sin(x)"));
        int brackets[255];
        int errCount = 0;
        int errors = f.FormulaChecker(brackets, errCount);
        cout << "Ошибок в скобках: " << errors << "\n";
        
        if (errors == 2) {
            cout << "--> Тест 7 пройден (обнаружено 2 ошибки в скобках)\n";
        } else {
            cout << "--> Тест 7 не пройден (ожидалось 2 ошибки, получено " << errors << ")\n";
        }
    }
    
    cout << "\n========================================\n";
    cout << "            ТЕСТИРОВАНИЕ ЗАВЕРШЕНО\n";
    cout << "========================================\n";
    
    return 0;
}