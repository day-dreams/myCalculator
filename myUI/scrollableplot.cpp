#include "scrollableplot.hpp"
#include"myLabels.h"
#include"qcustomplot.h"
#include<qboxlayout.h>

scrollablePlot::scrollablePlot(QWidget * parent) : QWidget(parent) {
	ui.setupUi(this);
	ui.widgetForPlot->setLayout(new QVBoxLayout);
	plot = new QCustomPlot;
	plot->setInteractions(QCP::iRangeZoom|QCP::iRangeDrag);
	ui.widgetForPlot->layout()->addWidget(plot);
	
	ui.horizontalScrollBar->setRange(-500, 500);
	ui.verticalScrollBar->setRange(-500, 500);

	connect(ui.horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
	connect(ui.verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)));
	connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
	connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));

	plot->xAxis->setRange(0, 6, Qt::AlignCenter);
	plot->yAxis->setRange(0, 10, Qt::AlignCenter);

	setFixedSize(518, 316);

}

scrollablePlot::~scrollablePlot() {
	
}


void scrollablePlot::horzScrollBarChanged(int value)
{
	if (qAbs(plot->xAxis->range().center() - value / 100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
	{
		plot->xAxis->setRange(value / 100.0, plot->xAxis->range().size(), Qt::AlignCenter);
		plot->replot();
	}
}

void scrollablePlot::vertScrollBarChanged(int value)
{
	if (qAbs(plot->yAxis->range().center() + value / 100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
	{
		plot->yAxis->setRange(-value / 100.0, plot->yAxis->range().size(), Qt::AlignCenter);
		plot->replot();
	}
}

void scrollablePlot::xAxisChanged(QCPRange range)
{
	ui.horizontalScrollBar->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
	ui.horizontalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

void scrollablePlot::yAxisChanged(QCPRange range)
{
	ui.verticalScrollBar->setValue(qRound(-range.center()*100.0)); // adjust position of scroll bar slider
	ui.verticalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

void scrollablePlot::mouseDoubleClickEvent(QMouseEvent* event) {
	pictureSaveWidget *widget = new pictureSaveWidget(plot->toPixmap());
	widget->show();
}
