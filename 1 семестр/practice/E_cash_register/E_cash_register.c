#include <stdio.h>      //Билиоткека ввода вывода 
#include <locale.h>     //Билиоткека локализации
#include <stdlib.h>     //Билиоткека основыне функции   
#include <Windows.h>    //Билиоткека Windows
/*
    Программа релаизует работу элетронной кассы
    Программа выполняет следующие операции
    1) «Сканировать» очередной товар,
    2) Вывести описание отсканированного товара,
    3) Добавить данные о товаре в чек,
    4) Сформировать чек за покупку,
    5) Рассчитать итоговую сумму к оплате.
*/


//Функция выводит подсказку о функциях программы
void hint()
{
    printf("___________________________________________________\n\n");
    printf("Функции програмы:\n");
    printf("1-Ввести штрихкод\n");
    printf("2-Вывести информацию о товаре\n");
    printf("3-Добавить товар в чек\n");
    printf("4-Вывсети промежуточный чек\n");
    printf("5-Вывести конечный чек и закончить работу\n");
    printf("___________________________________________________\n\n");
}


//Функция «сканирует» товар и проверяет есть ли шрихкод товара в массиве штрихкодов
int bacrcode_scan(int arr_length,char goods_barcode[][4])
{   
    char ch, barcode[4];    //Массив со штрихкодом пользователя
    do
    {
        printf("Введите штрихкод: ");
        scanf("%4c",&barcode);
        while(ch = getchar() != '\n' );     //Обнуление строки
        for(int i=0;i<arr_length;i++)
        {
            if(strncmp(barcode,goods_barcode[i],4)==0)
                return i;
        }
        printf("Такого штрихкода нет, поробуйте другой\n");
    }while(1);
}

//Функция выводит информации о отсканированом товаре
void goods_info(int sequence_num, char goods_barcode[][4],char goods_name[],int goods_cost,int goods_discount)
{   
    printf("Штрихкод: %s\n",goods_barcode[sequence_num]);
    printf("Наименование: %s\n",goods_name);
    printf("Цена: %d руб.\n",goods_cost);
    printf("Скидка, %%: %d%% \n",goods_discount);

}
//Функция выводит промежуточный чек или конечный чек
void cheque_goods(int arr_length, int quantity[],char goods_name[][100],int goods_cost[],int goods_discount[],int total)
{   
    printf("_____________________________________________________________________________________\n");
    printf("Наименование\tЦена за единицу товара, руб.\tКоличество\tОбщая стоимость, руб.\n");
    printf("______________________________________________________________________________________\n");

    int total_cost_goods;   //Общая стоимость одного товара без скидки
    int cost_cheque=0;      //Общая стоимость всех товара без скидки
    int discount=0;         //Общая скидка на все товары

//Вывод промежуточного чека
    for(int i=0;i<arr_length;i++)
    {
        if(quantity[i]!=0)
        {
            total_cost_goods =goods_cost[i] * quantity[i];  
            printf("%s\t\t%d\t\t\t\t%d\t\t%d\n",goods_name[i],goods_cost[i],quantity[i],total_cost_goods);
            discount += (goods_cost[i] * goods_discount[i] * quantity[i])/100;
            cost_cheque += total_cost_goods;     
        }
    }

//Вывод доп информации если выбран конечный чек
    if(total)
    {
        printf("______________________________________________________________________________________\n\n");
        printf("Всего: %d руб.\n",cost_cheque);
        printf("Скидка: %d руб.\n",discount);
        printf("Итого со скидкой: %d руб.\n",cost_cheque-discount);
        printf("______________________________________________________________________________________\n\n");
    }
}



void main()
{
setlocale(LC_ALL, "rus");   //Локализация
SetConsoleCP(1251);         //установка кодовой страницы win-cp 1251 в поток ввода
SetConsoleOutputCP(1251);

//Массивы с инормацией о товаре
char goods_name[][100]  = {"Рыба","Мясо","Яйца","Сок","Мука"};      //Название
char goods_barcode[][4] = {"1234","1111","1212","6788","3333"};     //Штрихкод
int goods_cost[]        = {90,80,100,120,33};                       //Цена за единицу товара
int goods_discount[]    = {10,20,30,50,2};                          //Скидка на товар

//Массив количества товаров
int quantity[]= {0,0,0,0,0};                                        

int sequence_num;   //Порядкое число товара в массиве  
int answer;         //Ответ пользователя
int resume;         //Переменая для продолжения работы 

//Переменая длины  массивов с товарами
int arr_length = sizeof(goods_barcode)/sizeof(goods_barcode[0]);
for(int i=0;i<arr_length;i++)
{
    quantity[i]=0;
}

do
{   
    hint();    
    int total=0;    //Вывод конечного чека    
    char ch;
    int answer,count=0;

    do
    {
        printf("Что вы хотите сделать? (Подсказка - введите 0))\n");
        scanf("%d",&answer);
        while(ch = getchar() != '\n' );     //Обнуление строки

        if(answer==0)        //Вывести подсказку для пользователя
        {
            hint();
        }
        else if(answer==1)  //Ввести штрихкод  
        {
            sequence_num=bacrcode_scan(arr_length, goods_barcode);
        }
        else if(answer==2)  //Вывести инфомацию о товаре
        {
            goods_info(sequence_num, goods_barcode ,goods_name[sequence_num], goods_cost[sequence_num], goods_discount[sequence_num]);
        }
        else if(answer==3)  //Добавить товар в чек
        {
            quantity[sequence_num]++;
            count++;
        }
        else if(answer==4)  //Вывести промежуточный чек
        {   
            if(count!=0)
            { 
                cheque_goods(arr_length, quantity, goods_name, goods_cost, goods_discount,total);
            }
            else
            {
                printf("Чек пустой\n");
            }
        }
        else if(answer==5)  //Вывод конечного чека
        {
            if(count!=0)
            { 
                total=1;
                cheque_goods(arr_length, quantity, goods_name, goods_cost, goods_discount,total);
            }
            else
            {
                printf("Чек пустой\n");
            }                                 
        }
        else
        {   
            printf("Некоректный ввод, ввидите заново\n");
        }
    }while((answer!=5)||(count==0));    //Вывод конечного чека

    //Обнуление количества товаров
    for(int i=0;i<arr_length;i++)
    {
        quantity[i]=0;
    }


    printf("Обслужить следущего посететеля? 1-Да, 0-Нет\n");
    scanf("%d",&resume);
    while(ch = getchar() != '\n' );

}while (resume);

printf("Конец работы");
getchar();  //Остановка программы до ввода любого символа
getchar();
}