#pragma once

#include <iostream>
#include <cstring>

class TFormula {
    char* str;
    
public:
    TFormula();                                                                                   //Конструктор по умолчанию
    TFormula(const char* _str);                                                                   //Конструктор 
    TFormula(const TFormula& other);                                                              //Конструктор копирования
    ~TFormula();                                                                                  //Деструктор
    
    TFormula& operator=(const TFormula& other);                                                   //оператор присваивания
    
    //Методы....
    int checkbrackets(int arr[], int& n);                                                        //проверка скобок
    char* Postfix();                                                                             //перевод в постфиксную форму
    double calculate();                                                                          //нахождение  результата
    int checkbrackets(int arr[], int& n);
    bool checkoperant();
    //ввод и вывод
    friend std::ostream& operator<<(std::ostream& out, const TFormula& form);
    friend std::istream& operator>>(std::istream& in, TFormula& form);
    
    //вспомогательое получение строки
    const char* getString() const { return str ? str : ""; }
    
private:
    //методы копирования и проверки 
    void copyString(const char* source);                                                        
    bool validateExpression() const;
};

// Вспомогательные функции для работы с символами
bool isDigit(char c);                                                                           //проверка на цифру
bool isOperator(char c);                                                                        //проверка на операцией
bool isBracket(char c);                                                                         //проверка на скобку
bool isLetter(char c);                                                                          //проверка на букву и тд
int priority(char op);                                                                          //нахождение приоритета операций
bool isSpace(char c);                                                                           //проверка на пробел                

