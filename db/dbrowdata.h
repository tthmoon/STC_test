#ifndef DBROWDATA_H
#define DBROWDATA_H

#include <QString>

class DbRowData
{
public:
  DbRowData();
  DbRowData(const int id);
  DbRowData(const int id, const QString &texteditor, const QString &fileformats, const QString &encoding, const QString &hasintellisense, const QString &hasplugins, const QString &cancompile);
  int id_;
  QString texteditor_ = "";
  QString fileformats_ = "";
  QString encoding_ = "";
  QString hasintellisense_ = "";
  QString hasplugins_ = "";
  QString cancompile_ = "";
};

#endif // DBROWDATA_H
