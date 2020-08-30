#include "dbaccessor.h"

DBAccessor::DBAccessor(QSqlDatabase db)
{
  db_ = db;
  query_ = new QSqlQuery(db);
}

DBAccessor::~DBAccessor()
{
  delete query_;
}

void DBAccessor::executeQuery(const QString& query_string)
{
  clearQueryResult();
  if(!query_->exec(query_string)){
    QString err_msg { "DBAccessor(): executeQuery(): " + query_string };
    err_msg.append(" DataBase query error: ");
    err_msg.append(query_->lastError().text());
    qDebug() << err_msg.toStdString().c_str();
  }
  if (!db_.open()) {
    QString err_msg {
      "DBAccessor(): executeQuery(): "
      + query_string
      + " Connection was closed from the Database"
    };
    qDebug() << err_msg.toStdString().c_str();
  }
}

bool DBAccessor::canReadNextResultRow()
{
  if (!query_->isActive()) {
    qDebug() << QString(
                  "MySQLSyncConnector(): canReadNextResultRow(): Query: "
                  + query_->executedQuery()
                  + " Query is not active"
                  ).toStdString().c_str();
    return false;
  }
  return query_->next();
}

QString DBAccessor::resultAsString(int index)
{
  return query_->value(index).toString();
}

void DBAccessor::clearQueryResult()
{
  query_->finish();
  query_->clear();
}


QString DBAccessor::requestForStatement(
  const QString& id
)
{
  query_->setForwardOnly(true);
  executeQuery("SELECT (id) FROM testtbkl");
//  if ( query_->last( ) ) {
//      do {
//          qDebug() << query_->value(0).toString();
//      } while (query_->previous());
//  }
  while (canReadNextResultRow()) {
      QSqlRecord record = query_->record();
      for(int i=0; i < record.count(); i++)
      {
          qDebug() << record.value(i).toString();
      }
//    qDebug() << resultAsString(0);
  }
  return "test";
}

void DBAccessor::addNewStatement(
  const QString& id
)
{
  executeQuery("INSERT INTO testtbkl (first_name,second_name) VALUES( 'test', 'tese' )");
}
