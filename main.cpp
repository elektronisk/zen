#include <iostream>
#include <QWidget>
#include <QApplication>
#include <QWidget>
#include <QSize>
#include "zen.h"

int main(int argc, char **argv) {
	QApplication app(argc,argv);
	app.setStyleSheet(QString("Tile { background: white }"));
	Zen *zen = new Zen();
	zen->show();
	return app.exec();
}
