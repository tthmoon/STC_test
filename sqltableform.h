#ifndef SQLTABLEFORM_H
#define SQLTABLEFORM_H

#include <QWidget>
#include "db/dbaccessor.h"
#include <QAbstractTableModel>

namespace Ui {
  class SqlTableForm;
}

class SqlTableForm : public QWidget
{
  Q_OBJECT

public:
  explicit SqlTableForm( DBAccessor* db = 0);
  ~SqlTableForm();

  void setModel(QAbstractTableModel *model);
private slots:
  void on_pb_add_new_clicked();

  void on_pb_clear_clicked();

private:
  DBAccessor* db_ = Q_NULLPTR;
  Ui::SqlTableForm *ui;
};

#endif // SQLTABLEFORM_H
