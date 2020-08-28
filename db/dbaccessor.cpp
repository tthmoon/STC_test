#include "dbaccessor.h"

DBAccessor::DBAccessor(QSqlDatabase* db)
{
  db_ = db;
  query_ = new QSqlQuery(*db);
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
  if (!db_->open()) {
    QString err_msg {
      "DBAccessor(): executeQuery(): "
      + query_string
      + " Connection was closed from the Database"
    };
    qDebug() << err_msg.toStdString().c_str();
  }
}

void DBAccessor::clearQueryResult()
{
  query_->finish();
  query_->clear();
}


//CatchList AllVehiclesProcessor::requestForLicnumInOneZoneFromSpecificDeviceCatchList(
//  const QString& zone_id,
//  const QString& licnum,
//  const QString& device_serial,
//  int offset,
//  int limit
//)
//{
//  executeQuery(
//    call("AllVehicles_LicnumInOneZoneFromSpecificDeviceCatchList") +
//    "(" +
//      queryString(zone_id)        + ", " +
//      queryString(licnum)         + ", " +
//      queryString(device_serial)  + ", " +
//      queryString(limit)          + ", " +
//      queryString(offset)         +
//    ")"
//  );

//  return buildCatchList(limit);
//}
