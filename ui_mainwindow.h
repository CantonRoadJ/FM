/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QSlider *horizontalSlider_CurFreq;
    QLCDNumber *lcdNumber_CurFreq;
    QLabel *label;
    QPushButton *pushButton_PageUp;
    QPushButton *pushButton_PageDown;
    QPushButton *pushButton_NextSatation;
    QPushButton *pushButton_PrevStation;
    QPushButton *pushButton_FM;
    QPushButton *pushButton_AM;
    QPushButton *pushButton_ScanSatation;
    QPushButton *pushButton_Power;
    QLabel *label_FreqMin;
    QLabel *label_FreqMax;
    QPushButton *pushButton_exit;
    QPushButton *pushButton_VolSetting;
    QPushButton *pushButton_Station1;
    QPushButton *pushButton_Station2;
    QPushButton *pushButton_Station4;
    QPushButton *pushButton_Station5;
    QPushButton *pushButton_Station3;
    QPushButton *pushButton_Station6;
    QPushButton *pushButton_RadioUp;
    QPushButton *pushButton_RadioDown;
    QSlider *verticalSlider_vol;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1280, 720);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalSlider_CurFreq = new QSlider(centralWidget);
        horizontalSlider_CurFreq->setObjectName(QStringLiteral("horizontalSlider_CurFreq"));
        horizontalSlider_CurFreq->setGeometry(QRect(256, 240, 768, 50));
        QFont font;
        font.setPointSize(80);
        horizontalSlider_CurFreq->setFont(font);
        horizontalSlider_CurFreq->setOrientation(Qt::Horizontal);
        lcdNumber_CurFreq = new QLCDNumber(centralWidget);
        lcdNumber_CurFreq->setObjectName(QStringLiteral("lcdNumber_CurFreq"));
        lcdNumber_CurFreq->setGeometry(QRect(410, 110, 230, 90));
        QFont font1;
        font1.setFamily(QStringLiteral("Calibri Light"));
        font1.setPointSize(80);
        font1.setBold(true);
        font1.setWeight(75);
        lcdNumber_CurFreq->setFont(font1);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(640, 110, 230, 90));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(80);
        font2.setBold(true);
        font2.setWeight(75);
        font2.setKerning(true);
        label->setFont(font2);
        pushButton_PageUp = new QPushButton(centralWidget);
        pushButton_PageUp->setObjectName(QStringLiteral("pushButton_PageUp"));
        pushButton_PageUp->setGeometry(QRect(1050, 350, 90, 90));
        QFont font3;
        font3.setPointSize(40);
        pushButton_PageUp->setFont(font3);
        pushButton_PageDown = new QPushButton(centralWidget);
        pushButton_PageDown->setObjectName(QStringLiteral("pushButton_PageDown"));
        pushButton_PageDown->setGeometry(QRect(1050, 460, 90, 90));
        pushButton_PageDown->setFont(font3);
        pushButton_NextSatation = new QPushButton(centralWidget);
        pushButton_NextSatation->setObjectName(QStringLiteral("pushButton_NextSatation"));
        pushButton_NextSatation->setGeometry(QRect(940, 110, 90, 90));
        pushButton_NextSatation->setFont(font3);
        pushButton_PrevStation = new QPushButton(centralWidget);
        pushButton_PrevStation->setObjectName(QStringLiteral("pushButton_PrevStation"));
        pushButton_PrevStation->setGeometry(QRect(250, 110, 90, 90));
        pushButton_PrevStation->setFont(font3);
        pushButton_FM = new QPushButton(centralWidget);
        pushButton_FM->setObjectName(QStringLiteral("pushButton_FM"));
        pushButton_FM->setGeometry(QRect(0, 590, 320, 130));
        QFont font4;
        font4.setFamily(QStringLiteral("Calibri Light"));
        font4.setPointSize(60);
        pushButton_FM->setFont(font4);
        pushButton_AM = new QPushButton(centralWidget);
        pushButton_AM->setObjectName(QStringLiteral("pushButton_AM"));
        pushButton_AM->setGeometry(QRect(320, 590, 320, 130));
        pushButton_AM->setFont(font4);
        pushButton_ScanSatation = new QPushButton(centralWidget);
        pushButton_ScanSatation->setObjectName(QStringLiteral("pushButton_ScanSatation"));
        pushButton_ScanSatation->setGeometry(QRect(960, 590, 320, 130));
        pushButton_ScanSatation->setFont(font4);
        pushButton_Power = new QPushButton(centralWidget);
        pushButton_Power->setObjectName(QStringLiteral("pushButton_Power"));
        pushButton_Power->setGeometry(QRect(0, 0, 180, 90));
        pushButton_Power->setFont(font3);
        label_FreqMin = new QLabel(centralWidget);
        label_FreqMin->setObjectName(QStringLiteral("label_FreqMin"));
        label_FreqMin->setGeometry(QRect(230, 280, 81, 41));
        QFont font5;
        font5.setPointSize(20);
        label_FreqMin->setFont(font5);
        label_FreqMax = new QLabel(centralWidget);
        label_FreqMax->setObjectName(QStringLiteral("label_FreqMax"));
        label_FreqMax->setGeometry(QRect(1000, 280, 81, 41));
        label_FreqMax->setFont(font5);
        pushButton_exit = new QPushButton(centralWidget);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(1100, 0, 180, 90));
        pushButton_exit->setFont(font3);
        pushButton_VolSetting = new QPushButton(centralWidget);
        pushButton_VolSetting->setObjectName(QStringLiteral("pushButton_VolSetting"));
        pushButton_VolSetting->setGeometry(QRect(640, 590, 320, 130));
        pushButton_VolSetting->setFont(font4);
        pushButton_Station1 = new QPushButton(centralWidget);
        pushButton_Station1->setObjectName(QStringLiteral("pushButton_Station1"));
        pushButton_Station1->setGeometry(QRect(160, 370, 220, 50));
        QFont font6;
        font6.setFamily(QStringLiteral("Arial"));
        font6.setPointSize(35);
        font6.setBold(true);
        font6.setWeight(75);
        pushButton_Station1->setFont(font6);
        pushButton_Station2 = new QPushButton(centralWidget);
        pushButton_Station2->setObjectName(QStringLiteral("pushButton_Station2"));
        pushButton_Station2->setGeometry(QRect(480, 370, 220, 50));
        pushButton_Station2->setFont(font6);
        pushButton_Station4 = new QPushButton(centralWidget);
        pushButton_Station4->setObjectName(QStringLiteral("pushButton_Station4"));
        pushButton_Station4->setGeometry(QRect(160, 480, 220, 50));
        pushButton_Station4->setFont(font6);
        pushButton_Station5 = new QPushButton(centralWidget);
        pushButton_Station5->setObjectName(QStringLiteral("pushButton_Station5"));
        pushButton_Station5->setGeometry(QRect(480, 480, 220, 50));
        pushButton_Station5->setFont(font6);
        pushButton_Station3 = new QPushButton(centralWidget);
        pushButton_Station3->setObjectName(QStringLiteral("pushButton_Station3"));
        pushButton_Station3->setGeometry(QRect(800, 370, 220, 50));
        pushButton_Station3->setFont(font6);
        pushButton_Station6 = new QPushButton(centralWidget);
        pushButton_Station6->setObjectName(QStringLiteral("pushButton_Station6"));
        pushButton_Station6->setGeometry(QRect(800, 480, 220, 50));
        pushButton_Station6->setFont(font6);
        pushButton_RadioUp = new QPushButton(centralWidget);
        pushButton_RadioUp->setObjectName(QStringLiteral("pushButton_RadioUp"));
        pushButton_RadioUp->setGeometry(QRect(1080, 220, 90, 90));
        pushButton_RadioUp->setFont(font3);
        pushButton_RadioDown = new QPushButton(centralWidget);
        pushButton_RadioDown->setObjectName(QStringLiteral("pushButton_RadioDown"));
        pushButton_RadioDown->setGeometry(QRect(120, 220, 90, 90));
        pushButton_RadioDown->setFont(font3);
        verticalSlider_vol = new QSlider(centralWidget);
        verticalSlider_vol->setObjectName(QStringLiteral("verticalSlider_vol"));
        verticalSlider_vol->setGeometry(QRect(790, 430, 16, 160));
        verticalSlider_vol->setMinimum(-60);
        verticalSlider_vol->setMaximum(24);
        verticalSlider_vol->setPageStep(2);
        verticalSlider_vol->setOrientation(Qt::Vertical);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QApplication::translate("MainWindow", "MHz", 0));
        pushButton_PageUp->setText(QApplication::translate("MainWindow", "\342\210\247", 0));
        pushButton_PageDown->setText(QApplication::translate("MainWindow", "\342\210\250", 0));
        pushButton_NextSatation->setText(QApplication::translate("MainWindow", "\357\274\236", 0));
        pushButton_PrevStation->setText(QApplication::translate("MainWindow", "\357\274\234", 0));
        pushButton_FM->setText(QApplication::translate("MainWindow", "FM", 0));
        pushButton_AM->setText(QApplication::translate("MainWindow", "AM", 0));
        pushButton_ScanSatation->setText(QApplication::translate("MainWindow", "\346\220\234\345\217\260", 0));
        pushButton_Power->setText(QApplication::translate("MainWindow", "\345\274\200\345\205\263", 0));
        label_FreqMin->setText(QApplication::translate("MainWindow", "87.5", 0));
        label_FreqMax->setText(QApplication::translate("MainWindow", "108.0", 0));
        pushButton_exit->setText(QApplication::translate("MainWindow", "\350\277\224\345\233\236", 0));
        pushButton_VolSetting->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", 0));
        pushButton_Station1->setText(QApplication::translate("MainWindow", "0.000MHz", 0));
        pushButton_Station2->setText(QApplication::translate("MainWindow", "0.000MHz", 0));
        pushButton_Station4->setText(QApplication::translate("MainWindow", "0.000MHz", 0));
        pushButton_Station5->setText(QApplication::translate("MainWindow", "0.000MHz", 0));
        pushButton_Station3->setText(QApplication::translate("MainWindow", "0.000MHz", 0));
        pushButton_Station6->setText(QApplication::translate("MainWindow", "0.000MHz", 0));
        pushButton_RadioUp->setText(QApplication::translate("MainWindow", "\357\274\236", 0));
        pushButton_RadioDown->setText(QApplication::translate("MainWindow", "\357\274\234", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
