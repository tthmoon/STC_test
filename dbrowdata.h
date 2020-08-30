#ifndef DBROWDATA_H
#define DBROWDATA_H

#include <QString>

class DbRowData
{
public:
  DbRowData();
  DbRowData(const QString &texteditor, const QString &fileformats, const QString &encoding, const QString &hasintellisense, const QString &hasplugins, const QString &cancompile);
  QString texteditor_ = "";
  QString fileformats_ = "";
  QString encoding_ = "";
  QString hasintellisense_ = "";
  QString hasplugins_ = "";
  QString cancompile_ = "";
};

#endif // DBROWDATA_H
