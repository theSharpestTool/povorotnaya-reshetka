#include "cells.h"

Cells::Cells(QWidget *parent) : QWidget(parent)
{
   //Установка начального размера
   n = 5;
   build();
}

void Cells::recieve_size(int size)
{
    //Изменение размера
    destroy();
    n = size;
    build();
}

void Cells::build()
{
    cell_group = new QButtonGroup;
    cell_group->setExclusive(false);
    base = new QGridLayout;
    cells = new int* [n];
    for(int i = 0; i < n; i++)
        cells[i] = new int [n];

    //Заполнение контейнера переключателей
    int all_cells = n*n;
    for(int i = 0; i < all_cells; i++)
    {
        QPushButton* cel = new QPushButton;
        cel->setCheckable(true);
        cel->setFixedSize(40, 40);
        cell_group->addButton(cel, i);
    }

    //Отключение центрального переключателя, если размер решетки нечетній
    if(n%2 != 0)
        cell_group->button((n/2*n)+(n/2%n))->setDisabled(true);

    //Связи и компоновка
    connect(cell_group, SIGNAL(buttonToggled(int,bool)), this, SLOT(cell_toggled(int,bool)));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            base->addWidget(cell_group->button((i*n)+(j%n)), i, j);

    setLayout(base);
    adjustSize();
}

void Cells::destroy()
{
    //Очистка слоя с кнопками
    while (QLayoutItem* item = base->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    delete base;
    delete cell_group;
}

void Cells::cell_toggled(int location, bool checked)
{
    //Заполнение массива состояния переключателей
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cells[i][j] = 0;
    //Двойка обозначает активированный переключатель
    cells[location/n][location%n] = 2;

    turn();

    //Отключение переключателей, которые будут перекрыты выбранным переключателем
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            //Единица обозначает переключатель, который будет перекрыт
            if(cells[i][j] == 1)
                cell_group->button((i*n)+(j%n))->setDisabled(checked);

    emit send_hole(location);
}

void Cells::turn()
{
    //3 поворота
    for(int t = 0; t < 3; t++)
    {
        //Временный массив для поворота
        int** temp = new int* [n];
        for(int i = 0; i < n; i++)
            temp[i] = new int [n];

        //Заполнение временного массива
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
            {
                temp[j][n-1-i] = cells[i][j];
                if(cells[i][j] == 2)
                    temp[j][n-1-i] = 1;
            }

        //Обновление основоного массива
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(cells[i][j] == 0 || cells[i][j] == 2)
                    cells[i][j] = temp[i][j];
    }
}
