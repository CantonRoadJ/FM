#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum FreqType{
        FM_Type = 1,
        AM_Type =2
    };

//    typedef  struct _tagStation{
//        //station list
//        QVector<int>FreqResult;
//        //current station
//        int currentStation;
//        //
//       int pageCurrent;
//       //
//       int pageMin;
//       //
//       int pageMax;
//    }StationClass;

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:

    void on_pushButton_RadioUp_clicked();

    void on_pushButton_RadioDown_clicked();

    void run();

    void on_pushButton_Power_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_PrevStation_clicked();

    void on_pushButton_NextSatation_clicked();    

    void on_horizontalSlider_CurFreq_sliderMoved(int position);

    void on_pushButton_ScanSatation_clicked();

    void on_pushButton_PageUp_clicked();

    void on_pushButton_PageDown_clicked();

    void on_pushButton_Station1_clicked();

    void on_pushButton_Station2_clicked();

    void on_pushButton_Station3_clicked();

    void on_pushButton_Station4_clicked();

    void on_pushButton_Station5_clicked();

    void on_pushButton_Station6_clicked();

    void on_horizontalSlider_CurFreq_sliderPressed();

    void on_pushButton_FM_clicked();

    void on_pushButton_AM_clicked();

    void on_pushButton_VolSetting_clicked();

    void on_verticalSlider_vol_valueChanged(int value);

    void on_verticalSlider_vol_actionTriggered(int action);

private:
    void updateStationButton();
    void updatePageButton();

private:
    Ui::MainWindow *ui;
    QTimer *timerRun;
    uint pageCurrent = 0;
    uint pageMin = 0;
    uint pageMax = 0;
    uint stationButtonCount = 6;
    uint FreqResultMax = 512;
    unsigned short int  FreqResult[512]={0};
    FreqType FMOrAM = FM_Type;
    volatile  bool mutexStatus = false;
};

#endif // MAINWINDOW_H
