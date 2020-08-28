#ifndef DBACCESSOR_H
#define DBACCESSOR_H

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

class DBAccessor
{
public:
  DBAccessor(QSqlDatabase* db);
  ~DBAccessor();
private:
  QSqlDatabase* db_ = Q_NULLPTR;
  QSqlQuery* query_ = Q_NULLPTR;
  void clearQueryResult();
  void executeQuery(const QString &query_string);
};

#endif // DBACCESSOR_H
