#pragma once
#include"scrollableplot.hpp"
#include"encode.h"
#include"myLabels.h"
#include"qcustomplot.h"
#include"parserMachine.h"
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


class bufferOutputLabel :public QLabel {
public:
	bufferOutputLabel(QWidget* parent = nullptr);
	bufferOutputLabel(QString content, QWidget *parent = nullptr);
};


class pictureSaveWidget :public QWidget {
public:
	pictureSaveWidget(QWidget* parent = nullptr);
	pictureSaveWidget(QPixmap pixmap, QWidget* parent = nullptr);
	void savePicture();
private:
	QPixmap pixmap;
	QFileSystemModel *fileModel;
	QTreeView *treeView;
	QLineEdit *lineEdit;
	QPushButton* pushButton;
};

class leftOutputLabel :public QLabel {
public:
	QTimer timer;
	moon::nodeType type;
	std::string text;
	leftOutputLabel(std::string text, moon::nodeType type, QWidget* parent = nullptr);
	QPixmap get_pixmap();
	void mousePressEvent(QMouseEvent *event);
};

class rightOutputLabel :public QLabel {
public:
	rightOutputLabel(QWidget* parent = nullptr);
	rightOutputLabel(QString content, QWidget *parent = nullptr);
};

class pictureLabel :public QLabel{
public:
	pictureLabel(QWidget *parent = nullptr);
	pictureLabel(QPixmap pix, QWidget *parent = nullptr);
protected:
	void mousePressEvent(QMouseEvent *event);
	void savePicture();
};

class blankLabel :public QLabel {
public:
	blankLabel(QWidget* parent=nullptr);
};

class pictureOptionWidget :public QWidget {
public:
	QString text;
	pictureOptionWidget(QString text = QString(), QWidget* parent = nullptr);
public:
	QVBoxLayout	*layout;
	QHBoxLayout *upLayout, *downLayout;
	QLabel *xLabel, *pointLabel;
	QLineEdit *xBegin, *xEnd, *pointNum;
	QPushButton *button;
	//-for test
	//pictureLabel *picture;
	//-for test again
	scrollablePlot *myPlot;
};

class pictureOptionHelp :public QObject {
	Q_OBJECT
signals:
	void buttonClicked(int num, double begin, double end, double min_piece, QString text);
public:
	pictureOptionWidget* x;// = new pictureOptionWidget;
	std::string text;
	pictureOptionHelp::pictureOptionHelp();
	pictureOptionHelp(std::string new_text);
	void setText(std::string new_text);
public slots:
void sendSignal();

};

 extern pictureOptionHelp optionHelp;

 class linerFttingWidget :public QWidget {
 private:
	 QVBoxLayout *layout;
	 QHBoxLayout *xLayout, *yLayout, *kLayout;
 public:
	 scrollablePlot *plot;
	 //pictureLabel *picture;
	 QPushButton *pushButton;
	 QLineEdit *edit_x, *edit_y, *edit_k;
	 linerFttingWidget(QWidget* parent = nullptr) :QWidget(parent) {
		 pushButton = new QPushButton(tr("确定前请确保数据量匹配"));
		 pushButton->setFont(QFont("Microsoft YaHei", 14));
		 edit_x = new QLineEdit;	edit_x->setFont(QFont("Microsoft YaHei", 14));
		 edit_y = new QLineEdit; edit_y->setFont(QFont("Microsoft YaHei", 14));
		 edit_k = new QLineEdit; edit_k->setFont(QFont("Microsoft YaHei", 14));
		 xLayout = new QHBoxLayout;
		 yLayout = new QHBoxLayout;
		 kLayout = new QHBoxLayout;
		 auto xlabel = new QLabel("请输入X值 :\r");	xlabel->setFont(QFont("Microsoft YaHei", 14));
		 auto ylabel = new QLabel("请输入Y值 :\r");	ylabel->setFont(QFont("Microsoft YaHei", 14));
		 auto klabel = new QLabel("请输入拟合阶数 :\r"); klabel->setFont(QFont("Microsoft YaHei", 14));

		 xLayout->addWidget(xlabel);
		 yLayout->addWidget(ylabel);
		 kLayout->addWidget(klabel);
		 xLayout->addWidget(edit_x);
		 yLayout->addWidget(edit_y);
		 kLayout->addWidget(edit_k);

		 layout = new QVBoxLayout;
		 auto xWidget = new QWidget;
		 auto yWidget = new QWidget;
		 auto kWidget = new QWidget;
		 xWidget->setLayout(xLayout);
		 yWidget->setLayout(yLayout);
		 kWidget->setLayout(kLayout);
		 layout->addWidget(xWidget);
		 layout->addWidget(yWidget);
		 layout->addWidget(kWidget);
		 layout->addWidget(pushButton);
		 this->setLayout(layout);
		 this->plot= new scrollablePlot;
		 layout->addWidget(this->plot);
	 }

 };
