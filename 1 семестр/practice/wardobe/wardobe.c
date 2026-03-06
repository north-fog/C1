#include <stdio.h>   // Библиотека ввода-вывода
#include <locale.h>  // Библиотека локализация
#include <math.h>    // Библиотека основных математических функций 
#include <string.h>  // Библиотека работы со строками 

/*
    Программа берёт данные о высоте, глУбИне и ширине шкафа и считает его массу   
*/

//проверка ввода



void main()
{

    setlocale(LC_CTYPE, "Ru_RU.UTF-8"); //локализация
    
    int d_DVP = 550;    //плотность ДВП
    int d_DSP = 650;    //плотность ДСП
    int d_pine = 520;   //полтность дерева (сосны)
    float height, wide, deep; //Высота, ширина, глуина

    float weight_b_w, weight_s_w, weight_tb_c, weight_d, weight_shelves; //вес частей шкафа
    /*
    weight_b_w    - (weight back wall) вес задней стенки
    weight_s_w    - (weight side wall) Вес боковой стенки
    weight_tb_c   - (weight top and bottom cover) верхняя и нижняя крышка
    weight_d      - (weight door) вес дверей
    weight_shelve - (weight shelve) вес полки
    */

    float final_weight; // Вес шкафа

    //Ввод данных
    char text[70] = "Введите высоту шкафа от 180 до 240 см: ";
    height = size_load(180, 220, text);
    strcpy(text, "Введите ширину шкафа от 80 до 120 см: "); 
    wide = size_load(80, 120, text);
    strcpy(text, "Введите глубину шкафа от 50 до 90 см: ");
    deep= size_load(50, 90, text);
    
    // Перевод из сантиметров в метры 
    height = height / 100;      // Высота
    wide = wide / 100;          // Ширина
    deep = deep / 100;          // Глубина
    
    // Рассчёт веса деталей
    weight_b_w = (height * wide  * 0.005) * d_DVP;          // Вес задней стенки
    weight_s_w = (( height * deep * 0.015) * d_DSP) * 2;    // Вес боковых стенок   
    weight_tb_c = (( wide * deep * 0.015) * d_DSP) * 2;     // Вес верхней и нижней крышки 
    weight_d = (height * wide  * 0.015) * d_pine;           // Вес дверей 
    weight_shelves = ( wide * deep * 0.015) * d_DSP;        // Вес одной полки

    // Рассчёт веса всего шкафа
    final_weight = weight_b_w + weight_s_w + weight_tb_c + weight_d +(trunc(height/40))*weight_shelves;
    
    // Вывод данных
    printf("\nВес шкафа равен: %3.3f%s",final_weight," кг");

    //остановка программы до ввода любого символа
    getchar();  
    getchar();
}


int size_load(int min, int max, char* text)
{
    int value; 
    while (1)
    {
        printf(text);                       
        scanf("%d", &value);            
        if(value >= min && value <= max)    
        {
            return value;                   
        }
        printf("Не верное значение, попробуйте снова!\n");  
    }
}