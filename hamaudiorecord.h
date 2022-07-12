#ifndef HAMAUDIORECORD_H
#define HAMAUDIORECORD_H

#include <QWidget>

#include <QMediaRecorder>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QMediaFormat>
#include <QAudioInput>
#include <QAudioDevice>
#include <QUrl>
#include <QDateTime>
#include <QTimer>
#include <QThread>

class QMediaRecorder;

class HamAudioRecord : public QWidget
{
    Q_OBJECT
public:
    explicit HamAudioRecord(QWidget *parent = nullptr,int LengthOfRecording=10,QString output_spec="");

    void Stop();

    void Record();
    bool getRecording() const;
    void setRecording(bool newRecording);

    int getRecordingLength() const;
    void setRecordingLength(int newRecordingLength);
    void Calc_Timer();

    const QString &getFileSpec() const;
    void setFileSpec(const QString &newFileSpec);

public slots:
    void RecordTimerTriggered();
    void ShowRecorderState(QMediaRecorder::RecorderState);
    void updateProgress(qint64  p);
//    void displayErrorMessage(QMediaRecorder::Error e,const QString &msg);
    void RecorderState(QMediaRecorder::RecorderState rs);

    void onStateChanged(QMediaRecorder::RecorderState state);
    void displayErrorMessage();
private:
    QMediaCaptureSession m_captureSession;
    QMediaRecorder *m_audioRecorder = nullptr;
    int RecordingLength;
    bool Recording;
    QTimer *NewFile;
    bool bFirstTime=true;
    QString FileSpec="/Users/tim/";

signals:

};

#endif // HAMAUDIORECORD_H
