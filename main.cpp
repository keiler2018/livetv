﻿#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "maincontroller.h"
int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);

    QGuiApplication app(argc, argv);
    qmlRegisterType<VideoModel>("VideoModel",1,0,"VideoModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
