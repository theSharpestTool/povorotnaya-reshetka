#include "output_table.h"

Output_table::Output_table(QWidget *parent) : QWidget(parent)
{
    //Установка начального размера
    n = 5;
    build();
}

void Output_table::recieve_size(int size)
{
    //Изменение размера
    destroy();
    n = size;
    build();
}

void Output_table::build()
{
    //Заполнение вектора объектов, отображающих текст
    for(int i = 0; i < n*n; i++)
    {
        letter << new QLabel;
        letter[i]->setFixedSize(40, 40);
        letter[i]->setAlignment(Qt::AlignCenter);
        letter[i]->setFrameStyle(QFrame::Box | QFrame::Raised);
        letter[i]->setStyleSheet(QString("font-size: %1px").arg(15));
    }

    //Заполение слоя объектами
    base = new QGridLayout;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            base->addWidget(letter[(i*n)+(j%n)], i, j);

    setLayout(base);
    adjustSize();
}

void Output_table::destroy()
{
    //Очистка вектора с объектами
    letter.clear();
    //Очистка слоя
    while (QLayoutItem* item = base->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    delete base;
}

void Output_table::recieve_text(QString** text)
{
    //Установка текста элементам контейнера
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            letter[(i*n)+(j%n)]->setText(text[i][j]);
}
