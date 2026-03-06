#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <string>
#include <sstream>

using namespace std;

// Класс для работы с дробями
class Fraction {
private:
    long long num; // числитель
    long long den; // знаменатель
    
    long long gcd(long long a, long long b) {
        while (b != 0) {
            long long temp = b;
            b = a % b;
            a = temp;
        }
        return llabs(a);
    }
    
    void reduce() {
        if (den < 0) {
            num = -num;
            den = -den;
        }
        if (num == 0) {
            den = 1;
            return;
        }
        long long g = gcd(llabs(num), den);
        if (g != 0) {
            num /= g;
            den /= g;
        }
    }
    
public:
    Fraction(long long n = 0, long long d = 1) : num(n), den(d) {
        if (den == 0) throw runtime_error("Zero denominator");
        reduce();
    }
    
    Fraction operator+(const Fraction& other) const {
        return Fraction(num * other.den + other.num * den, den * other.den);
    }
    
    Fraction operator-(const Fraction& other) const {
        return Fraction(num * other.den - other.num * den, den * other.den);
    }
    
    Fraction operator*(const Fraction& other) const {
        return Fraction(num * other.num, den * other.den);
    }
    
    Fraction operator/(const Fraction& other) const {
        if (other.num == 0) throw runtime_error("Division by zero");
        return Fraction(num * other.den, den * other.num);
    }
    
    bool operator<(const Fraction& other) const {
        return num * other.den < other.num * den;
    }
    
    bool operator<=(const Fraction& other) const {
        return num * other.den <= other.num * den;
    }
    
    bool operator>(const Fraction& other) const {
        return num * other.den > other.num * den;
    }
    
    bool operator>=(const Fraction& other) const {
        return num * other.den >= other.num * den;
    }
    
    bool operator==(const Fraction& other) const {
        return num * other.den == other.num * den;
    }
    
    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }
    
    Fraction operator-() const {
        return Fraction(-num, den);
    }
    
    bool isZero() const {
        return num == 0;
    }
    
    bool isPositive() const {
        return num > 0;
    }
    
    bool isNegative() const {
        return num < 0;
    }
    
    double toDouble() const {
        return static_cast<double>(num) / den;
    }
    
    friend ostream& operator<<(ostream& os, const Fraction& f) {
        if (f.den == 1) {
            os << f.num;
        } else {
            os << f.num << "/" << f.den;
        }
        return os;
    }
    
    long long getNum() const { return num; }
    long long getDen() const { return den; }
};

// Класс для решения ЗЛП
class SimplexSolver {
private:
    int m, n; // размерности: m ограничений, n переменных
    vector<vector<Fraction>> A; // матрица ограничений
    vector<Fraction> b; // правые части
    vector<Fraction> c; // коэффициенты целевой функции
    vector<int> basis; // базисные переменные
    bool isMax; // максимизация или минимизация
    
    void printTable(const vector<vector<Fraction>>& table, const vector<Fraction>& obj, 
                   const vector<Fraction>& rhs, const string& phase) {
        cout << "\n=== " << phase << " ===" << endl;
        cout << "Базис\t";
        for (int j = 0; j < n; j++) cout << "x" << j+1 << "\t";
        cout << "RHS" << endl;
        
        for (int i = 0; i < m; i++) {
            if (basis[i] < n) {
                cout << "x" << basis[i]+1 << "\t";
            } else {
                cout << "y" << basis[i]-n+1 << "\t";
            }
            for (int j = 0; j < n; j++) {
                cout << table[i][j] << "\t";
            }
            cout << rhs[i] << endl;
        }
        
        cout << "z\t";
        for (int j = 0; j < n; j++) {
            cout << obj[j] << "\t";
        }
        cout << "| " << rhs[m] << endl;
    }
    
    // Найти вводимую переменную (столбец) для фазы 1
    int findEnteringVarPhase1(const vector<Fraction>& obj) {
        int entering = -1;
        Fraction minVal(0, 1);
        
        for (int j = 0; j < n; j++) {
            if (obj[j] < minVal) {
                minVal = obj[j];
                entering = j;
            }
        }
        return entering;
    }
    
    // Найти вводимую переменную для фазы 2
    int findEnteringVarPhase2(const vector<Fraction>& obj) {
        if (isMax) {
            // Для максимизации: наибольший положительный коэффициент
            Fraction maxVal(0, 1);
            int entering = -1;
            for (int j = 0; j < n; j++) {
                if (obj[j] > maxVal) {
                    maxVal = obj[j];
                    entering = j;
                }
            }
            return entering;
        } else {
            // Для минимизации: наименьший отрицательный коэффициент
            Fraction minVal(0, 1);
            int entering = -1;
            for (int j = 0; j < n; j++) {
                if (obj[j] < minVal) {
                    minVal = obj[j];
                    entering = j;
                }
            }
            return entering;
        }
    }
    
    // Найти выводимую переменную (строку)
    int findLeavingVar(const vector<vector<Fraction>>& table, int entering, 
                      const vector<Fraction>& rhs) {
        int leaving = -1;
        Fraction minRatio = Fraction(999999999, 1); // Большое число
        
        for (int i = 0; i < m; i++) {
            if (table[i][entering] > Fraction(0, 1)) {
                Fraction ratio = rhs[i] / table[i][entering];
                if (ratio > Fraction(0, 1) && ratio < minRatio) {
                    minRatio = ratio;
                    leaving = i;
                }
            }
        }
        return leaving;
    }
    
    // Выполнить шаг симплекс-метода
    void pivot(vector<vector<Fraction>>& table, vector<Fraction>& obj, 
               vector<Fraction>& rhs, int entering, int leaving) {
        int m = table.size();
        int n = table[0].size();
        
        // Обновляем базис
        basis[leaving] = entering;
        
        // Делим ведущую строку на ведущий элемент
        Fraction pivotElem = table[leaving][entering];
        for (int j = 0; j < n; j++) {
            table[leaving][j] = table[leaving][j] / pivotElem;
        }
        rhs[leaving] = rhs[leaving] / pivotElem;
        
        // Обновляем остальные строки
        for (int i = 0; i < m; i++) {
            if (i != leaving) {
                Fraction factor = table[i][entering];
                if (factor != Fraction(0, 1)) {
                    for (int j = 0; j < n; j++) {
                        table[i][j] = table[i][j] - factor * table[leaving][j];
                    }
                    rhs[i] = rhs[i] - factor * rhs[leaving];
                }
            }
        }
        
        // Обновляем целевую функцию
        Fraction objFactor = obj[entering];
        if (objFactor != Fraction(0, 1)) {
            for (int j = 0; j < n; j++) {
                obj[j] = obj[j] - objFactor * table[leaving][j];
            }
            rhs[m] = rhs[m] - objFactor * rhs[leaving];
        }
    }
    
public:
    SimplexSolver(const vector<vector<Fraction>>& _A, const vector<Fraction>& _b,
                 const vector<Fraction>& _c, bool _isMax = true)
        : A(_A), b(_b), c(_c), isMax(_isMax) {
        m = A.size();
        if (m > 0) n = A[0].size();
        else n = 0;
    }
    
    // Двухфазный симплекс-метод
    pair<vector<Fraction>, Fraction> solveTwoPhase() {
        // Фаза 1: Искусственные переменные
        int totalVars = n + m;
        
        vector<vector<Fraction>> phase1Table(m, vector<Fraction>(totalVars, Fraction(0, 1)));
        vector<Fraction> phase1RHS(m + 1, Fraction(0, 1));
        vector<Fraction> phase1Obj(totalVars, Fraction(0, 1));
        
        // Инициализация таблицы фазы 1
        basis.resize(m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                phase1Table[i][j] = A[i][j];
            }
            // Искусственная переменная
            phase1Table[i][n + i] = Fraction(1, 1);
            phase1RHS[i] = b[i];
            basis[i] = n + i;
        }
        
        // Целевая функция фазы 1: минимизация суммы искусственных переменных
        for (int i = 0; i < m; i++) {
            phase1Obj[n + i] = Fraction(-1, 1);
        }
        
        // Преобразуем целевую функцию
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < totalVars; j++) {
                phase1Obj[j] = phase1Obj[j] + phase1Table[i][j];
            }
            phase1RHS[m] = phase1RHS[m] + phase1RHS[i];
        }
        
        // Симплекс-метод для фазы 1
        int phase1Iter = 0;
        while (phase1Iter++ < 100) {
            int entering = findEnteringVarPhase1(phase1Obj);
            if (entering == -1) break;
            
            int leaving = findLeavingVar(phase1Table, entering, phase1RHS);
            if (leaving == -1) {
                throw runtime_error("Задача неограничена в фазе 1");
            }
            
            pivot(phase1Table, phase1Obj, phase1RHS, entering, leaving);
        }
        
        // Проверка допустимости
        if (phase1RHS[m] != Fraction(0, 1)) {
            throw runtime_error("Нет допустимого решения");
        }
        
        // Фаза 2: исходная задача
        vector<vector<Fraction>> phase2Table(m, vector<Fraction>(n, Fraction(0, 1)));
        vector<Fraction> phase2RHS(m + 1, Fraction(0, 1));
        vector<Fraction> phase2Obj(n, Fraction(0, 1));
        
        // Копируем таблицу
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                phase2Table[i][j] = phase1Table[i][j];
            }
            phase2RHS[i] = phase1RHS[i];
        }
        
        // Настройка целевой функции фазы 2
        for (int j = 0; j < n; j++) {
            phase2Obj[j] = isMax ? -c[j] : c[j];
        }
        
        // Преобразуем целевую функцию
        for (int i = 0; i < m; i++) {
            int basicVar = basis[i];
            if (basicVar < n) {
                Fraction coeff = phase2Obj[basicVar];
                if (coeff != Fraction(0, 1)) {
                    for (int j = 0; j < n; j++) {
                        phase2Obj[j] = phase2Obj[j] - coeff * phase2Table[i][j];
                    }
                    phase2RHS[m] = phase2RHS[m] - coeff * phase2RHS[i];
                }
            }
        }
        
        // Симплекс-метод для фазы 2
        int phase2Iter = 0;
        while (phase2Iter++ < 100) {
            int entering = findEnteringVarPhase2(phase2Obj);
            if (entering == -1) break;
            
            int leaving = findLeavingVar(phase2Table, entering, phase2RHS);
            if (leaving == -1) {
                throw runtime_error("Целевая функция неограничена");
            }
            
            pivot(phase2Table, phase2Obj, phase2RHS, entering, leaving);
        }
        
        // Восстанавливаем решение
        vector<Fraction> solution(n, Fraction(0, 1));
        for (int i = 0; i < m; i++) {
            if (basis[i] < n) {
                solution[basis[i]] = phase2RHS[i];
            }
        }
        
        // Значение целевой функции
        Fraction objValue = isMax ? -phase2RHS[m] : phase2RHS[m];
        
        return {solution, objValue};
    }
};

// Функция для ввода задачи
void inputProblem(int& m, int& n, vector<vector<Fraction>>& A, 
                  vector<Fraction>& b, vector<Fraction>& c, bool& isMax) {
    cout << "Введите количество ограничений (m): ";
    cin >> m;
    cout << "Введите количество переменных (n): ";
    cin >> n;
    
    A.resize(m, vector<Fraction>(n));
    b.resize(m);
    c.resize(n);
    
    cout << "\nВведите коэффициенты целевой функции (c):\n";
    for (int i = 0; i < n; i++) {
        cout << "c[" << i+1 << "]: ";
        string s;
        cin >> s;
        
        size_t pos = s.find('/');
        if (pos != string::npos) {
            long long num = stoll(s.substr(0, pos));
            long long den = stoll(s.substr(pos+1));
            c[i] = Fraction(num, den);
        } else {
            c[i] = Fraction(stoll(s), 1);
        }
    }
    
    cout << "\nВведите матрицу ограничений A (m x n):\n";
    for (int i = 0; i < m; i++) {
        cout << "Строка " << i+1 << " (через пробел): ";
        for (int j = 0; j < n; j++) {
            string s;
            cin >> s;
            
            size_t pos = s.find('/');
            if (pos != string::npos) {
                long long num = stoll(s.substr(0, pos));
                long long den = stoll(s.substr(pos+1));
                A[i][j] = Fraction(num, den);
            } else {
                A[i][j] = Fraction(stoll(s), 1);
            }
        }
    }
    
    cout << "\nВведите правые части ограничений b:\n";
    for (int i = 0; i < m; i++) {
        cout << "b[" << i+1 << "]: ";
        string s;
        cin >> s;
        
        size_t pos = s.find('/');
        if (pos != string::npos) {
            long long num = stoll(s.substr(0, pos));
            long long den = stoll(s.substr(pos+1));
            b[i] = Fraction(num, den);
        } else {
            b[i] = Fraction(stoll(s), 1);
        }
    }
    
    cout << "\nЗадача на максимизацию? (1 - да, 0 - нет): ";
    cin >> isMax;
}

// Пример задачи из задания
void exampleProblem1() {
    cout << "\n=== Пример 1 из задания ===\n";
    
    int m = 3, n = 5;
    bool isMax = true;
    
    vector<vector<Fraction>> A = {
        {Fraction(-4), Fraction(1), Fraction(1), Fraction(1), Fraction(-2)},
        {Fraction(-3), Fraction(0), Fraction(5), Fraction(1), Fraction(1)},
        {Fraction(-1), Fraction(-1), Fraction(3), Fraction(5), Fraction(2)}
    };
    
    vector<Fraction> b = {Fraction(3), Fraction(3), Fraction(5)};
    vector<Fraction> c = {Fraction(0), Fraction(-2), Fraction(5), Fraction(-2), Fraction(-1)};
    
    try {
        SimplexSolver solver(A, b, c, isMax);
        auto result = solver.solveTwoPhase();
        auto solution = result.first;
        auto objValue = result.second;
        
        cout << "\nРезультат:\n";
        cout << "Оптимальное решение:\n";
        for (int i = 0; i < n; i++) {
            cout << "x" << i+1 << " = " << solution[i] << endl;
        }
        cout << "Значение целевой функции: " << objValue << endl;
        cout << "Приближенное значение: " << fixed << setprecision(6) 
             << objValue.toDouble() << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    cout << "Программа для решения ЗЛП двухфазным симплекс-методом\n";
    
    while (true) {
        cout << "\n=== Меню ===\n";
        cout << "1. Решить пример из задания\n";
        cout << "2. Ввести свою задачу\n";
        cout << "3. Выход\n";
        cout << "Выберите опцию: ";
        
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            exampleProblem1();
        } else if (choice == 2) {
            int m, n;
            vector<vector<Fraction>> A;
            vector<Fraction> b, c;
            bool isMax;
            
            inputProblem(m, n, A, b, c, isMax);
            
            try {
                SimplexSolver solver(A, b, c, isMax);
                auto result = solver.solveTwoPhase();
                auto solution = result.first;
                auto objValue = result.second;
                
                cout << "\nРезультат:\n";
                cout << "Оптимальное решение:\n";
                for (int i = 0; i < n; i++) {
                    cout << "x" << i+1 << " = " << solution[i] << endl;
                }
                cout << "Значение целевой функции: " << objValue << endl;
                cout << "Приближенное значение: " << fixed << setprecision(6) 
                     << objValue.toDouble() << endl;
            } catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            
        } else if (choice == 3) {
            break;
        } else {
            cout << "Неверный выбор!\n";
        }
    }
    
    return 0;
}