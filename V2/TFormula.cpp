#include "TFormula.h"
#include "TStack.h"


// Оператор вывода 
std::ostream& operator<<(std::ostream& out, const TFormula& form)
{
    out << form.str;
    return out;
}

// Оператор ввода
std::istream& operator>>(std::istream& in, TFormula& form)
{
    const int MAX = 25;                                                         // Максимальная длина вводимой формулы
    char buffer[MAX];                                                           //Буфер для чтения ввода
    int i = 0;
    char c;
    delete[] form.str;                                                          //Освобождение старой памяти

    while (in.get(c) && c != '\n' && i < MAX - 1) {                             //Чтение символов до конца строки или достижения максимума
        buffer[i] = c;
        i++;
    }
    if (i == MAX - 1) {                                                         //Обработка конца строки
        buffer[MAX - 1] = '\0';                                                 //Обрезание строки при переполнении
    }
    else {
        buffer[i] = '\0';                                                       
    }

    if (i > 0) {                                                                //Создание новой строки для объекта
        form.str = new char[i + 1];
        for (int j = 0; j <= i; j++) {
            form.str[j] = buffer[j];
        }
    }
    else {
        form.str = nullptr;                                                     //Пустая строка
    }
    return in;
}

// Проверка на число
bool isdigit(char c)
{
    bool res = true;
    if ((c != '1') && (c != '2') && (c != '3') && (c != '4') &&
        (c != '5') && (c != '6') && (c != '7') && (c != '8') &&
        (c != '9') && (c != '0')) {
        res = false;
    }
    return res;
}

// Проверка на оперант
bool isop(char c)
{
    bool res = false;
    if ((c == '+') || (c == '-') || (c == '*') || (c == '/')) {
        res = true;
    }
    return res;
}

// Проверка на скобку
bool isbracket(char c)
{
    bool res = false;
    if ((c == '(')  || (c == ')')) {
        res = true;
    }
    return res;
}

// Проверка на букву (только английский)
bool isletter(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

// Проверка на приоретет операнта
int priority(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' ||op == '/') return 2;
    return 0;
}

// Конструктор с параметром
TFormula::TFormula(char* _str)
{
    size_t len = strlen(_str);                                                          //Определение длины строки
    str = new char[len + 1];                                                            //Выделение памяти
    for (size_t i = 0; i <= len; i++) {
        str[i] = _str[i];
    }
}

// Деструктор
TFormula::~TFormula()
{
    delete[] str;
}

// Конструктор копирования
TFormula::TFormula(const TFormula& _str)
{
    if (_str.str) {
        size_t len = strlen(_str.str);                                  //Длина строки оригинала
        str = new char[len + 1];                                        //Выделение памяти
        for (size_t i = 0; i <= len; i++) {                             //Копирование
            str[i] = _str.str[i];
        }
    }
    else {
        str = nullptr;
    }
}
// Оператор присваивания
TFormula TFormula::operator=(const TFormula& _str)
{
    if (this != &_str) {                                                                    // Проверка на самоприсваивание
        delete[] str;

        if (_str.str) {
            size_t len = strlen(_str.str);
            str = new char[len + 1];
            for (size_t i = 0; i < len; i++) {
                str[i] = _str.str[i];
            }
        }
        else {
            str = nullptr;                                                                      // Новая строка пустая
        }
    }
    return *this;
}
// Конструктор по умолчанию
TFormula::TFormula() :str(nullptr) {}

// Проверка правильности расстановки скобок                 
int TFormula::checkbrackets(int arr[], int& n) {
    n = 0;
    int d = 0;
    if (!str) {
        return 0;
    }
    
    TStack<int> stack;
    int len = strlen(str);
    int bracketNumber = 1;
    
    std::cout << "\n=== ТАБЛИЦА СКОБОК ===" << std::endl;
    std::cout << "Открывающая | Закрывающая" << std::endl;
    std::cout << "------------|-------------" << std::endl;
    
    for (int i = 0; i < len; i++) {
        if (str[i] == '(') {

            stack.Push(d + 1);
            d++;                                                                                  
        }
        else if (str[i] == ')') {
            if (stack.IsEmpty()) {
                // Лишняя закрывающая скобка
                arr[n++] = i + 1;                                                                   // Сохраняем позицию
                std::cout << "    -       |     " << (d + 1) << std::endl;
                d++;
            }
            else {
                int openPos = stack.Pop();
                std::cout << "    " << openPos << "       |     " << (d + 1) << std::endl;
                bracketNumber++;
                d++;
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


bool TFormula::checkoperant()
{
    if (!str) {
        return false;
    }
    
    int len = strlen(str);
    int i = 0;
    
    // Пропускаем начальные пробелы
    while (i < len && str[i] == ' ') {
        i++;
    }
    
    while (i < len) {
        // Обработка чисел (включая многозначные)
        if (isdigit(str[i])) {
            // Пропускаем все цифры числа
            while (i < len && isdigit(str[i])) {
                i++;
            }
            
            // Пропускаем возможную десятичную точку и дробную часть
            if (i < len && str[i] == '.') {
                i++;
                // Пропускаем дробную часть
                while (i < len && isdigit(str[i])) {
                    i++;
                }
            }
            
            // Пропускаем пробелы после числа
            while (i < len && str[i] == ' ') {
                i++;
            }
            
            // Проверяем следующий символ
            if (i < len) {
                // Число не может быть перед открывающей скобкой без оператора
                if (str[i] == '(') {
                    return true;
                }
                
                // Число не может быть перед другим числом без оператора
                if (isdigit(str[i])) {
                    return true;
                }
                
                // Число не может быть перед буквой без оператора
                if (isletter(str[i])) {
                    return true;
                }
            }
            continue;
        }
        
        // Обработка идентификаторов (переменных)
        else if (isletter(str[i])) {
            // Пропускаем весь идентификатор (буквы и цифры)
            while (i < len && (isletter(str[i]) || isdigit(str[i]))) {
                i++;
            }
            
            // Пропускаем пробелы после идентификатора
            while (i < len && str[i] == ' ') {
                i++;
            }
            
            // Проверяем следующий символ
            if (i < len) {
                // Идентификатор не может быть перед открывающей скобкой без оператора
                if (str[i] == '(') {
                    return true;
                }
                
                // Идентификатор не может быть перед другим идентификатором без оператора
                if (isletter(str[i])) {
                    return true;
                }
                
                // Идентификатор не может быть перед числом без оператора
                if (isdigit(str[i])) {
                    return true;
                }
            }
            continue;
        }
        
        // Обработка закрывающей скобки
        else if (str[i] == ')') {
            i++;
            
            // Пропускаем пробелы
            while (i < len && str[i] == ' ') {
                i++;
            }
            
            if (i < len) {
                // Закрывающая скобка не может быть перед открывающей скобкой
                if (str[i] == '(') {
                    return true;
                }
                
                // Закрывающая скобка не может быть перед числом без оператора
                if (isdigit(str[i])) {
                    return true;
                }
                
                // Закрывающая скобка не может быть перед буквой без оператора
                if (isletter(str[i])) {
                    return true;
                }
            }
            continue;
        }
        
        // Обработка операторов и скобок - просто пропускаем
        else if (isop(str[i]) || str[i] == '(') {
            i++;
            continue;
        }
        
        // Пропускаем пробелы
        else if (str[i] == ' ') {
            i++;
            continue;
        }
        
        // Любой другой символ
        else {
            i++;
        }
    }
    
    return false;
}
// Преобразование в постфиксную форму
char* TFormula::Postfix()
{
    if (checkoperant()) {
        int expt = 8;  // Код ошибки: пропущен оператор
        throw expt;
    }
    int errorPositions[100];
    int errorCount = 0;
    // Проверяем скобки перед преобразованием
    if (checkbrackets(errorPositions, errorCount) != 0) {
        int expt = 1;
        throw expt;                                                                                     // Выходим в исключение
    }
    int len = strlen(str); 
         

    // Стек для операторов                                                                        
    TStack<char> st(len + 1);

    int maxSize = len * 3 + 1;                                                                  // Максимальный размер постфиксной записи
    char* result = new char[maxSize];                                                           // Результирующая строка
    int resultIndex = 0;                                                                        // Индекс в результирующей строке
    bool predetoop = false;                                                                     // Был ли предыдущий символ оператором
    
    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (c == ' ') continue;                                                                  // Пропуск пробелов


//Обработка строки на числа и буквы
if (isdigit(c) || (c == '.') || (isletter(c))) {
            bool tochka_bila = false;                                                       
            bool cifra_bila = false;
            bool bukva_bila = false;
            //Чтение чисел
            while (i < len && (isdigit(str[i]) || str[i] == '.' || isletter(str[i]))) {
                if (resultIndex >= maxSize - 1) {                                       // Проверка на переполнение 
                    delete[] result;
                    int expt = 5;                                                       // Код ошибки: переполнение
                    throw expt;
                }

                // Обработка цифр
                if (isdigit(str[i])) {
                    cifra_bila = true;
                }

                // Обработка точки
                else if (str[i] == '.') {
                    if (tochka_bila) {
                        delete[] result;
                        int expt = 2;                                                   // Код ошибки: неверный формат числа
                        throw expt;
                    }
                    tochka_bila = true;
                }
                // Обработка букв
                else if (isletter(str[i])) {
                    bukva_bila = true;
                }
                result[resultIndex++] = str[i++];
            }
            if (!bukva_bila) {
                if (!cifra_bila) {
                    delete[] result;
                    int expt = 3;                                                   // Код ошибки: пустое число
                    throw expt;
                }
            }
            
            // Добавление разделителя
            if (resultIndex >= maxSize - 1) {
                delete[] result;
                int expt = 5;
                throw expt;
            }
            result[resultIndex++] = ' ';
            i--;
            predetoop = false;
        }

        //Обротка операторов
        else if (isop(c)) {
            // Обработка унарного минуса
            if (c == '-' && (i == 0 || str[i - 1] == '(' || isop(str[i - 1]))) {
                result[resultIndex++] = '0';                            // Добавляем 0 для унарного минуса
                result[resultIndex++] = ' ';

                // Выталкивание операторов с большим или равным приоритетом
                while (!st.IsEmpty() && isop(st.Peek()) &&
                    priority(st.Peek()) >= priority(c)) {
                    if (resultIndex >= maxSize - 2) {
                        delete[] result;
                        int expt = 5;
                        throw expt;
                    }
                    result[resultIndex++] = st.Pop();
                    result[resultIndex++] = ' ';
                }
                st.Push(c);                                                         // Кладем унарный минус в стек
                predetoop = true;
            }
            else {
                // Проверка: два оператора подряд
                if (predetoop) {
                    delete[] result;
                    int expt = 6;
                    throw expt;         // Код ошибки: Два оператора подряд
                }
                // Выталкиваем операторы с большим или равным приоритетом
                while (!st.IsEmpty() && isop(st.Peek()) &&
                    priority(st.Peek()) >= priority(c)) {
                    if (resultIndex >= maxSize - 2) {
                        delete[] result;
                        int expt = 5;
                        throw expt;
                    }
                    result[resultIndex++] = st.Pop();
                    result[resultIndex++] = ' ';
                }
                st.Push(c);
                predetoop = true;
            }
        }

        //Обработка скобок
        else if (c == '(') {                                         // Открывающая скобка всегда в стек
            st.Push(c);
        }
        else if (c == ')') {
            while (!st.IsEmpty() && st.Peek() != '(') {                 // Выталкиваем все операторы до открывающей скобки
                if (resultIndex >= maxSize - 2) {
                    delete[] result;
                    int expt = 5;
                    throw expt;
                }
                result[resultIndex++] = st.Pop();
                result[resultIndex++] = ' ';
            }
            if (!st.IsEmpty()) {
                st.Pop();
            }
        }
        // Не известный символ
        else {
            delete[] result;
            int expt = 4;
            throw expt;
        }
    }
    // Выталкиваем оставшиеся операторы из стека
    while (!st.IsEmpty()) {
        if (resultIndex >= maxSize - 2) {
            delete[] result;
            int expt = 5;
            throw expt;
        }
        result[resultIndex++] = st.Pop();
        result[resultIndex++] = ' ';
    }
    // Завершение строки
    if (resultIndex > 0) {
        if (result[resultIndex - 1] == ' ') {
            result[resultIndex - 1] = '\0';             // Удаляем последний пробел
        }
        else {
            result[resultIndex] = '\0';
        }
    }
    else {
        result[0] = '\0';                               // Удаляем последний пробел
    }
    return result;                              
}

// Вычисление значения формулы
double TFormula::calculate(int& r)
{
    r = 0;
    char* pf = Postfix();                                   // Преобразуем в пост   фиксную форму
    std::cout << pf;                                        // Выводим постфиксную запись

    if (checkoperant()) {
        int expt = 8;  // Код ошибки: пропущен оператор
        throw expt;
    }
    TStack<double> st(strlen(pf) + 1);                      // Стек для вычислений

    for (int i = 0; i < strlen(pf); i++

) {
        if (pf[i] == ' ') continue;                         // Пропускаем пробелы

        if (isdigit(pf[i]) || pf[i] == '.') {
            double n = 0;
            double d = 1;
            bool point = false;                                 

             while (i < (int)strlen(pf) && (isdigit(pf[i]) || pf[i] == '.')) {
                if (pf[i] == '.') {
                    point = true;                           // Нашли десятичную точку
                }
                else if (!point) {                           // Целая часть
                    n = n * 10 + (pf[i] - '0');
                }                   
                else {                                          // Дробная часть
                    n = n + (pf[i] - '0') / (d * 10);
                    d = d * 10;
                }
                i++;
            }
            i--;
            st.Push(n);
        }

        // Обработка операторов
        else if (isop(pf[i])) {
            double b = st.Pop();
            double a = st.Pop();
            double res;

            if (pf[i] == '+') res = a + b;
            else if (pf[i] == '-') res = a - b;
            else if (pf[i] == '*') res = a * b;
            else if (pf[i] == '/') {
                if (b == 0) {                           // Проверка деления на ноль
                    int expt = 7;
                    throw expt;
                }
                res = a / b;
            }
            st.Push(res);
        }
    }

    //Получение результата
    double res = st.Pop();
    if (fabs(res) < 1e-9) {
        res = 0;
    }
    delete[] pf;
    return res;                             // Возвращаем результат
}