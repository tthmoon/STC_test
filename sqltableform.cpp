#include "sqltableform.h"
#include "ui_sqltableform.h"

SqlTableForm::SqlTableForm() :
  ui(new Ui::SqlTableForm)
{
  ui->setupUi(this);

  ui->tbl_sql_content->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  ui->tbl_sql_content->setContextMenuPolicy(Qt::CustomContextMenu);

  connect(ui->tbl_sql_content, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));

}

void SqlTableForm::setModel(QAbstractTableModel* model)
{
  ui->tbl_sql_content->setModel(model);
}

SqlTableForm::~SqlTableForm()
{
  delete ui;
  delete import_form_;
}

void SqlTableForm::on_pb_add_new_clicked()
{
  ui->tbl_sql_content->model()->insertRow(
        ui->tbl_sql_content->model()->rowCount(QModelIndex()),
        QModelIndex()
        );
}

void SqlTableForm::on_pb_clear_clicked()
{
  ui->tbl_sql_content->model()->removeRows(
        0,
        ui->tbl_sql_content->model()->rowCount(QModelIndex()),
        QModelIndex()
        );
}

void SqlTableForm::slotImportFinished()
{
  ui->pb_import->setEnabled(true);
  delete import_form_;
}

void SqlTableForm::on_pb_import_clicked()
{
  ui->pb_import->setEnabled(false);
  import_form_ = new ImportForm();
  connect(import_form_, SIGNAL( signalImportFinished()), this, SLOT(slotImportFinished()), Qt::QueuedConnection);
  import_form_->startImporting();
}

void SqlTableForm::slotRemoveRecord(){
  int row = ui->tbl_sql_content->selectionModel()->currentIndex().row();
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


