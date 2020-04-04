#include "CCMainWindow.h"
#include "BasicWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	BasicWindow w;
	w.show();
	return a.exec();
}
