#include"records.h"
#include"encode.h"
#include"caculatorUIinWIdget.h"
#include"parserMachine.h"
#include"qcustomplot.h"
#include"myLabels.h"
#include"justForPictureOptionHelp.h"
#include<qlabel.h>
#include<qwidget.h>
#include<qfont.h>
#include<qstring.h>
#include<qpixmap.h>
#include<qimage.h>
#include<qvector.h>
#include<qpushbutton.h>
#include<qevent.h>
#include<string>

bool for_option_help = false;

pictureOptionHelp optionHelp;
//extern pictureOptionHelp* optionHelp;

pictureSaveWidget::pictureSaveWidget(QWidget* parent ) :QWidget(parent) {}
pictureSaveWidget::pictureSaveWidget(QPixmap pixmap, QWidget* parent ) :QWidget(parent) {
		this->pixmap = pixmap;
		this->fileModel = new QFileSystemModel(this);
		this->fileModel->setRootPath(QDir::currentPath());


		this->treeView = new QTreeView;
		this->treeView->setModel(this->fileModel);
		//this->treeView->setRootIndex(fileModel->index(QDir::currentPath()));
		QFont font;
		font.setFamily("Microsoft YaHei");
		font.setPointSize(14);
		this->lineEdit = new QLineEdit;
		this->lineEdit->setText(QString("此处输入保存文件名.png"));
		this->lineEdit->setFont(font);
		this->pushButton = new QPushButton;
		this->pushButton->setText(tr("保存"));
		this->pushButton->setFont(font);

		connect(this->lineEdit, &QLineEdit::returnPressed, this, &pictureSaveWidget::savePicture);
		connect(this->pushButton, &QPushButton::clicked, this, &pictureSaveWidget::savePicture);

		this->setLayout(new QVBoxLayout);
		this->layout()->addWidget(treeView);
		QWidget *widget = new QWidget(this);
		auto buttonLayout = new QHBoxLayout;
		buttonLayout->addWidget(lineEdit);
		buttonLayout->addWidget(pushButton);
		widget->setLayout(buttonLayout);
		this->layout()->addWidget(widget);
		this->setFixedSize(600, 400);
	}
void pictureSaveWidget::savePicture() {
		auto str = this->fileModel->filePath(this->treeView->currentIndex()) + QString("/");
		if (lineEdit->text().isEmpty()) {
			auto str = QDateTime::currentDateTime().toString("yyyy-MM--dd-hh:mm::ss-ddd");
			this->pixmap.save(str + QString("wtfagain"), "PNG");
		}
		else {
			this->pixmap.save(str + lineEdit->text(), "PNG");
		}
		this->close();
	}
	
leftOutputLabel::leftOutputLabel(std::string text, moon::nodeType type, QWidget* parent ) :text(text), QLabel(parent) {
		this->setText(text.c_str());
		this->type = type;
		QFont font;
		font.setFamily("Microsoft YaHei");
		font.setPointSize(14);
		this->setFont(font);
	}
void leftOutputLabel::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		if (type == moon::nodeType::variable) return;
		auto index_left = text.find('(');
		auto new_text = text.substr(0, index_left);

		optionHelp.setText(new_text);
	}
	else {//rightbutton
		auto index_left = text.find('(');
		string new_text;
		//从leftwidget中删除
		this->type = moon::nodeType::variable;
		this->setText("(本条记录已删除)");
		//从map中删除
		if (index_left != string::npos) {
			new_text = text.substr(0, index_left);
			moon::custom_function.erase(new_text);
		}
		else {
			new_text = text;
			moon::custom_variable.erase(new_text);
		}
		//从文件中删除
		string line;
		records_file.open(fileName, fstream::app | fstream::in | fstream::out);
		fstream new_file;
		new_file.open("tem_records",fstream::out);
		while (!records_file.eof()) {
			getline(records_file, line);
			if (line == "") continue;
			if (line == this->text|| \
				line.substr(0,line.find("="))==text.substr(0,text.find("=")));
			else
				new_file << '\n'<<line;
		}
		records_file.close();
		remove(fileName.c_str());
		new_file.close();
		rename("tem_records", "records");
		//从completer中删除
		auto stringList = new QStringList;
		for (auto &entry : moon::base_fun_priority) {
			(*stringList) << entry.first.c_str();
		}
		for (auto &entry : moon::base_op_priority)
			(*stringList) << entry.first.c_str();
		for (auto &entry : moon::custom_function)
			(*stringList) << entry.first.c_str();
		for (auto &entry : moon::custom_variable)
			(*stringList) << entry.first.c_str();
		auto listModel = new QStringListModel(*stringList);
		completer->setModel(listModel);
	}
}

rightOutputLabel::rightOutputLabel(QWidget* parent) :QLabel(parent) {
		this->setText("input > hellokitty \n \twinter is comming");
		QFont font;
		font.setFamily("Microsoft YaHei");
		font.setPixelSize(20);
		this->setFont(font);
	}
rightOutputLabel::rightOutputLabel(QString content, QWidget *parent) :QLabel(parent) {
		this->setText(QString("input > ") + content);
		QFont font;
		font.setFamily("Microsoft YaHei");
		font.setPixelSize(20);
		this->setFont(font);
	}

pictureLabel::pictureLabel(QWidget *parent) :QLabel(parent) {
		QCustomPlot customPlot;
		customPlot.addGraph();
		customPlot.xAxis->setLabel("x");
		customPlot.yAxis->setLabel("y");
		customPlot.rescaleAxes();
		customPlot.setFixedSize(500, 300);
		auto pix = customPlot.toPixmap();
		this->setPixmap(pix);
	}
pictureLabel::pictureLabel(QPixmap pix, QWidget *parent ) :QLabel(parent) {
		this->setPixmap(pix);
	}
void pictureLabel::mousePressEvent(QMouseEvent *event) {
	this->savePicture();
}
void pictureLabel::savePicture() {
	pictureSaveWidget *widget = new pictureSaveWidget(*pixmap());
	widget->show();
}

pictureOptionWidget::pictureOptionWidget(QString text , QWidget* parent ) : text(text) {
	QFont font;
	font.setFamily("Microsoft YaHei");
	font.setPixelSize(18);
	this->setFont(font);

	layout = new QVBoxLayout;
	upLayout = new QHBoxLayout;
	downLayout = new QHBoxLayout;
	xLabel = new QLabel(tr("横坐标范围:")); xLabel->setFont(font);
	pointLabel = new QLabel(tr("绘制点数:")); pointLabel->setFont(font);
	xBegin = new QLineEdit();
	xEnd = new QLineEdit();
	pointNum = new QLineEdit();
	button = new QPushButton("确定"); button->setFont(font);
	myPlot = new scrollablePlot(this);
	upLayout->addWidget(xLabel);
	upLayout->addWidget(xBegin);
	upLayout->addWidget(new QLabel("=>", this));
	upLayout->addWidget(xEnd);
	downLayout->addWidget(pointLabel);
	downLayout->addWidget(pointNum);

	layout->addLayout(upLayout);
	layout->addLayout(downLayout);
	layout->addWidget(button);
	layout->addWidget(myPlot);

	this->setLayout(layout);
}

pictureOptionHelp::pictureOptionHelp() {
}

pictureOptionHelp::pictureOptionHelp(std::string new_text) :text(new_text) {
	x->text = QString(new_text.c_str());
	x->show();
	connect(x->button, &QPushButton::clicked, this, &pictureOptionHelp::sendSignal);
}

void pictureOptionHelp::setText(std::string new_text) {
	x->text = QString(new_text.c_str());
	x->show();
	connect(x->button, &QPushButton::clicked, this, &pictureOptionHelp::sendSignal);
}

void pictureOptionHelp::sendSignal() {
	if (!for_option_help) { for_option_help = true; return; }
	else for_option_help = false;
	auto begin = x->xBegin->text().toDouble();
	auto end = x->xEnd->text().toDouble();
	if (begin > end) {
		auto tem = end;
		end = begin;
		begin = tem;
	} 
	auto num = x->pointNum->text().toInt();
	auto min_piece = (end - begin) / num;
	emit buttonClicked(num, begin, end, min_piece, QString(x->text));
}

blankLabel::blankLabel(QWidget* parent):QLabel(parent) {
	this->setFixedSize(640, 480);
}

bufferOutputLabel::bufferOutputLabel(QWidget* parent ) {

}

bufferOutputLabel::bufferOutputLabel(QString content, QWidget *parent ) {
	this->setText("\n");
	QFont font;
	font.setFamily("Microsoft YaHei");
	font.setPixelSize(20);
	this->setFont(font);
}
