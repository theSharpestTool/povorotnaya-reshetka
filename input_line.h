#ifndef INPUT_LINE_H
#define INPUT_LINE_H

#include <QtWidgets>

class Input_line : public QWidget
{
    Q_OBJECT

private:
    QLabel* holla;//Приветствие
    QLineEdit* line;//Для ввода текста
    QPushButton* e_button;//Для запуска шифрования
    QPushButton* d_button;//Для запуска расшифровки
    QPushButton* l_button;
    QComboBox* size_changer;//Для выбора размера

public:
    Input_line(QWidget *parent = 0);

signals:
    //Передача текста и размера в другие объекты
    send_e_text(QString inp_text);
    send_d_text(QString inp_text);
    send_l_change();
    send_size(int size);

public slots:
    void e_clicked();
    void d_clicked();
    void l_clicked();
    void s_changed(int size);
};

#endif // INPUT_LINE_H
