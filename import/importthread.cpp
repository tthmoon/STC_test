#include <QDebug>
#include "importthread.h"

ImportThread::ImportThread()
{
}

ImportThread::~ImportThread()
{
}



void ImportThread::startProcess(
  QString directory
)
{
  directory_path_ = directory;
  work_is_enable_ = true;
  QThread::start();
}

void ImportThread::quit()
{
  work_is_enable_ = false;
}


void ImportThread::run()
{
  QDir directory(directory_path_);
  QStringList xmls = directory.entryList(QStringList() << "*.xml", QDir::Files);
  emit signalImportStart(xmls);

  XmlReader* xml_reader = new XmlReader();

  foreach(QString filename, xmls) {
    if (!work_is_enable_){
        return;
    }

    QString filepath = QDir::toNativeSeparators(directory_path_ + "\\" + filename);
    QFile xml_file(filepath);
    if (!xml_file.exists()){
      emit signalImportFileError("File does not exist");
      continue;
    }

    QMap<QString, QString> data = xml_reader->readFile(filepath);

    if (xml_reader->hasError()){
      emit signalImportFileError(xml_reader->getLastError());
      continue;
    }

//    tableControl_->addNewStatement(data);
    DBAccessor db;
//    using SqlTableModel::HEADER_DATA;
    DbRowData row(0,
                  data.value("texteditor"),
                  data.value("fileformats"),
                  data.value("encoding"),
                  data.value("hasintellisense"),
                  data.value("hasplugins"),
                  data.value("cancompile")
                  );
    db.addNewStatement(&row);
    emit signalImported();
  }
  emit signalImportFinished();
}
