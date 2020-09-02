#ifndef SQLTABLEFORM_H
#define SQLTABLEFORM_H

#include <QWidget>
#include "db/dbaccessor.h"
#include <QAbstractTableModel>
#include <QtWidgets>
#include <QFileDialog>

#include "importform.h"
#include "db/sqltablemodel.h"

namespace Ui {
  class SqlTableForm;
}

class SqlTableForm :
    public QWidget

{
  Q_OBJECT

public:
  SqlTableForm();
  ~SqlTableForm();
  void updateModel();
public slots:
  void slotImportFinished();
  void slotCustomMenuRequested(QPoint pos);
  void slotRemoveRecord();
private slots:
  void on_pb_add_new_clicked();

  void on_pb_clear_clicked();

  void on_pb_import_clicked();

private:
  Ui::SqlTableForm *ui;
  ImportForm* import_form_;
};

#endif // SQLTABLEFORM_H
