#ifndef IMPORT_THREAD_H
#define IMPORT_THREAD_H


#include <QThread>
#include <QList>
#include <QDir>
#include "../xml/xmlreader.h"
#include "../db/dbaccessor.h"

class ImportThread : public QThread
{
  Q_OBJECT

signals:
  void signalErrorImportDirectoryFail();
  void signalImportStart(QStringList file_names);
  void signalImportFileError(QString error);
  void signalImported();
  void signalImportFinished();

public:
  explicit ImportThread();
  virtual ~ImportThread() override;
  void quit();

  void coreStop();
  bool isCoreRunning();

  void startProcess(QString directory);
protected:
  void run() override;

private:
  bool work_is_enable_ = false;
  QString directory_path_;
};

#endif //IMPORT_THREAD_H
