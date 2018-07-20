#include "input_line.h"

Input_line::Input_line(QWidget *parent) : QWidget(parent)
{
    //Выделение памяти
    holla = new QLabel("<H2><CENTER>ENCODER</CENTER></H2>");
    line = new QLineEdit;
    e_button = new QPushButton("ENCRYPT");
    d_button = new QPushButton("DECRYPT");
    l_button = new QPushButton("ENG");
    size_changer = new QComboBox;

    //Добавление элементов в объект size_changer
    QStringList variants;

    for(int i = 5; i <= 10; i++)
    {
        QString str = QString::number(i);
        str += " x ";
        str += QString::number(i);
        variants << str;
    }
    size_changer->addItems(variants);

    //Связи и компоновка
    connect(e_button, SIGNAL(clicked()), this, SLOT(e_clicked()));
    connect(d_button, SIGNAL(clicked()), this, SLOT(d_clicked()));
    connect(l_button, SIGNAL(clicked()), this, SLOT(l_clicked()));
    connect(size_changer, SIGNAL(activated(int)), this, SLOT(s_changed(int)));

    QHBoxLayout* lay2 = new QHBoxLayout;
    lay2->addWidget(line);
    lay2->addWidget(l_button);
    lay2->addWidget(e_button);
    lay2->addWidget(d_button);

    QVBoxLayout* base = new QVBoxLayout;
    base->addWidget(holla);
    base->addLayout(lay2);
    base->addWidget(size_changer);

    setLayout(base);
}


//Передача текста и размера
void Input_line::e_clicked()
{
    emit send_e_text(line->text());
}

void Input_line::d_clicked()
{
    emit send_d_text(line->text());
}

void Input_line::l_clicked()
{
    if(l_button->text() == "ENG")
        l_button->setText("RU");
    else
        l_button->setText("ENG");
    emit send_l_change();
}

void Input_line::s_changed(int size)
{
    emit send_size(size+5);
    adjustSize();
}
