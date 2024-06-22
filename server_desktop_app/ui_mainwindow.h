/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QLabel *label_2;
    QLabel *ip_label;
    QLabel *port_label;
    QCheckBox *server_check_box;
    QLabel *label_9;
    QLabel *label_10;
    QGroupBox *groupBox_2;
    QListWidget *listWidget_3;
    QGroupBox *groupBox_3;
    QTableWidget *playerTable;
    QLabel *label;
    QLabel *label_4;
    QGroupBox *groupBox_7;
    QLabel *label_8;
    QLabel *label_5;
    QLabel *label_6;
    QProgressBar *progressBar_3;
    QProgressBar *progressBar_2;
    QProgressBar *progressBar_4;
    QProgressBar *progressBar;
    QLabel *label_7;
    QGroupBox *groupBox_5;
    QListWidget *listWidget_2;
    QListWidget *listWidget;
    QGroupBox *groupBox_6;
    QLabel *label_3;
    QLabel *ip_label_2;
    QLabel *port_label_2;
    QCheckBox *server_check_box_2;
    QPushButton *pushButton;
    QPushButton *pushButton_6;
    QGroupBox *groupBox_4;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_7;
    QPushButton *pushButton_5;
    QPushButton *pushButton_8;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1510, 749);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 351, 121));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 60, 63, 20));
        ip_label = new QLabel(groupBox);
        ip_label->setObjectName(QString::fromUtf8("ip_label"));
        ip_label->setGeometry(QRect(60, 30, 251, 20));
        port_label = new QLabel(groupBox);
        port_label->setObjectName(QString::fromUtf8("port_label"));
        port_label->setGeometry(QRect(60, 60, 251, 20));
        server_check_box = new QCheckBox(groupBox);
        server_check_box->setObjectName(QString::fromUtf8("server_check_box"));
        server_check_box->setGeometry(QRect(10, 30, 191, 24));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(110, 90, 161, 20));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 90, 63, 20));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 130, 351, 521));
        listWidget_3 = new QListWidget(groupBox_2);
        listWidget_3->setObjectName(QString::fromUtf8("listWidget_3"));
        listWidget_3->setGeometry(QRect(20, 30, 301, 441));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(390, 120, 721, 531));
        playerTable = new QTableWidget(groupBox_3);
        playerTable->setObjectName(QString::fromUtf8("playerTable"));
        playerTable->setGeometry(QRect(30, 50, 661, 192));
        playerTable->setSizeIncrement(QSize(1, 1));
        playerTable->setFrameShape(QFrame::Panel);
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 250, 63, 20));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(430, 250, 63, 20));
        groupBox_7 = new QGroupBox(groupBox_3);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(30, 280, 661, 231));
        label_8 = new QLabel(groupBox_7);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(80, 180, 63, 20));
        label_5 = new QLabel(groupBox_7);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(80, 50, 63, 20));
        label_6 = new QLabel(groupBox_7);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(80, 90, 63, 20));
        progressBar_3 = new QProgressBar(groupBox_7);
        progressBar_3->setObjectName(QString::fromUtf8("progressBar_3"));
        progressBar_3->setGeometry(QRect(330, 130, 251, 23));
        progressBar_3->setValue(24);
        progressBar_2 = new QProgressBar(groupBox_7);
        progressBar_2->setObjectName(QString::fromUtf8("progressBar_2"));
        progressBar_2->setGeometry(QRect(330, 90, 251, 23));
        progressBar_2->setValue(24);
        progressBar_4 = new QProgressBar(groupBox_7);
        progressBar_4->setObjectName(QString::fromUtf8("progressBar_4"));
        progressBar_4->setGeometry(QRect(330, 170, 251, 23));
        progressBar_4->setValue(24);
        progressBar = new QProgressBar(groupBox_7);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(330, 50, 251, 23));
        progressBar->setValue(24);
        label_7 = new QLabel(groupBox_7);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(80, 130, 63, 20));
        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(1130, 130, 371, 521));
        listWidget_2 = new QListWidget(groupBox_5);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));
        listWidget_2->setGeometry(QRect(50, 40, 311, 231));
        listWidget = new QListWidget(groupBox_5);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(50, 280, 311, 231));
        groupBox_6 = new QGroupBox(centralwidget);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(400, 10, 351, 101));
        label_3 = new QLabel(groupBox_6);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 60, 101, 20));
        ip_label_2 = new QLabel(groupBox_6);
        ip_label_2->setObjectName(QString::fromUtf8("ip_label_2"));
        ip_label_2->setGeometry(QRect(60, 30, 251, 20));
        port_label_2 = new QLabel(groupBox_6);
        port_label_2->setObjectName(QString::fromUtf8("port_label_2"));
        port_label_2->setGeometry(QRect(110, 60, 21, 20));
        server_check_box_2 = new QCheckBox(groupBox_6);
        server_check_box_2->setObjectName(QString::fromUtf8("server_check_box_2"));
        server_check_box_2->setGeometry(QRect(10, 30, 118, 24));
        pushButton = new QPushButton(groupBox_6);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(160, 20, 151, 31));
        pushButton_6 = new QPushButton(groupBox_6);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(160, 60, 151, 29));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(760, 0, 741, 121));
        plainTextEdit = new QPlainTextEdit(groupBox_4);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(370, 20, 361, 61));
        pushButton_2 = new QPushButton(groupBox_4);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(580, 90, 151, 31));
        pushButton_3 = new QPushButton(groupBox_4);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(10, 20, 151, 29));
        pushButton_4 = new QPushButton(groupBox_4);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(10, 50, 151, 29));
        pushButton_7 = new QPushButton(groupBox_4);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(10, 80, 151, 29));
        pushButton_5 = new QPushButton(groupBox_4);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(170, 20, 141, 29));
        pushButton_8 = new QPushButton(groupBox_4);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(170, 50, 141, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1510, 26));
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
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Server Info", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        ip_label->setText(QString());
        port_label->setText(QString());
        server_check_box->setText(QCoreApplication::translate("MainWindow", "Server Status", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "IP:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Received Messages", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Game Status", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Player", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Health", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "Player - Health", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Game Logs", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "Game Status", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Player Count :", nullptr));
        ip_label_2->setText(QString());
        port_label_2->setText(QString());
        server_check_box_2->setText(QCoreApplication::translate("MainWindow", "Game Started", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Start Game", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Start 3D model", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Tests", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Send All", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Add Player", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Send Location", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Revive", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Hit", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Test RSSI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
