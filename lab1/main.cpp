// BY DUKEND
// X^(2/3)+Y^(2/3)=A^(2/3)
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.resize(800, 800);
	w.show();

	return a.exec();
}
