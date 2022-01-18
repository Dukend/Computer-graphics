#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coordinate_system_panel.h"
#include "view.h"
#include <QDockWidget>
#include <QResizeEvent>
#include <QAction>
#include <QScrollArea>
#include <algorithm>
#include <utility>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    help_bool = true;
    coordinate_system_panel *cord = new coordinate_system_panel;
    QDockWidget *dock = new QDockWidget("Control coordinate system");
    dock->setWidget(cord);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    vw = new view;
    vw->set_cord_system_panel(cord);
    vw->setMinimumHeight(20);
    vw->setMinimumWidth(20);

    setCentralWidget(vw);

    QAction *quitAct = new QAction("&Quit", this);
    quitAct->setToolTip("Quit application");
    quitAct->setStatusTip("Closes the application");
    connect(quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(quitAct);

    QAction *panelAct = dock->toggleViewAction();
    panelAct->setStatusTip("Toggle panel");

    QMenu *viewMenu = menuBar()->addMenu("&View");
    viewMenu->addAction(panelAct);

    connect(cord, SIGNAL(div_x_changed(int)),
            this, SLOT(redrawOnValueChanged(int)));
    connect(cord, SIGNAL(div_y_changed(int)),
            this, SLOT(redrawOnValueChanged(int)));
    connect(cord, SIGNAL(param_changed(double)),
            this, SLOT(redrawOnValueChanged(double)));
    connect(cord, SIGNAL(plus_scale(bool)),
            this, SLOT(plusScale(bool)));
    connect(cord, SIGNAL(minus_scale(bool)),
            this, SLOT(minusScale(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::redrawOnValueChanged(int) {
    vw->update();
}

void MainWindow::redrawOnValueChanged(double) {
    vw->update();
}

void MainWindow::plusScale(bool) {
    auto s = vw->get_step();
    if (s.first >= 80 || s.second >= 80) {
        vw->set_division(vw->cord_system()->division_x() / 2, vw->cord_system()->division_y() / 2);
        return;
    }
    if (help_bool) {
        vw->set_step(s.first + 10, s.second + 10);
        help_bool = false;
    } else {
        vw->set_division(vw->cord_system()->division_x() / 2, vw->cord_system()->division_y() / 2);
        help_bool = true;
    }
    vw->update();
}

void MainWindow::minusScale(bool) {
    auto s = vw->get_step();
    if (s.first <= 30 || s.second <= 30) {
        vw->set_division(vw->cord_system()->division_x() * 2, vw->cord_system()->division_y() * 2);
        return;
    }
    if (!help_bool) {
        vw->set_step(s.first - 10, s.second - 10);
        help_bool = true;
    } else {
        vw->set_division(vw->cord_system()->division_x() * 2, vw->cord_system()->division_y() * 2);
        help_bool = false;
    }
    vw->update();
}
