#pragma once
#include"encode.h"
#include"myLabels.h"
#include <qwidget.h>
#include<qcompleter.h>
#include<qstringlistmodel.h>
#include<qstringlist.h>
#include "ui_caculatorUIinWIdget.h"
#include<fstream>

extern QCompleter *completer;

class caculatorUIinWIdget : public QWidget
{
    Q_OBJECT

public:
    caculatorUIinWIdget(QWidget *parent = Q_NULLPTR);

private:

	QStringList *stringList;
	QStringListModel *listModel;
	linerFttingWidget *fittingWidget;

public:
	Ui::caculatorUIinWIdgetClass ui;
	QWidget *leftWidget, *rightWidget;
	void on_new_input(QString &str);
	void load_records();
signals:
	void time_to_update();

public slots:
	void on_new_draw_command(int num, double begin, double end, double min_piece, QString text);
	void on_new_fitting_command();
	void add_buffer_to_update();
};
	
