#include "importform.h"
#include "ui_importform.h"

ImportForm::ImportForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ImportForm)
{
  ui->setupUi(this);
  import_thread_ = new ImportThread();
  connect(import_thread_, SIGNAL(finished()),                        import_thread_, SLOT(deleteLater()), Qt::QueuedConnection);
  connect(import_thread_, SIGNAL(signalImportStart(QStringList)), this,           SLOT(slotImportStart(QStringList)), Qt::QueuedConnection);
  connect(import_thread_, SIGNAL(signalImported()),                   this,           SLOT(slotFileImported()), Qt::QueuedConnection);
  connect(import_thread_, SIGNAL(signalImportFileError(QString)),           this,           SLOT(slotImportFileError(QString)), Qt::QueuedConnection);
  connect(import_thread_, SIGNAL(signalImportFinished()),            this,           SLOT(slotImportFinished()), Qt::QueuedConnection);
}

void ImportForm::slotImportStart(QStringList file_names){
  ui->progb_progress->setValue(0);
  ui->progb_progress->setMaximum(file_names.size());
  ui->lv_folders->addItems(file_names);
}

void ImportForm::slotImportFileError(QString error){
  ui->lv_folders->item(ui->progb_progress->value())->setText(
        ui->lv_folders->item(ui->progb_progress->value())->text()
        + " - " + error
        );
  ui->lv_folders->item(ui->progb_progress->value())->setForeground(Qt::red);
  ui->progb_progress->setValue(ui->progb_progress->value() + 1);
  if (ui->progb_progress->value() != ui->progb_progress->maximum())
    ui->lab_cur_folder->setText(ui->lv_folders->item(ui->progb_progress->value())->text());
}

void ImportForm::slotFileImported(){
  ui->lv_folders->item(ui->progb_progress->value())->setForeground(Qt::blue);
  ui->progb_progress->setValue(ui->progb_progress->value() + 1);
  if (ui->progb_progress->value() != ui->progb_progress->maximum())
    ui->lab_cur_folder->setText(ui->lv_folders->item(ui->progb_progress->value())->text());
}

void ImportForm::slotImportFinished(){
  ui->lab_cur_folder->setText("OK!");
}

void ImportForm::startImporting(QString dir){
  ui->progb_progress->setMaximum(0);
  ui->progb_progress->setMinimum(0);
  ui->lv_folders->clear();

  import_thread_->startProcess(dir);

  show();
}


ImportForm::~ImportForm()
{
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
