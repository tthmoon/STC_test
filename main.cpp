#include "mainwindow.h"
#include "db/sqlitedatabase.h"
#include <QApplication>
#include <QDir>
#include <QString>
#include <QSqlDatabase>
#include <QDebug>
#include "sqltableform.h"
#include "db/dbaccessor.h"
#include "db/sqltablemodel.h"


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  SQLiteDataBase* sql = new SQLiteDataBase(QDir::currentPath(), QString("test.sql"), QString("tester"));
  sql->connect();
  sql->createTable(QString("testtbkl"), QString("id INTEGER PRIMARY KEY, first_name TEXT NOT NULL, second_name TEXT NOT NULL"));
//  MainWindow w;
  DBAccessor* db = new DBAccessor(sql->getDataBase());
  SqlTableForm* sqlTable = new SqlTableForm(db);
  SqlTableModel myModel;
  sqlTable->setModel(&myModel);
  sqlTable->show();
//  w.show();

  return a.exec();
}
