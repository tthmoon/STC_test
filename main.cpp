#include "mainwindow.h"
#include "db/sqlitedatabase.h"
#include <QApplication>
#include <QDir>
#include <QString>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  SQLiteDataBase* sql = new SQLiteDataBase(QDir::currentPath(), QString("test.sql"), QString("tester"));
  sql->connect();
  sql->createTable(QString("testtbkl"), QString("first_name TEXT NOT NULL"));
  MainWindow w;
  w.show();

  return a.exec();
}
