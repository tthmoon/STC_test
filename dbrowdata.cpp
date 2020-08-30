#include "dbrowdata.h"

DbRowData::DbRowData(){}

DbRowData::DbRowData(
  const QString& texteditor,
  const QString& fileformats,
  const QString& encoding,
  const QString& hasintellisense,
  const QString& hasplugins,
  const QString& cancompile
):
  texteditor_{texteditor},
  fileformats_{fileformats},
  encoding_{encoding},
  hasintellisense_{hasintellisense},
  hasplugins_{hasplugins},
  cancompile_{cancompile}
{}

