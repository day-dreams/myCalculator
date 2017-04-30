#include"records.h"
#include"encode.h"
#include"ployFit.h"
#include"qcustomplot.h"
#include"parserMachine.h"
#include"base.h"
#include "caculatorUIinWIdget.h"
#include"myLabels.h"
#include"justForPictureOptionHelp.h"
#include<qvector.h>
#include<qlabel.h>
#include<string>
#include<map>
#include<set>
#include<fstream>	
#include<iostream>

using namespace std;

QCompleter *completer = new QCompleter();


bool lineFit(const QVector<double> &x, const QVector<double> &y, double &a, double &b, double &c);
QPixmap drawLinerFittingPix(QVector<double> &x, QVector<double> &y, double &a, double &b, double &c);
QCustomPlot* get_fitting_pixmap(vector<double>& x, vector<double> &y, int k,QCustomPlot* plot);

caculatorUIinWIdget::caculatorUIinWIdget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	leftWidget = new QWidget(this);
	ui.leftScrollArea->setWidget(leftWidget);
	ui.leftScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	leftWidget->setLayout(new QGridLayout(this));
	leftWidget->layout()->setMargin(0);
	leftWidget->layout()->setSpacing(0);

	for (int i = 0; i < 10; ++i) {
		leftWidget->layout()->addWidget(new QLabel(this));
	}

	rightWidget = new QWidget;
	ui.rightScrollArea->setWidget(rightWidget);
	ui.rightScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	rightWidget->setLayout(new QGridLayout);

	for (int i = 0; i < 1; ++i) {
		rightWidget->layout()->addWidget(new blankLabel(this));
	}

	ui.lineEdit->setFixedHeight(40);

	connect(ui.lineEdit, &QLineEdit::returnPressed, this, [&]() {
		on_new_input(ui.lineEdit->text());
		ui.lineEdit->clear();
	});

	connect(&optionHelp,&pictureOptionHelp::buttonClicked, this, &caculatorUIinWIdget::on_new_draw_command);

	stringList = new QStringList;
	for (auto &entry : moon::base_fun_priority) {
		(*stringList) << entry.first.c_str();
	}
	for (auto &entry : moon::base_op_priority)
		(*stringList) << entry.first.c_str();
	for (auto &entry : moon::custom_function)
		(*stringList) << entry.first.c_str();
	for (auto &entry : moon::custom_variable)
		(*stringList) << entry.first.c_str();
	listModel = new QStringListModel(*stringList);

	completer->setModel(listModel);
	completer->setCompletionMode(QCompleter::PopupCompletion);

	ui.lineEdit->setFont(QFont("Microsoft YaHei", 14));
	ui.lineEdit->setCompleter(completer);

	fittingWidget = new linerFttingWidget();
	connect(ui.fittingButton, &QPushButton::clicked, this, [&]() {
		fittingWidget->show();
	});

	connect(fittingWidget->pushButton, &QPushButton::clicked, this, &caculatorUIinWIdget::on_new_fitting_command);
	connect(this, &caculatorUIinWIdget::time_to_update, this, &caculatorUIinWIdget::add_buffer_to_update);

	load_records();
}

void caculatorUIinWIdget::on_new_input(QString &str) {
	auto result = moon::parse(str.toStdString());
	if (std::get<0>(result)) {
		// succeeded !
		records_file.open(fileName, fstream::app | fstream::in | fstream::out);
		if (std::get<1>(result) == moon::nodeType::functor_)
		{
			records_file <<'\n'<< str.toStdString();
			records_file.close();
			auto show_text = std::get<2>(result);
			leftOutputLabel *label = new leftOutputLabel(str.toStdString(), moon::nodeType::functor_,this);
			label->type = moon::nodeType::functor_;
			leftWidget->layout()->addWidget(label);
			ui.leftScrollArea->verticalScrollBar()->update();
			ui.leftScrollArea->verticalScrollBar()->setValue(ui.leftScrollArea->verticalScrollBar()->maximum());
			auto fun = str.toStdString();
			(*stringList) << QString(fun.substr(0, fun.find("=")).c_str());
		}
		else if (std::get<1>(result) == moon::nodeType::variable) {
			records_file << '\n' << str.toStdString();
			records_file.close();
			auto show_text = std::get<2>(result);
			leftOutputLabel *label = new leftOutputLabel(show_text, moon::nodeType::variable,this);
			label->type = moon::nodeType::variable;
			leftWidget->layout()->addWidget(label);
			//ui.leftScrollArea->verticalScrollBar()->setSliderPosition(0);
			ui.leftScrollArea->verticalScrollBar()->setValue(ui.leftScrollArea->verticalScrollBar()->maximum());
			ui.leftScrollArea->verticalScrollBar()->update();
			auto variable= str.toStdString();
			(*stringList) << QString(variable.substr(0, variable.find("=")).c_str());
		}
		string to_show(std::get<2>(result));
		to_show = str.toStdString() + string("\n\t = ") + to_show;
		rightOutputLabel *label = new rightOutputLabel(QString(to_show.c_str()), this);
		rightWidget->layout()->addWidget(label);
		ui.rightScrollArea->viewport()->update();
		ui.rightScrollArea->verticalScrollBar()->setValue(ui.rightScrollArea->verticalScrollBar()->maximum());
		ui.rightScrollArea->updateGeometry();
		ui.rightScrollArea->viewport()->update();
		ui.rightScrollArea->update();
		listModel = new QStringListModel(*stringList, this);
		completer->setModel(listModel);
	}
	else {
		auto show_text = std::get<3>(result);
		rightOutputLabel *label = new rightOutputLabel(QString((str.toStdString() + string("\n\t   ") + show_text).c_str()), this);
		auto a= ui.rightScrollArea->verticalScrollBar()->value();
		rightWidget->layout()->addWidget(label);
		auto b = ui.rightScrollArea->verticalScrollBar()->value();
		ui.rightScrollArea->verticalScrollBar()->update();
		auto c= ui.rightScrollArea->verticalScrollBar()->value();
		ui.rightScrollArea->verticalScrollBar()->setValue(ui.rightScrollArea->verticalScrollBar()->value() + 500);
		auto d = ui.rightScrollArea->verticalScrollBar()->value();
	}
	//this->repaint();
}

void caculatorUIinWIdget::on_new_draw_command(int num, double begin, double end, double min_piece, QString text) {
	//命令行显示图片
	//QCustomPlot customPlot;
	//QVector<double> x(num),y(num);
	//x[0] = begin;
	//auto result=moon::parse(text.toStdString() + string("(") + to_string(x[0]) + string(")"));
	//if (!get<0>(result)) y[0] = 0;
	//else y[0] = stod(get<2>(result));
	//for (int i = 1; i < num; ++i) {
	//	x[i] = x[i - 1] + min_piece;
	//	result = moon::parse(text.toStdString() + string("(") + to_string(x[i]) + string(")"));
	//	if (!get<0>(result)) y[i] = 0;
	//	else y[i] = stod(get<2>(result));
	//}
	//customPlot.addGraph();
	//customPlot.graph(0)->setData(x, y);	
	//customPlot.xAxis->setLabel("x");
	//customPlot.yAxis->setLabel("y");
	//customPlot.rescaleAxes();
	//customPlot.setFixedSize(500, 300);
	
	optionHelp.x->myPlot->plot->clearGraphs();
	auto customPlot = optionHelp.x->myPlot->plot;
	QVector<double> x(num), y(num);
	x[0] = begin;
	auto result = moon::parse(text.toStdString() + string("(") + to_string(x[0]) + string(")"));
	if (!get<0>(result)) y[0] = 0;
	else y[0] = stod(get<2>(result));
	for (int i = 1; i < num; ++i) {
		x[i] = x[i - 1] + min_piece;
		result = moon::parse(text.toStdString() + string("(") + to_string(x[i]) + string(")"));
		if (!get<0>(result)) y[i] = 0;
		else y[i] = stod(get<2>(result));
	}
	customPlot->addGraph();
	customPlot->graph(0)->setData(x, y);
	customPlot->xAxis->setLabel("x");
	customPlot->yAxis->setLabel("y");
	customPlot->rescaleAxes();
	customPlot->setFixedSize(500, 300);

}

void caculatorUIinWIdget::on_new_fitting_command() {
	auto str_x = moon::split(fittingWidget->edit_x->text().toStdString(), " ");
	auto str_y = moon::split(fittingWidget->edit_y->text().toStdString(), " ");
	int k = fittingWidget->edit_k->text().toInt();
	if (str_x.size() != str_y.size()) { 
		fittingWidget->hide();
		return; 
	}
	std::vector<double> x(str_x.size()), y(str_y.size());

	for (int i = 0; i < str_x.size(); ++i) {
		x[i] = std::stod(str_x[i]);
		y[i] = std::stod(str_y[i]);
	}
	auto new_plot = get_fitting_pixmap(x, y, k,fittingWidget->plot->plot);
	fittingWidget->plot->plot = new_plot;
	fittingWidget->repaint();
	//fittingWidget->picture->setPixmap(get_fitting_pixmap(x,y,k));
}

bool lineFit(const QVector<double> &x, const QVector<double> &y, double &a, double &b, double &c)
{
	int size = x.size();
	if (size < 2)
	{
		a = 0;
		b = 0;
		c = 0;
		return false;
	}
	double x_mean = 0;
	double y_mean = 0;
	for (int i = 0; i < size; i++)
	{
		x_mean += x[i];// x[i];
		y_mean += y[i];// y[i];
	}
	x_mean /= size;
	y_mean /= size; //至此，计算出了 x y 的均值

	double Dxx = 0, Dxy = 0, Dyy = 0;

	for (int i = 0; i < size; i++)
	{
		Dxx += (x[i] - x_mean) * (x[i] - x_mean);
		Dxy += (x[i] - x_mean) * (y[i] - y_mean);
		Dyy += (y[i] - y_mean) * (y[i] - y_mean);
	}
	double lambda = ((Dxx + Dyy) - sqrt((Dxx - Dyy) * (Dxx - Dyy) + 4 * Dxy * Dxy)) / 2.0;
	double den = sqrt(Dxy * Dxy + (lambda - Dxx) * (lambda - Dxx));
	a = Dxy / den;
	b = (lambda - Dxx) / den;
	c = -a * x_mean - b * y_mean;
	return true;
}

QPixmap drawLinerFittingPix(QVector<double> &x, QVector<double> &y, double &a, double &b, double &c) {
	QCustomPlot customPlot;
	QVector<double> fitting_y(x.size());
	//std::sort(x.begin(), x.end());
	for (int i = 0; i < y.size(); ++i) {
		fitting_y[i] = -1 * (a*x[i] + c) / b;
	}
	customPlot.addGraph();
	customPlot.graph(0)->setData(x, fitting_y);
	customPlot.addGraph();
	QPen pen;
	pen.setColor(Qt::blue);
	pen.setWidth(5);
	customPlot.graph(1)->setPen(pen);
	customPlot.graph(1)->setLineStyle(QCPGraph::lsNone);
	customPlot.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
	customPlot.graph(1)->setData(x, y);
	customPlot.xAxis->setLabel("x");
	customPlot.yAxis->setLabel("y");
	customPlot.xAxis->setRangeLower(1);
	//customPlot.xAxis->setRange(customPlot.xAxis->range() * 1);
	//customPlot.xAxis->scaleRange(2);
	//customPlot.yAxis->scaleRange(2);
	//customPlot.xAxis->ticker()->setTickCount(x.size() + 2);
	//customPlot.yAxis->ticker()->setTickCount(y.size() + 2);
	customPlot.rescaleAxes();
	customPlot.setFixedSize(500, 300);
	return std::move(customPlot.toPixmap());
}

QVector<double> fittingPloy(vector<double>& x, vector<double> &y, int k) {

	Fit fit;
	fit.polyfit(x, y, k);
	QVector<double> a;
	for (int i = 0; i <= k; ++i) {
		a.push_back(fit.getFactor(i));
	}
	return move(a);
}

double get_multi_expressioni(QVector<double>& a, double x) {
	double  result = 0;

	for (int i = 0; i < a.size(); ++i)
		result += pow(x, i)*a[i];
	return result;
}

QCustomPlot* get_fitting_pixmap(vector<double>& x, vector<double> &y, int k,QCustomPlot* plot) {
	auto a = fittingPloy(x, y, k);
	//QCustomPlot* customPlot=new QCustomPlot;
	auto customPlot = plot;
	customPlot->clearGraphs();
	customPlot->addGraph();
	double min = x[0], max = x[0];
	for (int i = 1; i != x.size(); ++i) {
		if (x[i] < min)
			min = x[i];
		if (x[i] > max)
			max = x[i];
	}
	auto piece = (max - min) / 500;
	for (int i = 0; i != 500; ++i) {
		auto value = get_multi_expressioni(a, min + piece*i);
		customPlot->graph(0)->addData(min + piece*i, value);
	}
	customPlot->addGraph();
	QPen pen;
	pen.setColor(Qt::blue);
	pen.setWidth(5);
	customPlot->graph(1)->setPen(pen);
	customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
	customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
	for (int i = 0; i < x.size(); ++i) {
		customPlot->graph(1)->addData(x[i], y[i]);
	}

	customPlot->xAxis->setLabel("x");
	customPlot->yAxis->setLabel("y");
	customPlot->rescaleAxes();
	customPlot->setFixedSize(500, 300);
	customPlot->xAxis->setRangeLower(1);

	return customPlot;
}

void caculatorUIinWIdget::add_buffer_to_update() {
	//rightWidget->layout()->addWidget(new bufferOutputLabel(this));
	ui.rightScrollArea->verticalScrollBar()->setValue(ui.rightScrollArea->verticalScrollBar()->maximum());
}

void caculatorUIinWIdget::load_records() {
	string records;
	records_file.open(fileName, fstream::app|fstream::in|fstream::out);
	while (!records_file.eof()) {
		getline(records_file, records);
		if (records == "\n") continue;
		auto result = moon::parse(records);
			// succeeded !
			if (std::get<1>(result) == moon::nodeType::functor_)
			{
				auto show_text = std::get<2>(result);
				leftOutputLabel *label = new leftOutputLabel(records, moon::nodeType::functor_, this);
				label->type = moon::nodeType::functor_;
				leftWidget->layout()->addWidget(label);
				ui.leftScrollArea->verticalScrollBar()->update();
				ui.leftScrollArea->verticalScrollBar()->setValue(ui.leftScrollArea->verticalScrollBar()->maximum());
				auto fun = records;
				(*stringList) << QString(fun.substr(0, fun.find("=")).c_str());
			}
			else if (std::get<1>(result) == moon::nodeType::variable) {
				auto show_text = std::get<2>(result);
				leftOutputLabel *label = new leftOutputLabel(show_text, moon::nodeType::variable, this);
				label->type = moon::nodeType::variable;
				leftWidget->layout()->addWidget(label);
				//ui.leftScrollArea->verticalScrollBar()->setSliderPosition(0);
				ui.leftScrollArea->verticalScrollBar()->setValue(ui.leftScrollArea->verticalScrollBar()->maximum());
				ui.leftScrollArea->verticalScrollBar()->update();
				auto variable = records;
				(*stringList) << QString(variable.substr(0, variable.find("=")).c_str());
			}
	}
	records_file.close();
}
