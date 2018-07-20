#include "encoder.h"

Encoder::Encoder(QObject *parent) : QObject(parent)
{
    n = 5;
    english = true;
}

void Encoder::recieve_size(int size)
{
    n = size;
    key.clear();
}

void Encoder::recieve_e_text(QString text)
{
    inp_text = text;
    //Проверка введенного текста на длину
    if(inp_text.size() > key.size()*4)
    {
        QMessageBox msg;
        msg.setText("The text is too long");
        msg.exec();
    }
    else
    {
        //Заполнение строки пробелами, если её размер меньше количества отверстий
        for(int i = 0; i < (key.size()*4 - inp_text.size()); i++)
            inp_text += " ";
        //Запуск шифрования
        encrypt();
    }
}

void Encoder::recieve_d_text(QString text)
{
    inp_text = text;

    //Проверка введенного текста на длину
    if(inp_text.size() > n*n)
    {
        QMessageBox msg;
        msg.setText("The text is too long");
        msg.exec();
    }
    else
    {
        //Заполнение строки пробелами, если её размер меньше таблицы
        for(int i = 0; i < (n*n - inp_text.size()); i++)
            inp_text += " ";

        //Запуск дешифрования
        decrypt();
    }
}

void Encoder::recieve_hole(int location)
{
    bool repeat = true;
    //Удаление соответствующего элемента с позицией, если пользователь выключит переключатель
    for(int i = 0; i < key.size(); i++)
        if(location == key[i])
        {
            key.remove(i);
            repeat = false;
        }

    //Добавление элемента с позицией
    if(repeat == true)
        key.push_back(location);
}

void Encoder::lang_change()
{
    english = !english;
}

void Encoder::encrypt()
{
    srand(time(0));

    key_table = new int* [n];
    for(int i = 0; i < n; i++)
        key_table[i] = new int [n];
    out_text = new QString* [n];
    for(int i = 0; i < n; i++)
        out_text[i] = new QString [n];

    //Преобразование вектора с позициями в двумерный массив
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            key_table[i][j] = 0;

    //Единица обозначает позицию отверстия на данном повороте
    for(int i = 0; i < key.size(); i++)
        key_table[key[i]/n][key[i]%n] = 1;

    int k = 0;//Индекс элемента строки для последовательного шифрования

    //4 итерации для каждой позиции решетки
    for(int t = 0; t < 4; t++)
    {
        //Заполнение массива с зашифрованным текстом
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
            {
                if(key_table[i][j] == 1)
                {
                   out_text[i][j] = inp_text[k];
                   k++;
                }
                else if(key_table[i][j] == 0)
                   out_text[i][j] = random_symbol();
            }
        turn();
    }

    out_text_str.clear();
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            out_text_str += out_text[i][j];

    emit send_text(out_text);
    emit send_text_line(out_text_str);
}

void Encoder::decrypt()
{   
    out_text = new QString* [n];
    for(int i = 0; i < n; i++)
        out_text[i] = new QString [n];
    key_table = new int* [n];
    for(int i = 0; i < n; i++)
        key_table[i] = new int [n];

    //Преобразование введонного текста в таблицу
    int k = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            out_text[i][j] = inp_text[k];
            k++;
        }

    //Преобразование вектора с позициями в двумерный массив
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            key_table[i][j] = 0;

    //Единица обозначает позицию отверстия на данном повороте
    for(int i = 0; i < key.size(); i++)
        key_table[key[i]/n][key[i]%n] = 1;

    out_text_str.clear();

    //4 итерации для каждой позиции решетки
    for(int t = 0; t < 4; t++)
    {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(key_table[i][j] == 1)
                   out_text_str += out_text[i][j];
        turn();
    }

    emit send_text(out_text);
    emit send_text_line(out_text_str);
}

QString Encoder::random_symbol()
{
    char symbol;
    QString str;
    if(english)
    {
        symbol = (char) (97 + qrand()%26);
        str = symbol;
    }
    else
    {
        QString arr[33] = {"а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н", "о", "п", "р", "с",
                           "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};
        str = arr[qrand()%33];
    }
    return str;
}

void Encoder::turn()
{
    //Временный массив для поворота
    int** temp = new int* [n];
    for(int i = 0; i < n; i++)
        temp[i] = new int [n];

    //Заполнение временного массива
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            temp[j][n-1-i] = key_table[i][j];

    //Заполнение основного массива
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            //Двойка обозначает позицию отверстия на предыдущих поворотах
            if(key_table[i][j] == 1)
                key_table[i][j] = 2;
            else if(key_table[i][j] == 0)
                key_table[i][j] = temp[i][j];
        }
}
