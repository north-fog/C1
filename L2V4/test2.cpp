#include <iostream> 
#include "Matrix.h" 
 
void main() 
{ 
  TMatrix<int> a(10), b(10), c(10); 
  int i, j, g; 
 
  setlocale(LC_ALL, "Russian"); 
  cout << "Тестирование программ поддержки треугольных матриц" << endl; 
  for (i = 0; i < 10; i++) 
    for (j = i; j < 10; j++ )  
    { 
      a(i, j) =  i * 10 + j; 
      b(i, j) = (i * 10 + j) * 100; 
    } 
  c = a + b; 
  cout << "Matrix a = " << endl << a << endl; 
  cout << "Matrix b = " << endl << b << endl; 
  cout << "Matrix c = a + b" << endl << c << endl; 
  cin >> g; 
}