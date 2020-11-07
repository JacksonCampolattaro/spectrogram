#include <QApplication>
#include "GraphGui.h"


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	GraphGui gui;
	gui.show();
	return app.exec();
}
