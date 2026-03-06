#include "formula.h"
#include "stack.h"
#include <cctype>
#include <cmath>
#include <stdexcept>



//проверка на цифру
//проверка на операцией
//проверка на скобку
//проверка на букву и тд
//нахождение приоритета операций
//проверка на пробел
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isBracket(char c) {
    return c == '(' || c == ')';
}

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool isSpace(char c) {
    return c == ' ' || c == '\t';
}

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

//Копирование строки
void TFormula::copyString(const char* source) {
    if (source) {
        size_t len = strlen(source);
        str = new char[len + 1];
        strcpy(str, source);
    }
    else {
        str = nullptr;
    }
}

//Конструктор по умолчанию и не только и деструктор
TFormula::TFormula() : str(nullptr) {}

TFormula::TFormula(const char* _str) {
    copyString(_str);
}

TFormula::TFormula(const TFormula& other) {
    copyString(other.str);
}

TFormula::~TFormula() {
    delete[] str;
}

TFormula& TFormula::operator=(const TFormula& other) {
    if (this != &other) {
        delete[] str;
        copyString(other.str);
    }
    return *this;
}

// Ввод и вывод
std::ostream& operator<<(std::ostream& out, const TFormula& form) {
    if (form.str) {
        out << form.str;
    }
    return out;
}

std::istream& operator>>(std::istream& in, TFormula& form) {
    const int MAX = 256;
    char buffer[MAX];
    in.getline(buffer, MAX);                                //чтение строки
    delete[] form.str;                                      //Освобождение памяти
    size_t len = strlen(buffer);                            //копируем новую строку
    form.str = new char[len + 1];
    strcpy(form.str, buffer);
    
    return in;
}

// Проверка скобок
int TFormula::checkbrackets(int arr[], int& n) {
    n = 0;
    if (!str) {
        return 0;
    }
    
    TDynamicStack<int> stack;
    int len = strlen(str);
    int bracketNumber = 1;
    
    std::cout << "\n=== ТАБЛИЦА СКОБОК ===" << std::endl;
    std::cout << "Открывающая | Закрывающая" << std::endl;
    std::cout << "------------|-------------" << std::endl;
    
    for (int i = 0; i < len; i++) {
        if (str[i] == '(') {
            stack.Push(n + 1);                                                                      //+1 удобство пользователя (с 1, можно было и трушный 0 но...)
        }
        else if (str[i] == ')') {
            if (stack.IsEmpty()) {
                // Лишняя закрывающая скобка
                arr[n++] = n  + 1;                                                                   // Сохраняем позицию
                std::cout << "    -       |     " << (i + 1) << std::endl;
            }
            else {
                int openPos = stack.Pop();
                std::cout << "    " << openPos << "       |     " << (i + 1) << std::endl;
                bracketNumber++;
            }
        }
    }
    
    // Обработка оставшихся открывающих скобок
    while (!stack.IsEmpty()) {
        int openPos = stack.Pop();
        arr[n++] = openPos;
        std::cout << "    " << openPos << "       |     -" << std::endl;
    }
    
    std::cout << "\nВсего ошибок: " << n << std::endl;
    
    if (n == 0) {
        std::cout << "Ошибок в расстановке скобок не обнаружено." << std::endl;
    }
    
    return n;
}

// Перевод в постфиксную форму
char* TFormula::Postfix() {
    if (!str || strlen(str) == 0) {
        throw std::runtime_error("Пустое выражение");
    }
    
    // Проверка скобок
    int errorPositions[100];
    int errorCount = 0;
    
    if (checkbrackets(errorPositions, errorCount) > 0) {
        throw std::runtime_error("Ошибка в расстановке скобок");
    }
    
    int len = strlen(str);
    TDynamicStack<char> st(len + 1);
    int maxSize = len * 3 + 1;
    char* result = new char[maxSize];
    int resultIndex = 0;
    bool previousWasOperator = true;                                                // true в начале выражения
    
    for (int i = 0; i < len; i++) {
        char c = str[i];
        
        if (isSpace(c)) {
            continue;
        }
        
        // Обработка чисел и переменных
        if (isDigit(c) || c == '.' || isLetter(c)) {
            bool decimalPointFound = false;
            bool digitFound = false;
            bool letterFound = false;
            
            while (i < len && (isDigit(str[i]) || str[i] == '.' || isLetter(str[i]))) {
                if (resultIndex >= maxSize - 1) {
                    delete[] result;
                    throw std::runtime_error("Превышен максимальный размер результата");
                }
                
                if (isDigit(str[i])) {
                    digitFound = true;
                }
                else if (str[i] == '.') {
                    if (decimalPointFound) {
                        delete[] result;
                        throw std::runtime_error("Несколько десятичных точек в числе");
                    }
                    decimalPointFound = true;
                }
                else if (isLetter(str[i])) {
                    letterFound = true;
                }
                
                result[resultIndex++] = str[i++];
            }
            
            // Проверка корректности числа
            if (!letterFound) { // Это число
                if (!digitFound) {
                    delete[] result;
                    throw std::runtime_error("Некорректное число");
                }
                if (decimalPointFound && !digitFound) {
                    delete[] result;
                    throw std::runtime_error("Некорректное число с точкой");
                }
            }
            
            if (resultIndex >= maxSize - 1) {
                delete[] result;
                throw std::runtime_error("Превышен максимальный размер результата");
            }
            
            result[resultIndex++] = ' ';
            i--;
            previousWasOperator = false;
        }
        // Обработка операторов
        else if (isOperator(c)) {
            // Проверка на унарный минус
            if (c == '-' && (i == 0 || str[i - 1] == '(' || isOperator(str[i - 1]) || previousWasOperator)) {
                // Унарный минус - добавляем 0 перед ним
                if (resultIndex >= maxSize - 3) {
                    delete[] result;
                    throw std::runtime_error("Превышен максимальный размер результата");
                }
                result[resultIndex++] = '0';
                result[resultIndex++] = ' ';
                
                // Обрабатываем унарный минус как операцию
                while (!st.IsEmpty() && isOperator(st.Peek()) && priority(st.Peek()) >= priority(c)) {
                    if (resultIndex >= maxSize - 2) {
                        delete[] result;
                        throw std::runtime_error("Превышен максимальный размер результата");
                    }
                    result[resultIndex++] = st.Pop();
                    result[resultIndex++] = ' ';
                }
                st.Push(c);
                previousWasOperator = true;
            }
            else {
                if (previousWasOperator && c != '-') {
                    delete[] result;
                    throw std::runtime_error("Два оператора подряд");
                }
                
                while (!st.IsEmpty() && isOperator(st.Peek()) && priority(st.Peek()) >= priority(c)) {
                    if (resultIndex >= maxSize - 2) {
                        delete[] result;
                        throw std::runtime_error("Превышен максимальный размер результата");
                    }
                    result[resultIndex++] = st.Pop();
                    result[resultIndex++] = ' ';
                }
                st.Push(c);
                previousWasOperator = true;
            }
        }
        // Обработка скобок
        else if (c == '(') {
            st.Push(c);
            previousWasOperator = true;
        }
        else if (c == ')') {
            while (!st.IsEmpty() && st.Peek() != '(') {
                if (resultIndex >= maxSize - 2) {
                    delete[] result;
                    throw std::runtime_error("Превышен максимальный размер результата");
                }
                result[resultIndex++] = st.Pop();
                result[resultIndex++] = ' ';
            }
            
            if (st.IsEmpty()) {
                delete[] result;
                throw std::runtime_error("Непарная закрывающая скобка");
            }
            
            st.Pop(); // Удаляем '('
            previousWasOperator = false;
        }
        else {
            delete[] result;
            throw std::runtime_error("Неизвестный символ в выражении");
        }
    }
    
    // Извлекаем оставшиеся операторы из стека
    while (!st.IsEmpty()) {
        char op = st.Pop();
        if (op == '(') {
            delete[] result;
            throw std::runtime_error("Непарная открывающая скобка");
        }
        
        if (resultIndex >= maxSize - 2) {
            delete[] result;
            throw std::runtime_error("Превышен максимальный размер результата");
        }
        
        result[resultIndex++] = op;
        result[resultIndex++] = ' ';
    }
    
    // Завершаем строку
    if (resultIndex > 0) {
        // Убираем последний пробел
        if (result[resultIndex - 1] == ' ') {
            result[resultIndex - 1] = '\0';
        }
        else {
            result[resultIndex] = '\0';
        }
    }
    else {
        result[0] = '\0';
    }
    
    return result;
}

// Вычисление выражения
double TFormula::calculate() {
    if (!str || strlen(str) == 0) {
        throw std::runtime_error("Пустое выражение");
    }
    
    // Получаем постфиксную форму
    char* postfix = Postfix();
    std::cout << "Постфиксная форма: " << postfix << std::endl;
    
    TDynamicStack<double> st(strlen(postfix) + 1);
    
    for (int i = 0; i < strlen(postfix); i++) {
        if (postfix[i] == ' ') {
            continue;
        }
        
        // Обработка чисел
        if (isDigit(postfix[i]) || postfix[i] == '.') {
            double number = 0;
            double decimalDivisor = 1;
            bool decimalPart = false;
            
            while (i < strlen(postfix) && (isDigit(postfix[i]) || postfix[i] == '.')) {
                if (postfix[i] == '.') {
                    decimalPart = true;
                }
                else if (!decimalPart) {
                    number = number * 10 + (postfix[i] - '0');
                }
                else {
                    decimalDivisor *= 10;
                    number = number + (postfix[i] - '0') / decimalDivisor;
                }
                i++;
            }
            i--;
            
            st.Push(number);
        }
        // Обработка операторов
        else if (isOperator(postfix[i])) {
            if (st.size() < 2) {
                delete[] postfix;
                throw std::runtime_error("Недостаточно операндов для операции");
            }
            
            double b = st.Pop();
            double a = st.Pop();
            double result = 0;
            
            switch (postfix[i]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': 
                    if (fabs(b) < 1e-10) {
                        delete[] postfix;
                        throw std::runtime_error("Деление на ноль");
                    }
                    result = a / b; 
                    break;
            }
            
            st.Push(result);
        }
        else if (isLetter(postfix[i])) {
            // Для переменных можно добавить обработку
            // Пока просто возвращаем ошибку
            delete[] postfix;
            throw std::runtime_error("Выражение содержит переменные. Введите числовое выражение.");
        }
    }
    
    if (st.size() != 1) {
        delete[] postfix;
        throw std::runtime_error("Ошибка в вычислении выражения");
    }
    
    double finalResult = st.Pop();
    delete[] postfix;
    
    return finalResult;
}