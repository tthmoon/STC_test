#include "sqltableform.h"
#include "ui_sqltableform.h"

SqlTableForm::SqlTableForm() :
  ui(new Ui::SqlTableForm)
{
  ui->setupUi(this);

}

void SqlTableForm::setModel(QAbstractTableModel* model)
{
  ui->tbl_sql_content->setModel(model);
  ui->tbl_sql_content->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//  ui->tbl_sql_content->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

SqlTableForm::~SqlTableForm()
{
  delete ui;
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
