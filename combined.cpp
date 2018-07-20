#include "combined.h"

Combined::Combined(QWidget *parent) : QWidget(parent)
{
    inp = new Input_line;
    cll = new Cells;
    out = new Output_table;
    enc = new Encoder;
    lin = new QLineEdit;

    //Связи между объектами
    connect(inp, SIGNAL(send_size(int)), cll, SLOT(recieve_size(int)));
    connect(inp, SIGNAL(send_size(int)), out, SLOT(recieve_size(int)));
    connect(inp, SIGNAL(send_size(int)), enc, SLOT(recieve_size(int)));
    connect(inp, SIGNAL(send_size(int)), this, SLOT(adjust()));
    connect(inp, SIGNAL(send_l_change()), enc, SLOT(lang_change()));
    connect(inp, SIGNAL(send_e_text(QString)), enc, SLOT(recieve_e_text(QString)));
    connect(inp, SIGNAL(send_d_text(QString)), enc, SLOT(recieve_d_text(QString)));
    connect(cll, SIGNAL(send_hole(int)), enc, SLOT(recieve_hole(int)));
    connect(enc, SIGNAL(send_text(QString**)), out, SLOT(recieve_text(QString**)));
    connect(enc, SIGNAL(send_text_line(QString)), lin, SLOT(setText(QString)));

    //Компоновка объектов в одном окне
    QHBoxLayout* spreadsheets = new QHBoxLayout;
    spreadsheets->addWidget(cll);
    spreadsheets->addWidget(out);

    QVBoxLayout* base = new QVBoxLayout;
    base->addWidget(inp);
    base->addLayout(spreadsheets);
    base->addWidget(lin);

    setLayout(base);
    setWindowTitle("Encoder");
}

void Combined::adjust()
{
    adjustSize();
    adjustSize();
}


