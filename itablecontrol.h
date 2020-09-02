#ifndef ITABLECONTROLL_H
#define ITABLECONTROLL_H

#include <QMap>
#include <QString>

class ITableControl
{
public:
  virtual ~ITableControl() = default;
  virtual void addNewStatement(QMap<QString, QString> data) = 0;
};

#endif // ITABLECONTROLL_H
