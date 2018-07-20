#ifndef CELLS_H
#define CELLS_H

#include <QtWidgets>

class Cells : public QWidget
{
    Q_OBJECT

private:
    QButtonGroup* cell_group;//Контейнер переключателей, образующих решетку
    int n;//Размер решетки
    int** cells;//Двумерный массив состояния переключателей
    QGridLayout* base;//Компоновка переключателей в виде квадрата

public:
    explicit Cells(QWidget *parent = 0);
    void build();//Построение решетки
    void destroy();//Удаление решетки
    void turn();//Поворот решетки

signals:
    send_hole(int location);//Передача позиции активированного переключателя

public slots:
    void recieve_size(int size);//Приём размера
    void cell_toggled(int location, bool checked);//Включение переключателя
};

#endif // CELLS_H
