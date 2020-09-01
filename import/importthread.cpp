#include <QDebug>
#include "importthread.h"

ImportThread::ImportThread()
{
}

ImportThread::~ImportThread()
{
}



void ImportThread::startProcess(
)
{
  work_is_enable_ = true;
  QThread::start();
}

void ImportThread::quit()
{
  work_is_enable_ = false;
}


void ImportThread::run()
{

}
