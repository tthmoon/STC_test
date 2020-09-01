#include "dbaccessor.h"

DBAccessor::DBAccessor()
{
  sql_ = new SQLiteDataBase(QDir::currentPath(), QString("test.sql"), randString(16));
  sql_->connect();
  query_ = new QSqlQuery(sql_->getDataBase());
}

DBAccessor::~DBAccessor()
{
  delete query_;
}

void DBAccessor::prepareRowId(int id){
//  qDebug() << QString::number(id_);
  id_ = id;
}

void DBAccessor::prepareRow(const DbRowData* row){
  row_ = row;
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

void DBAccessor::removeByID()
{
  executeQuery(QString("DELETE FROM testtbkl WHERE id='%1'").arg(QString::number(id_)));
  emit signal_removeByID(id_);
}

void DBAccessor::updateRow()
{
  executeQuery(QString("UPDATE testtbkl "
                       "SET texteditor = '%1', fileformats = '%2', encoding = '%3', hasintellisense = '%4', hasplugins = '%5', cancompile = '%6' "
                       "WHERE id =%7 ").arg(
                 row_->texteditor_,
                 row_->fileformats_,
                 row_->encoding_,
                 row_->hasintellisense_,
                 row_->hasplugins_,
                 row_->cancompile_,
                 QString::number(row_->id_)
                 )
               );
  emit signal_updateRow();
}

void DBAccessor::addNewStatement()
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
  emit signal_addNewStatement(id);
}
