#include <iostream>
#include "TSet.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    
    int t, n, m, k, count;
    t=1;
    while( t>0){
    cout << "Тестирование программ поддержки множества" << endl;
    cout << "              Решето Эратосфена" << endl;
    cout << "Введите верхнюю границу целых значений - ";
    cin >> n;
    
    // Создаем множество размером n+1 (для чисел от 0 до n)
    TSet s(n + 1);
    
    // Заполнение множества числами от 2 до n
    for (m = 2; m <= n; m++) {
        s.InsElem(m);
    }
    
    // Решето Эратосфена
    for (m = 2; m * m <= n; m++) {
        // если m в множестве, удаляем все кратные
        if (s.isMember(m)) {
            for (k = 2 * m; k <= n; k += m) {
                if (s.isMember(k)) {
                    s.DelElem(k);
                }
            }
        }
    }
    
    // Оставшиеся в s элементы - простые числа
    cout << endl << "Печать множества некратных чисел" << endl;
    cout << s << endl;
    
    cout << endl << "Печать простых чисел" << endl;
    count = 0;
    int perLine = 0;
    
    for (m = 2; m <= n; m++) {
        if (s.isMember(m)) {
            cout <<" "<< m;
            count++;
            perLine++;
            if (perLine % 10 == 0) {
                cout << endl;
            }
        }
    }
    
    if (perLine % 10 != 0) {
        cout << endl;
    }
    
    cout << "В первых " << n << " числах " << count << " простых" << endl;
    
    cout << "хотите повторить тест(1 - да, 0 - нет)?:";
    cin >> t;
}
}