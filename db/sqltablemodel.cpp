#include "sqltablemodel.h"

SqlTableModel::SqlTableModel()
{
  updateData();
}

void SqlTableModel::updateData(){
  DBAccessor* db = new DBAccessor();
  data_list = db->requestForAll();
  db->deleteLater();
  foreach (DbRowData t, data_list) {
     qDebug() << t.texteditor_;
    }
  emit(dataChanged(index(0, 0), index(4, columnCount())));
}


void SqlTableModel::slotSetData(rows_list dl){
  data_list = dl;
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

SqlTableModel::HEADER_DATA SqlTableModel::getEnumByString(QString edata){

  if (edata == "texteditor")
    return TEXTEDITOR;
  if (edata == "fileformats")
    return FILEFORMAT;
  if (edata == "encoding")
    return ENCODING;
  if (edata == "hasintellisense")
    return HASINTELLICENCE;
  if (edata == "hasplugins")
    return HASPLAGINS;
  if (edata == "cancompile")
    return CANCOMPILE;
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

//  qDebug() << "bbbb";
  if (!index.isValid())
    return QVariant();

  if (index.row() >= rowCount(index) || index.row() < 0)
    return QVariant();

  if (index.column() >= columnCount(index) || index.column() < 0)
    return QVariant();
  qDebug() << "bbbb";
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
//  beginInsertRows(QModelIndex(), position, position+rows-1);/
//  endInsertRows();
  for (int row=0; row < rows; row++) {
    QThread* thread = new QThread();
    DBAccessor* db = new DBAccessor();
    db->moveToThread(thread);
    connect(thread, SIGNAL(started()),                    db,         SLOT(addNewStatement()));
    connect(db,     SIGNAL(signal_addNewStatement(int)),  this,       SLOT(appendNewRow(int)), Qt::ConnectionType::QueuedConnection);
    connect(db,     SIGNAL(signal_addNewStatement(int)),  db,         SLOT(deleteLater()), Qt::ConnectionType::QueuedConnection);
    connect(db,     SIGNAL(signal_addNewStatement(int)),  thread,     SLOT(quit()), Qt::ConnectionType::QueuedConnection);
    connect(thread, SIGNAL(finished()),                   thread,     SLOT(deleteLater()), Qt::ConnectionType::QueuedConnection);
    thread->start();
    delay_--;
    data_list.append(DbRowData(data_list.size()));
  }
//   qDebug() << "a";
//  endInsertRows();
  return true;
}

void SqlTableModel::appendNewRow(int id){
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  data_list.append(DbRowData(id));
  endInsertRows();
}

bool SqlTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
  Q_UNUSED(index);

  for (int row=position; row < position+rows; ++row) {

    QThread* thread = new QThread();
    DBAccessor* db = new DBAccessor();
    db->prepareRowId(data_list.at(row).id_);
    db->moveToThread(thread);
    connect(thread, SIGNAL(started()),                    db,         SLOT(removeByID()));
    connect(db,     SIGNAL(signal_removeByID(int)),       this,       SLOT(slotRemoveById(int)), Qt::ConnectionType::QueuedConnection);
    connect(db,     SIGNAL(signal_removeByID(int)),       db,         SLOT(deleteLater()), Qt::ConnectionType::QueuedConnection);
    connect(db,     SIGNAL(signal_removeByID(int)),       thread,     SLOT(quit()), Qt::ConnectionType::QueuedConnection);
    connect(thread, SIGNAL(finished()),                   thread,     SLOT(deleteLater()), Qt::ConnectionType::QueuedConnection);
    thread->start();
  }
  return true;
}

void SqlTableModel::slotRemoveById(int id){
  for (int i = 0; i<data_list.size() ;i++){
    if (data_list[i].id_ == id){
      beginRemoveRows(QModelIndex(), i, i);
      data_list.removeAt(i);
      endRemoveRows();
      return;
    }
  }
}

bool SqlTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  qDebug() << value.toString() << index.row() << rowCount(index) <<index.row() ;
  if (index.row() >= rowCount(index) || index.row() < 0)
    return false;
//  qDebug() << 'value.toString()';
  if (index.column() >= columnCount(index) || index.column() < 0)
    return false;
//  qDebug() << 'value.toString()';
  if (role == Qt::EditRole) {
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

    QThread* thread = new QThread();
    DBAccessor* db = new DBAccessor();
    db->prepareRow(&data_list.at(row));
    db->moveToThread(thread);
    connect(thread, SIGNAL(started()),                db,         SLOT(updateRow()));
    connect(db,     SIGNAL(signal_updateRow()),       db,         SLOT(deleteLater()), Qt::ConnectionType::QueuedConnection);
    connect(db,     SIGNAL(signal_updateRow()),       thread,     SLOT(quit()), Qt::ConnectionType::QueuedConnection);
    connect(thread, SIGNAL(finished()),               thread,     SLOT(deleteLater()), Qt::ConnectionType::QueuedConnection);
    thread->start();

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
