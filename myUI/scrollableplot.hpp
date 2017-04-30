#pragma once
#ifndef SCROLLABLEPLOT_HPP
#define SCROLLABLEPLOT_HPP
#include"qcustomplot.h"
#include <QWidget>
#include "ui_scrollableplot.h"

class scrollablePlot : public QWidget {
	Q_OBJECT

public:
	QCustomPlot *plot;
	scrollablePlot(QWidget * parent = Q_NULLPTR);
	~scrollablePlot();
	void mouseDoubleClickEvent(QMouseEvent* event);
private:
	Ui::scrollablePlot ui;

private slots:
	void horzScrollBarChanged(int value);
	void vertScrollBarChanged(int value);
	void xAxisChanged(QCPRange range);
	void yAxisChanged(QCPRange range);

};

#endif // SCROLLABLEPLOT_HPP