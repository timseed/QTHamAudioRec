#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "hamaudiorecord.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
#include <QDebug>
#include <QTimer>
#include <QDateTime>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    QTimer *NewFile;
    HamAudioRecord *ham_audio;

private slots:
    void ButtonPressed();
    void OnTimer();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
