#include "qmllog.h"
#include "easylogging++.h"

QMLLog::QMLLog(QObject *parent) : QObject(parent)
{
}

void QMLLog::qLOG(int type, QString strInfo)
{
    switch(type)
    {
    case 0:
        LOG(INFO)<<"qml "<<strInfo;
        break;
    case 1:
        LOG(WARNING)<<"qml "<<strInfo;
        break;
    case 2:
        LOG(ERROR)<<"qml "<<strInfo;
        break;
    case 3:
        LOG(FATAL)<<"qml "<<strInfo;
     default:
        LOG(DEBUG)<<"qml "<<strInfo;
        break;
    }
}
