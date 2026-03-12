#include <iostream>
#include <limits>
#include "TBitField.h"
#include "TSet.h"

void menu() {
    std::cout << "1.  Добавить элемент в множество." << "\n"
        << "2.  Удалить элемент из множества." << "\n"
        << "3.  Проверить наличие элемента в множестве." << "\n"
        << "4.  Присвоить одному множеству другое." << "\n"
        << "5.  Сравнить два множества между собой на равенство." << "\n"
        << "6.  Протестировать оператор объединения." << "\n"
        << "7.  Протестировать оператор пересечения." << "\n"
        << "8.  Протестировать оператор дополнения ('Отрицание')." << "\n"
        << "9.  Протестировать оператор прибавления."<< "\n"
        << "10. Протестировать оператор вычитания."<< "\n"
        << "11. Выход." << "\n";
}

int main() {
    setlocale(LC_ALL, "Rus");
    
    int len1;
    do {
        std::cout << "Введите мощность желаемого множества № 1: ";
        std::cin >> len1;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (len1 <= 0) {
            std::cout << "Ошибка: мощность должна быть положительным числом!" << std::endl;
        }
    } while (len1 <= 0);
    len1++;
    
    TSet t1(len1);
    std::cout << "Пустое множество: " << t1 << std::endl;
    std::cout << "t1 (битовое поле):\n" << t1.operator TBitField() << std::endl;
    
    std::cout << "Введите через пробел элементы множества: ";
    std::cin >> t1;
    std::cout << "Результат (Множество № 1): " << t1 << std::endl;
    std::cout << "t1 (битовое поле):\n" << t1.operator TBitField() << std::endl;
    
    int len2;
    do {
        std::cout << "Введите мощность желаемого множества № 2: ";
        std::cin >> len2;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (len2 <= 0) {
            std::cout << "Ошибка: мощность должна быть положительным числом!" << std::endl;
        }
    } while (len2 <= 0);
    len2++;
    
    TSet t2(len2);
    std::cout << "t2 (битовое поле):\n" << t2.operator TBitField() << std::endl;
    
    std::cout << "Введите через пробел элементы множества: ";
    std::cin >> t2;
    std::cout << "Результат (Множество № 2): " << t2 << std::endl;
    std::cout << "t2 (битовое поле):\n" << t2.operator TBitField() << std::endl;
    
    int flag, n, count;
    int flagg = 1;
    
    std::cout << "Добро пожаловать!" << "\n";





    do {
        if (flagg == 1) {
            menu();
            
            do {
                std::cout << "Введите номер желаемого пункта из меню: " << "\n";
                std::cin >> flag;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                if (flag < 1 || flag > 11) {
                    std::cout << "Ошибка: введите число от 1 до 11!" << std::endl;
                }
            } while ((flag < 1) || (flag > 11));
            
            switch (flag) {
            case 1:
                std::cout << "Введите элемент для добавления: ";
                std::cin >> n;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                do {
                    std::cout << "Введите номер множества (1 или 2): ";
                    std::cin >> count;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    if (count < 1 || count > 2) {
                        std::cout << "Ошибка: введите 1 или 2!" << std::endl;
                    }
                } while ((count < 1) || (count > 2));
                
                if (count == 1) {
                    if (n >= len1 || n < 0) {
                        std::cout << "Элемент " << n << " вне диапазона (0-" << len1-1 << ")" << "\n";
                    }
                    else {
                        std::cout << "Множество № 1 до: " << t1 << std::endl;
                        t1.InsElem(n);
                        std::cout << "После добавления: " << t1 << std::endl;
                        std::cout << "t1 (битовое поле):\n" << t1.operator TBitField() << std::endl;
                    }
                }
                else {
                    if (n >= len2 || n < 0) {
                        std::cout << "Элемент " << n << " вне диапазона (0-" << len2-1 << ")" << "\n";
                    }
                    else {
                        std::cout << "Множество № 2 до: " << t2 << std::endl;
                        t2.InsElem(n);
                        std::cout << "После добавления: " << t2 << std::endl;
                        std::cout << "t2 (битовое поле):\n" << t2.operator TBitField() << std::endl;
                    }
                }
                break;
                
            case 2:
                std::cout << "Введите элемент для удаления: ";
                std::cin >> n;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                do {
                    std::cout << "Введите номер множества (1 или 2): ";
                    std::cin >> count;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    if (count < 1 || count > 2) {
                        std::cout << "Ошибка: введите 1 или 2!" << std::endl;
                    }
                } while ((count < 1) || (count > 2));
                
                if (count == 1) {
                    if (n >= 0 && n < len1) {
                        std::cout << "Множество № 1 до: " << t1 << std::endl;
                        t1.DelElem(n);
                        std::cout << "После удаления: " << t1 << std::endl;
                        std::cout << "t1 (битовое поле):\n" << t1.operator TBitField() << std::endl;
                    }
                    else {
                        std::cout << "Элемент " << n << " вне диапазона (0-" << len1-1 << ")" << std::endl;
                    }
                }
                else {
                    if (n >= 0 && n < len2) {
                        std::cout << "Множество № 2 до: " << t2 << std::endl;
                        t2.DelElem(n);
                        std::cout << "После удаления: " << t2 << std::endl;
                        std::cout << "t2 (битовое поле):\n" << t2.operator TBitField() << std::endl;
                    }
                    else {
                        std::cout << "Элемент " << n << " вне диапазона (0-" << len2-1 << ")" << std::endl;
                    }
                }
                break;
                
            case 3:
                std::cout << "Введите элемент для проверки: ";
                std::cin >> n;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                do {
                    std::cout << "Введите номер множества (1 или 2): ";
                    std::cin >> count;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    if (count < 1 || count > 2) {
                        std::cout << "Ошибка: введите 1 или 2!" << std::endl;
                    }
                } while ((count < 1) || (count > 2));
                
                if (count == 1) {
                    if (n >= 0 && n < len1) {
                        std::cout << "Множество № 1: " << t1 << std::endl;
                        std::cout << "Результат: " << (t1.isMember(n) ? "присутствует" : "отсутствует") << std::endl;
                        std::cout << "t1 (битовое поле):\n" << t1.operator TBitField() << std::endl;
                    }
                    else {
                        std::cout << "Элемент " << n << " вне диапазона" << std::endl;
                    }
                }
                else {
                    if (n >= 0 && n < len2) {
                        std::cout << "Множество № 2: " << t2 << std::endl;
                        std::cout << "Результат: " << (t2.isMember(n) ? "присутствует" : "отсутствует") << std::endl;
                        std::cout << "t2 (битовое поле):\n" << t2.operator TBitField() << std::endl;
                    }
                    else {
                        std::cout << "Элемент " << n << " вне диапазона" << std::endl;
                    }
                }
                break;
                
            case 4:
                do {
                    std::cout << "Введите номер множества для присваивания (1 или 2): ";
                    std::cin >> count;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    if (count < 1 || count > 2) {
                        std::cout << "Ошибка: введите 1 или 2!" << std::endl;
                    }
                } while ((count < 1) || (count > 2));
                
                if (count == 1) {
                    std::cout << "Множество № 1 до: " << t1 << std::endl;
                    std::cout << "t1 (битовое поле):\n" << t1.operator TBitField() << std::endl;
                    std::cout << "Множество № 2 (источник): " << t2 << std::endl;
                    std::cout << "t2 (битовое поле):\n" << t2.operator TBitField() << std::endl;
                    
                    t1 = t2;
                    
                    std::cout << "Множество № 1 после: " << t1 << std::endl;
                    std::cout << "t1 (битовое поле):\n" << t1.operator TBitField() << std::endl;
                }
                else {
                    std::cout << "Множество № 2 до: " << t2 << std::endl;
                    std::cout << "t2 (битовое поле):\n" << t2.operator TBitField() << std::endl;
                    std::cout << "Множество № 1 (источник): " << t1 << std::endl;
                    std::cout << "t1 (битовое поле):\n" << t1.operator TBitField() << std::endl;
                    
                    t2 = t1;
                    
                    std::cout << "Множество № 2 после: " << t2 << std::endl;
                    std::cout << "t2 (битовое поле):\n" << t2.operator TBitField() << std::endl;
                }
                break;
                
            case 5:
                std::cout << "Множество №1: " << t1 << std::endl;
                std::cout << "t1 (битовое поле):\n" << t1.operator TBitField() << std::endl;
                std::cout << "Множество №2: " << t2 << std::endl;
                std::cout << "t2 (битовое поле):\n" << t2.operator TBitField() << std::endl;
                
                if (t1 == t2) {
                    std::cout << "Результат: множества РАВНЫ!" << "\n";
                }
                else {
                    std::cout << "Результат: множества РАЗЛИЧАЮТСЯ!" << "\n";
                }
                break;
                
            case 6:
                {
                    std::cout << "Множество №1: " << t1 << std::endl;
                    std::cout << "t1 (битовое поле):\n" << t1.operator TBitField() << std::endl;
                    std::cout << "Множество №2: " << t2 << std::endl;
                    std::cout << "t2 (битовое поле):\n" << t2.operator TBitField() << std::endl;
                    
                    TSet result = t1 + t2;
                    std::cout << "Результат объединения: " << result << "\n";
                    std::cout << "Результат (битовое поле):\n" << result.operator TBitField() << std::endl;
                }
                break;
                
            case 7:
                {
                    std::cout << "Множество №1: " << t1 << std::endl;
                    std::cout << "t1 (битовое поле):\n" << t1.operator TBitField() << std::endl;
                    std::cout << "Множество №2: " << t2 << std::endl;
                    std::cout << "t2 (битовое поле):\n" << t2.operator TBitField() << std::endl;
                    
                    TSet result = t1 * t2;
                    std::cout << "Результат пересечения: " << result << "\n";
                    std::cout << "Результат (битовое поле):\n" << result.operator TBitField() << std::endl;
                }
                break;
                
            case 8:
                do {
                    std::cout << "Введите номер множества (1 или 2): ";
                    std::cin >> count;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    if (count < 1 || count > 2) {
                        std::cout << "Ошибка: введите 1 или 2!" << std::endl;
                    }
                } while ((count < 1) || (count > 2));
                
                if (count == 1) {
                    std::cout << "Множество №1 до: " << t1 << std::endl;
                    std::cout << "t1 (битовое поле):\n" << t1.operator TBitField() << std::endl;
                    
                    TSet result = ~t1;
                    std::cout << "Результат отрицания: " << result << "\n";
                    std::cout << "Результат (битовое поле):\n" << result.operator TBitField() << std::endl;
                }
                else {
                    std::cout << "Множество №2 до: " << t2 << std::endl;
                    std::cout << "t2 (битовое поле):\n" << t2.operator TBitField() << std::endl;
                    
                    TSet result = ~t2;
                    std::cout << "Результат отрицания: " << result << "\n";
                    std::cout << "Результат (битовое поле):\n" << result.operator TBitField() << std::endl;
                }
                break;
                
            case 9:
                std::cout << "Введите элемент для прибавления: ";
                std::cin >> n;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                do {
                    std::cout << "Введите номер множества (1 или 2): ";
                    std::cin >> count;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    if (count < 1 || count > 2) {
                        std::cout << "Ошибка: введите 1 или 2!" << std::endl;
                    }
                } while ((count < 1) || (count > 2));
                
                if (count == 1) {
                    if (n >= len1 || n < 0) {
                        std::cout << "Элемент " << n << " вне диапазона (0-" << len1-1 << ")" << "\n";
                    }
                    else {
                        std::cout << "Множество № 1 до: " << t1 << std::endl;
                        t1 + n;
                        std::cout << "После добавления: " << t1 << std::endl;
                        std::cout << "t1 (битовое поле):\n" << t1.operator TBitField() << std::endl;
                    }
                }
                else {
                    if (n >= len2 || n < 0) {
                        std::cout << "Элемент " << n << " вне диапазона (0-" << len2-1 << ")" << "\n";
                    }
                    else {
                        std::cout << "Множество № 2 до: " << t2 << std::endl;
                        t2 + n;
                        std::cout << "После добавления: " << t2 << std::endl;
                        std::cout << "t2 (битовое поле):\n" << t2.operator TBitField() << std::endl;
                    }
                }
                break;



            case 10:
                 std::cout << "Введите элемент для вычитания: ";
                std::cin >> n;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                do {
                    std::cout << "Введите номер множества (1 или 2): ";
                    std::cin >> count;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    if (count < 1 || count > 2) {
                        std::cout << "Ошибка: введите 1 или 2!" << std::endl;
                    }
                } while ((count < 1) || (count > 2));
                
                if (count == 1) {
                    if (n >= 0 && n < len1) {
                        std::cout << "Множество № 1 до: " << t1 << std::endl;
                        t1 - n;
                        std::cout << "После удаления: " << t1 << std::endl;
                        std::cout << "t1 (битовое поле):\n" << t1.operator TBitField() << std::endl;
                    }
                    else {
                        std::cout << "Элемент " << n << " вне диапазона (0-" << len1-1 << ")" << std::endl;
                    }
                }
                else {
                    if (n >= 0 && n < len2) {
                        std::cout << "Множество № 2 до: " << t2 << std::endl;
                        t2 - n;
                        std::cout << "После удаления: " << t2 << std::endl;
                        std::cout << "t2 (битовое поле):\n" << t2.operator TBitField() << std::endl;
                    }
                    else {
                        std::cout << "Элемент " << n << " вне диапазона (0-" << len2-1 << ")" << std::endl;
                    }
                }
                break;
            case 11:
                std::cout << "До новых встреч!" << "\n";
                flagg = 0;
                break;
                
            default:
                std::cout << "Ошибка: неверный пункт меню!" << std::endl;
                break;
            }
        }
    } while (flagg == 1);
    
    return 0;
}