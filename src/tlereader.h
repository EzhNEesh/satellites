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
    void fromFile(const QString &filePath);
    void fromURL(const QString &URL);
    ~TLEReader();

private slots:
    void requestFinished(QNetworkReply *reply);
    void connectionError();

signals:
    void dataIsReady(const std::vector<Satellite> &data);
    void errorOcurred(const QString &errorMessage);

private:
    QNetworkAccessManager *networkManager;
    Satellite createSatellite(const QString &name, const QString &row1, const QString &row2);
    QString preprocessRow(QString &row);
};

#endif // TLEREADER_H
