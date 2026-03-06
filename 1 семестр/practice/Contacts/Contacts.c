#include <stdio.h>      //Билиоткека ввода вывода 
#include <locale.h>     //Билиоткека локализации
#include <stdlib.h>     //Билиоткека основыне функции   
#include <Windows.h>    //Билиоткека Windows
#include <conio.h>
#include < string.h >

FILE *file;
char str[1000];
char text[50];
char *istr;

//Помощь
void help()
{
    printf("0-выйти из прогграммы\n");
    printf("1-Сделать новую запимь\n");
    printf("2-Вывести список контактов\n");
    printf("3-Поиск  контакта по полному номеру телефона\n");
    printf("4-удалить выбраный контакт\n");
}

//Помощь структура контакта
struct contact
{
    char number[20];
    char f_name[20];
    char l_name[20];
    char patronymic[20];
    char email[40];
    char organization[20];
    char post[20]; 
    int activate;

};

//Создание структур
struct contact info[100];

//Ввод с проверкой или без 
void input_s(char text[],int check, const char name[])
{      

    char ch[]="";
    if(check==1)
    {
    printf("%s",name);
    gets(text, 50);
    while(strcmp(text,ch)==0)
    {
        printf("Вы ничего не ввели:");
        gets(text, 50);
    }

    }
    else
    {   
        printf("%s",name);
        gets(text, 50);
        if (strcmp(text,ch)==0)
        {
            strcpy(text, " ");
        }
    }

}

//Ввод нового контакта
void input_p(int count)
{   
    input_s(text,1,"Введите номер телефона: ");
    strcpy(info[count].number, text);
    input_s(text,1,"Ведите имя: ");
    strcpy(info[count].f_name, text);
    input_s(text,1,"Ведите фамилию: ");
    strcpy(info[count].l_name, text);
    input_s(text,0,"Ведите отчество: ");
    strcpy(info[count].patronymic, text); 
    info[count].activate =1;

}
//Поиск контакта по полнолму номеру телефона
int search(int count)
{
    printf("Введите номер телефона: ");
    scanf("%s",text);
    for(int i=0;i<count;i++)
    {
        if (strcmp(text,info[i].number)==0)
        {
            printf("%s ",info[i].f_name);
            printf("%s ",info[i].l_name);
            printf("%s ",info[i].patronymic);
            printf("%s\n",info[i].number);
            return i;
        }
    }
    printf("Такого контакта нет");
    return -1;
}
//Чтение файла 
int read_file(int count)
{
    file = fopen("test.csv", "r");
    while (fgets(str, sizeof(str), file) != NULL)
        {
        istr = strtok (str,";");
        strcpy(info[count].number, istr);
        istr = strtok (NULL,";");
        strcpy(info[count].f_name, istr);
        istr = strtok (NULL,";");
        strcpy(info[count].l_name, istr);
        istr = strtok (NULL,"\n"); 
        strcpy(info[count].patronymic, istr);
        info[count].activate =1;
        count++;
        }
    return count;
}


void main()
{
    setlocale(LC_ALL, "rus");   //Локализация
    SetConsoleCP(1251);         //Установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251);
    int answer;
    char cp[]="111";
    char ch;
    int count=0;
    int cont;

    help();
    count = read_file(count);
    do
    {
    printf("Выберите действие:(9-помощь) ");
    scanf("%d",&answer);
    while(ch = getchar() != '\n' );    
    switch (answer)
    {
    case 1:
        input_p(count);
        count++;
        break;
    case 2:
        int *arr = (int*)malloc(count * sizeof(int));
        
        for(int i=0;i<count;i++)
        {
            int l=arr[i];
            printf("%s ",info[l].f_name);
            printf("%s ",info[l].l_name);
            printf("%s ",info[l].patronymic);
            printf("%s\n",info[l].number);
        }
        break;
    case 3:
        cont = search(count);
        break;
    case 4:
        printf("Удалить выбраного пользователя?:");
        int answer2;
        scanf("%d",&answer2);
        if(answer2==1)
        {
        info[cont].activate=0;
        }
        break;
    case 9:
        help();
        break;
    }
    }while(answer!=0);
    file = fopen("test.csv", "w");
    for(int i=0; i<count;i++)
    {
        if(info[i].activate==1)
        {
        fprintf(file, "%s;", info[i].number);
        fprintf(file, "%s;", info[i].f_name);
        fprintf(file, "%s;", info[i].l_name);
        fprintf(file, "%s\n", info[i].patronymic);
        }
    }
    fclose(file);
}