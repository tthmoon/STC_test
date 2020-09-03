#include <QDebug>
#include "importthread.h"

ImportThread::ImportThread()
{
}

ImportThread::~ImportThread()
{
}

//Запуск потока
void ImportThread::startProcess(
  QString directory
)
{
  directory_path_ = directory;
  work_is_enable_ = true;
  QThread::start();
}

//Установка переменной для остановки процессов внутри потока
void ImportThread::quit()
{
  work_is_enable_ = false;
}


void ImportThread::run()
{
  QDir directory(directory_path_);
  QStringList xmls = directory.entryList(QStringList() << "*.xml", QDir::Files);
//  Сообщение о начале, соообщает список обрабатываемых файлов
  emit signalImportStart(xmls);

  XmlReader* xml_reader = new XmlReader();
//  Перебор файлов
  foreach(QString filename, xmls) {
//    Проверка на внешнюю остановку процеса
    if (!work_is_enable_){
        return;
    }

    QString filepath = QDir::toNativeSeparators(directory_path_ + "\\" + filename);
    QFile xml_file(filepath);
    if (!xml_file.exists()){
//      Сигнал об отсутствии файла
      emit signalImportFileError("File does not exist");
      continue;
    }

    QMap<QString, QString> data = xml_reader->readFile(filepath);

    if (xml_reader->hasError()){
//      Сигнал об ошибке чтение, с текстом ошибки
      emit signalImportFileError(xml_reader->getLastError());
      continue;
    }
//Запись в БД новых данных
    DBAccessor* db = new DBAccessor();
    DbRowData row(0,
                  data.value("texteditor"),
                  data.value("fileformats"),
                  data.value("encoding"),
                  data.value("hasintellisense"),
                  data.value("hasplugins"),
                  data.value("cancompile")
                  );
    db->addNewStatement(&row);
    delete db;
//    Сигнал об успешной обработке файла
    emit signalImported();
  }
//  Сигнал о завершении
  emit signalImportFinished();
}
