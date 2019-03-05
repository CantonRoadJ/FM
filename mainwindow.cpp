#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>

#define ROOT
#include "public.h"
#include "Tuner_Boot_Lithio.h"

#include <QElapsedTimer>
#include <QDebug>

void SPI_Test(void);
void devSAF775x_test(void);
void SPI_Flash_Test(void);
void UartTest(void);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mutexStatus = false;

    ui->setupUi(this);
    ui->verticalSlider_vol->setHidden(true);
    showFullScreen();

    I2C1_Init();


    timerRun = new QTimer (this);

//    Tuner_Process();
//    devTEF668x_Audio_Set_Output_Source(33,4);
    on_pushButton_FM_clicked();

    timerRun->start(1);
    connect(timerRun,SIGNAL(timeout()),this,SLOT(run()));
}

void MainWindow::run()
{
//Init();
//Dbg_printf(" init finish\n");

//I2C1_Init();

//while(1)
{
    //WatchDog_Feed();
    //LED_Flash();
    //Key_Proc();
    //Clock_Proc();
    //Audio_Proc();
    //Power_Proc();
    //Tuner_Mode_Proc();
    //Sys_Mute_Proc();
    //DisplayProc();
    //StandBy_Proc();

    Tuner_Process();
//Tuner_Boot();
    //SPI_Flash_Test();
    //UartTest();

#ifdef RDS_ENABLE
    RDS_Module();
#endif
}
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_RadioUp_clicked()
{
#if 1
    Radio_ChangeFreqOneStep(1);
    /*write "new programmble value" into PLL*/
    Tuner_Update_ProgCnt(Radio_PRESETMODE);
    /*clear station number*/
    //Radio_ClearCurrentStation();

    QString freqString;
    freqString.setNum((float)Radio_GetCurrentFreq()/100);
    ui->lcdNumber_CurFreq->display(freqString);

    ui->horizontalSlider_CurFreq->setValue(Radio_GetCurrentFreq());

#endif
}

void MainWindow::on_pushButton_RadioDown_clicked()
{
#if 1
    Radio_ChangeFreqOneStep(0);
    /*write "new programmble value" into PLL*/
    Tuner_Update_ProgCnt(Radio_PRESETMODE);
    /*clear station number*/
    //Radio_ClearCurrentStation();

    QString freqString;
    freqString.setNum((float)Radio_GetCurrentFreq()/100);
    ui->lcdNumber_CurFreq->display(freqString);

    ui->horizontalSlider_CurFreq->setValue(Radio_GetCurrentFreq());
#endif
}

void MainWindow::on_pushButton_Power_clicked()
{
    static int powerStatus = 1;

    if (powerStatus)
    {
        powerStatus = 0;
    }
    else
    {
        powerStatus = 1;
    }

    APPL_PowerSwitch(powerStatus);
}

void MainWindow::on_pushButton_exit_clicked()
{
    APPL_PowerSwitch(0);
    exit(0);
}

void MainWindow::on_pushButton_PrevStation_clicked()
{
    timerRun->stop();

    qDebug("Radio_IsFMBand = %d",Radio_IsFMBand());

#if 1
    Radio_ChangeFreqOneStep(0);
    /*write "new programmble value" into PLL*/
    Tuner_Update_ProgCnt(Radio_PRESETMODE);
    /*clear station number*/
    Radio_ClearCurrentStation();



    Radio_CheckStationInit();//set check  and IF start step
    Radio_ClearCurrentStation();//Clear station number


    //Radio_CheckStation();

    while(1)
    {
        qDebug("Radio_CheckStationd");

        //Radio_CheckStation();

        //usleep(1000);

        if( Radio_CheckStationStatus() >=NO_STATION)
        {
            if(Radio_CheckStationStatus()== PRESENT_STATION)
            {
                qDebug("find the Radio station");
                break;
            }
            else
            {

                qDebug("can not find");

                QString freqString;
                freqString.setNum((float)Radio_GetCurrentFreq()/100);
                ui->lcdNumber_CurFreq->display(freqString);

                Radio_ChangeFreqOneStep(0);
                //usleep(1000);
                /*write "new programmble value" into PLL*/
                Tuner_Update_ProgCnt(Radio_PRESETMODE);
                /*clear station number*/
                Radio_ClearCurrentStation();

                Radio_CheckStationInit();//set check  and IF start step
                Radio_ClearCurrentStation();//Clear station number
                Radio_CheckStation();
                //break;
            }
        }
        else
        {
            Radio_CheckStation();
        }
    }
#endif
    qDebug("CurrentFreq = %d",Radio_GetCurrentFreq() );

    QString freqString;
    freqString.setNum((float)Radio_GetCurrentFreq()/100);
    ui->lcdNumber_CurFreq->display(freqString);

    ui->horizontalSlider_CurFreq->setValue(Radio_GetCurrentFreq());

    timerRun->start(1);

    qDebug("on_page_down_btu_clicked");
}

void MainWindow::on_pushButton_NextSatation_clicked()
{
    timerRun->stop();

#if 1
    Radio_ChangeFreqOneStep(1);
    /*write "new programmble value" into PLL*/
    Tuner_Update_ProgCnt(Radio_PRESETMODE);
    /*clear station number*/
    Radio_ClearCurrentStation();
#endif


    Radio_CheckStationInit();//set check  and IF start step
    Radio_ClearCurrentStation();//Clear station number


    //Radio_CheckStation();

    while(1)
    {
        qDebug("Radio_CheckStationd");

        //Radio_CheckStation();

        usleep(1000);

        if( Radio_CheckStationStatus() >=NO_STATION)
        {
            if(Radio_CheckStationStatus()== PRESENT_STATION)
            {
                qDebug("find the Radio station");
                break;
            }
            else
            {

                qDebug("can not find");

                Radio_ChangeFreqOneStep(1);
                //usleep(1000);
                /*write "new programmble value" into PLL*/
                Tuner_Update_ProgCnt(Radio_PRESETMODE);
                /*clear station number*/
                Radio_ClearCurrentStation();

                Radio_CheckStationInit();//set check  and IF start step
                Radio_ClearCurrentStation();//Clear station number
                Radio_CheckStation();
                //break;
            }
        }
        else
        {
            Radio_CheckStation();
        }
    }

    qDebug("CurrentFreq = %d",Radio_GetCurrentFreq() );

    QString freqString;
    freqString.setNum((float)Radio_GetCurrentFreq()/100);
    ui->lcdNumber_CurFreq->display(freqString);

    ui->horizontalSlider_CurFreq->setValue(Radio_GetCurrentFreq());

    timerRun->start(1);

    qDebug("on_page_down_btu_clicked");
}

void MainWindow::on_horizontalSlider_CurFreq_sliderMoved(int position)
{

    int tmpFreq = ui->horizontalSlider_CurFreq->value();

    if (tmpFreq % 10 != 0)
    {
        tmpFreq = (tmpFreq / 10) * 10;
        ui->horizontalSlider_CurFreq->setValue(tmpFreq);
    }

    qDebug("ui->horizontalSlider_CurFreq->value() = %d",tmpFreq);



    Radio_SetCurrentFreq(tmpFreq);
    Tuner_Update_ProgCnt(Radio_PRESETMODE);

    QString freqString;
    freqString.setNum((float)Radio_GetCurrentFreq()/100);
    ui->lcdNumber_CurFreq->display(freqString);


}

void MainWindow::on_horizontalSlider_CurFreq_sliderPressed()
{
    int tmpFreq = ui->horizontalSlider_CurFreq->value();

    if (tmpFreq % 10 != 0)
    {
        tmpFreq = (tmpFreq / 10) * 10;
        ui->horizontalSlider_CurFreq->setValue(tmpFreq);
    }

    qDebug("ui->horizontalSlider_CurFreq->value() = %d",tmpFreq);

    Radio_SetCurrentFreq(tmpFreq);
    Tuner_Update_ProgCnt(Radio_PRESETMODE);

    QString freqString;
    freqString.setNum((float)Radio_GetCurrentFreq()/100);
    ui->lcdNumber_CurFreq->display(freqString);
}

void MainWindow::on_pushButton_ScanSatation_clicked()
{
        //ui->pushButton_ScanSatation->setDisabled(true);

        qDebug("test");

        if (mutexStatus!=false)
        {
            qDebug("return");
            return ;
        }

        ui->pushButton_FM->setEnabled(false);
        ui->pushButton_AM->setEnabled(false);
        ui->pushButton_NextSatation->setEnabled(false);
        ui->pushButton_PrevStation->setEnabled(false);
        ui->pushButton_RadioDown->setEnabled(false);
        ui->pushButton_RadioUp->setEnabled(false);

        mutexStatus = true;

        timerRun->stop();

        U16 minFreq;
        U16 maxFreq;

        if (FMOrAM == FM_Type)
        {
            minFreq = Get_FM_Min_Freq();
            maxFreq = Get_FM_Max_Freq();
        }
        else
        {
            minFreq = Get_AM_Min_Freq();
            maxFreq = Get_AM_Max_Freq();
        }

      int count = 0;

      Radio_SetCurrentFreq(minFreq);
      Tuner_Update_ProgCnt(Radio_PRESETMODE);

     QString freqString;
     freqString.setNum((float)Radio_GetCurrentFreq()/100);
    ui->lcdNumber_CurFreq->display(freqString);

    ui->horizontalSlider_CurFreq->setValue(Radio_GetCurrentFreq());
    //usleep(50000);



    Radio_CheckStationInit();//set check  and IF start step
    Radio_ClearCurrentStation();//Clear station number

    //
    for(int i=0;i<FreqResultMax; i++)
    {
        FreqResult[i] = 0;
    }

    pageCurrent=pageMin;

    updateStationButton();

    updatePageButton();

    //usleep(50000);
#if 1
    while( (Radio_GetCurrentFreq() < maxFreq) )
    {
        //qDebug("Radio_CheckStationd");

        QCoreApplication::processEvents();

        freqString.setNum((float)Radio_GetCurrentFreq()/100);
        ui->lcdNumber_CurFreq->display(freqString);

        ui->horizontalSlider_CurFreq->setValue(Radio_GetCurrentFreq());

        Radio_CheckStation();

        usleep(1000);

        if( Radio_CheckStationStatus() >=NO_STATION)
        {
            if(Radio_CheckStationStatus()== PRESENT_STATION)
            {
                //qDebug("find the Radio station");
                FreqResult[count] = Radio_GetCurrentFreq();
                count++;

                if (count%stationButtonCount==0)
                {
                    pageMax = (count/stationButtonCount) - 1;
                }
                else
                {
                    pageMax = (count/stationButtonCount);
                }

                updateStationButton();
                on_pushButton_PageDown_clicked();
                updatePageButton();


                Radio_ChangeFreqOneStep(1);
                Tuner_Update_ProgCnt(Radio_PRESETMODE);
                Radio_CheckStationInit();
                continue;
            }
            else
            {
                //qDebug("can not find");
                Radio_ChangeFreqOneStep(1);
                usleep(1000);
                /*write "new programmble value" into PLL*/
                Tuner_Update_ProgCnt(Radio_PRESETMODE);
                /*clear station number*/
                //Radio_ClearCurrentStation();

                Radio_CheckStationInit();//set check  and IF start step
//                Radio_ClearCurrentStation();//Clear station number
//                Radio_CheckStation();
                //break;
                continue;
            }
        }
        else
        {
            //Radio_CheckStation();
            continue;
        }
    }

    for(int i=0;i<count; i++)
    {
        qDebug("FreqResult[%d]=%d",i,FreqResult[i]);
    }

//    pageCurrent=pageMin;

//    if (count%stationButtonCount==0)
//    {
//        pageMax = (count/stationButtonCount) - 1;
//    }
//    else
//    {
//        pageMax = (count/stationButtonCount);
//    }

//    updateStationButton();
    on_pushButton_Station1_clicked();
    qDebug("on_pushButton_ScanSatation_clicked is finish");
#endif
    timerRun->start(1);
    mutexStatus = false;
    //ui->pushButton_ScanSatation->setDisabled(false);
    ui->pushButton_FM->setEnabled(true);
    ui->pushButton_AM->setEnabled(true);
    ui->pushButton_NextSatation->setEnabled(true);
    ui->pushButton_PrevStation->setEnabled(true);
    ui->pushButton_RadioDown->setEnabled(true);
    ui->pushButton_RadioUp->setEnabled(true);

}

void MainWindow::on_pushButton_PageUp_clicked()
{
    if (pageCurrent != pageMin)
    {
        pageCurrent--;
    }

    updateStationButton();
    updatePageButton();
}

void MainWindow::on_pushButton_PageDown_clicked()
{
    if (pageCurrent < pageMax)
    {
        pageCurrent++;
    }

    updateStationButton();
    updatePageButton();
}

void MainWindow::updatePageButton()
{
    ui->pushButton_PageUp->setEnabled(true);
    ui->pushButton_PageDown->setEnabled(true);

    if (pageMax == pageMin)
    {
        ui->pushButton_PageUp->setEnabled(false);
        ui->pushButton_PageDown->setEnabled(false);
    }

    if (pageCurrent==pageMin)
    {
        ui->pushButton_PageUp->setEnabled(false);
    }

    if (pageCurrent==pageMax)
    {
        ui->pushButton_PageDown->setEnabled(false);
    }
}

void MainWindow::updateStationButton()
{
    QString tmpFreqString;
    tmpFreqString.setNum( (float)(FreqResult[pageCurrent*stationButtonCount+0]) / 100);
    ui->pushButton_Station1->setText(tmpFreqString);

    if (tmpFreqString=="0")
    {
        ui->pushButton_Station1->setHidden(true);
    }
    else
    {
        ui->pushButton_Station1->setHidden(false);
    }

    tmpFreqString.setNum( (float)(FreqResult[pageCurrent*stationButtonCount+1]) / 100);
    ui->pushButton_Station2->setText(tmpFreqString);

    if (tmpFreqString=="0")
    {
        ui->pushButton_Station2->setHidden(true);
    }
    else
    {
        ui->pushButton_Station2->setHidden(false);
    }


    tmpFreqString.setNum( (float)(FreqResult[pageCurrent*stationButtonCount+2]) / 100);
    ui->pushButton_Station3->setText(tmpFreqString);

    if (tmpFreqString=="0")
    {
        ui->pushButton_Station3->setHidden(true);
    }
    else
    {
        ui->pushButton_Station3->setHidden(false);
    }


    tmpFreqString.setNum( (float)(FreqResult[pageCurrent*stationButtonCount+3]) / 100);
    ui->pushButton_Station4->setText(tmpFreqString);

    if (tmpFreqString=="0")
    {
        ui->pushButton_Station4->setHidden(true);
    }
    else
    {
        ui->pushButton_Station4->setHidden(false);
    }


    tmpFreqString.setNum( (float)(FreqResult[pageCurrent*stationButtonCount+4]) / 100);
    ui->pushButton_Station5->setText(tmpFreqString);

    if (tmpFreqString=="0")
    {
        ui->pushButton_Station5->setHidden(true);
    }
    else
    {
        ui->pushButton_Station5->setHidden(false);
    }


    tmpFreqString.setNum( (float)(FreqResult[pageCurrent*stationButtonCount+5]) / 100);
    ui->pushButton_Station6->setText(tmpFreqString);

    if (tmpFreqString=="0")
    {
        ui->pushButton_Station6->setHidden(true);
    }
    else
    {
        ui->pushButton_Station6->setHidden(false);
    }

}

void MainWindow::on_pushButton_Station1_clicked()
{
    int freq = ui->pushButton_Station1->text().toFloat() *100;

    if (freq == 0)
    {
        return ;
    }

    Radio_SetCurrentFreq(freq);
    Tuner_Update_ProgCnt(Radio_PRESETMODE);

    QString freqString;
    freqString.setNum((float)Radio_GetCurrentFreq()/100);
    ui->lcdNumber_CurFreq->display(freqString);

    ui->horizontalSlider_CurFreq->setValue(Radio_GetCurrentFreq());

}

void MainWindow::on_pushButton_Station2_clicked()
{
    int freq = ui->pushButton_Station2->text().toFloat() *100;

    if (freq == 0)
    {
        return ;
    }

    Radio_SetCurrentFreq(freq);
    Tuner_Update_ProgCnt(Radio_PRESETMODE);

    QString freqString;
    freqString.setNum((float)Radio_GetCurrentFreq()/100);
    ui->lcdNumber_CurFreq->display(freqString);

    ui->horizontalSlider_CurFreq->setValue(Radio_GetCurrentFreq());
}

void MainWindow::on_pushButton_Station3_clicked()
{
    int freq = ui->pushButton_Station3->text().toFloat() *100;

    if (freq == 0)
    {
        return ;
    }

    Radio_SetCurrentFreq(freq);
    Tuner_Update_ProgCnt(Radio_PRESETMODE);

    QString freqString;
    freqString.setNum((float)Radio_GetCurrentFreq()/100);
    ui->lcdNumber_CurFreq->display(freqString);

    ui->horizontalSlider_CurFreq->setValue(Radio_GetCurrentFreq());

}

void MainWindow::on_pushButton_Station4_clicked()
{
    int freq = ui->pushButton_Station4->text().toFloat() *100;

    if (freq == 0)
    {
        return ;
    }

    Radio_SetCurrentFreq(freq);
    Tuner_Update_ProgCnt(Radio_PRESETMODE);

    QString freqString;
    freqString.setNum((float)Radio_GetCurrentFreq()/100);
    ui->lcdNumber_CurFreq->display(freqString);

    ui->horizontalSlider_CurFreq->setValue(Radio_GetCurrentFreq());

}

void MainWindow::on_pushButton_Station5_clicked()
{
    timerRun->stop();

    int freq = ui->pushButton_Station5->text().toFloat() *100;

    if (freq == 0)
    {
        return ;
    }

    Radio_SetCurrentFreq(freq);
    Tuner_Update_ProgCnt(Radio_PRESETMODE);

    QString freqString;
    freqString.setNum((float)Radio_GetCurrentFreq()/100);
    ui->lcdNumber_CurFreq->display(freqString);

    ui->horizontalSlider_CurFreq->setValue(Radio_GetCurrentFreq());

    timerRun->start(1);
}

void MainWindow::on_pushButton_Station6_clicked()
{
    int freq = ui->pushButton_Station6->text().toFloat() *100;

    if (freq == 0)
    {
        return ;
    }

    Radio_SetCurrentFreq(freq);
    Tuner_Update_ProgCnt(Radio_PRESETMODE);

    QString freqString;
    freqString.setNum((float)Radio_GetCurrentFreq()/100);
    ui->lcdNumber_CurFreq->display(freqString);

    ui->horizontalSlider_CurFreq->setValue(Radio_GetCurrentFreq());
}

void MainWindow::on_pushButton_FM_clicked()
{
    timerRun->stop();

    FMOrAM = FM_Type;

    Radio_SetBand(FM3_BAND);

    Radio_SetCurrentFreq(9620);
    Tuner_Update_ProgCnt(Radio_PRESETMODE);

    QString tmpFreqString;
    tmpFreqString.setNum((float)(Radio_GetCurrentFreq())/100);

    ui->lcdNumber_CurFreq->display(tmpFreqString);


    ui->label_FreqMin->setText(QString::number(Get_FM_Min_Freq(),10));
    ui->label_FreqMax->setText(QString::number(Get_FM_Max_Freq(),10));

    ui->horizontalSlider_CurFreq->setMinimum(Get_FM_Min_Freq());
    ui->horizontalSlider_CurFreq->setMaximum(Get_FM_Max_Freq());
    ui->horizontalSlider_CurFreq->setSingleStep(10);

    ui->horizontalSlider_CurFreq->setValue(Radio_GetCurrentFreq());

    for(int i=0;i<FreqResultMax; i++)
    {
        FreqResult[i] = 0;
    }

    pageCurrent = pageMin;
    pageMax = pageMin;

    updateStationButton();
    updatePageButton();
    timerRun->start(1);
}

void MainWindow::on_pushButton_AM_clicked()
{
    timerRun->stop();

    FMOrAM = AM_Type;

    Radio_SetBand(MW_BAND);
    Radio_SetCurrentFreq(Get_AM_Min_Freq());
    Tuner_Update_ProgCnt(Radio_PRESETMODE);

    QString tmpFreqString;
    tmpFreqString.setNum((float)(Radio_GetCurrentFreq())/100);

    ui->lcdNumber_CurFreq->display(tmpFreqString);

    ui->label_FreqMin->setText(QString::number(Get_AM_Min_Freq(),10));
    ui->label_FreqMax->setText(QString::number(Get_AM_Max_Freq(),10));

    ui->horizontalSlider_CurFreq->setMinimum(Get_AM_Min_Freq());
    ui->horizontalSlider_CurFreq->setMaximum(Get_AM_Max_Freq());
    ui->horizontalSlider_CurFreq->setSingleStep(10);

    ui->horizontalSlider_CurFreq->setValue(Radio_GetCurrentFreq());

    for(int i=0;i<FreqResultMax; i++)
    {
        FreqResult[i] = 0;
    }

    pageCurrent = pageMin;
    pageMax = pageCurrent;

    updateStationButton();
    updatePageButton();

    timerRun->start(1);
}

void MainWindow::on_pushButton_VolSetting_clicked()
{
    static bool isShowVolSetting = false;

    isShowVolSetting = !isShowVolSetting;

    if (isShowVolSetting)
    {
        ui->verticalSlider_vol->setHidden(false);
    }
    else
    {
        ui->verticalSlider_vol->setHidden(true);
    }
}

void MainWindow::on_verticalSlider_vol_valueChanged(int value)
{
    qDebug()<<"on_verticalSlider_vol_valueChanged is "<<value;
    AUDIO_Set_Volume(value);
}

void MainWindow::on_verticalSlider_vol_actionTriggered(int action)
{

}
