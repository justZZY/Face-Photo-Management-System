#include <QtWidgets/QApplication>
#include "Global.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SqlOperation *sqloperation = new SqlOperation();
	mainWindow = new FacerRecognize(sqloperation);
	mainWindow->show();
	return a.exec();
}
