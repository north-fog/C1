
#include "Tbitfield.h"

// Получить индекс элемента в массиве pMem для бита с номером n
// (используем сдвиг вправо на 5 бит вместо деления на 32)
int TBitField::GetMemIndex(const int n) const
{
    return n >> 5;
}

// Получить битовую маску для доступа к биту с номером n
// (n & 31) эквивалентно (n % 32)
TELEM TBitField::GetMemMask(const int n) const
{
    return 1 << (n & 31);
}

// Установить бит n в 1
void TBitField::SetBit(int n)
{
    if (n >= 0 && n < BitLen) {
        // Делим на 32, а не на sizeof(TELEM)*8, что не совсем корректно
        // но работает если TELEM = unsigned int = 32 бита
        pMem[n / 32] |= (1 << (n % 32));
    }
    // Должна быть проверка корректности, но кода обработки ошибки нет
}

// Установить бит n в 0
void TBitField::ClearBit(int n)
{
    if (n >= 0 && n < BitLen) {
        pMem[n / 32] &= ~(1 << (n % 32));
    }
}

// Получить значение бита n
bool TBitField::GetBit(int n) const
{
    bool res = false;
    if (n >= 0 && n < BitLen) {
        res = (pMem[n / 32] & (1 << (n % 32))) != 0;
    }
    return res;
}

// Оператор присваивания
TBitField& TBitField::operator=(const TBitField& bf)
{
    if (this != &bf) { // Проверка на самоприсваивание
        BitLen = bf.BitLen;
        if (MemLen != bf.MemLen) {
            delete[] pMem;
            MemLen = bf.MemLen;
            pMem = new TELEM[MemLen];
        }
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

// Сравнение на равенство (возвращает int, должен возвращать bool)
int TBitField::operator==(const TBitField& bf)
{
    int res = 1;
    if (BitLen != bf.BitLen) {
        res = 0;
    }
    else {
        for (int i = 0; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i]) {
                res = 0; 
                break;
            }
        }
    }
    return res;
}

// Побитовое И (пересечение)
TBitField TBitField::operator&(const TBitField& bf)
{
    // Определяем минимальную длину
    int minBitLen = (BitLen < bf.BitLen) ? BitLen : bf.BitLen;
    TBitField tmp(minBitLen);
    
    // Определяем минимальную длину памяти
    int minMemLen = (MemLen < bf.MemLen) ? MemLen : bf.MemLen;
    
    // Применяем операцию И к общей части
    for (int i = 0; i < minMemLen; i++) {
        tmp.pMem[i] = pMem[i] & bf.pMem[i];
    }
    
    // Остальные биты остаются нулевыми (из-за конструктора)
    // Но нужно обнулить оставшиеся элементы, если они есть
    // В текущей реализации это уже сделано в конструкторе
    
    return tmp;
}

// Побитовое ИЛИ (объединение)
TBitField TBitField::operator|(const TBitField& bf)
{
    // Определяем максимальную длину
    int maxBitLen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField tmp(maxBitLen);
    
    // Определяем минимальную длину памяти
    int minMemLen = (MemLen < bf.MemLen) ? MemLen : bf.MemLen;
    
    // Применяем операцию ИЛИ к общей части
    for (int i = 0; i < minMemLen; i++) {
        tmp.pMem[i] = pMem[i] | bf.pMem[i];
    }
    
    // Копируем оставшуюся часть из большего операнда
    if (MemLen > bf.MemLen) {
        for (int i = bf.MemLen; i < MemLen; i++) {
            tmp.pMem[i] = pMem[i];
        }
    }
    else if (bf.MemLen > MemLen) {
        for (int i = MemLen; i < bf.MemLen; i++) {
            tmp.pMem[i] = bf.pMem[i];
        }
    }
    
    return tmp;
}

// Конструктор по умолчанию
TBitField::TBitField()
{
    BitLen = 0;
    MemLen = 0;
    pMem = new TELEM[MemLen]; // Создает массив нулевой длины (не проблема)
}

// Конструктор с заданной длиной
TBitField::TBitField(int len) : BitLen(len)
{
    // Вычисляем количество элементов TELEM для хранения len бит
    // (len + 31) >> 5 эквивалентно ceil(len/32)
    MemLen = (len + 31) >> 5;
    pMem = new TELEM[MemLen];
    
    // Проверка pMem != NULL устарела - new бросает исключение при ошибке
    // Убираем проверку и просто инициализируем
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

// Конструктор копирования
TBitField::TBitField(const TBitField& bf)
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

// Деструктор
TBitField::~TBitField()
{
    delete[] pMem;
}

// Получить длину битового поля
int TBitField::getlen() const
{
    return BitLen;
}

// Оператор вывода в поток
std::ostream& operator<<(std::ostream& out, const TBitField& bf)
{
    for (int i = 0; i < bf.BitLen; i++) {
        if (bf.GetBit(i)) {
            out << '1';
        }
        else {
            out << '0';
        }
    }
    return out;
}

// Оператор ввода из потока (ИСПРАВЛЕН)
std::istream& operator>>(std::istream& is, TBitField& bf)
{
    const int maxsize = 100;
    char buffer[maxsize];
    int len = 0;
    char c;
    
    // Считываем строку символов '0' и '1'
    while ((is.get(c) && c != '\n') && (len < maxsize - 1)) { // Исправлено: is вместо std::cin
        if (c == '0' || c == '1') {
            buffer[len] = c;
            len++;
        }
        else if (c == '\n') {
            break;
        }
        else {
            // Пропускаем некорректные символы или прерываем ввод
            break;
        }
    }
    
    // Добавляем завершающий нуль-символ
    buffer[len] = '\0';
    
    // Если длина не совпадает, создаем новое битовое поле
    if (bf.BitLen != len) {
        TBitField newbf(len);
        bf = newbf;
    }
    
    // Устанавливаем биты согласно введенным символам
    for (int i = 0; i < len; i++) { // Исправлено: i < len вместо i < bf.BitLen
        if (buffer[i] == '0') {
            bf.ClearBit(i);
        }
        else if (buffer[i] == '1') {
            bf.SetBit(i);
        }
    }
    
    return is;
}