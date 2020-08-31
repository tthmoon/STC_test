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
