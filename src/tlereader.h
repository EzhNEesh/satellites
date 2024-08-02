#ifndef TLEREADER_H
#define TLEREADER_H

#include <vector>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "satellite.h"

class TLEReader : public QObject
{
    Q_OBJECT

public:
    explicit TLEReader(QObject *parent = nullptr);
    void fromFile(const QString &);
    void fromURL(const QString &);
    ~TLEReader();

private slots:
    void requestFinished(QNetworkReply *reply);
    void connectionError();

signals:
    void dataIsReady(const std::vector<Satellite> &);
    void errorOcurred(const QString &);

private:
    QNetworkAccessManager *networkManager;
    Satellite createSatellite(const QString &, const QString &, const QString &);
    QString preprocessRow(QString &);
};

#endif // TLEREADER_H
