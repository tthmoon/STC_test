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
  executeQuery("SELECT * FROM testtbkl");
  while (canReadNextResultRow()) {
    qDebug() << resultAsString(0) << resultAsString(1);
  }
  return "test";
}

QString DBAccessor::randString(int len)
{
    QString str;
    str.resize(len);
    for (int s = 0; s < len ; ++s)
        str[s] = QChar('A' + char(qrand() % ('Z' - 'A')));

    return str;
}


void DBAccessor::addNewStatement(
  const QString& id
)
{
  executeQuery(QString("INSERT INTO testtbkl (first_name,second_name) VALUES( '%1', '%2' )").arg(randString(2), randString(4)));
}
