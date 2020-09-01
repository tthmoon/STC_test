#ifndef XMLREADER_H
#define XMLREADER_H

#include <QFile>
#include <QDir>
#include <QString>
#include <QXmlStreamReader>
#include <QDebug>

class XmlReader
{
public:
  XmlReader();
  void readFile(QString filepath);
};

#endif // XMLREADER_H
