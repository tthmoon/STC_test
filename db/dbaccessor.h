#ifndef DBACCESSOR_H
#define DBACCESSOR_H

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QDir>
#include <QThread>

#include "sqlitedatabase.h"
#include "../db/dbrowdata.h"
using rows_list = QList<DbRowData>;

class DBAccessor : public QObject
{
  Q_OBJECT

signals:
  void signal_addNewStatement(int);
  void signal_removeByID(int);
  void signal_updateRow();

public:

  DBAccessor();
  ~DBAccessor();
  QString randString(int len);
  rows_list requestForAll();

  void prepareRowId(int id);
  void prepareRow(const DbRowData* row);
  int addNewStatement(DbRowData *data);
public slots:
  void addNewStatement();
  void updateRow();
  void removeByID();
private:
  QSqlDatabase db_ ;
  SQLiteDataBase* sql_ = Q_NULLPTR;
  QSqlQuery* query_ = Q_NULLPTR;
  int id_;
  const DbRowData* row_ = Q_NULLPTR;
  void clearQueryResult();
  void executeQuery(const QString &query_string);
  bool canReadNextResultRow();
  QString resultAsString(int index);
};

#endif // DBACCESSOR_H
