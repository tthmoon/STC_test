#include "sqltableform.h"
#include "ui_sqltableform.h"

SqlTableForm::SqlTableForm() :
  ui(new Ui::SqlTableForm)
{
  ui->setupUi(this);

//  Обноаление модели таблицы
  updateModel();

  ui->tbl_sql_content->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  ui->tbl_sql_content->setContextMenuPolicy(Qt::CustomContextMenu);

//  Соединение сигнала на вызов контекстного меню
  connect(ui->tbl_sql_content, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));

}

//  Обноаление модели таблицы
void SqlTableForm::updateModel()
{
  ui->tbl_sql_content->setModel(new SqlTableModel());
}

SqlTableForm::~SqlTableForm()
{
  qDebug() << "aaaa";
  delete ui;
  delete import_form_;
}


// Вставка новой строки
void SqlTableForm::on_pb_add_new_clicked()
{
  ui->tbl_sql_content->model()->insertRow(
        ui->tbl_sql_content->model()->rowCount(QModelIndex()),
        QModelIndex()
        );
}

//Полная очистка таблицы
void SqlTableForm::on_pb_clear_clicked()
{
  ui->tbl_sql_content->model()->removeRows(
        0,
        ui->tbl_sql_content->model()->rowCount(QModelIndex()),
        QModelIndex()
        );
}

//Слот окончания импорта, вызов обновления модели таблицы, удаление формы импорта
void SqlTableForm::slotImportFinished()
{
  updateModel();
  ui->pb_import->setEnabled(true);
  delete import_form_;
}

void SqlTableForm::on_pb_import_clicked()
{
//  Вызов диалога для выбора директории + проверка на корректность
  QString dir = QFileDialog::getExistingDirectory(
        this,
        "Choose folder with xml files",
        QDir::currentPath(),
        QFileDialog::DontResolveSymlinks);

  QDir pathDir(dir);
  if ( pathDir.exists() && dir != NULL ){
    ui->pb_import->setEnabled(false);
//    Создание формы для обработки файлов + связывание с уничтножающим сигналом
    import_form_ = new ImportForm();
    connect(import_form_, SIGNAL( signalImportFinished()), this, SLOT(slotImportFinished()), Qt::QueuedConnection);
    import_form_->startImporting(dir);
   }
}

//Удаление строки через контекстного меню
void SqlTableForm::slotRemoveRecord(){
  int row = ui->tbl_sql_content->selectionModel()->currentIndex().row();
  if (row > -1)
    ui->tbl_sql_content->model()->removeRow(row);
}

void SqlTableForm::slotCustomMenuRequested(QPoint pos)
{
  QMenu * menu = new QMenu(this);
  QAction * deleteDevice = new QAction("Delete", this);
  connect(deleteDevice, SIGNAL(triggered()), this, SLOT(slotRemoveRecord()));
  menu->addAction(deleteDevice);
  menu->popup(ui->tbl_sql_content->viewport()->mapToGlobal(pos));
}


