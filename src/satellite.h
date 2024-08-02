#ifndef SATELLITE_H
#define SATELLITE_H

#include <QDate>
#include <QString>
#include <map>

class Satellite
{
public:
    explicit Satellite(const QString &_name);
    void parseAndSetFirstRow(const QString &row);
    void parseAndSetSecondRow(const QString &row);
    int getYearLaunch();
    QDate getDataDate();
    float getInclination();
    static QDate getOldestDate(std::vector<Satellite> &satellites);
    static std::map<int, int> groupByDate(std::vector<Satellite> &satellites);
    static std::map<int, int> groupByInclination(std::vector<Satellite> &satellites);

private:
    QString name;
    int number;
    QString classification;
    int yearLaunch;
    int numberInYearLaunch;
    QString partInYearLaunch;
    int yearOfTheEra;
    std::pair<int, int> timeOfEra;
    float inclination;
    bool checkControlSum(const QString &row);
};

#endif // SATELLITE_H
