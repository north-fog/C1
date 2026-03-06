#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

// Класс для работы с дробями
class Fraction {
private:
    long long numerator;
    long long denominator;
    
    void simplify() {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        long long g = gcd(llabs(numerator), llabs(denominator));
        if (g > 1) {
            numerator /= g;
            denominator /= g;
        }
    }
    
    long long gcd(long long a, long long b) {
        while (b != 0) {
            long long t = b;
            b = a % b;
            a = t;
        }
        return a;
    }
    
public:
    Fraction(long long num = 0, long long den = 1) : numerator(num), denominator(den) {
        if (denominator == 0) denominator = 1;
        simplify();
    }
    
    Fraction operator+(const Fraction& other) const {
        long long num = numerator * other.denominator + other.numerator * denominator;
        long long den = denominator * other.denominator;
        return Fraction(num, den);
    }
    
    Fraction operator-(const Fraction& other) const {
        long long num = numerator * other.denominator - other.numerator * denominator;
        long long den = denominator * other.denominator;
        return Fraction(num, den);
    }
    
    Fraction operator*(const Fraction& other) const {
        long long num = numerator * other.numerator;
        long long den = denominator * other.denominator;
        return Fraction(num, den);
    }
    
    Fraction operator/(const Fraction& other) const {
        long long num = numerator * other.denominator;
        long long den = denominator * other.numerator;
        return Fraction(num, den);
    }
    
    Fraction operator-() const {
        return Fraction(-numerator, denominator);
    }
    
    bool operator<(const Fraction& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }
    
    bool operator<=(const Fraction& other) const {
        return numerator * other.denominator <= other.numerator * denominator;
    }
    
    bool operator>(const Fraction& other) const {
        return numerator * other.denominator > other.numerator * denominator;
    }
    
    bool operator>=(const Fraction& other) const {
        return numerator * other.denominator >= other.numerator * denominator;
    }
    
    bool operator==(const Fraction& other) const {
        return numerator * other.denominator == other.numerator * denominator;
    }
    
    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }
    
    bool isZero() const {
        return numerator == 0;
    }
    
    bool isPositive() const {
        return numerator > 0;
    }
    
    bool isNegative() const {
        return numerator < 0;
    }
    
    Fraction abs() const {
        return Fraction(llabs(numerator), llabs(denominator));
    }
    
    string toString() const {
        if (denominator == 1) {
            return to_string(numerator);
        }
        return to_string(numerator) + "/" + to_string(denominator);
    }
    
    double toDouble() const {
        return static_cast<double>(numerator) / denominator;
    }
    
    long long getNumerator() const { return numerator; }
    long long getDenominator() const { return denominator; }
};

class SimplexMSolver {
private:
    int m, n; // Количество уравнений и переменных
    vector<vector<Fraction>> table;
    vector<int> basis; // Индексы базисных переменных
    vector<string> var_names;
    bool is_max;
    vector<double> original_c; // Сохраняем исходные коэффициенты c
    
    // Для М-метода
    Fraction M;
    
public:
    SimplexMSolver(const vector<vector<double>>& A,
                   const vector<double>& b,
                   const vector<double>& c,
                   bool maximize = true)
        : is_max(maximize), M(Fraction(1000000, 1)), original_c(c) {
        
        m = A.size();
        n = A[0].size();
        
        // Инициализация имен переменных
        var_names.resize(n + m); // x1..xn, y1..ym
        for (int i = 0; i < n; i++) {
            var_names[i] = "x" + to_string(i+1);
        }
        for (int i = 0; i < m; i++) {
            var_names[n + i] = "y" + to_string(i+1);
        }
        
        // Создаем таблицу для М-метода: m+1 строк, n+m+1 столбцов (последний - RHS)
        table.resize(m + 1, vector<Fraction>(n + m + 1, Fraction(0, 1)));
        
        // Заполняем ограничения
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                table[i][j] = Fraction(static_cast<long long>(A[i][j] * 1000), 1000);
            }
            // Добавляем искусственные переменные
            table[i][n + i] = Fraction(1, 1);
            // Правая часть
            table[i][n + m] = Fraction(static_cast<long long>(b[i] * 1000), 1000);
        }
        
        // Начальный базис - искусственные переменные
        basis.resize(m);
        for (int i = 0; i < m; i++) {
            basis[i] = n + i;
        }
        
        // Целевая функция М-задачи
        // Мы решаем min w = sum(y_i) (для нахождения допустимого решения)
        // Затем переходим к исходной задаче
        
        // Сначала заполняем строку F коэффициентами для искусственной функции w = y1+y2+...+ym
        // w = M*(y1+y2+...+ym)
        for (int i = 0; i < m; i++) {
            table[m][n + i] = M; // Коэффициенты M при y_i
        }
        
        // Выражаем w через небазисные переменные (x)
        // y_i = b_i - sum(a_ij * x_j)
        // w = M*sum(y_i) = M*sum(b_i) - M*sum(sum(a_ij * x_j))
        // Делаем коэффициенты при базисных переменных (y_i) равными 0
        for (int i = 0; i < m; i++) {
            Fraction coeff = table[m][n + i]; // M для y_i
            if (!coeff.isZero()) {
                for (int j = 0; j <= n + m; j++) {
                    table[m][j] = table[m][j] - coeff * table[i][j];
                }
            }
        }
    }
    
    void printTable(int step, const string& phase, bool show_m = false) {
        cout << "\n" << string(80, '=') << "\n";
        cout << phase << " - Шаг " << step << "\n";
        cout << string(80, '=') << "\n";
        
        // Заголовок
        cout << setw(10) << "Базис" << " |" << setw(12) << "RHS";
        for (int j = 0; j < n + (show_m ? m : 0); j++) {
            cout << " |" << setw(12) << var_names[j];
        }
        cout << "\n" << string(14 + (n + (show_m ? m : 0)) * 15, '-') << "\n";
        
        // Строки ограничений
        for (int i = 0; i < m; i++) {
            cout << setw(10) << var_names[basis[i]] << " |";
            int last_col = n + (show_m ? m : 0);
            cout << setw(12) << table[i][last_col].toString();
            
            for (int j = 0; j < last_col; j++) {
                cout << " |" << setw(12) << table[i][j].toString();
            }
            cout << "\n";
        }
        
        // Строка целевой функции
        cout << setw(10) << (show_m ? "F(M)" : "F") << " |";
        int last_col = n + (show_m ? m : 0);
        cout << setw(12) << table[m][last_col].toString();
        
        for (int j = 0; j < last_col; j++) {
            cout << " |" << setw(12) << table[m][j].toString();
        }
        cout << "\n";
    }
    
    bool isOptimalPhase1() {
        // В фазе 1 оптимально, когда все коэффициенты в строке F >= 0
        for (int j = 0; j < n + m; j++) {
            if (table[m][j].isNegative()) {
                return false;
            }
        }
        return true;
    }
    
    int findEnteringVariablePhase1() {
        // Находим переменную с наиболее отрицательным коэффициентом
        int entering = -1;
        Fraction min_val(0, 1);
        
        for (int j = 0; j < n + m; j++) {
            // Пропускаем базисные переменные
            bool is_basic = false;
            for (int i = 0; i < m; i++) {
                if (basis[i] == j) {
                    is_basic = true;
                    break;
                }
            }
            
            if (!is_basic && table[m][j] < min_val) {
                min_val = table[m][j];
                entering = j;
            }
        }
        
        return entering;
    }
    
    int findLeavingVariable(int entering) {
        int leaving = -1;
        Fraction min_ratio(999999999, 1);
        
        for (int i = 0; i < m; i++) {
            if (table[i][entering].isPositive()) {
                Fraction ratio = table[i][n + m] / table[i][entering];
                if (ratio > Fraction(0, 1) && ratio < min_ratio) {
                    min_ratio = ratio;
                    leaving = i;
                }
            }
        }
        
        return leaving;
    }
    
    void pivot(int row, int col) {
        // Нормализуем ведущую строку
        Fraction pivot_val = table[row][col];
        for (int j = 0; j <= n + m; j++) {
            table[row][j] = table[row][j] / pivot_val;
        }
        
        // Обновляем остальные строки
        for (int i = 0; i <= m; i++) {
            if (i != row) {
                Fraction factor = table[i][col];
                if (!factor.isZero()) {
                    for (int j = 0; j <= n + m; j++) {
                        table[i][j] = table[i][j] - factor * table[row][j];
                    }
                }
            }
        }
        
        // Обновляем базис
        basis[row] = col;
    }
    
    bool solvePhase1() {
        cout << "\n????????????????????????????????????????????????????????????????????\n";
        cout << "?                         ФАЗА 1: М-МЕТОД                          ?\n";
        cout << "?                    (поиск допустимого базиса)                    ?\n";
        cout << "????????????????????????????????????????????????????????????????????\n";
        
        int step = 0;
        printTable(step, "Фаза 1 - Начальная таблица", true);
        
        while (!isOptimalPhase1()) {
            int entering = findEnteringVariablePhase1();
            if (entering == -1) {
                break;
            }
            
            int leaving = findLeavingVariable(entering);
            if (leaving == -1) {
                cout << "Задача неограничена в фазе 1\n";
                return false;
            }
            
            cout << "\nИтерация " << step + 1 << ": ";
            cout << "Вводим " << var_names[entering] 
                 << ", выводим " << var_names[basis[leaving]]
                 << " (строка " << leaving + 1 << ")\n";
            
            pivot(leaving, entering);
            step++;
            printTable(step, "Фаза 1", true);
            
            if (step > 100) {
                cout << "Слишком много итераций в фазе 1\n";
                return false;
            }
        }
        
        // Проверяем, что все искусственные переменные равны 0
        bool has_artificial = false;
        for (int i = 0; i < m; i++) {
            if (basis[i] >= n) { // Искусственная переменная в базисе
                if (!table[i][n + m].isZero()) {
                    cout << "Искусственная переменная " << var_names[basis[i]] 
                         << " = " << table[i][n + m].toString() << " ? 0\n";
                    cout << "Задача не имеет допустимых решений!\n";
                    return false;
                }
                has_artificial = true;
            }
        }
        
        cout << "\n? Фаза 1 завершена успешно!\n";
        if (has_artificial) {
            cout << "Внимание: некоторые искусственные переменные остались в базисе,\n";
            cout << "но имеют нулевые значения - допустимое решение найдено.\n";
        }
        
        return true;
    }
    
    void convertToPhase2() {
        cout << "\n????????????????????????????????????????????????????????????????????\n";
        cout << "?                  ПЕРЕХОД К ФАЗЕ 2                               ?\n";
        cout << "?               (оптимизация исходной задачи)                     ?\n";
        cout << "????????????????????????????????????????????????????????????????????\n";
        
        // Удаляем столбцы искусственных переменных
        // Создаем новую таблицу только для исходных переменных
        vector<vector<Fraction>> new_table(m + 1, vector<Fraction>(n + 1, Fraction(0, 1)));
        
        // Копируем коэффициенты для исходных переменных
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                new_table[i][j] = table[i][j];
            }
            new_table[i][n] = table[i][n + m]; // RHS
        }
        
        // Устанавливаем исходную целевую функцию
        // Для max: f = c·x, мы будем минимизировать -f = -c·x
        // Для min: f = c·x, мы минимизируем f
        
        // Сначала заполняем коэффициентами из original_c
        for (int j = 0; j < n; j++) {
            double c_val = original_c[j];
            if (is_max) {
                c_val = -c_val; // Для max работаем с -f
            }
            new_table[m][j] = Fraction(static_cast<long long>(c_val * 1000), 1000);
        }
        
        // Значение f в текущей точке
        new_table[m][n] = Fraction(0, 1);
        
        // Теперь нужно сделать коэффициенты при базисных переменных равными 0
        // Для этого выразим f через небазисные переменные
        
        for (int i = 0; i < m; i++) {
            if (basis[i] < n) { // Если базисная переменная - исходная
                int var_idx = basis[i];
                Fraction coeff = new_table[m][var_idx];
                if (!coeff.isZero()) {
                    // Вычитаем coeff * строку i из строки F
                    for (int j = 0; j <= n; j++) {
                        new_table[m][j] = new_table[m][j] - coeff * new_table[i][j];
                    }
                }
            }
        }
        
        // Обновляем таблицу
        table = new_table;
        
        // Обновляем имена переменных
        var_names.resize(n + 1);
        for (int i = 0; i < n; i++) {
            var_names[i] = "x" + to_string(i+1);
        }
        var_names[n] = "RHS";
        
        // Обновляем базис - удаляем искусственные переменные
        vector<int> new_basis;
        for (int i = 0; i < m; i++) {
            if (basis[i] < n) {
                new_basis.push_back(basis[i]);
            }
        }
        
        // Если в базисе осталось меньше m переменных, добавляем недостающие
        while (new_basis.size() < m) {
            // Ищем свободную переменную для добавления в базис
            for (int j = 0; j < n; j++) {
                bool in_basis = false;
                for (int k : new_basis) {
                    if (k == j) {
                        in_basis = true;
                        break;
                    }
                }
                if (!in_basis) {
                    new_basis.push_back(j);
                    break;
                }
            }
        }
        
        basis = new_basis;
        
        cout << "Таблица преобразована для второй фазы.\n";
        cout << "Базисные переменные: ";
        for (int i = 0; i < m; i++) {
            cout << var_names[basis[i]] << " ";
        }
        cout << "\n";
    }
    
    bool isOptimalPhase2() {
        // Для max: мы минимизируем -f, поэтому оптимально при всех коэффициентах >= 0
        // Для min: мы минимизируем f, поэтому оптимально при всех коэффициентах >= 0
        for (int j = 0; j < n; j++) {
            if (table[m][j].isNegative()) {
                return false;
            }
        }
        return true;
    }
    
    int findEnteringVariablePhase2() {
        // Находим переменную с наиболее отрицательным коэффициентом
        int entering = -1;
        Fraction min_val(0, 1);
        
        for (int j = 0; j < n; j++) {
            // Пропускаем базисные переменные
            bool is_basic = false;
            for (int i = 0; i < m; i++) {
                if (basis[i] == j) {
                    is_basic = true;
                    break;
                }
            }
            
            if (!is_basic && table[m][j] < min_val) {
                min_val = table[m][j];
                entering = j;
            }
        }
        
        return entering;
    }
    
    bool solvePhase2() {
        cout << "\n????????????????????????????????????????????????????????????????????\n";
        cout << "?                         ФАЗА 2: ОПТИМИЗАЦИЯ                       ?\n";
        cout << "????????????????????????????????????????????????????????????????????\n";
        
        int step = 0;
        printTable(step, "Фаза 2 - Начальная таблица", false);
        
        while (!isOptimalPhase2()) {
            int entering = findEnteringVariablePhase2();
            if (entering == -1) {
                break;
            }
            
            int leaving = findLeavingVariable(entering);
            if (leaving == -1) {
                cout << "Задача неограничена во второй фазе\n";
                return false;
            }
            
            cout << "\nИтерация " << step + 1 << ": ";
            cout << "Вводим " << var_names[entering] 
                 << ", выводим " << var_names[basis[leaving]]
                 << " (строка " << leaving + 1 << ")\n";
            
            pivot(leaving, entering);
            step++;
            printTable(step, "Фаза 2", false);
            
            if (step > 100) {
                cout << "Слишком много итераций в фазе 2\n";
                return false;
            }
        }
        
        cout << "\n? Фаза 2 завершена успешно!\n";
        return true;
    }
    
    void printSolution() {
        cout << "\n" << string(80, '=') << "\n";
        cout << "                        РЕЗУЛЬТАТ\n";
        cout << string(80, '=') << "\n";
        
        // Вектор решения
        vector<Fraction> x(n, Fraction(0, 1));
        for (int i = 0; i < m; i++) {
            if (basis[i] < n) {
                x[basis[i]] = table[i][n];
            }
        }
        
        cout << "Оптимальное решение:\n";
        for (int i = 0; i < n; i++) {
            cout << "  x" << i+1 << " = " << x[i].toString();
            if (x[i].getDenominator() != 1) {
                cout << " ? " << fixed << setprecision(6) << x[i].toDouble();
            }
            cout << "\n";
        }
        
        // Вычисляем значение исходной целевой функции f = c·x
        Fraction f_value(0, 1);
        for (int i = 0; i < n; i++) {
            f_value = f_value + Fraction(static_cast<long long>(original_c[i] * 1000), 1000) * x[i];
        }
        
        cout << "\nЗначение целевой функции:\n";
        cout << "  f = ";
        for (int i = 0; i < n; i++) {
            if (i > 0 && original_c[i] >= 0) cout << " + ";
            if (original_c[i] < 0) cout << " - ";
            
            double abs_c = abs(original_c[i]);
            if (abs_c != 1.0) {
                cout << abs_c;
            }
            cout << "·x" << i+1;
        }
        
        cout << " = " << f_value.toString();
        if (f_value.getDenominator() != 1) {
            cout << " ? " << fixed << setprecision(6) << f_value.toDouble();
        }
        cout << "\n";
        
        if (is_max) {
            cout << "Максимальное значение: " << f_value.toString() << "\n";
        } else {
            cout << "Минимальное значение: " << f_value.toString() << "\n";
        }
        
        // Проверка ограничений
        cout << "\nПроверка ограничений:\n";
    }
    
    bool solve() {
        if (!solvePhase1()) {
            return false;
        }
        
        convertToPhase2();
        
        if (!solvePhase2()) {
            return false;
        }
        
        printSolution();
        return true;
    }
};

// Решение примера из задания
void solveExampleFromTask() {
    cout << "\n" << string(80, '=') << "\n";
    cout << "           РЕШЕНИЕ ПРИМЕРА ИЗ ЗАДАНИЯ\n";
    cout << "\nЗадача:\n";
    cout << "  max   f = -2x1 - 3x2 + 3x3 + x4 + x5\n";
    cout << "  при условиях:\n";
    cout << "        -x1 +  x2 + 2x3 + 3x4 - x5 = 1\n";
    cout << "         x1 -  x2 -  x3 + 4x4 + x5 = 3\n";
    cout << "        -4x1 + 0x2 - 4x3 + 4x4 + x5 = 2\n";
    cout << "        x1, x2, x3, x4, x5 ? 0\n";
    cout << string(80, '=') << "\n";
    
    // Коэффициенты матрицы A
    vector<vector<double>> A = {
        {-1, 1, 2, 3, -1},
        {1, -1, -1, 4, 1},
        {-4, 0, -4, 4, 1}
    };
    
    // Вектор правых частей
    vector<double> b = {1, 3, 2};
    
    // Коэффициенты целевой функции (для max)
    vector<double> c = {-2, -3, 3, 1, 1};
    
    // Создаем решатель для задачи максимизации
    SimplexMSolver solver(A, b, c, true);
    solver.solve();
}

// Ввод пользовательской задачи
void solveCustomProblem() {
    cout << "\n" << string(80, '=') << "\n";
    cout << "                    РЕШЕНИЕ ПОЛЬЗОВАТЕЛЬСКОЙ ЗАДАЧИ\n";
    cout << string(80, '=') << "\n";
    
    int m, n;
    cout << "Введите количество ограничений (m): ";
    cin >> m;
    cout << "Введите количество переменных (n): ";
    cin >> n;
    
    vector<vector<double>> A(m, vector<double>(n));
    vector<double> b(m);
    vector<double> c(n);
    
    cout << "\nВведите коэффициенты матрицы A (" << m << "x" << n << "):\n";
    for (int i = 0; i < m; i++) {
        cout << "Строка " << i+1 << ": ";
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    
    cout << "\nВведите правые части b: ";
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    
    cout << "\nВведите коэффициенты целевой функции c: ";
    for (int j = 0; j < n; j++) {
        cin >> c[j];
    }
    
    char choice;
    cout << "Задача на максимизацию (y/n)? ";
    cin >> choice;
    bool maximize = (choice == 'y' || choice == 'Y');
    
    SimplexMSolver solver(A, b, c, maximize);
    solver.solve();
}

int main() {
    setlocale(LC_ALL, "Rus");
    
    while (true) {
        cout << "\nМЕНЮ:\n";
        cout << "1. Решить пример из задания\n";
        cout << "2. Решить свою задачу\n";
        cout << "3. Выход\n";
        cout << "Выберите: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                solveExampleFromTask();
                break;
            case 2:
                solveCustomProblem();
                break;
            case 3:
                cout << "Выход.\n";
                return 0;
            default:
                cout << "Неверный выбор!\n";
        }
        
        cout << "\n" << string(80, '=') << "\n";
        cout << "Нажмите Enter для продолжения...";
        cin.ignore();
        cin.get();
    }
    
    return 0;
}