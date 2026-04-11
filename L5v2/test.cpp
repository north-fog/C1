#include <iostream>
#include "Polinom.h"
using namespace std;

// Вспомогательная функция для создания индекса из степеней
int MakeIndex(int a, int b, int c) {
    return a * 100 + b * 10 + c;
}

// Функция вывода полинома
void PrintPolynom(const TPolinom& p, const char* name) {
    cout << name << " = ";
    
    TPolinom temp = p;
    temp.Reset();
    bool first = true;
    
    while (!temp.IsListEnded()) {
        TMonom* m = temp.GetMonom();
        int coeff = m->GetCoeff();
        int idx = m->GetIndex();
        int a, b, c;
        DecodeIndex(idx, a, b, c);  
        
        if (coeff > 0 && !first) {
            cout << " + ";
        } else if (coeff < 0) {
            cout << " - ";
            coeff = -coeff;
        }
        
        if (coeff != 1 || (a == 0 && b == 0 && c == 0)) {
            cout << coeff;
        }
        
        if (a > 0) cout << "x^" << a;
        if (b > 0) cout << "y^" << b;
        if (c > 0) cout << "z^" << c;
        
        first = false;
        temp.GoNext();
    }
    
    if (first) {
        cout << "0";
    }
    
    cout << endl;
}


int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "=== Тестирование ===\n\n";
    
    // Создаем первый полином
    cout << "1. Создание P:\n";
    int P_monoms[][2] = {
        {3, MakeIndex(5, 2, 5)},
        {-5, MakeIndex(4, 3, 3)},
        {7, MakeIndex(3, 5, 1)}
    };
    TPolinom P(P_monoms, 3);
    cout << "P создан, длина списка: " << P.GetListLength() << endl;
    PrintPolynom(P, "P");
    
    cout << "\n2. Создание Q:\n";
    int Q_monoms[][2] = {
        {4, MakeIndex(3, 2, 6)},
        {-6, MakeIndex(2, 0, 8)}
    };
    TPolinom Q(Q_monoms, 2);
    cout << "Q создан, длина списка: " << Q.GetListLength() << endl;
    PrintPolynom(Q, "Q");
    
    // Тест 3: Сложение полиномов
    cout << "3. Сложение P + Q:\n";
    TPolinom R = P + Q;
    PrintPolynom(R, "P + Q");
    cout << endl;
    
    // Тест 4: Сложение с подобными мономами
    cout << "4. Сложение с подобными мономами:\n";
    int A_monoms[][2] = {
        {3, MakeIndex(5, 2, 5)},   // 3x^5y^2z^5
        {-5, MakeIndex(4, 3, 3)}    // -5x^4y^3z^3
    };
    int B_monoms[][2] = {
        {4, MakeIndex(5, 2, 5)},   // 4x^5y^2z^5
        {5, MakeIndex(4, 3, 3)}     // 5x^4y^3z^3
    };
    
    TPolinom A(A_monoms, 2);
    TPolinom B(B_monoms, 2);
    PrintPolynom(A, "A");
    PrintPolynom(B, "B");
    
    TPolinom C = A + B;
    PrintPolynom(C, "A + B");
    cout << endl;
    
    // Тест 5: Нулевой результат
    cout << "5. Нулевой результат:\n";
    int D_monoms[][2] = {
        {3, MakeIndex(5, 2, 5)},
        {-5, MakeIndex(4, 3, 3)}
    };
    int E_monoms[][2] = {
        {-3, MakeIndex(5, 2, 5)},
        {5, MakeIndex(4, 3, 3)}
    };
    
    TPolinom D(D_monoms, 2);
    TPolinom E(E_monoms, 2);
    PrintPolynom(D, "D");
    PrintPolynom(E, "E");
    
    TPolinom F = D + E;
    PrintPolynom(F, "D + E");
    cout << endl;
    
    // Тест 6: Пустой полином
    cout << "6. Пустой полином:\n";
    TPolinom Empty;
    PrintPolynom(Empty, "Empty");
    
    cout << "\n=== Все тесты завершены ===\n";
    return 0;
}