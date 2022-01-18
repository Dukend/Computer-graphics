#ifndef COORDINATE_SYSTEM_PANEL_H
#define COORDINATE_SYSTEM_PANEL_H

#include <QWidget>

class QSpinBox;
class QDoubleSpinBox;
class QPushButton;

class coordinate_system_panel : public QWidget
{
    Q_OBJECT
public:
    explicit coordinate_system_panel(QWidget *parent = nullptr);
    void set_div_x(const int &x);
    void set_div_y(const int &y);
    int division_x() const;
    int division_y() const;
    double parametr() const;
private:
    QSpinBox *div_x;
    QSpinBox *div_y;
    QDoubleSpinBox *param;
    QPushButton *plus;
    QPushButton *minus;
signals:
    void div_x_changed(int);
    void div_y_changed(int);
    void param_changed(double);
    void plus_scale(bool);
    void minus_scale(bool);
public slots:
};

#endif // COORDINATE_SYSTEM_PANEL_H
