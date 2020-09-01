#include "xmlreader.h"

XmlReader::XmlReader(){
}

void XmlReader::readFile(QString filepath){
  QFile* xmlFile = new QFile(filepath);
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() <<"Load XML File Problem";
      return;
    }
  QXmlStreamReader* xmlReader = new QXmlStreamReader(xmlFile);


  //Parse the XML until we reach end of it
  while(!xmlReader->atEnd() && !xmlReader->hasError()) {
    // Read next element
    QXmlStreamReader::TokenType token = xmlReader->readNext();
    //If token is just StartDocument - go to next
    if (token == QXmlStreamReader::StartDocument) {
      continue;
    }
    //If token is StartElement - read it
    if (token == QXmlStreamReader::StartElement) {

      if (xmlReader->name() == "root") {
        continue;
      }
//      Доделать заполение мапы, проверку единичного появляения тегов мапы и вывод
      if (xmlReader->name() == "id") {
        qDebug() << xmlReader->readElementText();
      }
    }
  }

  if(xmlReader->hasError()) {
    qDebug() << "xmlFile.xml Parse Error" << xmlReader->errorString();
    return;
  }

  //close reader and flush file
  xmlReader->clear();
  xmlFile->close();
}
