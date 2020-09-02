#ifndef XMLREADER_H
#define XMLREADER_H

#include <QFile>
#include <QDir>
#include <QString>
#include <QXmlStreamReader>
#include <QDebug>
#include <QMap>


class XmlReader
{
public:
  XmlReader();
  bool hasError();
  QMap<QString, QString> readFile(QString filepath);
  QString getLastError();
private:
  bool has_error_ = false;
  QString last_error = "";
};

#endif // XMLREADER_H
