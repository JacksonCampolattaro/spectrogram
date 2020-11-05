#include <QApplication>
#include "QtMainApplication.h"


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QtMainApplication gui;
	gui.show();
	return app.exec();
}
