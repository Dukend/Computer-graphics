#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class view;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    view *vw;
    bool help_bool;
private slots:
    void redrawOnValueChanged(int);
    void redrawOnValueChanged(double);
    void plusScale(bool);
    void minusScale(bool);
};

#endif // MAINWINDOW_H
