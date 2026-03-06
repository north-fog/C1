#include "TBitField.h"
int TBitField::GetMemIndex(const int n) const {
	return n >> 5;
}

// Возвращает битовую маску для бита n (остаток от деления на 32)
TELEM TBitField::GetMemMask(const int n) const {
	return 1 << (n & 31);
}

// Конструктор: создает битовое поле длины len
TBitField::TBitField(int len) :BitLen(len) {
	// Вычисляем размер памяти в элементах TELEM (каждый по 32 бита)
	MemLen = (len + 31) >> 5;
	// Выделяем память
	pMem = new TELEM[MemLen];
	// Инициализируем все биты нулями
	if (pMem != nullptr) {
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = 0;
		}
	}
}

// Конструктор копирования: создает копию битового поля bf
TBitField::TBitField(const TBitField& bf) {
	// Копируем длину в битах
	BitLen = bf.BitLen;
	// Копируем длину в памяти
	MemLen = bf.MemLen;
	// Выделяем новую память
	pMem = new TELEM[MemLen];
	// Копируем данные из bf
	if (pMem != nullptr) {
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
}

// Деструктор: освобождает выделенную память
TBitField::~TBitField() {
	if (pMem != nullptr) {
		delete[] pMem;
	}
}

// Устанавливает бит n в 1 (если n в допустимых пределах)
void TBitField::SetBit(const int n) {
	if ((n >= 0) && (n < BitLen)) {
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
}

// Устанавливает бит n в 0 (если n в допустимых пределах)
void TBitField::ClrBit(const int n) {
	if ((n >= 0) && (n < BitLen)) {
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}
}

// Возвращает значение бита n (1 или 0)
int TBitField::GetBit(const int n) const {
	if ((n >= 0) && (n < BitLen)) {
		return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
	}
	return 0;
}

// Оператор присваивания: копирует битовое поле bf в текущий объект
TBitField&TBitField::operator=(const TBitField& bf) {
	// Копируем длину в битах
	BitLen = bf.BitLen;
	// Если размер памяти разный, перевыделяем память
	if (MemLen != bf.MemLen) {
		MemLen = bf.MemLen;
		if (pMem != nullptr) {
			delete[]pMem;
		}
		pMem = new TELEM[MemLen];
	}
	// Копируем данные из bf
	if (pMem != nullptr) {
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

// Оператор сравнения: проверяет равенство двух битовых полей
int TBitField::operator==(const TBitField& bf) {
	int res = 1;
	// Если разная длина в битах - не равны
	if (BitLen != bf.BitLen) { res = 0; }
	else {
		// Сравниваем содержимое памяти
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i]) {
				res = 0;
				break;
			}
		}
	}
	return res;
}

// Оператор И (побитовое И) для двух битовых полей
TBitField TBitField::operator&(const TBitField bf) {
	// Берем минимальную длину
	int min = BitLen;
	int mm = MemLen;
	if (bf.BitLen < min) {
		min = bf.BitLen;
		mm = bf.MemLen;
	}
	// Создаем временный объект минимальной длины
	TBitField tmp(min);
	// Применяем побитовое И к элементам массива
	for (int i = 0; i < mm; i++) {
		tmp.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return tmp;
}

// Оператор ИЛИ (побитовое ИЛИ) для двух битовых полей
TBitField TBitField::operator|(const TBitField bf) {
	// Берем максимальную длину
	int max = BitLen;
	if (bf.BitLen > max) {
		max = bf.BitLen;
	}
	// Создаем временный объект максимальной длины
	TBitField tmp(max);
	// Копируем данные из текущего объекта
	for (int i = 0; i < MemLen; i++) {
		tmp.pMem[i] = pMem[i];
	}
	// Применяем побитовое ИЛИ с элементами второго объекта
	for (int i = 0; i < bf.MemLen; i++) {
		tmp.pMem[i] |= bf.pMem[i];
	}
	return tmp;
}

// Оператор НЕ (побитовое отрицание) для битового поля
TBitField TBitField::operator~() {
	// Создаем объект такой же длины
	TBitField res(BitLen);
	// Применяем побитовое НЕ ко всем элементам
	for (int i = 0; i < MemLen; i++) {
		res.pMem[i] = ~pMem[i];
	}
	// Обнуляем лишние биты в последнем элементе (если BitLen не кратен 32)
	if (BitLen % 32 != 0) {
		int bit = BitLen % 32;
		TELEM mask = (1 << bit) - 1;
		res.pMem[MemLen - 1] &= mask;
	}
	return res;
}

// Возвращает длину битового поля в битах
int TBitField::GetLen() const{
	return BitLen;
}
