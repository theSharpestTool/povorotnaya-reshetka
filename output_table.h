#ifndef OUTPUT_TABLE_H
#define OUTPUT_TABLE_H

#include <QtWidgets>

class Output_table : public QWidget
{
    Q_OBJECT

private:
    int n;//Размер решетки
    QVector<QLabel*> letter;//Контейнер объектов, отображающих текст
    QGridLayout* base;//Для отображения текста в виде квадрата

public:
    explicit Output_table(QWidget *parent = 0);
    void build();//Построение таблицы с текстом
    void destroy();//Удаление таблицы с текстом

public slots:
    //Прием размера и зашифрованного текста
    void recieve_size(int size);
    void recieve_text(QString** text);
};

#endif // OUTPUT_TABLE_H
