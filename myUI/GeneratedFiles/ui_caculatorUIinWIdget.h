/********************************************************************************
** Form generated from reading UI file 'caculatorUIinWIdget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CACULATORUIINWIDGET_H
#define UI_CACULATORUIINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_caculatorUIinWIdgetClass
{
public:
    QHBoxLayout *horizontalLayout_2;
    QWidget *leftWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *leftLayout;
    QScrollArea *leftScrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *mainLayout;
    QWidget *rightWidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QScrollArea *rightScrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QPushButton *fittingButton;
    QLineEdit *lineEdit;

    void setupUi(QWidget *caculatorUIinWIdgetClass)
    {
        if (caculatorUIinWIdgetClass->objectName().isEmpty())
            caculatorUIinWIdgetClass->setObjectName(QStringLiteral("caculatorUIinWIdgetClass"));
        caculatorUIinWIdgetClass->resize(1026, 620);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(caculatorUIinWIdgetClass->sizePolicy().hasHeightForWidth());
        caculatorUIinWIdgetClass->setSizePolicy(sizePolicy);
        caculatorUIinWIdgetClass->setMinimumSize(QSize(1000, 600));
        caculatorUIinWIdgetClass->setMaximumSize(QSize(1026, 700));
        horizontalLayout_2 = new QHBoxLayout(caculatorUIinWIdgetClass);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        leftWidget = new QWidget(caculatorUIinWIdgetClass);
        leftWidget->setObjectName(QStringLiteral("leftWidget"));
        leftWidget->setMinimumSize(QSize(200, 600));
        leftWidget->setMaximumSize(QSize(200, 600));
        verticalLayout_2 = new QVBoxLayout(leftWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        leftLayout = new QVBoxLayout();
        leftLayout->setSpacing(6);
        leftLayout->setObjectName(QStringLiteral("leftLayout"));
        leftScrollArea = new QScrollArea(leftWidget);
        leftScrollArea->setObjectName(QStringLiteral("leftScrollArea"));
        leftScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 178, 578));
        leftScrollArea->setWidget(scrollAreaWidgetContents);

        leftLayout->addWidget(leftScrollArea);


        verticalLayout_2->addLayout(leftLayout);


        horizontalLayout_2->addWidget(leftWidget);

        mainLayout = new QHBoxLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        rightWidget = new QWidget(caculatorUIinWIdgetClass);
        rightWidget->setObjectName(QStringLiteral("rightWidget"));
        rightWidget->setMinimumSize(QSize(800, 600));
        rightWidget->setMaximumSize(QSize(800, 600));
        verticalLayout_3 = new QVBoxLayout(rightWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));

        verticalLayout_3->addLayout(verticalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        rightScrollArea = new QScrollArea(rightWidget);
        rightScrollArea->setObjectName(QStringLiteral("rightScrollArea"));
        rightScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 778, 509));
        rightScrollArea->setWidget(scrollAreaWidgetContents_2);

        verticalLayout->addWidget(rightScrollArea);


        verticalLayout_3->addLayout(verticalLayout);

        fittingButton = new QPushButton(rightWidget);
        fittingButton->setObjectName(QStringLiteral("fittingButton"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        fittingButton->setFont(font);

        verticalLayout_3->addWidget(fittingButton);

        lineEdit = new QLineEdit(rightWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout_3->addWidget(lineEdit);


        mainLayout->addWidget(rightWidget);


        horizontalLayout_2->addLayout(mainLayout);


        retranslateUi(caculatorUIinWIdgetClass);

        QMetaObject::connectSlotsByName(caculatorUIinWIdgetClass);
    } // setupUi

    void retranslateUi(QWidget *caculatorUIinWIdgetClass)
    {
        caculatorUIinWIdgetClass->setWindowTitle(QApplication::translate("caculatorUIinWIdgetClass", "caculatorUIinWIdget", 0));
        fittingButton->setText(QApplication::translate("caculatorUIinWIdgetClass", "\347\202\271\345\207\273\350\277\233\350\241\214\346\233\262\347\272\277\346\213\237\345\220\210", 0));
    } // retranslateUi

};

namespace Ui {
    class caculatorUIinWIdgetClass: public Ui_caculatorUIinWIdgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CACULATORUIINWIDGET_H
