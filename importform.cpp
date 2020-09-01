#include "importform.h"
#include "ui_importform.h"

ImportForm::ImportForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ImportForm)
{
  ui->setupUi(this);
  import_thread_ = new ImportThread();
  connect(import_thread_ , SIGNAL(finished()), import_thread_ , SLOT(deleteLater()));
}

void ImportForm::slotImportStart(QList<QString> file_names){
  ui->progb_progress->setMaximum(file_names.size());
  ui->lv_folders->addItems(file_names);
}

void ImportForm::slotImportFileError(){
  ui->lv_folders->item(ui->progb_progress->value())->setForeground(Qt::red);
  ui->progb_progress->setValue(ui->progb_progress->value()+1);
  ui->lab_cur_folder->setText(ui->lv_folders->item(ui->progb_progress->value())->text());
}

void ImportForm::slotImported(){
  ui->lv_folders->item(ui->progb_progress->value())->setForeground(Qt::blue);
  ui->progb_progress->setValue(ui->progb_progress->value()+1);
  ui->lab_cur_folder->setText(ui->lv_folders->item(ui->progb_progress->value())->text());
}

void ImportForm::slotImportFinished(){
  ui->lab_cur_folder->setText("OK!");
}

void ImportForm::startImporting(){
  ui->progb_progress->setMaximum(0);
  ui->progb_progress->setMinimum(0);
  ui->lv_folders->clear();

  import_thread_->startProcess();

  show();
}

ImportForm::~ImportForm()
{
  qDebug() << "delete";
  import_thread_->quit();
  delete ui;
}

void ImportForm::closeEvent(QCloseEvent *event)
{
  emit signalImportFinished();
  event->accept();
}

void ImportForm::on_pb_exit_clicked()
{
  emit signalImportFinished();
}