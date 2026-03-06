#include "Tset.h"

// Конструктор: создает пустое множество с заданной максимальной мощностью (размером универсума)
TSet::TSet(int mp) :maxpower(mp), bitfield(mp)
{
}

// Конструктор копирования: создает копию существующего множества
TSet::TSet(const TSet& s) :maxpower(s.maxpower), bitfield(s.bitfield)
{
}

// Конструктор из битового поля: создает множество на основе существующего битового поля
TSet::TSet(const TBitField& bf) : bitfield(bf)
{
 maxpower = bitfield.getlen(); // Размер универсума = длина битового поля
}

// Оператор преобразования: преобразует TSet в TBitField
TSet::operator TBitField()
{
 TBitField tmp(this->bitfield);
 return tmp;
}

// Добавление элемента в множество
void TSet::inslen(int n)
{
 bitfield.SetBit(n); // Устанавливаем соответствующий бит в 1
}

// Удаление элемента из множества
void TSet::dellen(const int n)
{
 bitfield.ClearBit(n); // Сбрасываем соответствующий бит в 0
}

// Проверка принадлежности элемента множеству
bool TSet::isMember(int n) const
{
 return bitfield.GetBit(n); // Возвращает true, если бит установлен
}

// Оператор сравнения на равенство множеств (НО: реализован НЕПРАВИЛЬНО!)
int TSet::operator==(const TSet& s)
{
 std::cout << bitfield << std::endl<< std::endl<< std::endl<< s.bitfield << std::endl;

 bool res = true;
 TBitField bitfili = bitfield & s.bitfield; // Пересечение
 TBitField bitfi = bitfield | s.bitfield;   // Объединение
 

 if (bitfili == bitfi) {
  res = false;
 }
 return res; 
}

// Оператор присваивания
TSet& TSet::operator=(const TSet& s)
{
 maxpower = s.maxpower;
 bitfield = s.bitfield;
 return *this;
}

// Объединение множеств (оператор +)
TSet TSet::operator+(const TSet& s)
{
 TSet res(bitfield | s.bitfield); // Использует побитовое ИЛИ битовых полей
 return res;
}

// Пересечение множеств (оператор *)
TSet TSet::operator*(const TSet& s)
{
 TSet res(bitfield & s.bitfield); // Использует побитовое И битовых полей
 return res;
}

// Оператор вывода в поток: выводит множество в формате {1, 3, 5}
std::ostream& operator<<(std::ostream& out, const TSet& s)
{
 out << '{';
 bool first = true;
 for (int i = 0; i < s.maxpower; i++) {
  if (s.isMember(i)) {
   if (!first) {
    out << ", ";
   }
   out << i;
   first = false;
  }
 }
 out << '}';
 return out;
}

// Оператор ввода из потока 
std::istream& operator>>(std::istream& is, TSet& s)
{
 const int maxsize = 200;
 int buffer[maxsize];
 int tmp;
 char c='1';
 //is >> c;
 

 while (c != '.') {
  std::cout << "num";
  is >> tmp;
  s.inslen(tmp);
  std::cout << "char"; 
  is >> c; // Ввод символа-разделителя
 }
 return is;
}