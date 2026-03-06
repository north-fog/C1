#pragma once
#include <iostream>
#include <string>
#include <algorithm>

typedef unsigned int TELEM;

class TBitField
{
private:
    int BitLen;
    TELEM* pMem;
    int MemLen;
    
    int GetMemIndex(const int n) const;
    TELEM GetMemMask(const int n) const;
    
public:
    TBitField(int len);
    TBitField(const TBitField& bf);
    ~TBitField();
    
    int GetLen() const;
    void SetBit(const int n);
    void ClrBit(const int n);
    int GetBit(const int n) const;
    
    TBitField& operator=(const TBitField& bf);
    int operator==(const TBitField& bf);
    TBitField operator&(const TBitField bf);
    TBitField operator|(const TBitField bf);
    TBitField operator~();
    
    friend std::ostream& operator<<(std::ostream& out, const TBitField& bf) {
        for (int i = 0; i < bf.BitLen; i++) {
            out << (bf.GetBit(i) ? '1' : '0');
        }
        return out;
    }
    
    friend std::istream& operator>>(std::istream& is, TBitField& bf) {
        std::string line;
        std::getline(is, line);
        
        // Удаляем пробелы из строки
        std::string clean;
        for (char c : line) {
            if (c == '0' || c == '1') {
                clean += c;
            }
            else if (c != ' ' && c != '\t') {
                // Если встретили недопустимый символ (не 0, не 1, не пробел)
                std::cout << "Ошибка: недопустимый символ '" << c << "'. Разрешены только 0 и 1." << std::endl;
                // Очищаем все биты и возвращаем пустое поле
                for (int i = 0; i < bf.BitLen; i++) {
                    bf.ClrBit(i);
                }
                return is;
            }
        }
        
        // Проверяем, достаточно ли символов
        if (clean.length() < bf.BitLen) {
            std::cout << "Предупреждение: введено меньше " << bf.BitLen 
                      << " символов. Недостающие биты установлены в 0." << std::endl;
        }
        else if (clean.length() > bf.BitLen) {
            std::cout << "Предупреждение: введено больше " << bf.BitLen 
                      << " символов. Лишние символы игнорируются." << std::endl;
        }
        
        // Очищаем все биты
        for (int i = 0; i < bf.BitLen; i++) {
            bf.ClrBit(i);
        }
        
        // Устанавливаем биты из очищенной строки
        int n = std::min(bf.BitLen, (int)clean.length());
        for (int i = 0; i < n; i++) {
            if (clean[i] == '1') {
                bf.SetBit(i);
            }
        }
        
        return is;
    }
};