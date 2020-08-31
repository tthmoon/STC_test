#include "sqltablemodel.h"

SqlTableModel::SqlTableModel(DBAccessor* db)
  : db_{db}
{
  data_list = db_->requestForAll();
}

QVariant SqlTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{

  if (role != Qt::DisplayRole)
      return QVariant();

  if (orientation == Qt::Horizontal) {
    switch (section) {
      case TEXTEDITOR:
        return tr("Text editor");
      case FILEFORMAT:
        return tr("File format");
      case ENCODING:
        return tr("Encoding");
      case HASINTELLICENCE:
        return tr("Has intell licence");
      case HASPLAGINS:
        return tr("Has plagins");
      case CANCOMPILE:
        return tr("Can compile");
      default:
          return QVariant();
    }
  }
  return QVariant();
}

int SqlTableModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);

  return data_list.size();
}

int SqlTableModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);

  return HEADER_DATA::Count;
}

QVariant SqlTableModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= rowCount(index) || index.row() < 0)
    return QVariant();

  if (index.column() >= columnCount(index) || index.column() < 0)
    return QVariant();

  if (role == Qt::DisplayRole) {
    DbRowData row = data_list.at(index.row());
    switch (index.column()) {
      case TEXTEDITOR:
        return row.texteditor_;
      case FILEFORMAT:
        return row.fileformats_;
      case ENCODING:
        return row.encoding_;
      case HASINTELLICENCE:
        return row.hasintellisense_;
      case HASPLAGINS:
        return row.hasplugins_;
      case CANCOMPILE:
        return row.cancompile_;
    }
  }
  return QVariant();
}

bool SqlTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
  Q_UNUSED(index);
  beginInsertRows(QModelIndex(), position, position+rows-1);

  for (int row=0; row < rows; row++) {
    int id = db_->addNewStatement();
    data_list.append(DbRowData(id));
  }

  endInsertRows();
  return true;
}

bool SqlTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
  Q_UNUSED(index);
  beginRemoveRows(QModelIndex(), position, position+rows-1);

  for (int row=0; row < rows; ++row) {
    db_->removeByID( data_list.at(position).id_ );
    data_list.removeAt(position);
  }

  endRemoveRows();
  return true;
}

bool SqlTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (index.row() >= rowCount(index) || index.row() < 0)
    return false;
  if (index.column() >= columnCount(index) || index.column() < 0)
    return false;
  if (index.isValid() && role == Qt::EditRole) {
    int row = index.row();
    DbRowData rowdata = data_list.value(row);

    switch (index.column()) {
      case TEXTEDITOR:
        rowdata.texteditor_= value.toString();
        break;
      case FILEFORMAT:
        rowdata.fileformats_= value.toString();
        break;
      case ENCODING:
        rowdata.encoding_= value.toString();
        break;
      case HASINTELLICENCE:
        rowdata.hasintellisense_= value.toString();
        break;
      case HASPLAGINS:
        rowdata.hasplugins_= value.toString();
        break;
      case CANCOMPILE:
        rowdata.cancompile_ = value.toString();
        break;
      default:
        return false;
    }
    data_list.replace(row, rowdata);
    db_->updateRow(&data_list.at(row));
    emit(dataChanged(index, index));

    return true;
  }
  return false;
}

rows_list SqlTableModel::getList()
{
    return data_list;
}

Qt::ItemFlags SqlTableModel::flags(const QModelIndex &index)const
{
    if(index.isValid())
            return QAbstractTableModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return Qt::NoItemFlags;
}
