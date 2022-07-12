#include "hamaudiorecord.h"

HamAudioRecord::HamAudioRecord(QWidget *parent, int LengthOfRecording, QString output_spec)
    : QWidget{parent} {
  qInfo() << "Starting ";
  m_audioRecorder = new QMediaRecorder(this);
  m_captureSession.setRecorder(m_audioRecorder);
  m_captureSession.setAudioInput(new QAudioInput(this));
  setRecording(false);
  setRecordingLength(LengthOfRecording);
  NewFile = new QTimer();

  if (output_spec!="")
  {
      setFileSpec(output_spec);
      qInfo() << "Output base specification set as "<< getFileSpec();

  }


  connect(NewFile, SIGNAL(timeout()), this, SLOT(RecordTimerTriggered()));

  m_captureSession.audioInput()->setDevice(QMediaDevices::defaultAudioInput());
  // FLAC needs aprox 37Mb per Hour
  // WAV needs apx 600Mb per Hour !!
  m_audioRecorder->setMediaFormat(QMediaFormat::MP3);
  m_audioRecorder->setAudioSampleRate(44100);
  m_audioRecorder->setAudioBitRate(3200);
  m_audioRecorder->setAudioChannelCount(2);
  m_audioRecorder->setQuality(QMediaRecorder::Quality(2));
  m_audioRecorder->setEncodingMode(QMediaRecorder::ConstantQualityEncoding);

  connect(m_audioRecorder, SIGNAL(durationChanged(qint64)), this,
          SLOT(updateProgress(qint64)));

  connect(m_audioRecorder, &QMediaRecorder::durationChanged, this,
          &HamAudioRecord::updateProgress);
  connect(m_audioRecorder, &QMediaRecorder::recorderStateChanged, this,
          &HamAudioRecord::onStateChanged);
  connect(m_audioRecorder, &QMediaRecorder::errorChanged, this,
          &HamAudioRecord::displayErrorMessage);
}

void HamAudioRecord::Record() {
  setRecording(true);
  QString fname = getFileSpec() + QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd_hh_mm_ss_z");
  QUrl audiooutput_url = QUrl::fromLocalFile(fname);
  qInfo() << "Output url is valid " << audiooutput_url.isValid();
  qInfo() << "Filename should be " << fname;
  m_audioRecorder->setOutputLocation(audiooutput_url);
  qInfo() << "Saving to " << m_audioRecorder->outputLocation().fileName();
  // m_audioRecorder->record();

  if (m_audioRecorder->recorderState() == QMediaRecorder::StoppedState) {
    qInfo() << "Starting Recorder";
    m_audioRecorder->record();
  }
}

void HamAudioRecord::Calc_Timer() {
  if (!bFirstTime) {
    qInfo() << "Timer is active";
    qInfo() << "Std Record "
            << QDateTime::currentDateTimeUtc().toString("hh:mm:ss.z");
    NewFile->setInterval(getRecordingLength() * 1000);
    NewFile->start();
  } else {
    qInfo() << "Timer is in-active";
    int timed_spacing = getRecordingLength();
    QDateTime now = QDateTime::currentDateTimeUtc();
    qint64 remainder = now.toMSecsSinceEpoch();
    remainder = timed_spacing * 1000 - remainder % (timed_spacing * 1000);
    NewFile->setInterval(
        remainder); // Milli Second Fidge for the previous calcs
    NewFile->start();

    qInfo() << "We want a Timer for " << timed_spacing << " Seconds";
    qInfo() << " Current Time is " << now.toString("hh:mm:ss.z");
    qInfo() << "We need to set a timer for the remainder of this time period";
    qInfo() << "Initial Timer needs to be " << remainder << " milli seconds";
    bFirstTime = false;
  }
}

void HamAudioRecord::RecordTimerTriggered() { m_audioRecorder->stop(); }

void HamAudioRecord::ShowRecorderState(QMediaRecorder::RecorderState rs) {
  switch (rs) {
  case QMediaRecorder::RecorderState::PausedState:
    qInfo() << "Paused State";
    break;
  case QMediaRecorder::RecorderState::RecordingState:
    qInfo() << "Recording State";
    Calc_Timer();
    Record();
    break;
  case QMediaRecorder::RecorderState::StoppedState:
    qInfo() << "Stopped State";
    break;
  default:
    qInfo() << "Unknown State";
  }
}

void HamAudioRecord::updateProgress(qint64 p) {
  if (p % 100 == 0)
    qInfo() << "UpdateProgress is now " << p;
}

void HamAudioRecord::RecorderState(QMediaRecorder::RecorderState rs) {}

void HamAudioRecord::onStateChanged(QMediaRecorder::RecorderState state) {
  QString statusMessage;

  switch (state) {
  case QMediaRecorder::RecordingState:
    statusMessage =
        tr("Recording to %1").arg(m_audioRecorder->actualLocation().toString());
    qInfo() << statusMessage;

    break;
  case QMediaRecorder::PausedState:
    statusMessage = tr("Paused");
    qInfo() << statusMessage;
    break;
  case QMediaRecorder::StoppedState:

    statusMessage = tr("Stopped");
    qInfo() << statusMessage;
    if (getRecording()) {
      Calc_Timer();
      Record();
    }
    break;
  }
}

void HamAudioRecord::displayErrorMessage() {}

const QString &HamAudioRecord::getFileSpec() const
{
    return FileSpec;
}

void HamAudioRecord::setFileSpec(const QString &newFileSpec)
{
    FileSpec = newFileSpec;
}

// void HamAudioRecord::displayErrorMessage(QMediaRecorder::Error e, const
// QString &msg)
//{
//     qWarning() << m_audioRecorder->errorString();
// }

void HamAudioRecord::Stop() {
  setRecording(false);
  m_audioRecorder->stop();
  qInfo() << "Recording has stopped";
}

bool HamAudioRecord::getRecording() const { return Recording; }

void HamAudioRecord::setRecording(bool newRecording) {
  Recording = newRecording;
}

int HamAudioRecord::getRecordingLength() const { return RecordingLength; }

void HamAudioRecord::setRecordingLength(int newRecordingLength) {
  RecordingLength = newRecordingLength;
}
