#ifndef COMBINED_H
#define COMBINED_H

#include <QtWidgets>
#include "input_line.h"
#include "cells.h"
#include "output_table.h"
#include "encoder.h"

class Combined : public QWidget
{
    Q_OBJECT

private:
    Input_line* inp;//Объект для ввода текста и изменения размера решетки
    Cells* cll;//Объект для задавания решетки
    Output_table* out;//Объект для вывода зашифрованного текста
    Encoder* enc;//Объект, выполняющий шифрование текста
    QLineEdit* lin;//Объект для вывода текста в строку

public:
    explicit Combined(QWidget *parent = 0);

public slots:
    void adjust();//Изменение размеров окна
};

#endif // COMBINED_H
