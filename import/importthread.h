#ifndef IMPORT_THREAD_H
#define IMPORT_THREAD_H


#include <QThread>
#include <QList>


class ImportThread : public QThread
{
  Q_OBJECT

signals:
  void signalErrorImportDirectoryFail();
  void signalImportStart(QList<QString> file_names);
  void signalImportFileError();
  void signalImported();
  void signalImportFinished();

public:
  explicit ImportThread();
  virtual ~ImportThread() override;
  void startProcess(
  );
  void quit();

  void coreStop();
  bool isCoreRunning();

protected:
  void run() override;

private:
  bool work_is_enable_ = false;
  QString directory_path_;
};

#endif //IMPORT_THREAD_H
