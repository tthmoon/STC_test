#ifndef DBACCESSOR_H
#define DBACCESSOR_H

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

#include "sqlitedatabase.h"
#include "../dbrowdata.h"
//#include "sqltablemodel.h"
using rows_list = QList<DbRowData>;

class DBAccessor
{
public:
  DBAccessor(QSqlDatabase db);
  ~DBAccessor();
  int addNewStatement();
  QString requestForStatement(const QString &id);
  QString randString(int len);
  void removeByID(int id);
  void updateRow(const DbRowData* data);
  rows_list requestForAll();
private:
  QSqlDatabase db_ ;
  QSqlQuery* query_ = Q_NULLPTR;
  void clearQueryResult();
  void executeQuery(const QString &query_string);
  bool canReadNextResultRow();
  QString resultAsString(int index);
};

#endif // DBACCESSOR_H
