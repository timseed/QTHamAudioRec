#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
 //   ui->lb_length->setText(ui->comboBox->currentText());
//    NewFile = new QTimer();
//    connect(NewFile,SIGNAL(timeout()),this,SLOT(OnTimer()));
    ham_audio = new HamAudioRecord(NULL,15,"/Users/tim/TLogAudio/IOTA_");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ButtonPressed()
{
//    int timed_spacing = ui->comboBox->currentText().toInt();
//    QDateTime now = QDateTime::currentDateTimeUtc();
//    qint64  remainder=now.toMSecsSinceEpoch();
//    remainder=timed_spacing*1000 - remainder%(timed_spacing*1000);
//    NewFile->setInterval(remainder);    // Milli Second Fidge for the previous calcs
//    NewFile->start();
//    qInfo() << "We want a Timer for " << timed_spacing << " Seconds";
//    qInfo() << " Current Time is " << now.toString("hh:mm:ss.z");
//    qInfo() << "We need to set a timer for the remainder of this time period";
//    qInfo() << "Initial Timer needs to be " << remainder << " milli seconds";
}

void MainWindow::OnTimer()
{
//    int timed_spacing = ui->comboBox->currentText().toInt();
//    NewFile->setInterval(timed_spacing*1000);
//    QDateTime now = QDateTime::currentDateTimeUtc();
//    qInfo() << " Timer has gone off " << now.toString("hh:mm:ss.z");

}


void MainWindow::on_pushButton_clicked()
{
    ham_audio->Calc_Timer();
    ham_audio->Record();
}


void MainWindow::on_pushButton_2_clicked()
{
    ham_audio->Stop();
}

