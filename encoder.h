#ifndef ENCODER_H
#define ENCODER_H

#include <QtWidgets>

class Encoder : public QObject
{
    Q_OBJECT

private:
    QString inp_text;//Введенный текст
    QVector<int> key;//Массив, содержащий позиции актвированных переключателей(отверстий)
    int n;//Размер решетки
    int** key_table;//Двумерный массив отверстий решетки
    QString** out_text;//Выводимый текст в виде таблицы
    QString out_text_str;//Выводимый текст в виде строки
    bool english;

public:
    explicit Encoder(QObject *parent = 0);
    void encrypt();//Шифрование
    void decrypt();//Дешифрование
    QString random_symbol();//Случайный символ для заполнения таблицы
    void turn();//Поворот решетки

signals:
    send_text(QString** enc_text);//Передача зашифрованного или расшифрованного текста таблицей
    send_text_line(QString enc_text_line);//Передача зашифрованного или расшифрованного текста строкой

public slots:
    //Приём разера, текста и позиции переключателя
    void recieve_size(int size);
    void recieve_e_text(QString text);
    void recieve_d_text(QString text);
    void recieve_hole(int location);
    void lang_change();
};

#endif // ENCODER_H
