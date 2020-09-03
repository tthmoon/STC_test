#include "dbrowdata.h"

DbRowData::DbRowData(){}

DbRowData::DbRowData(const int id):
  id_{id}
{}

//Класс, Описывающий строку в таблице

DbRowData::DbRowData(
  const int id,
  const QString& texteditor,
  const QString& fileformats,
  const QString& encoding,
  const QString& hasintellisense,
  const QString& hasplugins,
  const QString& cancompile
):
  id_{id},
  texteditor_{texteditor},
  fileformats_{fileformats},
  encoding_{encoding},
  hasintellisense_{hasintellisense},
  hasplugins_{hasplugins},
  cancompile_{cancompile}
{}

