#ifndef SQLTABLEMODEL_H
#define SQLTABLEMODEL_H

#include <QAbstractTableModel>

#include "dbrowdata.h"

using rows_list = QList<DbRowData>;


class SqlTableModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  explicit SqlTableModel(QObject *parent = 0);

  // Header:
  enum HEADER_DATA{
    TEXTEDITOR,
    FILEFORMAT,
    ENCODING,
    HASINTELLICENCE,
    HASPLAGINS,
    CANCOMPILE,
    Count
  };
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  bool insertRows(int position, int rows, const QModelIndex &index);
  bool removeRows(int position, int rows, const QModelIndex &index);
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  rows_list getList();
private:
  rows_list data_list;
};

#endif // SQLTABLEMODEL_H
