#include "xmlreader.h"

XmlReader::XmlReader(){
}

//Класс для чтение xml
//!!! Работает только с xml файлами для данного ТЗ
QMap<QString, QString> XmlReader::readFile(QString filepath){
  has_error_ = false;

  QFile* xmlFile = new QFile(filepath);

  QXmlStreamReader* xml_reader = new QXmlStreamReader(xmlFile);

  QMap<QString, QString> file_entry;
  file_entry.insert("texteditor",       NULL);
  file_entry.insert("fileformats",      NULL);
  file_entry.insert("encoding",         NULL);
  file_entry.insert("hasintellisense",  NULL);
  file_entry.insert("hasplugins",       NULL);
  file_entry.insert("cancompile",       NULL);

  if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
    last_error = "Load XML File Problem";
    return file_entry;
  }

  while(!xml_reader->atEnd() && !xml_reader->hasError()) {
    QXmlStreamReader::TokenType token = xml_reader->readNext();
    if (token == QXmlStreamReader::StartDocument) {
      continue;
    }
    if (token == QXmlStreamReader::StartElement) {

      if (xml_reader->name() == "root") {
        continue;
      }
      if (
          file_entry.keys().contains(xml_reader->name().toString())
          && file_entry.value(xml_reader->name().toString()) == NULL
          )
      {
        file_entry.insert(xml_reader->name().toString(), xml_reader->readElementText());
      }
    }
  }
  QMapIterator<QString, QString> i(file_entry);
  while (i.hasNext()) {
    i.next();
    if (i.value()==NULL){
      has_error_ = true;
      last_error = QString("xml Parse Error ") +  QString("not all tags are present") ;
      return file_entry ;
    }
  }

  if (xml_reader->hasError()) {
    has_error_ = true;
    last_error =  "xml Parse Error " + xml_reader->errorString();
    return file_entry;
  }

  xml_reader->clear();
  xmlFile->close();

  return file_entry;
}

//Возвращении флага о успешности обработки
bool XmlReader::hasError(){
  return has_error_;
}

//Возвращение текста послейдней ошибки
QString XmlReader::getLastError(){
  return last_error;
}
