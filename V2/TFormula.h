#pragma once
#include <iostream>

class TFormula {
  char* str;
public:
    TFormula();                                                                   //конструктор по умолчанию
    TFormula(char* _str);                                                         //конструктор с параметром
    ~TFormula();                                                                  //деструктор
    TFormula(const TFormula& _str);                                               //конструктор копирования
    TFormula operator=(const TFormula& _str);                                     //оператор присваивания
    int checkbrackets(int arr[], int& n);                                         //проверка корректности скобок
    friend std::ostream& operator<<(std::ostream& out, const TFormula& form);     //оператор вывод 
    char* Postfix();                                                              //преобразование формулы в постфиксную запись
    friend std::istream& operator>>(std::istream& in, TFormula& form);            //оператор ввода
    double calculate(int& r);                                                     //вычисление значения формулы
    bool checkoperant();                                                          //проверка на пропущеные операции
};

bool isdigit(char c);                                                             //проверка на цифру
bool isop(char c);                                                                //проверка на оперант
bool isbracket(char c);                                                           //проверка на скобку
int priority(char op);                                                            //проверка приоритета операции