#ifndef SQLTABLEFORM_H
#define SQLTABLEFORM_H

#include <QWidget>
#include "db/dbaccessor.h"
#include <QAbstractTableModel>
#include <QtWidgets>

namespace Ui {
  class SqlTableForm;
}

class SqlTableForm : public QWidget
{
  Q_OBJECT

public:
  explicit SqlTableForm();
  ~SqlTableForm();

  void setModel(QAbstractTableModel *model);
private slots:
  void on_pb_add_new_clicked();

  void on_pb_clear_clicked();

private:
  Ui::SqlTableForm *ui;
};

#endif // SQLTABLEFORM_H
