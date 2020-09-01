#ifndef IMPORTFORM_H
#define IMPORTFORM_H


#include <QWidget>
#include <QDebug>

#include "import/importthread.h"

namespace Ui {
  class ImportForm;
}

class ImportForm : public QWidget
{
  Q_OBJECT
signals:
  void signalImportFinished();

public:
  explicit ImportForm(QWidget *parent = 0);
  ~ImportForm();

  void startImporting();
  void closeEvent(QCloseEvent *event);
public slots:
  void slotImportStart(QList<QString> file_names);
  void slotImportFileError();
  void slotImported();
  void slotImportFinished();
private slots:
  void on_pb_exit_clicked();

private:
  Ui::ImportForm *ui;
  ImportThread* import_thread_;
};

#endif // IMPORTFORM_H
