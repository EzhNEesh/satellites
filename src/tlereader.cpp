#include "tlereader.h"

TLEReader::TLEReader(QObject *parent) : QObject(parent) {
    networkManager = new QNetworkAccessManager();
}

void TLEReader::fromFile(const QString &filePath) {
    std::ifstream file(filePath.toStdString());
    std::vector <Satellite> satellites;
    if (file.is_open()) {
        std::string name;
        while (getline(file, name)) {
            std::string row1;
            getline(file, row1);
            std::string row2;
            getline(file, row2);

            try {
                Satellite satellite = createSatellite(
                                QString::fromStdString(name),
                                QString::fromStdString(row1),
                                QString::fromStdString(row2)
                            );
                satellites.push_back(satellite);
            } catch (std::out_of_range &excp) {
                emit errorOcurred(QString::fromStdString(excp.what()));
                satellites.clear();
                break;
            } catch (std::logic_error &excp) {
                emit errorOcurred(QString::fromStdString(excp.what()));
                satellites.clear();
                break;
            }
        }
        file.close();
        if (satellites.size() != 0) {
            emit dataIsReady(satellites);
        }
    } else {
        emit errorOcurred(filePath + ": File not exist");
    }
}

void TLEReader::fromURL(const QString &URL) {
    connect(networkManager, &QNetworkAccessManager::finished, this, &TLEReader::requestFinished);
    QNetworkReply* reply = networkManager->get(QNetworkRequest(QUrl(URL)));
    connect(reply, &QNetworkReply::errorOccurred, this, &TLEReader::connectionError);
}

void TLEReader::requestFinished(QNetworkReply *reply) {
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (statusCode.isValid()) {
        QString replyHtml = reply->readAll();
        std::vector<Satellite> satellites;
        QStringList rowList = replyHtml.split('\n');
        for (int i = 0; i < rowList.size() - 2; i+=3) {
            try {
                Satellite satellite = createSatellite(
                    preprocessRow(rowList[i]),
                    preprocessRow(rowList[i+1]),
                    preprocessRow(rowList[i+2])
                    );
                satellites.push_back(satellite);
            } catch (std::out_of_range &excp) {
                emit errorOcurred(QString::fromStdString(excp.what()));
                satellites.clear();
                break;
            } catch (std::logic_error &excp) {
                emit errorOcurred(QString::fromStdString(excp.what()));
                satellites.clear();
                break;
            }
        }
        if (satellites.size() != 0) {
            emit dataIsReady(satellites);
        } else if (replyHtml.size() != 0 && replyHtml.sliced(0, 13) == "Invalid query") { // ?При многократном обращении к URL
            emit errorOcurred("Invalid query"); // возвращает пустую строку, но при этом повторно берет откуда-то данные
        }
    }
}

void TLEReader::connectionError() {
    emit errorOcurred("Connection error");
}

Satellite TLEReader::createSatellite(const QString &name, const QString &row1, const QString &row2) {
    Satellite satellite{name};
    satellite.parseAndSetFirstRow(row1);
    satellite.parseAndSetSecondRow(row2);

    return satellite;
}

QString TLEReader::preprocessRow(QString &row) {
    return row.replace("\r", "");
}

TLEReader::~TLEReader(){}
