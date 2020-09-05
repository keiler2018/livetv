#ifndef QMLLOG_H
#define QMLLOG_H

#include <QObject>

class QMLLog : public QObject
{
    Q_OBJECT
public:
    explicit QMLLog(QObject *parent = nullptr);
    Q_INVOKABLE void qLOG(int type, QString strInfo);

signals:

public slots:
};

#endif // QMLLOG_H
