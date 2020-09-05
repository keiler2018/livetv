#include "setting.h"
#include <iostream>
#include <fstream>
#include <qDebug>
#include <QCoreApplication>
#include "../../third_party/json/json.h"

using namespace std;
Setting::Setting(QObject *parent) : QObject(parent)
{
    readSettings();
}

QMap<QString, QString> Setting::map() const
{
    return m_map;
}

void Setting::readSettings()
{
    Json::Reader reader;
    Json::Value root;

    QString jsonPath =QCoreApplication::applicationDirPath()+"/tvlist.json" ;
    ifstream in(jsonPath.toStdString().c_str(), ios::binary);
    if(!in.is_open())
    {
        qDebug() << "Error opening file\n";
        return;
    }

    if (reader.parse(in, root))
    {
        const Json::Value arrayObj = root["list"];
        for (unsigned int i = 0; i < arrayObj.size(); i++)
        {
            string name = arrayObj[i]["name"].asString();
            string url = arrayObj[i]["url"].asString();
            m_map.insert(QString::fromStdString(name),QString::fromStdString(url));
        }
        qDebug() << "Reading Complete!" << endl;
    }
    else
    {
        qDebug() << "parse error\n" << endl;
    }

    in.close();
}
