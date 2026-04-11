#include <iostream>
#include "Vector.h"
#include "Matrix.h"

using namespace std;

void testVector() {
    cout << "\n========== ТЕСТИРОВАНИЕ ВЕКТОРА ==========\n";
    
    TVector<int> v1(5);
    cout << "Введите 5 элементов вектора v1: ";
    cin >> v1;
    cout << "v1 = " << v1 << endl;
    
    TVector<int> v2(v1);
    cout << "v2 (копия v1) = " << v2 << endl;
    
    TVector<int> v3 = v1 + 10;
    cout << "v1 + 10 = " << v3 << endl;
    
    TVector<int> v4 = v1 * 2;
    cout << "v1 * 2 = " << v4 << endl;
    
    TVector<int> v5 = v1 + v2;
    cout << "v1 + v2 = " << v5 << endl;
    
    int dot = v1 * v2;
    cout << "v1 · v2 = " << dot << endl;
    
    cout << "|v1| = " << v1.Length() << endl;
    cout << "v1 == v2: " << (v1 == v2 ? "да" : "нет") << endl;
}

void testMatrix() {
    cout << "\n========== ТЕСТИРОВАНИЕ МАТРИЦЫ ==========\n";
    
    int n = 4;
    TMatrix<int> A(n), B(n);
    
    cout << "Введите элементы верхнетреугольной матрицы A (4x4):\n";
    for (int i = 0; i < n; i++) {
        cout << "Строка " << i << " (элементы от " << i << " до " << n-1 << "): ";
        for (int j = i; j < n; j++) {
            cin >> A(i, j);
        }
    }
    
    cout << "\nМатрица A:" << endl;
    cout << A << endl;
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            B(i, j) = (i * 10 + j) * 100;
        }
    }
    
    cout << "Матрица B:" << endl;
    cout << B << endl;
    
    TMatrix<int> C = A + B;
    cout << "A + B:" << endl;
    cout << C << endl;
    
    TMatrix<int> D = A - B;
    cout << "A - B:" << endl;
    cout << D << endl;
    
    TMatrix<int> E = A * B;
    cout << "A * B:" << endl;
    cout << E << endl;
    
    TMatrix<int> F = A;
    cout << "F (копия A):" << endl;
    cout << F << endl;
    
    cout << "A == F: " << (A == F ? "да" : "нет") << endl;
    cout << "A == B: " << (A == B ? "да" : "нет") << endl;
}

void testMatrixVectorMultiplication() {
    cout << "\n========== УМНОЖЕНИЕ МАТРИЦЫ НА ВЕКТОР ==========\n";
    
    int n = 3;
    TMatrix<int> A(n);
    TVector<int> v(n);
    
    cout << "Введите элементы верхнетреугольной матрицы 3x3:\n";
    for (int i = 0; i < n; i++) {
        cout << "Строка " << i << " (элементы от " << i << " до 2): ";
        for (int j = i; j < n; j++) {
            cin >> A(i, j);
        }
    }
    
    cout << "Матрица A:" << endl;
    cout << A << endl;
    
    cout << "Введите 3 элемента вектора: ";
    cin >> v;
    cout << "Вектор v: " << v << endl;
    
    TVector<int> result = A * v;
    cout << "A * v = " << result << endl;
}

void demoFromMethodology() {
    cout << "\n========== ДЕМОНСТРАЦИЯ ИЗ МЕТОДИЧКИ ==========\n";
    
    TMatrix<int> a(5), b(5), c(5);
    
    cout << "Заполнение матриц тестовыми значениями...\n";
    for (int i = 0; i < 5; i++) {
        for (int j = i; j < 5; j++) {
            a(i, j) = i * 10 + j;
            b(i, j) = (i * 10 + j) * 100;
        }
    }
    
    cout << "\nМатрица a:" << endl;
    cout << a << endl;
    
    cout << "Матрица b:" << endl;
    cout << b << endl;
    
    c = a + b;
    cout << "Матрица c = a + b:" << endl;
    cout << c << endl;
}

// ========== ГЛАВНАЯ ФУНКЦИЯ ==========
int main() {
    setlocale(LC_ALL, "Russian");
    
    int choice;
    
    do {
        cout << "\nМЕНЮ:\n";
        cout << "1. Тестирование вектора\n";
        cout << "2. Тестирование матрицы\n";
        cout << "3. Умножение матрицы на вектор\n";
        cout << "4. Демонстрация из методички\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                testVector();
                break;
            case 2:
                testMatrix();
                break;
            case 3:
                testMatrixVectorMultiplication();
                break;
            case 4:
                demoFromMethodology();
                break;
            case 0:
                cout << "До свидания!\n";
                break;
            default:
                cout << "Неверный выбор!\n";
        }
    } while (choice != 0);
    
    return 0;
}