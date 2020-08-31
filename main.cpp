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

using rows_list = QList<DbRowData>;
Q_DECLARE_METATYPE(rows_list)
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  qRegisterMetaType<rows_list>();
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
  SqlTableModel* myModel = new SqlTableModel();
  sqlTable->setModel(myModel);
  sqlTable->show();
//  w.show();

  return a.exec();
}
