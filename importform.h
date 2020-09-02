#ifndef IMPORTFORM_H
#define IMPORTFORM_H


#include <QWidget>
#include <QDebug>

#include "import/importthread.h"


namespace Ui {
  class ImportForm;
}

class ImportForm :
    public QWidget
{
  Q_OBJECT
signals:
  void signalImportFinished();

public:
  explicit ImportForm(QWidget *parent=0);
  ~ImportForm();

  void closeEvent(QCloseEvent *event);
  void startImporting(QString dir);
//  void addNewStatement(QMap<QString, QString>);

public slots:
  void slotImportStart(QStringList file_names);
  void slotFileImported();
  void slotImportFinished();
  void slotImportFileError(QString error);
private slots:
  void on_pb_exit_clicked();

private:
  Ui::ImportForm *ui;
  ImportThread* import_thread_;
};

#endif // IMPORTFORM_H
