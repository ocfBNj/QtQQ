#include "UserLogin.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	UserLogin* userLogin = new UserLogin;
	userLogin->show();
	return a.exec();
}
