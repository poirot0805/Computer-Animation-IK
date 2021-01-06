/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <controller.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    Controller *paintCon;
    QLabel *methodTitle;
    QLabel *targetTitle;
    QLabel *methodLabel;
    QLabel *targetLabel;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *CCDsingle;
    QPushButton *CCD;
    QPushButton *Jacobi;
    QPushButton *startButton;
    QPushButton *resetButton;
    QCheckBox *trace;
    QCheckBox *circletrace;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(895, 810);
        MainWindow->setAutoFillBackground(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        paintCon = new Controller(centralwidget);
        paintCon->setObjectName(QString::fromUtf8("paintCon"));
        paintCon->setGeometry(QRect(19, 9, 711, 751));
        paintCon->setAutoFillBackground(true);
        QPalette pal(paintCon->palette());
        pal.setColor(QPalette::Background, Qt::white);
        paintCon->setPalette(pal);
        methodTitle = new QLabel(paintCon);
        methodTitle->setObjectName(QString::fromUtf8("methodTitle"));
        methodTitle->setGeometry(QRect(10, 720, 54, 12));
        targetTitle = new QLabel(paintCon);
        targetTitle->setObjectName(QString::fromUtf8("targetTitle"));
        targetTitle->setGeometry(QRect(430, 720, 54, 16));
        methodLabel = new QLabel(paintCon);
        methodLabel->setObjectName(QString::fromUtf8("methodLabel"));
        methodLabel->setGeometry(QRect(70, 720, 151, 16));
        targetLabel = new QLabel(paintCon);
        targetLabel->setObjectName(QString::fromUtf8("targetLabel"));
        targetLabel->setGeometry(QRect(480, 710, 191, 31));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(740, 170, 141, 401));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        CCDsingle = new QPushButton(verticalLayoutWidget);
        CCDsingle->setObjectName(QString::fromUtf8("CCDsingle"));

        verticalLayout->addWidget(CCDsingle);

        CCD = new QPushButton(verticalLayoutWidget);
        CCD->setObjectName(QString::fromUtf8("CCD"));

        verticalLayout->addWidget(CCD);

        Jacobi = new QPushButton(verticalLayoutWidget);
        Jacobi->setObjectName(QString::fromUtf8("Jacobi"));

        verticalLayout->addWidget(Jacobi);

        startButton = new QPushButton(verticalLayoutWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        verticalLayout->addWidget(startButton);

        resetButton = new QPushButton(verticalLayoutWidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));

        verticalLayout->addWidget(resetButton);

        trace = new QCheckBox(verticalLayoutWidget);
        trace->setObjectName(QString::fromUtf8("trace"));

        verticalLayout->addWidget(trace);

        circletrace = new QCheckBox(verticalLayoutWidget);
        circletrace->setObjectName(QString::fromUtf8("circletrace"));

        verticalLayout->addWidget(circletrace);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 895, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        methodTitle->setText(QCoreApplication::translate("MainWindow", "Method\357\274\232", nullptr));
        targetTitle->setText(QCoreApplication::translate("MainWindow", "Target\357\274\232", nullptr));
        methodLabel->setText(QString());
        targetLabel->setText(QString());
        CCDsingle->setText(QCoreApplication::translate("MainWindow", "\345\215\225\346\254\241CCD", nullptr));
        CCD->setText(QCoreApplication::translate("MainWindow", "\345\276\252\347\216\257\345\235\220\346\240\207\344\270\213\351\231\215\346\263\225", nullptr));
        Jacobi->setText(QCoreApplication::translate("MainWindow", "\351\200\206\345\220\221\351\233\205\345\205\213\346\257\224\346\263\225", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Start/Stop", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        trace->setText(QCoreApplication::translate("MainWindow", "\350\275\250\350\277\271\346\230\276\347\244\272", nullptr));
        circletrace->setText(QCoreApplication::translate("MainWindow", "\345\274\247\345\275\242\350\277\220\345\212\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
