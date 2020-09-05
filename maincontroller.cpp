#include "maincontroller.h"
#include <windows.h>
#include <winbase.h>
#include <winnls.h>
#include <dbt.h>
#include <QDebug>
#include <QStorageInfo>
#include <QDir>
#include <QDesktopServices>
#include <QIcon>
#include <QUrl>
#include <QProcess>
#include <QtConcurrent>

#include "setting.h"
VideoData::VideoData(const QString &videoName,const QString &videoUrl, const QString &iconPath)
    :videoName_(videoName)
    ,videoUrl_(videoUrl)
    ,iconPath_(iconPath)
{

}

QString VideoData::videoName() const
{
    return videoName_;
}

QString VideoData::videoUrl() const
{
    return videoUrl_;
}

QString VideoData::iconPath() const
{
    return iconPath_;
}


VideoModel::VideoModel(QObject *)
{

}

VideoModel::~VideoModel()
{

}

void VideoModel::delay(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void VideoModel::getAllImg()
{
    QMap<QString,QString> map = Setting::GetInst().map();
    for(int i=0;i<map.size();i++){
        QString name = map.keys().at(i);

        if (m_tempDir.isValid()) {
            QString iconPath = m_tempDir.path()+"/"+name+".png";
            QString url = map.values().at(i);
            QtConcurrent::run([=](){
                QString param = QString("ffmpeg.exe -i %1 -f image2 -ss 0 -vframes 1 -s 350*350 %2 -y").arg(url).arg(iconPath);
                QProcess::execute(param);
                //QProcess process;
                //QProcess::startDetached(param);

                });
            QFile file(iconPath);
            if(file.exists()){
                m_nameImgMap[name]=iconPath;
                qDebug()<<"getAllImg "<<iconPath;
            }
        }
    }
    emit imgUpdate();
}

void VideoModel::getAllName()
{
    QMap<QString,QString> map = Setting::GetInst().map();
    for(int i=0;i<map.size();i++){
        QString name = map.keys().at(i);
        QString url = map.values().at(i);

        if (m_tempDir.isValid()) {
            append(name,url,"");
        }
    }
}


int VideoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return dataList_.count();
}

QVariant VideoModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= dataList_.count()) {
        return QVariant();
    }

    const VideoData &data = dataList_[row];
    switch (role) {
    case VideoNameRole:
        return data.videoName();

    case VideoUrlRole:
        return data.videoUrl();

    case IconPathRole:
        return data.iconPath();

    }

    return QVariant();
}

void VideoModel::clear()
{
    while (dataList_.count()) {
        remove(dataList_.count()-1);
    }
}

QString VideoModel::getImgByName(QString name)
{
    return m_nameImgMap.value(name);
}

void VideoModel::playUrl(QString url)
{
    QtConcurrent::run([=](){
        QString param = QString("ffplay.exe -i %1 -fs").arg(url);
        QProcess::execute(param);

        });
}

void VideoModel::insert(int index, const VideoData &data)
{
    if(index < 0 || index > dataList_.count()) {
        return;
    }

    //防止重复
    for(int i=0;i<dataList_.size();i++){
        if(dataList_.at(i).videoName()==data.videoName()){
            remove(i);
            return;
        }
    }

    emit beginInsertRows(QModelIndex(), index, index);
    dataList_.insert(index, data);
    emit endInsertRows();

}

void VideoModel::remove(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    dataList_.removeAt(index);
    endRemoveRows();
}

void VideoModel::append(const QString &videoName,const QString &videoUrl, const QString &iconPath)
{
    insert(count(), VideoData(videoName,videoUrl,iconPath));
}

int VideoModel::count() const
{
    return rowCount(QModelIndex());
}


//dm : data model
QHash<int, QByteArray> VideoModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[VideoNameRole] = "dmVideoName";
    roles[VideoUrlRole] = "dmVideoUrl";
    roles[IconPathRole] = "dmIconPath";
    return roles;
}
