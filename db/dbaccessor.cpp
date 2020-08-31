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
    return;
  }
//  if (!db_.open()) {
//    QString err_msg {
//      "DBAccessor(): executeQuery(): "
//      + query_string
//      + " Connection was closed from the Database"
//    };
//    qDebug() << err_msg.toStdString().c_str();
//    return;
//  }
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


rows_list DBAccessor::requestForAll(
)
{
  executeQuery("SELECT * FROM testtbkl");
  rows_list data_set;
  while (canReadNextResultRow()) {
    data_set.append(DbRowData(
                      resultAsString(0).toInt(),
                      resultAsString(1),
                      resultAsString(2),
                      resultAsString(3),
                      resultAsString(4),
                      resultAsString(5),
                      resultAsString(6)
                      ));
  }
  return data_set;
}

QString DBAccessor::randString(int len)
{
    QString str;
    str.resize(len);
    for (int s = 0; s < len ; ++s)
        str[s] = QChar('A' + char(qrand() % ('Z' - 'A')));

    return str;
}

void DBAccessor::removeByID(int id)
{
  executeQuery(QString("DELETE FROM testtbkl WHERE id='%1'").arg(QString::number(id)));
}

void DBAccessor::updateRow(const DbRowData* data)
{
  executeQuery(QString("UPDATE testtbkl "
                       "SET texteditor = '%1', fileformats = '%2', encoding = '%3', hasintellisense = '%4', hasplugins = '%5', cancompile = '%6' "
                       "WHERE id =%7 ").arg(
                 data->texteditor_,
                 data->fileformats_,
                 data->encoding_,
                 data->hasintellisense_,
                 data->hasplugins_,
                 data->cancompile_,
                 QString::number(data->id_)
                 )
               );
}

int DBAccessor::addNewStatement()
{
  executeQuery(QString("INSERT INTO testtbkl "
                       "(texteditor, fileformats, encoding, hasintellisense, hasplugins, cancompile) "
                       "VALUES( ' ',  ' ', ' ', ' ', ' ', ' ' )"
                       )
               );
  executeQuery(QString("SELECT last_insert_rowid()"));
  int id = -1;
  if (canReadNextResultRow())
    id = resultAsString(0).toInt();
  return id;
}
