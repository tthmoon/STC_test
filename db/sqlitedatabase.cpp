#include <QDebug>
#include <QDir>

#include <QSqlError>
#include <QSqlQuery>

#include "sqlitedatabase.h"

const QString CLASS_ID = "QSQLITE";

SQLiteDataBase::SQLiteDataBase(
  const QString& database_directory_path,
  const QString& database_file_name,
  const QString& database_connection_name
) :
  directory_path_{database_directory_path},
  file_name_{database_file_name},
  connection_name_{database_connection_name}
{

}

SQLiteDataBase::~SQLiteDataBase()
{
  QSqlDatabase::removeDatabase(connection_name_);
}

void SQLiteDataBase::connect()
{
  if (file_name_.isEmpty()){
    QString err_msg;
    QTextStream errs(&err_msg);
    errs << CLASS_ID;
    errs << " SQLiteDataBase() ";
    errs << "database_file_name is empty(): " << file_name_;
    errs.flush();
    qDebug() << err_msg.toStdString().c_str();
  }

  if (connection_name_.isEmpty()){
    QString err_msg;
    QTextStream errs(&err_msg);
    errs << CLASS_ID;
    errs << " SQLiteDataBase() ";
    errs << "database_connection_name is empty(): " << connection_name_;
  }

  QDir dir(directory_path_);
  if (!dir.exists()) {
    QString err_msg;
    QTextStream errs(&err_msg);
    errs << CLASS_ID;
    errs << " SQLiteDataBase() ";
    errs << "DataBase directory is fail: " << dir.path();
    qDebug() << err_msg.toStdString().c_str();
  }

  QString db_file_path(dir.path() + QDir::separator() + file_name_);
  QSqlDatabase db = QSqlDatabase::addDatabase(CLASS_ID, connection_name_);
  qDebug() << db_file_path;
  db.setDatabaseName(db_file_path);
  if (!db.open()) {
    QString err_msg;
    QTextStream errs(&err_msg);
    errs << CLASS_ID;
    errs << " SQLiteDataBase() ";
    errs << file_name_;
    errs << " DataBase file open error: " << db.lastError().text();
    qDebug() << err_msg.toStdString().c_str();
  }
}

QSqlDatabase SQLiteDataBase::getDataBase()
{
  return QSqlDatabase::database(connection_name_, true);
}

void SQLiteDataBase::createTable(
  const QString& table_name,
  const QString& table_structure
)
{
  QSqlDatabase db = getDataBase();
  QSqlQuery query(db);
  QString tbl_request =
    "CREATE TABLE IF NOT EXISTS " +
    table_name +
    " (" +
    table_structure +
    ")"
  ;
  if(!query.exec(tbl_request)){
    QString err_msg;
    QTextStream errs(&err_msg);
    errs << CLASS_ID;
    errs << " createTable() ";
    errs << "DataBase structure create error: " << db.lastError().text();
    errs.flush();
    qDebug() << err_msg.toStdString().c_str();
  }
}

