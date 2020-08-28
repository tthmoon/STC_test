#ifndef DB_SQLITE_DATABASE_H
#define DB_SQLITE_DATABASE_H

namespace Db {
  class SQLiteDataBase;
}

#include <QString>
#include <QSqlDatabase>


class SQLiteDataBase
{
  Q_DISABLE_COPY(SQLiteDataBase)
public:
  explicit SQLiteDataBase(
    const QString& database_directory_path,
    const QString& database_file_name,
    const QString& database_connection_name
  );
  virtual ~SQLiteDataBase();
  void connect();
  QSqlDatabase getDataBase();
  void createTable(
    const QString& table_name,
    const QString& table_structure
  );

private:
  const QString directory_path_;
  const QString file_name_;
  const QString connection_name_;
};

#endif // DB_SQLITE_DATABASE_H
