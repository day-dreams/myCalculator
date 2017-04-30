#include"scrollableplot.hpp"
#include"encode.h"
#include "caculatorUIinWIdget.h"
#include"myLabels.h"
#include <QtWidgets/QApplication>
#include<qtimer.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	optionHelp.x = new pictureOptionWidget;
	QObject::connect(optionHelp.x->button, &QPushButton::clicked, &optionHelp, &pictureOptionHelp::sendSignal);
	
	caculatorUIinWIdget w;
	w.setWindowTitle("Tiny Matlab");
	w.show();	

	QTimer *timer = new QTimer;
	QObject::connect(timer, &QTimer::timeout, &w, &caculatorUIinWIdget::add_buffer_to_update);
	timer->start(100);

	return a.exec();
}


//int main(int argc, char **argv) {
//	QApplication a(argc, argv);
//	scrollablePlot plot;
//	plot.show();
//	return a.exec();
//}