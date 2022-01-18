#include "coordinate_system_panel.h"
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QPushButton>

coordinate_system_panel::coordinate_system_panel(QWidget *parent) : QWidget(parent)
{
    QLabel("X^(2/3)+Y^(2/3)=A^(2/3)");
    QLabel *value_division_x = new QLabel("Цена деления x");
    div_x = new QSpinBox;
    div_x->setRange(1, 10000);
    div_x->setSingleStep(5);
    div_x->setValue(1);

    QLabel *value_division_y = new QLabel("Цена деления y");
    div_y = new QSpinBox;
    div_y->setRange(1, 10000);
    div_y->setSingleStep(5);
    div_y->setValue(1);

    QLabel *value_param = new QLabel("Параметр a");
    param = new QDoubleSpinBox;
    param->setDecimals(3);
    param->setRange(0.001, 10000);
    param->setSingleStep(1);
    param->setValue(1);

    plus = new QPushButton("+", this);

    minus = new QPushButton("-", this);

    QVBoxLayout *lout = new QVBoxLayout;
    lout->addWidget(value_division_x);
    lout->addWidget(div_x);
    lout->addWidget(value_division_y);
    lout->addWidget(div_y);
    lout->addWidget(value_param);
    lout->addWidget(param);
    lout->addWidget(plus);
    lout->addWidget(minus);
    lout->addStretch();
    setLayout(lout);

    connect(div_x, SIGNAL(valueChanged(int)),
            this, SIGNAL(div_x_changed(int)));
    connect(div_y, SIGNAL(valueChanged(int)),
            this, SIGNAL(div_y_changed(int)));
    connect(param, SIGNAL(valueChanged(double)),
            this, SIGNAL(param_changed(double)));
    connect(plus, SIGNAL(clicked(bool)),
            this, SIGNAL(plus_scale(bool)));
    connect(minus, SIGNAL(clicked(bool)),
            this, SIGNAL(minus_scale(bool)));
}

void coordinate_system_panel::set_div_x(const int &x) {
    div_x->setValue(x);
}

void coordinate_system_panel::set_div_y(const int &y) {
    div_y->setValue(y);
}

int coordinate_system_panel::division_x() const {
    return div_x->value();
}

int coordinate_system_panel::division_y() const {
    return div_y->value();
}

double coordinate_system_panel::parametr() const {
    return param->value();
}
