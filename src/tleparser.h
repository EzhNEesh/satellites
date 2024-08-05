#ifndef TLEPARSER_H
#define TLEPARSER_H

#include <vector>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "satellite.h"

class TLEParser : public QObject
{
    Q_OBJECT

public:
    explicit TLEParser(QObject *parent = nullptr);
    void fromFile(const QString &filePath);
    void fromURL(const QString &URL);
    void saveToFile(const QString &pathToSave,
                           const int &satellitesCount,
                           const QString &oldestDate,
                           std::map<int, int> groupedByYearSatellites,
                           std::map<int, int> groupedByInclinationSatellites);
    ~TLEParser();

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

#endif // TLEPARSER_H
