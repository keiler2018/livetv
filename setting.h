#ifndef SETTING_H
#define SETTING_H
#include <QObject>
#include <QMap>
class Setting : public QObject
{
    Q_OBJECT
public:
    explicit Setting(QObject *parent = nullptr);

    static Setting& GetInst() {
        static Setting inst;
        return inst;
    }

    QMap<QString, QString> map() const;

signals:

public slots:

private:
    QMap<QString,QString> m_map;

    void readSettings();
};

#endif // SETTING_H
