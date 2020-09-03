#include <QApplication>
#include <QDir>
#include <QString>
#include <QSqlDatabase>
#include <QDebug>
#include "sqltableform.h"
#include "db/sqlitedatabase.h"

using rows_list = QList<DbRowData>;
//  Регистрация мета-типа для использование я вызовах
Q_DECLARE_METATYPE(rows_list)
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
//  Регистрация мета-типа для использование я вызовах
  qRegisterMetaType<rows_list>();

  SQLiteDataBase* sql = new SQLiteDataBase(QDir::currentPath(), QString("test.sql"), QString("tester"));
//  Создание таблицы
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
  SqlTableForm* sqlTable = new SqlTableForm();
  sqlTable->show();

  return a.exec();
}
