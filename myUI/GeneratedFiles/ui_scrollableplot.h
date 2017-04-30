/********************************************************************************
** Form generated from reading UI file 'scrollableplot.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCROLLABLEPLOT_H
#define UI_SCROLLABLEPLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_scrollablePlot
{
public:
    QWidget *widgetForPlot;
    QScrollBar *horizontalScrollBar;
    QScrollBar *verticalScrollBar;

    void setupUi(QWidget *scrollablePlot)
    {
        if (scrollablePlot->objectName().isEmpty())
            scrollablePlot->setObjectName(QStringLiteral("scrollablePlot"));
        scrollablePlot->resize(518, 316);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollablePlot->sizePolicy().hasHeightForWidth());
        scrollablePlot->setSizePolicy(sizePolicy);
        widgetForPlot = new QWidget(scrollablePlot);
        widgetForPlot->setObjectName(QStringLiteral("widgetForPlot"));
        widgetForPlot->setGeometry(QRect(0, 0, 500, 300));
        horizontalScrollBar = new QScrollBar(scrollablePlot);
        horizontalScrollBar->setObjectName(QStringLiteral("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(0, 300, 491, 16));
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        verticalScrollBar = new QScrollBar(scrollablePlot);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(500, 0, 16, 311));
        verticalScrollBar->setOrientation(Qt::Vertical);

        retranslateUi(scrollablePlot);

        QMetaObject::connectSlotsByName(scrollablePlot);
    } // setupUi

    void retranslateUi(QWidget *scrollablePlot)
    {
        scrollablePlot->setWindowTitle(QApplication::translate("scrollablePlot", "scrollablePlot", 0));
    } // retranslateUi

};

namespace Ui {
    class scrollablePlot: public Ui_scrollablePlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCROLLABLEPLOT_H
