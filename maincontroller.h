#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <QAbstractListModel>
#include <QTemporaryDir>
#include <QUdpSocket>

class VideoData
{
public:
    VideoData(const QString &videoName,const QString &videoUrl, const QString &iconPath);

    QString videoName() const;
    QString videoUrl() const;
    QString iconPath() const;

private:
    QString videoName_;
    QString videoUrl_;
    QString iconPath_;
};

class VideoModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DataRoles{
        VideoNameRole = Qt::UserRole + 1,
        VideoUrlRole ,
        IconPathRole
    };
    explicit VideoModel(QObject *parent = nullptr);
    virtual ~VideoModel();

    static void delay(int msec);

    Q_INVOKABLE void getAllName();
    Q_INVOKABLE void getAllImg();

    Q_INVOKABLE void clear();
    Q_INVOKABLE QString getImgByName(QString name);

    Q_INVOKABLE void playUrl(QString url);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void insert(int index,const VideoData &data);
    void remove(int index);
    void append(const QString &videoName,const QString &videoUrl,const QString  &iconPath);
    int count() const;

signals:
    void imgUpdate();

private:
    QUdpSocket *socket;

protected: // interface QAbstractListModel
    virtual QHash<int, QByteArray> roleNames() const;
    QList<VideoData> dataList_;
    QTemporaryDir m_tempDir;

    //名字与图片路径
    QMap<QString,QString> m_nameImgMap;

public slots:
    void readPendingDatagrams();

};

#endif // FILECONTROLLER_H
