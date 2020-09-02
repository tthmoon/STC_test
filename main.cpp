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

#include "xml/xmlreader.h"

using rows_list = QList<DbRowData>;
Q_DECLARE_METATYPE(rows_list)
//Q_DECLARE_METATYPE(QMap<QString,QString>)
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  qRegisterMetaType<rows_list>();
  qRegisterMetaType<QMap<QString,QString>>();

  SQLiteDataBase* sql = new SQLiteDataBase(QDir::currentPath(), QString("test.sql"), QString("tester"));
  sql->connect();
  sql->createTable(QString("testtbkl"),
                   QString("id INTEGER PRIMARY KEY, "
                           "texteditor TEXT NOT NULL,"
                           "fileformats TEXT NOT NULL,"
                           "encoding TEXT NOT NULL,"
                           "hasintellisense TEXT NOT NULL,"
                           "hasplugins TEXT NOT NULL,"
                           "cancompile TEXT NOT NULL"
                           )
                   );
//  MainWindow w;
//  DBAccessor* db = new DBAccessor(sql->getDataBase());
  SqlTableForm* sqlTable = new SqlTableForm();
  sqlTable->show();
//  w.show();

  return a.exec();
}
