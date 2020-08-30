#ifndef DBACCESSOR_H
#define DBACCESSOR_H

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

#include "sqlitedatabase.h"

class DBAccessor
{
public:
  DBAccessor(QSqlDatabase db);
  ~DBAccessor();
  void addNewStatement(const QString &id);
  QString requestForStatement(const QString &id);
private:
  QSqlDatabase db_ ;
  QSqlQuery* query_ = Q_NULLPTR;
  void clearQueryResult();
  void executeQuery(const QString &query_string);
  bool canReadNextResultRow();
  QString resultAsString(int index);
};

#endif // DBACCESSOR_H
