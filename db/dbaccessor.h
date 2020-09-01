#ifndef DBACCESSOR_H
#define DBACCESSOR_H

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QDir>
#include <QThread>

#include "sqlitedatabase.h"
#include "../dbrowdata.h"
//#include "sqltablemodel.h"
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
//  int addNewStatement();
  QString randString(int len);
//  void removeByID(int id);
//  void updateRow(const DbRowData* data);
  rows_list requestForAll();

  void prepareRowId(int id);
  void prepareRow(const DbRowData* row);
public slots:
  void addNewStatement();
  void updateRow();
  void removeByID();
private:
//  rows_list& data_list_ ;
  QSqlDatabase db_ ;
  SQLiteDataBase* sql_;
  QSqlQuery* query_ = Q_NULLPTR;
  int id_;
  const DbRowData* row_;
  void clearQueryResult();
  void executeQuery(const QString &query_string);
  bool canReadNextResultRow();
  QString resultAsString(int index);
};

#endif // DBACCESSOR_H
